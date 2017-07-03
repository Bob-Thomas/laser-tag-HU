/**
 * \file      game-data.cpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "game-data.hpp"
GameData::GameData() {
}

void GameData::set_player(int id) {
    playerId = id;
}

int GameData::get_player() {
    return playerId;
}

void GameData::set_weapon(int id) {
    weaponId = id;
}

int GameData::get_weapon() {
    return weaponId;
}

void GameData::set_time(int time)
{
    endTime = time;
}

int GameData::get_time() {
    return endTime;
}

void GameData::set_health(int hp) {
    health =hp ;
}

int GameData::get_health() {
    return health;
}

int GameData::getShotsFired() const {
    return shotsFired;
}

void GameData::increaseShotsFired() {
    shotsFired++;
}

int GameData::getReceivedHits() const {
    return receivedHits;
}

void GameData::increaseReceivedHits() {
    receivedHits++;
}

void GameData::insertHitBy(int playerId, int weaponId) {
    hitByArr[receivedHits] = {playerId, weaponId};
    health -= arsenal.getWeaponById(weaponId).getDamage();
}

HitBy GameData::getHitByArrFromIndex(int i) const {
    return hitByArr[i];
}