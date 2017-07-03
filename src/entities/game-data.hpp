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

    void setPlayer(int id);

    int getPlayer();

    void setWeapon(int id);

    int getWeapon();

    void setTime(int time);

    int getTime();

    void setHealth(int hp);

    int getHealth();

    
};
#endif