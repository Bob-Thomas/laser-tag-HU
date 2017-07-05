/**
 * \file      arsenal.hpp
 * \author    Bob Thomas
 * \author    Robbie Valkenburg
 * \brief     class that will run the application task for game leader/master.
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef MASTER_TASK_HPP
#define MASTER_TASK_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "../interfaces/i-controller.hpp"
#include "../entities/game-data.hpp"
#include "../application-logic/command.hpp"
#include "../boundaries/ir-send-controller.hpp"
#include "../boundaries/display-controller.hpp"
#include "stdlib.h"

struct {
    bool is_alive = false;
    int playerId = 0;
    int score = 0;
} typedef PlayerScore;


class MasterTask : public rtos::task<>, public IController {
private:
    /**
     * \brief the amount of menu items
     */
    static constexpr int menuSize = 4;
    /**
     * \brief load in menu items
     */
    static constexpr const char* const menuItems[menuSize] = {
            "Press A add Player",
            "Press B receive \n Gamedata",
            "Press C to Add a\n new Command",
            "Press * to start\n"
    };
    /// selected menu item
    int menuSelected = 0;
    /// Refererence to the display controller
    DisplayController &display;
    /// Reference to the transmitter controller
    IrController &irTransmitter;
    /// Channel that gets filled by keypad inputs
    rtos::channel<char, 1> keypadInput;
    /// Channel that gets filled by the received ir commmands
    rtos::channel<Command,1> received;
    /// Custom command the master can use
    uint16_t customCommand = 0;
    /// Gamedata to save the gametime and whatnot
    GameData gameData;
    /// Scores of the players
    PlayerScore scores[32];
    /// Rtos main function that runs the task
    void main();
    /// function that uses the keypad and ir to register players
    void registerPlayer();
    /// function that reads in the serial for game data from the players
    void receiveData();
    /// function that gives the master the ability to create a custom command
    void newCommand();
    /**
     *\brief function that sends the start command
     * start command is 1 00000 00000 00000
     */
    void sendStart();

    /// function that sends the saved custom command over ir
    void sendSavedCommand();

    /// function that returns index playerScore from array by playerId
    int getScoreIndexById(int id);
public:
    /**
     * Constructor for the MasterTask class
     * \param[in] display Reference to an existing DisplayController
     * \param[in] irTransmitter Reference to an existing IrController
     */
    MasterTask(DisplayController &display, IrController &irTransmitter);
    /**
     * \brief function that writes keypad input into it's channel
     * Overload of the pure virtual function in IController
     * \param c key that has bene pressed on the keypad
     */
    void keypadPressed(char c);
    /**
     * \brief function that writes the received command over ir into it's channel
     * Overload of the pure virtual function in IController
     * \param c command that has been received by the IrReceiveController
     */
    void commandReceived(Command c);
    /**
     * \brief overload of the pure virtual function it has no use for this task
     */
    void buttonPressed() {}

};
#endif //MASTER_TASK_HPP