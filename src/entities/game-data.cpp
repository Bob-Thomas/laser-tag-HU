/**
 * \file      game-data.cpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "game-data.hpp"
GameData::GameData()
{
}

GameData::GameData(int playerId, int weaponId) : playerId(playerId), weaponId(weaponId) {

}

void GameData::setPlayer(int id)
{
    playerId = id;
}

int GameData::getPlayer()
{
    return playerId;
}

void GameData::setWeapon(int id)
{
    weaponId = id;
}

int GameData::getWeapon() {
    return weaponId;
}

void GameData::setTime(int time)
{
    endTime = time;
}

int GameData::getTime() {
    return endTime;
}

void GameData::setHealth(int hp) {
    health =hp ;
}

int GameData::getHealth() {
    return health;
}