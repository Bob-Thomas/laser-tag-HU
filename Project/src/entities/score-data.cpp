/**
 * \file      score-data.cpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */
#include "score-data.hpp"

ScoreData::ScoreData() {
    empty();
}

void ScoreData::empty() {
    for(auto player : scores) {
        player = {0, 0, 0};
    }
    filledScores = 0;
}

void ScoreData::add(int id, int weapon, bool alive) {
    int index = getIndex(id);
    if(index == -1) {
        scores[filledScores] = {alive, id, 0};
        filledScores++;
    } else {
        scores[index].alive = alive;
    }
    scores[index].score += arsenal.getWeaponById(weapon).getDamage();
}

void ScoreData::printScores() {
    hwlib::cout << "SCORE LIST\n\n";
    hwlib::cout << "WINNNER: " << getWinner().id << ": " << getWinner().score << "\n\n";
    hwlib::cout  << "PLAYER | SCORE | ALIVE\n\n";
    for(auto player : scores) {
        if(player.id != -1) {
            hwlib::cout << player.id << "     " << player.score << "      " << ((player.alive) ? "YES" : "NO") << "\n";
        }
    }
}

int ScoreData::getIndex(int id) {
    for(int i = 0; i < 32; i++) {
        if(scores[i].id == id) {
            return i;
        }
    }
    return -1;
}

PlayerScore ScoreData::getWinner() {
    PlayerScore tempScore = {0, 0, 0};
    for(auto player : scores) {
        if(player.id != 0) {
            if(player.score > tempScore.score) {
                tempScore.score = player.score;
                tempScore.id = player.id;
            }
        }
    }
    return tempScore;
}