#!/bin/bash
xterm -hold -e  ./sim.sh &
arm-none-eabi-gdb --command=./command.gdb

