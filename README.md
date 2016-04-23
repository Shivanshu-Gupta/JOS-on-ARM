Arunos
======

Arunos is a simple operating system for ARM processors. I started creating it to
teach myself how operating systems work. Its design is based on the JOS 
operating system which is used in the labs of the [6.828 operating system
engineering course at MIT](http://pdos.csail.mit.edu/6.828/2011/schedule.html). 
I will improve it as I continue studying this course.


Hardware Support
----------------

I test the operating system on [ARM926][arm926] processor and Versatile Platform
Baseboard using [QEMU][qemu]. The reason for choosing ARM926 and VersatilePB
was QEMU's good support for this platform.

This operating system also works on [raspberry pi][raspberrypi]. To install it on
raspberry pi,

 * Run ```make arch=raspberrypi``` to create ```arunos.bin```,
 * Assuming that you have already installed Raspbian on the raspberry pi's SD
   card, replace ```kernel.img``` on the SD card with ```arunos.bin```.
 * Boot raspberry pi.


Current Status
--------------

Currently:

 * it boots,
 * has a simple shell with some utility commands for system information,
 * communicates with serial I/O port uart0,
 * uses the virtual memory hardware,
 * does some basic process management and can load user programs.

run "help" in the shell to see a list of available commands.


Compiling
---------

You need to install the GNU tools for cross-compilation for arm-none-eabi target
to be able to compile the code. To install these tools in Fedora 19, you can do:

    sudo yum install arm-none-eabi-binutils-cs
    sudo yum install arm-none-eabi-gcc-cs

After installing these tools, you can run the following command to build the
kernel:

    make

After making, the OS image is created as a single "arunos.bin" binary file.


Emulating
---------

To emulate the operating system, you need to install QEMU. To do this in Fedora 19,
you can do:

    sudo yum install qemu-system-arm

After qemu-system-arm is installed, run the following command to emulate the OS:

    make qemu

To terminate the emulation, you can press Ctrl-A X key combination.


Debugging
---------

The default GDB doesn't work with ARM binaries, so you need to compile GDB
manually to be able to debug Arunos. To do this, you can download gdb, then
configure it for arm-none-eabi target, and then make and install it:

    wget http://ftp.gnu.org/gnu/gdb/gdb-7.7.tar.gz
    tar -xzf gdb-7.7.tar.gz
    cd gdb-7.7
    ./configure --target=arm-none-eabi
    make
    sudo make install

After installation finishes, open two terminal windows and set their current
directories to the directory of Arunos. In terminal window 1, run:

    make qemu-gdb

In terminal window 2, run:
    
    arm-none-eabi-gdb

Then, you can use gdb commands to debug Arunos.

**Note**. You may need to add the following line to ~/.gdbinit:

    set auto-load safe-path /


Coding Style
------------

The coding style used in this project is based on [Linux kernel coding style]
(https://www.kernel.org/doc/Documentation/CodingStyle). Here are some guidelines:

 * Use tabs for indentation,
 * Each tab is 8 characters wide,
 * Each line should be limited to 80 characters,
 * Use underscore delimited names for functions and variables,
 * Use camel case names for structs and enums,
 * Don't typedef structs and enums,
 * Open the braces in the same line, except for functions,
 * If a condition is multiple lines, open the braces in a separate line,
 * Don't use braces for single line blocks,
 * Don't indent "case" statements in a switch/case statement,
 * Separate functions by a single empty line,
 * Don't comment how something is done, but what is being done,
 * Short names for local variables are allowed unless they introduce confusion,
 * Use descriptive names for global variables and functions.



License
-------

This software is BSD licensed. For more details, see the LICENSE file.


[arm926]: http://www.arm.com/products/processors/classic/arm9/arm926.php
[qemu]: http://wiki.qemu.org/Main_Page
[raspberrypi]: http://www.raspberrypi.org/# JOS-on-ARM
