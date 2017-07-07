/**
 * \file      game-data.cpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "game-data.hpp"
GameData::GameData() {
}

void GameData::setPlayerId(int id) {
    playerId = id;
}

int GameData::getPlayerId() const {
    return playerId;
}

void GameData::setWeaponId(int id) {
    weaponId = id;
}

int GameData::getWeaponId() const {
    return weaponId;
}

void GameData::setTime(int time) {
    endTime = time;
}

int GameData::getTime() const {
    return endTime;
}

void GameData::setHealth(int hp) {
    health =hp;
}

int GameData::getHealth() const {
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

void GameData::insertHitBy(int playerId, int weaponId) {
    hitByArr[receivedHits++] = {playerId, weaponId};
    health -= arsenal.getWeaponById(weaponId).getDamage();
}

int GameData::getWeaponDamageById(int weaponid) const {
    return arsenal.getWeaponById(weaponId).getDamage();
}
int GameData::getWeaponCooldownById(int weaponid) const {
    return arsenal.getWeaponById(weaponId).getCooldownInMilliSeconds();
}

const char* GameData::getWeaponNameById(int weaponid) const {
    return arsenal.getWeaponById(weaponId).getName();
}

HitBy GameData::getHitByArrFromIndex(int i) const {
    return hitByArr[i];
}