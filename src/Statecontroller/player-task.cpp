#include "player-task.hpp"

PlayerTask::PlayerTask(SoundController &sound, DisplayController &display, IrController &irTransmitter) : task("Player task"), sound(sound), display(display), irTransmitter(irTransmitter), shoot(this, "shoot-flag"), received(this, "received channel"), gameTimer(this, 60 * rtos::s, "gametimer") {
}

void PlayerTask::main() {
    for (;;) {
        init();
        start();
        end();
    }
}

void PlayerTask::init() {
    display.getWindowOstream() <<
     "     Welcome\n" <<
     " to LaserTak 0.1\n\n" <<
     " Press fire to\n\n" <<
     "   to start";
     display.flush();
     wait(shoot);
     display.getWindowOstream() <<
     "\fWaiting for\n\n" <<
     "  player data";
     display.flush();
     Command c;
     while(c.get_id() == -1) {
         wait(received);
         c = received.read();
     }
    display.getWindowOstream() <<
     "\fPlayer data received\n" <<
     "ID: " << c.get_id() << "\n" <<
     "WEAPON: " << c.get_data();
     display.flush();
     hwlib::wait_ms(2*rtos::s);
     display.getWindowOstream() <<
     "\fWaiting for\n\n" <<
     "  game data";
     display.flush();
    while(c.get_id() != 0) {
         wait(received);
         c = received.read();
     }
     display.getWindowOstream() <<
     "\fTime received\n" <<
     "Minutes: " << c.get_data() <<
     "\n\n Wait for master";
     display.flush();
     wait(shoot);
    while(c.get_id() != 0 || c.get_data() != 0) {
         wait(received);
         c = received.read();
     }
     display.getWindowOstream() << "\f\n\n  STARTING";
     display.flush();
     display.getWindowOstream() << "\f\n\n 5s";
     display.flush();
     display.getWindowOstream() << "\f\n\n 4s";
     display.flush();
     display.getWindowOstream() << "\f\n\n 3s";
     display.flush();
     display.getWindowOstream() << "\f\n\n 2s";
     display.flush();
     display.getWindowOstream() << "\f\n\n 1s";
     display.flush();
     display.getWindowOstream() << "\f\n\n 0s";



<<<<<<< HEAD
=======
    display.displayText("Waiting to\nreceive player\ndata");
    while (c.get_id() == -1) {
        wait(received);
        c = received.read();
    }
    data.setPlayer(c.get_id());
    data.setWeapon(c.get_data());
    display.displayText("player data received");
    while(received.get_size() == 0) {
        irTransmitter.send(Command(0, data.getWeapon()).get_encoded());
        irTransmitter.send(Command(0, data.getWeapon()).get_encoded());
        irTransmitter.send(Command(0, data.getWeapon()).get_encoded());
    }
    display.displayText("Waiting for time");
    while (c.get_id() != 0) {
        wait(received);
        c = received.read();
    }
    data.setTime(c.get_data());
    display.displayText("game time received");
    while(received.get_size() == 0) {
        irTransmitter.send(Command(data.getPlayer(), data.getTime()).get_encoded());
        irTransmitter.send(Command(data.getPlayer(), data.getTime()).get_encoded());
        irTransmitter.send(Command(data.getPlayer(), data.getTime()).get_encoded());
    }
    hwlib::wait_ms(2000);
    char txt[] = "GAMETIME 10\n\nPlayer:  \nWeapon: id\n\nWaiting on start signal";
    if (data.getTime() < 10) {
        txt[9] = '0';
        txt[10] = (char)(48 + data.getTime());
    } else {
        txt[9] = (char)(48 + (data.getTime() / 10));
        txt[10] = (char)(48 + (data.getTime() % 10));
    }
    if (data.getPlayer() < 10) {
        txt[20] = '0';
        txt[21] = (char)(48 + data.getPlayer());
    } else {
        txt[20] = (char)(48 + (data.getPlayer() / 10));
        txt[21] = (char)(48 + (data.getPlayer() % 10));
    }
    if (data.getWeapon() < 10) {
        txt[31] = '0';
        txt[32] = (char)(48 + data.getWeapon());
    } else {
        txt[31] = (char)(48 + (data.getWeapon() / 10));
        txt[32] = (char)(48 + (data.getWeapon() % 10));
    }
    display.displayText(txt);
    wait(received);
    display.displayText("STARTING GAME in \n\n      5S");
    display.displayText("STARTING GAME in \n\n      4S");
    display.displayText("STARTING GAME in \n\n      3S");
    display.displayText("STARTING GAME in \n\n      2S");
    display.displayText("STARTING GAME in \n\n      1S");
    display.displayText("STARTING GAME in \n\n      0S");
    updateDisplay(true);
>>>>>>> origin/game-master
}

void PlayerTask::start() {
    gameTimer.clear();
    rtos::clock test(this, 1 * rtos::s, "test tmer");
    for (;;) {
        auto event = wait(shoot + received + gameTimer + test);
        if (event == shoot) {
            hwlib::cout << "pew\n";
            sound.play_shoot();
<<<<<<< HEAD
            data.increaseShotsFired();
        }
        else if(event == received) {
            hwlib::cout << "received command\n";
            Command c = received.read();
            if(c.get_id() != 0 && c.get_id() != data.getPlayerId()) {
                data.insertHitBy(c.get_id(), c.get_data());
=======
            irTransmitter.send(Command(data.getPlayer(), data.getWeapon()).get_encoded());
        } else if (event == received) {
            hwlib::cout << "received command\n";
            Command c = received.read();
            if (c.get_id() != 0 && c.get_id() != data.getPlayer()) {
>>>>>>> origin/game-master
            }
        } else if (event == gameTimer) {
            data.setTime(data.getTime() - 1);
            if (data.getTime() < 0) {
<<<<<<< HEAD

                if(data.getReceivedHits() == 0) {
                    hwlib::cout << "No hit information";
                } else {
                    for(int i = 0; i < data.getReceivedHits(); i++) {
                        hwlib::cout << "player id " << data.getHitByArrFromIndex(i).playerId << " with weapon " <<
                        data.getHitByArrFromIndex(i).WeaponId << "\n";
=======
                char txt[] = "\n\n   YOU SURVIVED \n    END SCORE \n\n      100";
                if (data.getHealth() < 100) {
                    if (data.getHealth() < 10) {
                        txt[41] = '0';
                        txt[42] = (char)(48 + data.getHealth());
                    } else {
                        txt[41] = (char)(48 + (data.getHealth() / 10));
                        txt[42] = (char)(48 + (data.getHealth() % 10));
>>>>>>> origin/game-master
                    }
                }
                // print amount of shots fired
                hwlib::cout << "amount of shots fired by you : " << data.getShotsFired();
            } else {
                updateDisplay(true);
            }
        }
    }
}

void PlayerTask::end() {
}

void PlayerTask::updateDisplay(bool alive) {
<<<<<<< HEAD
=======
    if (!alive) {
        char txt[] = "\n\n\n   YOU'RE DEAD \n Remaining time \n\n      10";
        if (data.getTime() < 10) {
            txt[43] = '0';
            txt[44] = (char)(48 + data.getTime());
        } else {
            txt[43] = (char)(48 + (data.getTime() / 10));
            txt[44] = (char)(48 + (data.getTime() % 10));
        }
        display.displayText(txt);
    } else {
        char txt[] = "hp: 100\nminutes left: 00";
        hwlib::cout << data.getTime() << "\n";
        if (data.getTime() < 10) {
            txt[22] = '0';
            txt[23] = (char)(48 + data.getTime());
        } else {
            txt[22] = (char)(48 + (data.getTime() / 10));
            txt[23] = (char)(48 + (data.getTime() % 10));
        }
        if (data.getHealth() < 100) {
            if (data.getHealth() < 10) {
                txt[4] = '0';
                txt[5] = (char)(48 + data.getHealth());
            } else {
                txt[4] = (char)(48 + (data.getHealth() / 10));
                txt[5] = (char)(48 + (data.getHealth() % 10));
            }
            txt[6] = ' ';
        }
        display.displayText(txt);
    }
>>>>>>> origin/game-master
}

void PlayerTask::button_pressed() {
    shoot.set();
}

void PlayerTask::command_received(Command c) {
    received.clear();
    received.write(c);
}