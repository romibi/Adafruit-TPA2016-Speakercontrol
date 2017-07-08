#!/bin/bash
g++ speakercontrol.cpp -o speakercontrol -I. -Itpa2016/ -lwiringPi -lboost_program_options -lcurses
