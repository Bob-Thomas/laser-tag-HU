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
    /**
     * RTOS buffer for storing the char to write to oled display
     */
    rtos::channel< char, 2048 > buffer;

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
    DisplayController(hwlib::glcd_oled_buffered &o);

    /**
     * interface function to write string on screen
     */
    void displayText(const char *);
};


#endif //CODE_DISPLAYCONTROLLER_H