#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <osci_render_core/osci_render_core.h>

namespace osci {
// How deeply an XML document's elements nest, found without recursion:
// JUCE reads XML recursively, and thousands of nested elements overflow
// the stack.
int xmlNestingDepth(const juce::String& xml);
}

class SvgParser {
public:
	// `reportErrors`: when it can't be read, say so in an alert and draw a
	// cross in its place. Otherwise loaded() says, and it draws nothing.
	SvgParser(juce::String svgFile, bool reportErrors = true);
	~SvgParser();

	bool loaded() const { return ok; }
	// Whether JUCE can read it safely: it reads an SVG recursively, and
	// thousands of nested elements overflow the stack.
	static bool readable(const juce::String& svg);

	static void pathToShapes(juce::Path& path, std::vector<std::unique_ptr<osci::Shape>>& shapes, bool normalise = false);

	std::vector<std::unique_ptr<osci::Shape>> draw();
private:
	
	std::vector<std::unique_ptr<osci::Shape>> shapes;
	bool ok = false;
};
