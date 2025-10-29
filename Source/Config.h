#pragma once

namespace Config
{
    static juce::File getSettingsFile()
    {
        auto pathSettingFolder = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory)
                                     .getChildFile("ScreenSaver");
        if (!pathSettingFolder.exists())
            pathSettingFolder.createDirectory();
        return pathSettingFolder.getChildFile("images.path");
    }
}