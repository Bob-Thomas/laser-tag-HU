#include "player-task.hpp"

PlayerTask::PlayerTask(SoundController &sound, DisplayController &display, IrController &irTransmitter) : task("Player task"), sound(sound), display(display), irTransmitter(irTransmitter), shoot(this, "shoot-flag"), received(this, "received channel"), gameTimer(this, 60 * rtos::s, "gametimer"), gunCooldown(this, "cooldown-timer"), hitCooldown(this, "hit-cooldown-timer") {
}

void PlayerTask::main() {
    for (;;) {
        init();
        start();
        end();
    }
}

void PlayerTask::init() {
    display.getWindowOstream() << "     Welcome\n"
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
                hwlib::cout << "pew\n";
                sound.play_shoot();
                irTransmitter.send(Command(data.getPlayerId(), data.getWeaponId()).get_encoded());
                data.increaseShotsFired();
                canShoot = false;
                gunCooldown.set(data.getWeaponCooldownById(data.getWeaponId())*rtos::ms);
            }
        } else if (event == received) {
            if(canBeHit) {
                hwlib::cout << "received command\n";
                Command c = received.read();
                if (c.get_id() != 0 && c.get_id() != data.getPlayerId()) {
                    hwlib::cout << "hit\n";
                    data.insertHitBy(c.get_id(), c.get_data());
                    if(data.getHealth() <= 0) {
                        break;
                    }
                }
                hitCooldown.set(10*rtos::ms);
                canBeHit = false;
            }
        } else if (event == gameTimer) {
            data.setTime(data.getTime() - 1);
            if (data.getTime() < 0) {
                break;
            }
        } else if (event == gunCooldown) {
            canShoot = true;
        } else if (event == hitCooldown) {
            canBeHit = true;
        }
    }
    end();
}

void PlayerTask::end() {
    display.getWindowOstream() << "Game over.\n";
    display.getWindowOstream() << "Return to game master.\n";
    display.getWindowOstream() << "Shoot when connected.\n";
    display.flush();
    wait(shoot);
    for (;;) {
        hwlib::cout << data.getPlayerId() << "-";
        hwlib::cout << data.getHealth() << "-";
        hwlib::cout << data.getShotsFired() << "-";
        for (int i = 0; i < data.getReceivedHits(); i++) {
            hwlib::cout << data.getHitByArrFromIndex(i).playerId << "-";
            hwlib::cout << data.getHitByArrFromIndex(i).WeaponId << "-";
        }
        hwlib::cout << data.getReceivedHits() << "-";
        hwlib::cout << data.getTime() << ";";
    }
}

void PlayerTask::updateDisplay(bool alive) {
}

void PlayerTask::buttonPressed() {
    shoot.set();
}

void PlayerTask::commandReceived(Command c) {
    hwlib::cout << c.get_id() << " | " << c.get_data() << "\n";
    received.clear();
    received.write(c);
}