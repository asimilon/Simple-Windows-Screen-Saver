# Simple Windows ScreenSaver

I wanted a simple screen saver that will show a slideshow of pictures with a "Ken Burns" style effect, but couldn't find anything suitable and without a price tag attached.  In those situations you just need to make it yourself!

## Building

1. Clone the repository
2. Run `cmake -B build`
3. Run `cmake --build build`
4. Find `ScreenSaver.scr` in the `build` folder, put it somewhere safe and then right click and `Install`

## Usage

1. Download [ScreenSaver.scr](https://github.com/asimilon/ScreenSaver/blob/main/Binary/ScreenSaver.scr) from this repository, put it somewhere safe and then right click and `Install`.
2. Click `Settings...` from the screen saver settings dialogue.
3. Choose a folder of pictures to be used as the slideshow, and pick how long you want each image to show for.

I would suggest downloading some [excellent images](https://conspiracy.hu/files/screenshots/empires/8k_cranked/) from Conspiracy's website if you need some inspiration.

## Contributing

Any improvements will be happily merged if I also find them useful, or just fork and have fun.

If anyone knows how to make JUCE play nicely with the "real" screensaver preview in Windows, please let me know!