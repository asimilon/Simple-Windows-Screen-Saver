#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class ConfigComponent : public juce::Component
{
public:
    ConfigComponent() { setSize(600, 400); }

    void paint(juce::Graphics& g) override { g.fillAll(juce::Colours::grey); }
};

class ConfigWindow : public juce::DocumentWindow
{
public:
    ConfigWindow(juce::String name)
        : juce::DocumentWindow(
              name,
              juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
              juce::DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new ConfigComponent(), true);
        setVisible(true);
        centreWithSize(getWidth(), getHeight());
    }

    void closeButtonPressed() override
    {
        // This is called when the user tries to close this window. Here, we'll just
        // ask the app to quit when this happens, but you can change this to do
        // whatever you need.
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConfigWindow)
};