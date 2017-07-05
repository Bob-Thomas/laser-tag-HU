#include "master-task.hpp"
constexpr const char *const MasterTask::menuItems[];

MasterTask::MasterTask(DisplayController &display, IrController &irTransmitter)
    : task("Master task"), display(display), irTransmitter(irTransmitter),
      keypadInput(this, "keypad channel"), received(this, "received channel") {
}

void MasterTask::main() {
    display.getWindowOstream() << "\fWelcome to\n LaserTak 0.1\n\nPress anykey";
    display.flush();
    wait(keypadInput);
    keypadInput.clear();
    display.getWindowOstream() << "\fFill in gametime\n\n"
                               << "Minutes: ";
    display.flush();
    wait(keypadInput);
    int time = keypadInput.read() - 48;
    display.getWindowOstream() << "\fFill in gametime\n\n"
                               << "Minutes: " << time;
    display.flush();

    wait(keypadInput);
    time = (10 * time) + (keypadInput.read() - 48);
    display.getWindowOstream() << "\fFill in gametime\n\n"
                               << "Minutes: " << time << "\n press anykey";
    display.flush();
    gameData.setTime(time);
    hwlib::wait_ms(200);
    while (true) {
        wait(keypadInput);
        char c = keypadInput.read();
        if (c == '2') {
            if (menuSelected >= menuSize - 1) {
                menuSelected = 0;
            } else {
                menuSelected++;
            }
        } else if (c == '8') {
            if (menuSelected - 1 < 0) {
                menuSelected = menuSize - 1;
            } else {
                menuSelected--;
            }
        } else if (c == 'A') {
            registerPlayer();
        } else if (c == 'B') {
            receiveData();
        } else if (c == 'C') {
            newCommand();
        } else if (c == '*') {
            sendStart();
        } else if (c == '#') {
            sendSavedCommand();
        }
        display.getWindowOstream() << "\f Press 2 or 8\n   To scroll: " << menuSelected << "\n\n\n"
                                   << menuItems[menuSelected];
        display.flush();
    }
}
void MasterTask::commandReceived(Command c) {
    hwlib::cout << c.get_id() << " | " << c.get_data() << "\n";
    received.clear();
    received.write(c);
}

void MasterTask::keypadPressed(char c) {
    keypadInput.write(c);
}

void MasterTask::receiveData() {
    //TODO serial reads from the weapons
    Arsenal arsenal;
    display.getWindowOstream() << "\fReceive hits \n Press C to start \n Press # to cancel \n Press B to \n Show winner";
    display.flush();
    char d;
    int count = 0;
    int index = -1;
    PlayerScore &score = scores[0];
    while (true) {
        wait(keypadInput);
        char key = keypadInput.read();
        if (key == 'C') {
            display.getWindowOstream() << "\fRECEIVING STARTED";
            display.flush();
            while(!hwlib::cin.char_available()){}
            hwlib::cin >> d;
            d = d - 48;
            if (d == 0) {
                d = -1;
                display.getWindowOstream() << "\f\n\n\n  RECEIVING DATA..";
                display.flush();
                //GET PLAYER ID
                while(!hwlib::cin.char_available()){}
                d = hwlib::cin.getc();
                d = d - 48;
                while(!hwlib::cin.char_available()){}
                hwlib::cin >> d;
                if (d == '-') {
                    index = getScoreIndexById(d);
                } else {
                    d = (d * 10) + (d - 48);
                    index = getScoreIndexById(d);
                }
                if (index != -1) {
                    score = scores[index];
                } else {
                    scores[count] = {false, d, 0};
                    score = scores[count];
                    count++;
                }
                //IS PLAYER ALIVE
                while(!hwlib::cin.char_available()){}
                hwlib::cin >> d;
                d = d - 48;
                score.is_alive = d;
                //RETRIEVE HIT DATA
                while (d != 0) {
                    index = -1;
                    //PLAYER ID
                    while(!hwlib::cin.char_available()){}
                    hwlib::cin >> d;
                    d = d - 48;
                    while(!hwlib::cin.char_available()){}
                    hwlib::cin >> d;
                    if (d == '-') {
                        index = getScoreIndexById(d);
                    } else {
                        d = (d * 10) + (d - 48);
                        index = getScoreIndexById(d);
                    }
                    if (index != -1) {
                        score = scores[index];
                    } else {
                        scores[count] = {false, d, 0};
                        score = scores[count];
                        count++;
                    }
                    while(!hwlib::cin.char_available()){}
                    hwlib::cin >> d;
                    d = d - 48;
                    score.score = score.score + arsenal.getWeaponById(d).getDamage();
                    display.getWindowOstream() << "\f\n\n\n  RECEIVING DATA...";
                    display.flush();
                }
                display.getWindowOstream() << "\fCOMPLETED";
                display.flush();
                break;
            }
        }
        if (key == 'B') {
           for(int i = 0; i < 32; i++) {
               if(scores[i].playerId != 0) {
                   hwlib::cout << "PLAYER -" << scores[i].playerId << " : " << scores[i].score << "\n";
               }
           }
        }
        if (key == '#') {
            break;
        }
    }
}

void MasterTask::newCommand() {
    int counter = 1;
    uint16_t tempCustomCommand = (1 << 15);
    while (true) {
        display.getWindowOstream() << "\f ADD NEW COMMAND\n\n";
        for (int i = 0; i < 11; i++) {
            if (counter <= i) {
                display.getWindowOstream() << 'x';
            } else {
                display.getWindowOstream() << (tempCustomCommand >> (15 - i) & 1);
            }
        }
        if (counter >= 16) {
            display.getWindowOstream() << "\n\nCHECKSUM = ";
            for (int i = 0; i < 5; i++) {
                display.getWindowOstream() << (tempCustomCommand >> (i)&1);
            }
            display.getWindowOstream() << "\n Ready to save";
        }
        display.flush();
        wait(keypadInput);
        char c = keypadInput.read();
        if (c == '#') {
            if (counter < 16) {
                display.getWindowOstream() << "\fInvalid command";
                display.flush();
                sleep(200);
            } else {
                customCommand = tempCustomCommand;
                display.getWindowOstream() << "\fCommand saved";
                display.flush();
                sleep(200);
            }
            break;
        }
        if (c == '1' || c == '0') {
            tempCustomCommand |= ((int)(c - 48) << (15 - counter));
            counter++;
            if (counter >= 11) {
                tempCustomCommand = tempCustomCommand + (Command::get_id_from_byte(tempCustomCommand) ^
                                                         Command::get_data_from_byte(tempCustomCommand));
                counter += 5;
            }
        }
        hwlib::cout << "\n"
                    << counter << "\n";
    }
}

void MasterTask::sendStart() {
    display.getWindowOstream() << "\f START\n\n SENDING...";
    display.flush();
    irTransmitter.send(Command(0, 0).get_encoded());
    display.getWindowOstream() << "\f START\n\n SENDING..";
    display.flush();
}

void MasterTask::sendSavedCommand() {
    if (customCommand != 0) {
        display.getWindowOstream() << "\f  SENDING...\n\n";
        for (int i = 0; i < 16; i++) {
            display.getWindowOstream() << (customCommand >> (15 - i) & 1);
        }
        display.flush();
        irTransmitter.send(customCommand);
        display.getWindowOstream() << "\f  SENDING...\n\n";
        for (int i = 0; i < 16; i++) {
            display.getWindowOstream() << (customCommand >> (15 - i) & 1);
        }
        display.flush();
    } else {
        display.getWindowOstream() << "\n\n NO SAVED \n   COMMAND";
        display.flush();
    }
}

void MasterTask::registerPlayer() {
    display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                               << "ID: \n"
                               << "Weapon: ";
    display.flush();
    wait(keypadInput);
    int id = keypadInput.read() - 48;
    display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                               << "ID: " << id << "\nWeapon: ";
    display.flush();
    wait(keypadInput);
    id = (id * 10) + (keypadInput.read() - 48);
    display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                               << "ID: " << id << "\nWeapon: ";
    display.flush();
    wait(keypadInput);
    int weapon = keypadInput.read() - 48;
    display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                               << "ID: " << id << "\nWeapon: " << weapon;
    display.flush();
    wait(keypadInput);
    weapon = (weapon * 10) + (keypadInput.read() - 48);
    display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                               << "ID: " << id << "\nWeapon: " << weapon;
    display.flush();
    wait(keypadInput);
    keypadInput.clear();
    display.flush();
    while (true) {
        display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                                   << "* to send player\n B to continue";
        display.flush();
        wait(keypadInput);
        char c = keypadInput.read();
        if (c == '*') {
            display.getWindowOstream() << "\f  SENDING...";
            display.flush();
            irTransmitter.send(Command(id, weapon).get_encoded());
            display.getWindowOstream() << "\f  SENDING..";
            display.flush();
        }
        if (c == 'B') {
            while (true) {
                display.getWindowOstream() << "\f  NEW PLAYER\n\n"
                                           << "* to send time\n B to continue";
                display.flush();
                wait(keypadInput);
                char c = keypadInput.read();
                if (c == '*') {
                    display.getWindowOstream() << "\f  SENDING...";
                    display.flush();
                    irTransmitter.send(Command(0, gameData.getTime()).get_encoded());
                    display.getWindowOstream() << "\f  SENDING..";
                    display.flush();
                }
                if (c == 'B') {
                    break;
                }
            }
            break;
        }
    }
}

int MasterTask::getScoreIndexById(int id) {
    for (int i = 0; i < 32; i++) {
        if (scores[i].playerId == id) {
            return i;
        }
    }
    return -1;
}