/**
 * \file      game-data.hpp
 * \author    Bob Thomas
 * \brief     Class to save and get game data.
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP
#include "arsenal.hpp"
/**
 * \struct HitBy
 * \brief simple struct to maintain the received player id and weapon id.
 */
struct {
    int playerId;
    int weaponId;
} typedef HitBy;

class GameData {
private:
    /// Player id for the client.
    int playerId = -1;
    /// Weapon id that client uses.
    int weaponId = -1;
    /// Current health left.
    int health = 100;
    /// End time in minutes.
    int endTime = 25;
    /// Amount of shots that fired during game from the client side.
    int shotsFired = 0;
    /// Amount of incoming hits that are received.
    int receivedHits = 0;
    /// Array will store the incoming hits with the received player id and weapon id.
    HitBy hitByArr[10];
    /// Arsenal class will be used for getting information about the gun.
    Arsenal arsenal;
public:
    /**
    * \brief Constructor for class GameData.
    */
    GameData();

    /**
    * \brief Function to set player id when received from the game master.
    * \param Id that will be set to the player.
    */
    void setPlayerId(int id);

    /**
     * @return Player id.
     */
    int getPlayerId() const;

    /*
     * \brief Function to set the weapon id.
     */
    void setWeaponId(int id);

    /**
     * @return Weapon id.
     */
    int getWeaponId() const;

    /*
     * \brief Set the game duration in minutes.
     */
    void setTime(int time);

    /**
     * @return The time left in minutes of game.
     */
    int getTime() const;

    /*
     * \brief Setter function for health.
     */
    void setHealth(int hp);

    /**
     * @return Current health left of the player.
     */
    int getHealth() const;

    /**
     * @return Amount of shots that are fired by player.
     */
    int getShotsFired() const;

    /**
     * \brief Simple function that will increase the amount of shots fired by 1.
     */
    void increaseShotsFired();

    /**
     * @return Amount of incoming hits that are received by player.
     */
    int getReceivedHits() const;

    /**
     * \brief Get a single received hit information.
     * \param The index of the list that will determine the structure to return.
     * @return A structure that contains each received player id and weapon id.
     */
    HitBy getHitByArrFromIndex(int i) const;

    /**
    * \brief Store the player id and weapon id in to the list of received hits.
    * \param Received player id.
    * \param Received weapon id.
    * @return Damage of the weapon.
    */
    void insertHitBy(int playerId, int weaponId);

    /**
     * \brief Simple function that will return the damage of a weapon by id.
     * @return Damage of the weapon.
     */
    int getDamageWeaponId(int weaponId) const;
};
#endif