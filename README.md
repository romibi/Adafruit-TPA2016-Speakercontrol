# Adafruit-TPA2016-Speakercontrol
A small project to control the Adafruit AMP from Raspberry Pi terminal. Used in my Super Game Pi

compile using compile.sh

(I know something like a makefile or cmake would be nicer)


usage:
```
speakercontrol --getGain
speakercontrol --setGain 3
speakercontrol --mute true
speakercontrol --mute false

speakercontrol --interactive
speakercontrol -i
```
-> use y to increasse, a to decrease, x to mute, s to unmute
(controls have to do with my super game pi)
