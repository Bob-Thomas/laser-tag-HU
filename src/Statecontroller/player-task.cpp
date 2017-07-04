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



}

void PlayerTask::start() {
    gameTimer.clear();
    rtos::clock test(this, 1 * rtos::s, "test tmer");
    for (;;) {
        auto event = wait(shoot + received + gameTimer + test);
        if (event == shoot) {
            hwlib::cout << "pew\n";
            sound.play_shoot();
            data.increaseShotsFired();
        }
        else if(event == received) {
            hwlib::cout << "received command\n";
            Command c = received.read();
            if(c.get_id() != 0 && c.get_id() != data.getPlayerId()) {
                data.insertHitBy(c.get_id(), c.get_data());
            }
        } else if (event == gameTimer) {
            data.setTime(data.getTime() - 1);
            if (data.getTime() < 0) {

                if(data.getReceivedHits() == 0) {
                    hwlib::cout << "No hit information";
                } else {
                    for(int i = 0; i < data.getReceivedHits(); i++) {
                        hwlib::cout << "player id " << data.getHitByArrFromIndex(i).playerId << " with weapon " <<
                        data.getHitByArrFromIndex(i).WeaponId << "\n";
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
}

void PlayerTask::button_pressed() {
    shoot.set();
}

void PlayerTask::command_received(Command c) {
    received.clear();
    received.write(c);
}