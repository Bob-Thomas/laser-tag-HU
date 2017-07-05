/**
 * \file      game-data.hpp
 * \author    Bob Thomas
 * \brief     Class to save and get game data
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP
#include "arsenal.hpp"

struct {
    int playerId;
    int WeaponId;
} typedef HitBy;

class GameData {
private:
    int playerId = -1;
    int weaponId = -1;
    int health = 100;
    int endTime = 25;
    int shotsFired = 0;
    int receivedHits = 0;
    HitBy hitByArr[10];
    Arsenal arsenal;
public:
    GameData();

    void setPlayerId(int id);
    int getPlayerId() const;

    void setWeaponId(int id);
    int getWeaponId() const;

    void setTime(int time);
    int getTime() const;

    void setHealth(int hp);
    int getHealth() const;

    int getShotsFired() const;
    void increaseShotsFired();

    int getReceivedHits() const;

    HitBy getHitByArrFromIndex(int i) const;
    void insertHitBy(int playerId, int weaponId);

    int getDamageWeaponId(int weaponId) const;
};
#endif