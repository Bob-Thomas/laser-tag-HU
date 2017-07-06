/**
 * \file      keypad-controller.hpp
 * \author    Bob Thomas
 * \brief     Makes a keypad task to listen to keypad input
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef KEYPAD_CONTROLLER_HPP
#define KEYPAD_CONTROLLER_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "../interfaces/i-controller.hpp"

class KeypadController : public rtos::task<> {
private:
    /// The poll time to check on keypad input.
    static constexpr int pollTime = 50*rtos::ms;
    /// Instance of the keypad.
    hwlib::keypad<16> &keypad;
    /// Listener for keypad.
    IController *controller = nullptr;
    /// RTOS task
    void main();
public:
    /*
     * \brief The constructor.
     * \param The keyPad instance from hwlib
     * \param The listener for the keypad controller.
     */
    KeypadController(hwlib::keypad<16> &keypad, IController *controller);

};

#endif //KEYPAD_CONTROLLER_HPP