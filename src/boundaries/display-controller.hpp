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
     * RTOS flag to flush screen
     */
    rtos::flag flushFlag;

    /**
     * RTOS task function
     */
    void main();
public:

    /**
     * \brief DisplayController Constructor
     *
     * /param hwlib::glc_oled_buffered &cled  will be the oled boundary object for writing on screen.
     *
     */
    DisplayController(hwlib::glcd_oled_buffered &oled );


    /**
     * \brief Get the oled.
     *
     * This function will return a reference to the made oled.
     *
     * \return hwlib::glcd_oled_buffered The oled.
     */
    hwlib::glcd_oled_buffered &getOled();


    /**
     * \brief Get the Font.
     *
     * This function will return the font that is used on the display.
     *
     * \return hwlib::font_default_8x8 The used font.
     */
    hwlib::font_default_8x8 getFont();


    /**
     * \brief Get the window_ostream.
     *
     * This function will return the window_ostream.
     *
     * \return hwlib::window_ostream The window_ostream.
     */
    hwlib::window_ostream &getWindowOstream();

    /**
     * \brief Flush the display.
     *
     * This function will flush the oled what will make that the stream will
     * be printed on the screen and cleared afterwards.
     *
     */
    void flush();

    /**
     * \brief Set a text to print on the display.
     *
     * \param text The text that has to be printed on the display.
     *
     */
    void setDisplayText(const char * text);

    /**
     * \brief set the flushFlag.
     *
     * This function will set the flushFlag to the stream will be printed.
     *
     */
    void setFlushFlag();


};


#endif //CODE_DISPLAYCONTROLLER_H