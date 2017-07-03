#include "player-task.hpp"

PlayerTask::PlayerTask(SoundController& sound, DisplayController& display): task("Player task"), sound(sound), display(display), shoot(this, "shoot-flag"), received(this, "received channel"), gameTimer(this, 60*rtos::s, "gametimer") {

}

void PlayerTask::main() {
    for(;;) {
        init();
        start();
        end();
    }
}

void PlayerTask::init() {
    Command c;
    display.displayText("Starting game\nPress fire when\nthe game master\nnotifies you");
    wait(shoot);
    display.displayText("Waiting to\nreceive player\ndata");
    hwlib::wait_ms(2000);
    received.write(Command(1, 1));
    wait(received);
    c = received.read();
    data.set_player(c.get_id());
    data.set_weapon(c.get_data());

    display.displayText("player data received");
    hwlib::wait_ms(2000);

    display.displayText("Waiting for time");
    received.write(Command(0, 10));
    wait(received);
    c = received.read();
    if(c.get_id() == 0) {
        data.set_time(c.get_data());
    }
    display.displayText("game time received");
    hwlib::wait_ms(2000);
    char txt[] = "GAMETIME 10\n\nPlayer:  \nWeapon: id\n\nWaiting on start signal";
    if (data.get_time() < 10) {
        txt[9] = '0';
        txt[10] = (char) (48 + data.get_time());
    } else {
        txt[9] = (char) (48 + (data.get_time() / 10));
        txt[10] = (char) (48 + (data.get_time() % 10));
    }
    if (data.get_player() < 10) {
        txt[20] = '0';
        txt[21] = (char) (48 + data.get_player());
    } else {
        txt[20] = (char) (48 + (data.get_player() / 10));
        txt[21] = (char) (48 + (data.get_player() % 10));
    }
    if (data.get_weapon() < 10) {
        txt[31] = '0';
        txt[32] = (char) (48 + data.get_weapon());
    } else {
        txt[31] = (char) (48 + (data.get_weapon() / 10));
        txt[32] = (char) (48 + (data.get_weapon() % 10));
    }
    display.displayText(txt);
    received.write(Command(0,0));
    wait(received);
    hwlib::wait_ms(20000);
    wait(received);
    display.displayText("STARTING GAME in \n\n      5S");
    display.displayText("STARTING GAME in \n\n      4S");
    display.displayText("STARTING GAME in \n\n      3S");
    display.displayText("STARTING GAME in \n\n      2S");
    display.displayText("STARTING GAME in \n\n      1S");
    display.displayText("STARTING GAME in \n\n      0S");
    updateDisplay(true);
}

void PlayerTask::start() {
    gameTimer.clear();
    rtos::clock test(this, 1*rtos::s, "test tmer");
    for(;;) {
        auto event = wait(shoot + received + gameTimer + test);
        if(event == shoot) {
            hwlib::cout << "pew\n";
            sound.play_shoot();
        }
        else if(event == received) {
            hwlib::cout << "received command\n";
        }
        else if(event == gameTimer) {
            data.set_time(data.get_time()-1);
            if(data.get_time() < 0) {
                char txt[] = "\n\n   YOU SURVIVED \n    END SCORE \n\n      100";
                if(data.get_health() < 100) {
                    if (data.get_health() < 10) {
                        txt[41] = '0';
                        txt[42] = (char) (48 + data.get_health());
                    } else {
                        txt[41] = (char) (48 + (data.get_health() / 10));
                        txt[42] = (char) (48 + (data.get_health() % 10));
                    }
                    txt[43] = ' ';
                }
                display.displayText(txt);
            } else {
                updateDisplay(true);
            }

        }
    }
}

void PlayerTask::end() {
 
}

void PlayerTask::updateDisplay(bool alive) {
 if(!alive) {
        char txt[] = "\n\n\n   YOU'RE DEAD \n Remaining time \n\n      10";
        if (data.get_time() < 10) {
            txt[43] = '0';
            txt[44] = (char) (48 + data.get_time());
        } else {
            txt[43] = (char) (48 + (data.get_time() / 10));
            txt[44] = (char) (48 + (data.get_time() % 10));
        }
        display.displayText(txt);
    } else {
        char txt[] = "hp: 100\nminutes left: 00";
        hwlib::cout << data.get_time() << "\n";        
        if (data.get_time() < 10) {
            txt[22] = '0';
            txt[23] = (char) (48 + data.get_time());
        } else {
            txt[22] = (char) (48 + (data.get_time() / 10));
            txt[23] = (char) (48 + (data.get_time() % 10));
        }
        if(data.get_health() < 100) {
            if (data.get_health() < 10) {
                txt[4] = '0';
                txt[5] = (char) (48 + data.get_health());
            } else {
                txt[4] = (char) (48 + (data.get_health() / 10));
                txt[5] = (char) (48 + (data.get_health() % 10));
            }
            txt[6] = ' ';
        }
        display.displayText(txt);
    }  
}

void PlayerTask::button_pressed() {
    shoot.set();
}