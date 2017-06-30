#include "player-task.hpp"

PlayerTask::PlayerTask(SoundController& sound, DisplayController& display): task("Player task"), sound(sound), display(display), shoot(this, "shoot-flag"), received(this, "received channel"), gameTimer(this, 5*rtos::s, "gametimer") {

}

void PlayerTask::main() {
    for(;;) {
        init();
        start();
        end();
    }
}

void PlayerTask::init() {
    display.displayText("Starting game\n Press fire when the game master notifies you");
    wait(shoot);
    display.displayText("Waiting to receive player data");
    wait(received);
    display.displayText("player data received");
    wait(received);
    display.displayText("game time received");
    wait(received);
    display.displayText("time received\n");
    sleep(500*rtos::ms);
    display.displayText("\tGAMETIME 10\nPlayer: name \n Weapon: id\n\n Waiting on start signal ");
    wait(received);
    display.displayText("STARTING GAME in \n\n      5S");
    display.displayText("STARTING GAME in \n\n      4S");
    display.displayText("STARTING GAME in \n\n      3S");
    display.displayText("STARTING GAME in \n\n      2S");
    display.displayText("STARTING GAME in \n\n      1S");
    display.displayText("STARTING GAME in \n\n      0S");
}

void PlayerTask::start() {
    gameTimer.clear();
    for(;;) {
        auto event = wait(shoot + received + gameTimer);
        if(event == shoot) {
            hwlib::cout << "pew\n";
            sound.play_shoot();
        }
        else if(event == received) {
            hwlib::cout << "received command\n";
        }
        else if(event == gameTimer) {
            data.setTime(data.getTime()-5);
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