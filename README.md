#Leap Motion Plugin for ShiVa 3D
This repository contains a plugin for the ShiVa 3D game engine.  This plugin needs to be compiled before it is usable in ShiVa 3D, generally that means you need the following items:

* The Leap Motion SDK (0.7.5)
* Visual Studio 2010
* ShiVa 3D
* This code repository

##Adding Leap SDKs

The Leap SDKs are not included in this repository.  To compile successfully you need to create a Leap_SDK folder under Plugins\com_synapticbytes_sbLeap\Sources\.  Place the following in this folder:

* The *include* directory from the Leap SDK
* The contents of the *x86/libs* or *x64/libs* folder from the Leap SDK libs folder

When finished you should have content in the following folders:

Plugins\com_synapticbytes_sbLeap\Sources\Leap_SDK\include\

Plugins\com_synapticbytes_sbLeap\Sources\Leap_SDK\libs\

##The ShiVa 3D Sample Projects
The 2 sample projects were made using ShiVa 3D 1.9.2 beta 4.  This means that the project files will not be compatible with older versions of ShiVa.

###LeapMotionDemo
A simple visualizer showing hands, fingers and grip radius.  This project also has simple logging of any detected leap gestures.

###LeapAdvancedDemo
A more advanced demo that uses gestures and pinching.  There are many sample functions implemented that can be enabled/disabled in *LeapAdvancedDemo.Interact_onLoop*:

* Pinching - Allows 2 finger pinching to pick up object, spreading fingers drops the object while bringing fingers together will slingshot the object forward.
* Grabbing - Uses grip radious to pick up objects
* Panning  - Moves the camera forward/back/left/right based on palm position relative to leap origin
* Zooming  - A more simple version of panning
