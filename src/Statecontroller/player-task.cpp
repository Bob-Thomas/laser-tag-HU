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
    display.displayText("Starting game\nPress fire when\nthe game master\nnotifies you");
    wait(shoot);
    display.displayText("Waiting to\nreceive player\ndata");
    hwlib::wait_ms(2000);
    received.write('c');
    wait(received);
    display.displayText("player data received");
    received.read();
    hwlib::wait_ms(2000);
    received.write('c');
    wait(received);
    display.displayText("game time received");
    received.read();
    hwlib::wait_ms(2000);
    received.write('c');
    wait(received);
    display.displayText("time received\n");
    received.read();
    hwlib::wait_ms(2000);
    received.write('c');
    wait(received);
    display.displayText("GAMETIME 10\n\nPlayer: name\nWeapon: id\n\nWaiting on start signal ");
    received.read();
    hwlib::wait_ms(20000);
    received.write('c');
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
            data.setTime(data.getTime()-1);
            if(data.getTime() < 0) {
                char txt[] = "\n\n   YOU SURVIVED \n    END SCORE \n\n      100";
                if(data.getHealth() < 100) {
                    if (data.getHealth() < 10) {
                        txt[41] = '0';
                        txt[42] = (char) (48 + data.getHealth());
                    } else {
                        txt[41] = (char) (48 + (data.getHealth() / 10));
                        txt[42] = (char) (48 + (data.getHealth() % 10));
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
        if (data.getTime() < 10) {
            txt[43] = '0';
            txt[44] = (char) (48 + data.getTime());
        } else {
            txt[43] = (char) (48 + (data.getTime() / 10));
            txt[44] = (char) (48 + (data.getTime() % 10));
        }
        display.displayText(txt);
    } else {
        char txt[] = "hp: 100\nminutes left: 00";
        hwlib::cout << data.getTime() << "\n";        
        if (data.getTime() < 10) {
            txt[22] = '0';
            txt[23] = (char) (48 + data.getTime());
        } else {
            txt[22] = (char) (48 + (data.getTime() / 10));
            txt[23] = (char) (48 + (data.getTime() % 10));
        }
        if(data.getHealth() < 100) {
            if (data.getHealth() < 10) {
                txt[4] = '0';
                txt[5] = (char) (48 + data.getHealth());
            } else {
                txt[4] = (char) (48 + (data.getHealth() / 10));
                txt[5] = (char) (48 + (data.getHealth() % 10));
            }
            txt[6] = ' ';
        }
        display.displayText(txt);
    }  
}

void PlayerTask::button_pressed() {
    shoot.set();
}