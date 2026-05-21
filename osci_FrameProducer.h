#pragma once

#include <juce_core/juce_core.h>

#include "osci_FrameConsumer.h"
#include "osci_FrameSource.h"

class FrameProducer : public juce::Thread {
public:
	FrameProducer(FrameConsumer&, std::shared_ptr<FrameSource>);
	~FrameProducer() override;

	void run() override;
private:
	juce::SpinLock lock;
	FrameConsumer& frameConsumer;
	std::shared_ptr<FrameSource> frameSource;
};
