#include "player-task.hpp"

PlayerTask::PlayerTask(SoundController &sound, DisplayController &display, IrController &irTransmitter) : task("Player task"), sound(sound), display(display), irTransmitter(irTransmitter), shoot(this, "shoot-flag"), received(this, "received channel"), gameTimer(this, 600000000000, "gametimer"), gunCooldown(this, "cooldown-timer"), hitCooldown(this, "hit-cooldown-timer") {
}

void PlayerTask::main() {
    for (;;) {
        init();
        start();
        end();
    }
}

void PlayerTask::init() {
    display.getWindowOstream() << "\f     Welcome\n"
                               << " to LaserTak 0.1\n\n"
                               << " Press fire to\n\n"
                               << "   to start";
    display.flush();
    wait(shoot);
    display.getWindowOstream() << "\fWaiting for\n\n"
                               << "  player data";
    display.flush();
    Command c;
    wait(received);
    c = received.read();
    display.getWindowOstream() << "\fPlayer data received\n"
                               << "ID: " << c.get_id() << "\n"
                               << "WEAPON: " << c.get_data();
    display.flush();
    data.setPlayerId(c.get_id());
    data.setWeaponId(c.get_data());
    sleep(5 * rtos::s);
    display.getWindowOstream() << "\fWaiting for\n\n"
                               << "  game data";
    display.flush();
    wait(received);
    c = received.read();
    display.getWindowOstream() << "\fTime received\n"
                               << "Minutes: " << c.get_data() << "\n\n Wait for master";
    data.setTime(c.get_data());
    display.flush();
    wait(shoot);
    wait(received);
    c = received.read();
    while(c.get_id() != 0 && c.get_data() != 0) {
        wait(received);
        c = received.read();
    }
    if (c.get_id() == 0 && c.get_data() == 0) {
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
        display.flush();
    }
}

void PlayerTask::start() {
    gameTimer.clear();
    for (;;) {
        auto event = wait(shoot + received + gameTimer + gunCooldown + hitCooldown);
        if (event == shoot) {
            if(canShoot) {
                //hwlib::cout << "pew\n";
                sound.play_shoot();
                irTransmitter.send(Command(data.getPlayerId(), data.getWeaponId()).get_encoded());
                data.increaseShotsFired();
                canShoot = false;
                gunCooldown.set(data.getWeaponCooldownById(data.getWeaponId())*rtos::ms);
            } else {
                //hwlib::cout << "in cooldown here.. \n";
            }
        } else if (event == received) {
            if(canBeHit) {
                //hwlib::cout << "received command\n";
                Command c = received.read();
                if (c.get_id() != 0 && c.get_id() != data.getPlayerId()) {
                    //hwlib::cout << "hit\n";
                    data.insertHitBy(c.get_id(), c.get_data());
                    hitCooldown.set(10*rtos::ms);
                    canBeHit = false;
                    if(data.getHealth() <= 0) {
                        break;
                    }
                }
            }
        } else if (event == gameTimer) {
            data.setTime(data.getTime() - 1);
            if (data.getTime() <= 0) {
                break;
            }
        } else if (event == gunCooldown) {
            canShoot = true;
        } else if (event == hitCooldown) {
            canBeHit = true;
        }

        display.getWindowOstream() << "\fHP :" << data.getHealth() << "\n";
        display.getWindowOstream() << "Time left :" << data.getTime() << "\n";
        display.flush();
    }
    end();
}

void PlayerTask::end() {
    display.getWindowOstream() << "\fGame over.\n";
    display.getWindowOstream() << "Return to game master.\n";
    display.getWindowOstream() << "Shoot when connected.\n";
    display.flush();
    while(true) {
        Command c;
        while (c.get_encoded() != Command(0, 0).get_encoded()) {
            auto event = wait(shoot + received);
            if (event == shoot) {
                irTransmitter.send(Command(0, 1).get_encoded());
            }
            if (event == received) {
                c = received.read();
            }
        }
        hwlib::wait_ms(500);
        irTransmitter.send(Command(data.getPlayerId(), (bool) data.getHealth()).get_encoded());
        hwlib::wait_ms(500);
        for (int i = 0; i < data.getReceivedHits(); i++) {
            irTransmitter.send(Command(data.getHitByArrFromIndex(i).playerId,
                                       data.getHitByArrFromIndex(i).weaponId).get_encoded());
            hwlib::wait_ms(500);
        }
        irTransmitter.send(Command(0, 1).get_encoded());
    }
}

void PlayerTask::updateDisplay(bool alive) {
}

void PlayerTask::buttonPressed() {
    shoot.set();
}

void PlayerTask::commandReceived(Command c) {
    ////hwlib::cout << c.get_id() << " | " << c.get_data() << "\n";
    received.clear();
    received.write(c);
}