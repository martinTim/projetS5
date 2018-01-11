#!/bin/bash
xterm -hold -e  ./sim.sh &
arm-none-eabi-gdb -se "Examples/example"$1 --command=./command.gdb

