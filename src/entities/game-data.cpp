#include "game-data.hpp"
GameData::GameData()
{
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