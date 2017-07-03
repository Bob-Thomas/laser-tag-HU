//
// Created by robbie on 29-6-2017.
//

#ifndef LASER_CONTROLLER_HPP
#define LASER_CONTROLLER_HPP

#include "./rtos.hpp"
#include "../applicationLogic/command.hpp"

class Controller {
public:
    virtual void irReceived(Command c) = 0;
    virtual void buttonPressed() = 0;
    virtual void enable() = 0;
};
#endif //LASER_CONTROLLER_HPP
