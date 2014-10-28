Zcl-Gigecam-Directshow
======================
Directshow driver for XCG-H280E Gige Camera

1/ download and install the 32 bit sdk depending on your platform
http://www.image-sensing-solutions.eu/XCG-H280E.html

2/ git this project
you will find a compiled dll in folder /Release

3/ register the dll with windows command promt:
with command: regsvr32 <path to the dll>

4/ you should see the dll successfully registered.

5/ download virtual dub, install it, and connect your camera.
you should see the device available for any directshow compatible camera source.

