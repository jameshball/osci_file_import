#include "osci_ObjectServer.h"

ObjectServer::ObjectServer() : juce::Thread("Object Server") {}

ObjectServer::ObjectServer(Callbacks callbacks) : ObjectServer() {
    setCallbacks(std::move(callbacks));
}

ObjectServer::~ObjectServer() {
    socket.close();
    stopThread(-1);
}

void ObjectServer::setCallbacks(Callbacks newCallbacks) {
    {
        juce::SpinLock::ScopedLockType lock(callbacksLock);
        callbacks = std::move(newCallbacks);
    }
    reload();
}

void ObjectServer::reload() {
    socket.close();
    stopThread(-1);
    setRendering(false);
    startThread();
}

int ObjectServer::getPort() {
    std::function<int()> callback;
    {
        juce::SpinLock::ScopedLockType lock(callbacksLock);
        callback = callbacks.getPort;
    }
    return callback ? callback() : 51677;
}

void ObjectServer::setRendering(bool enabled) {
    std::function<void(bool)> callback;
    {
        juce::SpinLock::ScopedLockType lock(callbacksLock);
        callback = callbacks.setRendering;
    }
    if (callback) {
        callback(enabled);
    }
}

void ObjectServer::addFrame(std::vector<std::unique_ptr<osci::Shape>>& frame, bool force) {
    std::function<void(std::vector<std::unique_ptr<osci::Shape>>&, bool)> callback;
    {
        juce::SpinLock::ScopedLockType lock(callbacksLock);
        callback = callbacks.addFrame;
    }
    if (callback) {
        callback(frame, force);
    }
}

bool ObjectServer::processMessage(const char* data, int size) {
    const auto message = juce::String::fromUTF8(data, size).trimEnd();
    if (message == "CLOSE") {
        return false;
    }
    if (message.isEmpty()) {
        return true;
    }

    std::vector<osci::Line> lines;
    if (message.startsWith("R1BMQSAg")) {
        juce::MemoryOutputStream binary;
        if (!juce::Base64::convertFromBase64(binary, message) || binary.getDataSize() < 8) {
            return true;
        }
        int ignoredFrameRate = 0;
        auto frames = LineArtParser::parseBinaryFrames(static_cast<const char*>(binary.getData()),
                                                      static_cast<int>(binary.getDataSize()), ignoredFrameRate);
        if (frames.empty()) {
            return true;
        }
        lines = std::move(frames.front());
    } else {
        const auto json = juce::JSON::parse(message);
        const auto objects = json.getProperty("objects", juce::var());
        if (!objects.isArray()) {
            return true;
        }
        // The shared geometry parser expects arrays and a complete transform matrix.
        for (const auto& object : *objects.getArray()) {
            const auto vertices = object.getProperty("vertices", juce::var());
            const auto matrix = object.getProperty("matrix", juce::var());
            if (!vertices.isArray() || !matrix.isArray() || matrix.size() != 16) {
                return true;
            }
            for (const auto& stroke : *vertices.getArray()) {
                if (!stroke.isArray() || stroke.size() == 0) {
                    return true;
                }
            }
        }
        lines = LineArtParser::generateFrame(*objects.getArray(), json.getProperty("focalLength", 1));
    }
    std::vector<std::unique_ptr<osci::Shape>> frame;
    frame.reserve(lines.size());
    for (const auto& line : lines) {
        frame.push_back(std::make_unique<osci::Line>(line.x1, line.y1, line.x2, line.y2));
    }
    addFrame(frame, false);
    return true;
}

void ObjectServer::run() {
    if (!socket.createListener(getPort(), "127.0.0.1")) {
        return;
    }
    constexpr int maxMessageBytes = 10 * 1024 * 1024;
    std::unique_ptr<char[]> message { new char[maxMessageBytes] };
    while (!threadShouldExit()) {
        const int ready = socket.waitUntilReady(true, 200);
        if (ready < 0) {
            break;
        }
        if (ready == 0) {
            continue;
        }
        std::unique_ptr<juce::StreamingSocket> connection(socket.waitForNextConnection());
        if (connection == nullptr || threadShouldExit()) {
            continue;
        }
        setRendering(true);
        int messageSize = 0;
        while (!threadShouldExit() && connection->isConnected()) {
            const int readable = connection->waitUntilReady(true, 200);
            if (readable < 0) {
                break;
            }
            if (readable == 0) {
                continue;
            }
            char buffer[4096];
            const int bytesRead = connection->read(buffer, sizeof(buffer), false);
            if (bytesRead <= 0) {
                break;
            }
            for (int i = 0; i < bytesRead && !threadShouldExit(); ++i) {
                if (buffer[i] == '\n') {
                    if (!processMessage(message.get(), messageSize)) {
                        connection->close();
                        break;
                    }
                    messageSize = 0;
                } else if (messageSize == maxMessageBytes || buffer[i] == '\0') {
                    connection->close();
                    break;
                } else {
                    message[messageSize++] = buffer[i];
                }
            }
        }
        connection->close();
        // reload clears the source after joining; destruction must not issue callbacks.
        if (!threadShouldExit()) {
            setRendering(false);
        }
    }
}
