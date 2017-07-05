/**
 * \file      display-controller.cpp
 * \author    Robbie Valkenburg
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "display-controller.hpp"
DisplayController::DisplayController(hwlib::glcd_oled_buffered &oled ):
        oled(oled),
        stream(oled, font),
        flushFlag(this, "set flush flag")
{}

void DisplayController::main() {
    for(;;){
        oled.clear();
        wait( flushFlag );
        flush();
    }
}

  //////////////////////
 //  Get functions   //
//////////////////////
hwlib::glcd_oled_buffered &DisplayController::getOled(){
    return oled;
}

hwlib::font_default_8x8 DisplayController::getFont(){
    return font;
}

hwlib::window_ostream& DisplayController::getWindowOstream(){
    return stream;
}

  //////////////////////
 //  Set functions   //
//////////////////////
void DisplayController::setFlushFlag(){
    flushFlag.set();
}

//flush
void DisplayController::flush(){
    oled.flush();
}





