/**
 * \file      i-controller.hpp
 * \brief     Task that listens for a button press and notifies a controller
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#ifndef I_CONTROLLER_HPP
#define I_CONTROLLER_HPP
#include "../application-logic/command.hpp"
#include "rtos.hpp"
/**
 * \brief Interface controller
 */
class IController  {
public:
    ///Pure virtual function that inherited classes can override
    virtual void buttonPressed() = 0;
    virtual rtos::channel<Command, 1>* getReceivedChannel() = 0;
    virtual rtos::channel<char, 1>* getKeypadChannel() = 0;
};
#endif //I_CONTROLLER_HPP