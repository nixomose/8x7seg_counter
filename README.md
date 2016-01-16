# 8x7seg_counter
display a counter on a 8 digit 7 segment led.

I got one of these..


http://www.dx.com/p/diy8-x-seven-segment-displays-module-for-arduino-595-driver-250813#.VppbZnUrIXc

which appears to be the exact same thing as this:

http://www.dx.com/p/bonatech-8-digit-led-seven-segment-display-module-deep-blue-297686#.VppbdXUrIXc

except it's a dollar cheaper.

I took some python examples and made a java program which, using pi4j turned out to be way
too slow and it just flickered a lot.

So I used wiring pi and ported it to C, and now it's wicked fast, doesn't flicker and uses almost
no cpu.


