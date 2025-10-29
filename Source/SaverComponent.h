#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "Config.h"

class SaverComponent
    : public juce::Component
    , private juce::Timer
{
public:
    explicit SaverComponent(bool isPreview, std::function<void()> onExitFn)
        : onExit(std::move(onExitFn))
        , preview(isPreview)
    {
        reset();

        setWantsKeyboardFocus(true);
        setMouseClickGrabsKeyboardFocus(true);
        if (!preview)
            setMouseCursor(juce::MouseCursor::NoCursor);
        startTimerHz(60);
        lastMousePos = juce::Desktop::getInstance().getMainMouseSource().getScreenPosition();
    }

    void reset()
    {
        currentImageIndex = -1;
        imagePaths.clear();
        auto settingsFile = Config::getSettingsFile();
        auto imagesPath = juce::File(settingsFile.loadFileAsString());
        if (imagesPath.exists())
        {
            imagePaths = imagesPath.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, "*.jpg");
            currentImageIndex = random.nextInt(imagePaths.size());
            DBG(imagePaths[currentImageIndex].getFullPathName());
        }
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
    }

private:
    juce::Point<float> lastMousePos;
    std::function<void()> onExit;
    bool preview;
    juce::Array<juce::File> imagePaths;
    int currentImageIndex = -1;

    juce::Random random;

    void timerCallback() override
    {
        auto mousePos = juce::Desktop::getInstance().getMainMouseSource().getScreenPosition();
        if (!preview && mousePos.getDistanceFrom(lastMousePos) > 5.0f)
            triggerExit();

        if (currentImageIndex != -1)
        {
        }

        repaint();
    }

    void mouseDown(const juce::MouseEvent&) override
    {
        if (!preview)
            triggerExit();
    }

    bool keyPressed(const juce::KeyPress&) override
    {
        if (!preview)
            triggerExit();
        return !preview;
    }

    void triggerExit()
    {
        if (onExit)
            onExit();
    }
};