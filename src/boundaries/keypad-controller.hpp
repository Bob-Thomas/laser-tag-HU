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
    static constexpr int pollTime = 50*rtos::ms;
    hwlib::keypad<16> &keypad;
    IController *controller = nullptr;
    void main();
public:
    KeypadController(hwlib::keypad<16> &keypad, IController *controller);

};

#endif //KEYPAD_CONTROLLER_HPP