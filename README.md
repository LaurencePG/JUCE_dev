JUCE_dev
========

VST development in C++ using the JUCE library

##Installation Trouble Shooting
-Make sure you have Xcode (I use 5.1.1).
-Launch to Introjucer in JUCE/extras/introjucer/ (if that fails, rebuild it).
-Try to build vst demo at JUCE/extras/audio plugin demo/
-If you get a rez error 3, here's some things that might help:
  -Core Audio Utility Classes:
    -[1.1](https://developer.apple.com/library/ios/samplecode/CoreAudioUtilityClasses/Introduction/Intro.html)
     or [Older?](https://github.com/thehtb/AppleCoreAudioUtilityClasses)
    -Put a copy of the CoreAudio folder in Xcode.app/Contents/Developer/ and .../Developer/Extras
  -AUResource.h
    - Duplicate and rename juce_AUResource.h
