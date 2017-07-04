/**
 * \file      display-controller.cpp
 * \author    Robbie Valkenburg
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "display-controller.hpp"
DisplayController::DisplayController(hwlib::glcd_oled_buffered &oled ):
        oled(oled),
        stream(oled, font),
        timer_screen(this, "timer screen"),
        clearFlag(this, "clear screen flag"),
        flushFlag(this, "set flush flag")

{}

void DisplayController::main() {
    for(;;){
        oled.clear();
        wait( flushFlag );
        flush();
    }
}


void DisplayController::setDisplayText(const char * text) {
    hwlib::cout << text << "\n";
    oledText = (char*)text;
    flushFlag.set();
}



hwlib::glcd_oled_buffered DisplayController::getOled(){
    return oled;
}

hwlib::font_default_8x8 DisplayController::getFont(){
    return font;
}

hwlib::window_ostream& DisplayController::getWindowOstream(){
    return stream;
}

void DisplayController::setFlushFlag(){
    flushFlag.set();
}


void DisplayController::flush(){
    oled.flush();
}





