#include "master-task.hpp"

MasterTask::MasterTask(DisplayController &display, IrController &irTransmitter)
    : task("Master task"), display(display), irTransmitter(irTransmitter),
      keypadInput(this, "keypad channel"), received(this, "received channel") {}

void MasterTask::main() {
    display.displayText("Welcome to LaserTak 0.1\n\nPress anykey");
    wait(keypadInput);
    keypadInput.clear();
    char txt_1[9] = "Time: 00";
    display.displayText(txt_1);

    // getting first character
    wait(keypadInput);
    auto first = keypadInput.read();
    txt_1[6] = first;
    txt_1[7] = '\0';
    display.displayText(txt_1);

    // getting second character
    wait(keypadInput);
    auto second = keypadInput.read();
    txt_1[7] = second;
    txt_1[8] = '\0';
    display.displayText(txt_1);
    char txt_id[2];
    txt_id[0] = first;
    txt_id[1] = second;
    int time = atoi(txt_id);
    gameData.setTime(time);
    for (;;) {
        hwlib::cout << "Connected Players: " << connectedPlayers << "\n";
        char txt[] = "Press A to \n insert player.\n\nPress B to \nreceive data\n "
                     "\nPress C to \ninsert command. \nPress * to start";

        // default screen
        display.displayText(txt);
        wait(keypadInput);
        auto c = keypadInput.read();

        if (c == '*') {
            char start[32] = "STARTING GAME\n\n ";
            uint16_t c = Command(0, 0).get_encoded();
            for (int i = 0; i < 16; i++) {
                start[16 + i] = ((c >> (15 - i)) & 1) ? '1' : '0';
            }
            display.displayText(start);
            irTransmitter.send(c);
            hwlib::wait_ms(500);
        }

        if (c == 'B') {
            display.displayText("Ready to receive data\nPlayer");
        }

        if (c == 'A') {
            int playerId = 0;
            int weaponId = 0;
            char txt_1[15] = "Type id: \n\n\n";
            display.displayText(txt_1);

            // getting first character
            wait(keypadInput);
            auto first = keypadInput.read();
            txt_1[12] = first;
            txt_1[13] = '\0';
            display.displayText(txt_1);

            // getting second character
            wait(keypadInput);
            auto second = keypadInput.read();
            txt_1[13] = second;
            txt_1[14] = '\0';
            display.displayText(txt_1);

            // check if the id is valid
            auto valid = valid_id(first, second);

            // when valid is alright
            if (valid != 0) {

                // assign to player id
                playerId = valid;

                // asking for weapon
                display.displayText("Press B to \n Select weapon.");

                wait(keypadInput);
                auto c = keypadInput.read();

                // weapon select
                if (c == 'B') {

                    display.displayText(
                        "Weapons: \n 1.Power Beam \n 2.Sonic Beam \n 3.Laser Beam \n");
                    wait(keypadInput);
                    char c = keypadInput.read();
                    // player selected weapon
                    while (c != '1' && c != '2' && c != '3' && c != 'A') {

                        // listen again for keypad input
                        wait(keypadInput);
                        c = keypadInput.read();
                    }

                    if (c != 'A') {

                        weaponId = (c-48);

                        hwlib::cout << "TEST CASE PLAYER ID:" << playerId
                                    << "\n TEST CASE WEAPON ID " << weaponId << "\n";
                        display.displayText("Press * to \n send data.");
                        wait(keypadInput);
                        auto c = keypadInput.read();
                        if (c == '*') {
                            registerPlayer(playerId, weaponId);
                        }
                    }
                }

                // player can select id again...
            } else {
                display.displayText("incorrect id.");
            }
        }

        if (c == 'C') {
            int counter = 1;
            customCommand = 0;
            customCommand |= 1 << 15;
            char first_screen_command[] = "1..........xxxxx";
            display.displayText(first_screen_command);

            while (counter < 11) {
                wait(keypadInput);
                char c = keypadInput.read();
                if (c == '1' || c == '0') {
                    first_screen_command[counter] = c;
                    if (c == '1') {
                        customCommand |= (1 << (15 - counter));
                    }
                    display.displayText(first_screen_command);
                    counter++;
                } else {
                    commandFull = 0;
                    break;
                }
            }
            customCommand += (Command::get_id_from_byte(customCommand) ^
                              Command::get_data_from_byte(customCommand));
            for (int i = 0; i < 16; i++) {
                first_screen_command[i] = ((customCommand >> (15 - i)) & 1) ? '1' : '0';
            }
            display.displayText(first_screen_command);
            sleep(2 * rtos::s);
            display.displayText("Press * \nany time \nto send  \ncommand. \nPress "
                                "any \nkey to \ncontinue.");
            commandFull = '1';
        }
        if (c == '#') {

            if (commandFull == '1') {
                display.displayText("send last \ninserted command");
                irTransmitter.send(customCommand);
            } else {
                display.displayText("Incorrect  \nCommand");
            }
        }

        hwlib::cout << c;
    }
}
int MasterTask::valid_id(char first, char second) {

    // check if the chars are numbers
    if (first >= '0' && first <= '9' && second >= '0' && second <= '9') {
        char txt_id[2];
        txt_id[0] = first;
        txt_id[1] = second;
        int id = atoi(txt_id);

        if (id > 0 && id < 32) {
            return id;
        }

        return 0;
    }

    return 0;
}

void MasterTask::command_received(Command c) {
    hwlib::cout << c.get_id() << " | " << c.get_data() << "\n";
    received.clear();
    received.write(c);
}

void MasterTask::keypad_pressed(char c) {
    keypadInput.write(c);
}

void MasterTask::registerPlayer(int playerId, int weaponId) {
    Command playerData(playerId, weaponId);
    Command confirmationCommand;
    while (true) {
        display.displayText("Sending player.. \nWaiting for\n confirmation");
        while (received.get_size() <= 0) {
            irTransmitter.send(playerData.get_encoded());
            hwlib::wait_ms(10);
        }
        confirmationCommand = received.read();
        if (confirmationCommand.get_encoded() == Command(0, weaponId).get_encoded()) {
            registerTime(playerId, weaponId);
        } else {
            display.displayText("Adding failed");
        }
    }
}

void MasterTask::registerTime(int playerId, int weaponId) {
    Command gameTime(0, gameData.getTime());
    Command confirmationCommand;
    display.displayText("Player confirmed\n sending time\n ");
    sleep(2 * rtos::s);
    display.displayText("Sending time.. \nWaiting for\n confirmation");
    while (true) {
        while (received.get_size() <= 0) {
            irTransmitter.send(gameTime.get_encoded());
            irTransmitter.send(gameTime.get_encoded());
            irTransmitter.send(gameTime.get_encoded());
            irTransmitter.send(gameTime.get_encoded());
            irTransmitter.send(gameTime.get_encoded());
            hwlib::wait_ms(1000);
        }
        confirmationCommand = received.read();
        if (confirmationCommand.get_encoded() == Command(playerId, gameData.getTime()).get_encoded()) {
            players[connectedPlayers] = GameData(playerId, weaponId);
            connectedPlayers++;
            display.displayText("Confirmation received\n returning to menu");
            break;
        } else {
            display.displayText("Adding failed");
        }
    }
    display.displayText("Player added");
}