/**
 * \file      i-controller.hpp
 * \brief     Task that listens for a button press and notifies a controller
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP
/**
 * \brief Interface controller
 */
class IController {
public:
    ///Pure virtual function that inherited classes can overide
    virtual void button_pressed() = 0;
    virtual void keypad_pressed(char c) = 0;
};
#endif //I_CONTROLLER_HPP