/**
 * \file      game-data.hpp
 * \author    Bob Thomas
 * \brief     Class to save and get game data
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP
class GameData {
private:
    int playerId = -1;
    int weaponId = -1;
    int health = 100;
    int endTime = 25;
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

    
};
#endif