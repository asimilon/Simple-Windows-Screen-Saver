#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "SaverComponent.h"
#include "Config.h"

class ConfigComponent : public juce::Component
{
public:
    ConfigComponent()
    {
        auto pathSettingFile = Config::getSettingsFile();
        if (pathSettingFile.existsAsFile())
            pathLabel.setText(pathSettingFile.loadFileAsString(), juce::dontSendNotification);
        else
            pathLabel.setText("<choose images folder>", juce::dontSendNotification);

        addAndMakeVisible(imagesLabel);
        imagesLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);

        addAndMakeVisible(pathLabel);
        pathLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);

        addAndMakeVisible(setPathButton);
        setPathButton.onClick = [this]
        {
            filechooser = std::make_unique<juce::FileChooser>(
                "Choose images folder",
                juce::File::getSpecialLocation(juce::File::SpecialLocationType::userPicturesDirectory));
            filechooser->launchAsync(juce::FileBrowserComponent::FileChooserFlags::canSelectDirectories,
                                     [this](const juce::FileChooser& fc)
                                     {
                                         if (fc.getResult().exists())
                                         {
                                             auto pathSettingFile = Config::getSettingsFile();
                                             pathSettingFile.replaceWithText(fc.getResult().getFullPathName());
                                             pathLabel.setText(fc.getResult().getFullPathName(), juce::dontSendNotification);
                                             configPreview.reset();
                                         }
                                     });
        };

        addAndMakeVisible(previewButton);

        addAndMakeVisible(configPreview);

        setSize(600, 400);
    }

    void resized() override
    {
        auto bounds = getBounds().reduced(20);

        auto imagesBounds = bounds.removeFromTop(30);
        imagesLabel.setBounds(imagesBounds);

        bounds.removeFromTop(5);

        auto pathBounds = bounds.removeFromTop(30);

        setPathButton.setBounds(pathBounds.removeFromLeft(100));
        pathBounds.removeFromLeft(20);
        pathLabel.setBounds(pathBounds);

        bounds.removeFromTop(5);

        previewButton.setBounds(bounds.removeFromTop(30).removeFromLeft(100));

        auto previewBounds = bounds.reduced(20);

        constexpr auto ratio = 16.f / 9.f;

        configPreview.setBounds(
            previewBounds.withSizeKeepingCentre(static_cast<int>(static_cast<float>(previewBounds.getHeight()) * ratio),
                                                previewBounds.getHeight()));
    }

private:
    juce::Label imagesLabel { "images", "Images to use:" };
    juce::Label pathLabel;
    juce::TextButton setPathButton { "Choose" };
    juce::TextButton previewButton { "Preview" };
    SaverComponent configPreview { true, [] { } };

    std::unique_ptr<juce::FileChooser> filechooser;
};

class ConfigWindow : public juce::DocumentWindow
{
public:
    ConfigWindow(juce::String name)
        : juce::DocumentWindow(name, juce::Colours::grey, juce::DocumentWindow::allButtons)
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