#!/bin/bash

scp -r /sp/home/nixo/git/cdclock/cdclock/ccl.c pi@clock:cdclock

ssh pi@clock bash -c "pwd;cd /home/pi/cdclock; pwd; gcc -lwiringPi \
ccl.c -o ccl; sudo ./ccl"


