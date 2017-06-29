#############################################################################
#
# makefile.due common settings for Arduino Due projects
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# settings for Arduino Due projects
TARGET            ?= arduino_due
SERIAL_PORT       ?= COM3
CONSOLE_BAUDRATE  ?= 38400
STACK_SIZE        ?= 81920
HEAP              ?= BMPTK

PROJECT 	  	  ?= src/main

# use
SEARCH            += ./src/applicationLogic/ ./src/boundaries ./src/stateController
HEADERS           += command.hpp ir-receive-controller.hpp init-game-controller.hpp controller.hpp
SOURCES           += command.cpp ir-receive-controller.cpp init-game-controller.cpp

# use hwlib
SEARCH            += ./libs/hwlib
SOURCES           += hwlib.cpp
# use the rtos
SEARCH            += ./libs/rtos
HEADERS           += coroutine.hpp switch_to.hpp
SOURCES           += coroutine.cpp switch_to.asm
HEADERS           += rtos.hpp
SOURCES           += rtos.cpp

DEFINES           += -DPlAYER=2
DEFINES           += -DLEADER=1
DEFINES           += -DGAMEMODE=LEADER
OS ?= $(shell uname)

player:
	export DEFINES=DEFINES-DGAMEMODE=PLAYER

leader:
	export DEFINES=DEFINES-DGAMEMODE=LEADER

playerRun: player runAvr
leaderRun: leader runAvr

# set BMPTK to the bmptk subdirectory
BMPTK := $(BMPTK)./libs/bmptk/

# Defer to the bmptk/Makefile.inc to do the work
include $(BMPTK)Makefile.inc

ifeq ($(OS), Linux)
run:
	sudo stty -F /dev/ttyACM0 speed 1200 cs8 -cstopb -parenb && make build && sudo bossac --info --port "ttyACM0" --erase --write --verify --reset --debug --boot -U false ./src/main.bin && sudo platformio serialports monitor -b 38400
endif