/**
 * \file      display-controller.hpp
 * \author    Robbie Valkenburg
 * \brief     will be used as communcation controller between oled boundary and other game state controllers
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef CODE_DISPLAYCONTROLLER_HPP
#define CODE_DISPLAYCONTROLLER_HPP

#include "rtos.hpp"
#include "hwlib.hpp"

/**
 * \class DisplayController
 * \brief will be used as communcation controller between oled boundary and other game state controllers
 */

class DisplayController : public rtos::task<> {
private:
    /**
     * oled boundary reference
     */
    hwlib::glcd_oled_buffered &oled;
    hwlib::window_ostream stream;
    hwlib::font_default_8x8 font;

    char *oledText;

    /**
     * RTOS timer for updating screen
     */
    rtos::timer timer_screen;

    /**
     * RTOS flag to clear screen
     */
    rtos::flag clearFlag;

    /**
     * RTOS flag to flush screen
     */
    rtos::flag flushFlag;

    /**
     * RTOS task function
     */
    void main();
public:

    /**
     * DisplayController Constructor
     * /param hwlib::glc_oled_buffered &c  will be the oled boundary object for writing on screen
     */
    DisplayController(hwlib::glcd_oled_buffered &oled );

    /**
     * interface function to write string on screen
     */


    hwlib::glcd_oled_buffered getOled();
    hwlib::font_default_8x8 getFont();
    hwlib::window_ostream &getWindowOstream();

    void flush();

    void setDisplayText(const char * text);
    void setFlushFlag();


};


#endif //CODE_DISPLAYCONTROLLER_H