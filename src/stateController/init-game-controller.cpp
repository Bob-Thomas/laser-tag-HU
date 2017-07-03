//
// Created by robbie on 29-6-2017.
//

#include "init-game-controller.hpp"

void InitGameController::irReceived(Command c) {
    hwlib::cout << c.get_sender() << "-" << c.get_data() << "\n";
}

void InitGameController::buttonPressed() {

}

void InitGameController::enable() {

}