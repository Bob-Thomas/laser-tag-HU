//
// Created by robbie on 29-6-2017.
//

#ifndef LASER_INITGAMECONTROLLER_HPP
#define LASER_INITGAMECONTROLLER_HPP

#include "controller.hpp"
#include "../applicationLogic/command.hpp"
#include "../stateController/controller.hpp"

class InitGameController : public Controller {
private:
    void main();
public:
    void irReceived(Command c);
    void buttonPressed();
    void enable();
};


#endif //LASER_INITGAMECONTROLLER_HPP
