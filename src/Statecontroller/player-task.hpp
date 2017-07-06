/**
 * \file      player-task.hpp
 * \author    Bob Thomas
 * \author    Robbie Valkenburg
 * \brief     Class that will run the application task for the player/client side.
 * \copyright Copyright (c) 2017, Lasertak
 */
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
    /// The current game data.
    GameData data;
    /// Sound controller class for playing a sound.
    SoundController &sound;
    /// Display controller class for writing on the oled.
    DisplayController &display;
    /// IRController for sending information with infrared.
    IrController &irTransmitter;
    /// Flag for checking when the player has shot.
    rtos::flag shoot;
    /// A channel that can be used to write and read the received commands.
    rtos::channel<Command, 1> received;
    /// Clock for handling the game time.
    rtos::clock gameTimer;

    rtos::timer gunCooldown;
    rtos::timer hitCooldown;
    bool canShoot = true;
    bool canBeHit = true;
    /// Update function for the display.
    void updateDisplay(bool alive);
    /// The RTOS task for executing the main function.
    void main();
public:
    /*
     * \brief The constructor for the PlayerTask.
     * \param SoundController for handling sounds.
     * \param DisplayController for writing on oled.
     * \param IrController for sending data with infrared.
     */
    PlayerTask(SoundController& sound, DisplayController& display, IrController &irTransmitter);

    /// Function that will be used for init process with game master.
    void init();
    /// Function that will be used for playing the game.
    void start();
    /// Function when game ends. Serial connection can be made with game master.
    void end();
    /// Interface function for the button pressed. Will set the shoot flag.
    void buttonPressed();
    /**
     * \brief function that returns the received channel
     * Overload of the pure virtual function in IController
     */
    rtos::channel<Command, 1>* getReceivedChannel();

    /**
     * Overload for the pure virtual function not being used
     */
    rtos::channel<char, 1>* getKeypadChannel() {return nullptr;}

};
#endif // PLAYER_TASK_HPP