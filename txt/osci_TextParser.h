#pragma once

#include <juce_graphics/juce_graphics.h>
#include <osci_render_core/osci_render_core.h>

class TextParser {
public:
	TextParser(juce::String text, juce::Font& font);
	~TextParser();

	std::vector<std::unique_ptr<osci::Shape>> draw();
    
private:
    void parse(juce::String text);
    juce::AttributedString parseFormattedText(const juce::String& text, juce::Font font);
    void processFormattedTextBody(const juce::String& text, juce::AttributedString& result, juce::Font font);
    
    juce::Font& font;
	std::vector<std::unique_ptr<osci::Shape>> shapes;
    juce::Font currentFont;
    juce::String text;
    juce::AttributedString attributedString;
};
