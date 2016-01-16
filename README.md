# 8x7seg_counter

This C program displays a counter on a 8 digit 7 segment led.

I got one of these...

http://www.dx.com/p/diy8-x-seven-segment-displays-module-for-arduino-595-driver-250813#.VppbZnUrIXc

which appears to be the exact same thing as this:

http://www.dx.com/p/bonatech-8-digit-led-seven-segment-display-module-deep-blue-297686#.VppbdXUrIXc

except it's a dollar cheaper.

I started with this:

https://github.com/hennroja/raspberrypi-yl-3-demo/blob/master/demo-YL3.py

and made a java program which, using pi4j turned out to be way
too slow and it just flickered a lot.

I was surprised that the python one ran better than java, but I think it was the pi4j library not so much java vs python on the pi, but I didn't check that out.

So I used wiring pi and ported it to C, and now it's wicked fast, doesn't flicker and uses almost
no cpu.


What took me a while to figure out was this:

The first 8 bit byte you send to the display is a bit flag of which of the 8 positions you want to update.
The second byte is the pattern you want to update it with.
Which means it's really easy to set all 8 digits to the same pattern.
But there is no way to present a different display pattern in different digit positions.

The answer is turns out, is that you just have to keep updating it very quickly, and put a delay in after you latch each digit so that the display has time to light up the digit you set.
1 ms is long enough.
So you set digit 1's pattern, latch, delay, set digit 2's pattern, latch, delay, repeat for as many of the 8 digits as you want to display, then repeat the process all over, never stopping.

The display hardware is faster than the pi apparently, so you don't have to delay in the program at all in order for the clock or latch kick to take.

The only delay you need is after the latch, so 1) you're not spinning your cpu, and 2) the display shows bright red as opposed to being a dimmer flickering red.


