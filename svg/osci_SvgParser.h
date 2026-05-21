#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <osci_render_core/osci_render_core.h>

class SvgParser {
public:
	SvgParser(juce::String svgFile);
	~SvgParser();

	static void pathToShapes(juce::Path& path, std::vector<std::unique_ptr<osci::Shape>>& shapes, bool normalise = false);

	std::vector<std::unique_ptr<osci::Shape>> draw();
private:
	
	std::vector<std::unique_ptr<osci::Shape>> shapes;
};
