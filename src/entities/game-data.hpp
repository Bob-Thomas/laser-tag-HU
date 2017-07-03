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

    void set_player(int id);
    int get_player();

    void set_weapon(int id);
    int get_weapon();

    void set_time(int time);
    int get_time();

    void set_health(int hp);
    int get_health();

    int getShotsFired() const;
    void increaseShotsFired();

    int getReceivedHits() const;
    void increaseReceivedHits();

    HitBy getHitByArrFromIndex(int i) const;
    void insertHitBy(int playerId, int weaponId);

    int getDamageWeaponId(int weaponId) const;
};
#endif