#ifndef PLAYER_TASK_HPP
#define PLAYER_TASK_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "../interfaces/i-controller.hpp"
#include "../boundaries/sound-controller.hpp"
#include "../boundaries/display-controller.hpp"
#include "../boundaries/ir-send-controller.hpp"
#include "../entities/game-data.hpp"
#include "../application-logic/command.hpp"
class PlayerTask : public rtos::task<>, public IController {
private:
    GameData data;
    SoundController &sound;
    DisplayController &display;
    IrController &irTransmitter;
    rtos::flag shoot;
    rtos::channel<Command, 1> received;
    rtos::clock gameTimer;
    void updateDisplay(bool alive);
    void main();
public:
    PlayerTask(SoundController& sound, DisplayController& display, IrController &irTransmitter);

    void init();
    void start();
    void end();

    void button_pressed();
    void command_received(Command c);
    void keypad_pressed(char c) {}

};
#endif // PLAYER_TASK_HPP