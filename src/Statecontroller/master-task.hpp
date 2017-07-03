#ifndef MASTER_TASK_HPP
#define MASTER_TASK_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "../interfaces/i-controller.hpp"
#include "../entities/game-data.hpp"
#include "../application-logic/command.hpp"
#include "../boundaries/ir-controller.hpp"
#include "../boundaries/display-controller.hpp"
#include "stdlib.h"
class MasterTask : public rtos::task<>, public IController {
private:
    int connectedPlayers = 0;
    DisplayController &display;
    IrController &irTransmitter;
    rtos::channel<char, 1> keypadInput;
    rtos::channel<Command,1> received;
    uint16_t customCommand = 0;
    int commandFull = 0;
    GameData players[31];
    GameData gameData;
    void main();
    int valid_id(char first, char second);
public:
    MasterTask(DisplayController &display, IrController &irTransmitter);
    void keypad_pressed(char c);
    void command_received(Command c);
    void button_pressed() {}

};
#endif //MASTER_TASK_HPP