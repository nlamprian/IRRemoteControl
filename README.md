IRRemoteControl
===============

This is a wrapper on the [`IRremote`](https://github.com/shirriff/Arduino-IRremote) library that enables a more natural way of setting up an IR remote and developing applications with it.

If you wanna know more about IR, you can read [Ken Shirriff's blog post](http://www.righto.com/2009/08/multi-protocol-infrared-remote-library.html) about his IRremote library and/or the tutorial on [IR Communication](https://learn.sparkfun.com/tutorials/ir-communication/getting-started) from Sparkfun.

![project](http://i859.photobucket.com/albums/ab154/lampnick67/project_zpsf8955b1a.png)

The library has been set up for the [IR Remote Control](https://www.sparkfun.com/products/11759) from Sparkfun, but it can easily support other remotes by updating the `button`, `numButtons` and `address` variables in the `IRRemoteControl.h` file. To find the commands sent by your remote, you will have to run either the `IRrecvDump` or `IRrecord` example from the [`IRremote`](https://github.com/shirriff/Arduino-IRremote) library.

Interface
---------

```cpp
enable() // Starts the receiver
pair(button b, void (*func)()) // Pairs button b with function func
check() // Checks if data has been received, decodes them, and calls the appropriate function
```

So, all you have to do is define the functions (e.g. `void upButton() {...}`) you would like to be called with each button press, pair those functions (e.g. `*.pair(UP, upButton)`) with specific buttons, and you are good to go... every time you call `check`, your button press will be parsed and its paired function will be called.

Your functions must take `no arguments` and return `void`. If you need to manipulate variables in your code, you can use `global` variables, or `static` variables inside the functions.

Examples
--------

The library has two accompanying examples.

One is the `IRControlTest` example and it's a dummy sketch to test that your system (Arduino-IR Receiver-IR Remote) is working properly.
The other is the `IRLEDStrip` example that implements a remote for controlling an [LED Strip](http://i859.photobucket.com/albums/ab154/lampnick67/project_zpsf8955b1a.png). For details on how the buttons function, read the comments in the code.

===

Thank you `Ken Shirriff` for an awesome library. You made the whole process of experimenting with IR really fun!
