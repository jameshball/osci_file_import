#pragma once

#include <juce_core/juce_core.h>
#include "../gpla/osci_LineArtParser.h"

#include <functional>
#include <memory>
#include <vector>

class ObjectServer : public juce::Thread {
public:
    struct Callbacks {
        std::function<int()> getPort;
        std::function<void(bool)> setRendering;
        std::function<void(std::vector<std::unique_ptr<osci::Shape>>&, bool)> addFrame;
    };

    ObjectServer();
    explicit ObjectServer(Callbacks callbacks);
    ~ObjectServer() override;

    void run() override;
    void setCallbacks(Callbacks callbacks);
    void reload();

private:
    int getPort();
    void setRendering(bool enabled);
    void addFrame(std::vector<std::unique_ptr<osci::Shape>>& frame, bool force);

    juce::SpinLock callbacksLock;
    Callbacks callbacks;

    int port = 51677;
    juce::StreamingSocket socket;
};
