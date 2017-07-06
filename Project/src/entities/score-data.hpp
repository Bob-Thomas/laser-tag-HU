/**
 * \file      score-data.hpp
 * \author    Bob Thomas
 * \brief     class to store our player scores in and show the score list at the end
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef SCORE_DATA_HPP
#define SCORE_DATA_HPP
#include "hwlib.hpp"
#include "arsenal.hpp"

/**
 * \brief datatype to save our Scores in
 */
struct {
    bool alive = false;
    int id = -1;
    int score = 0;
} typedef PlayerScore;

/**
 * \brief Entity class to store and retrieve player scores
 */
class ScoreData {
private:
  /// Array with the max amount of available players
  PlayerScore scores[32];
  /// Indicator on how many scores have been received
  int filledScores = 0;
  /// Access to the weapons
  Arsenal arsenal;
public:
    /**
     * \brief constructor for the Score class
     */
    ScoreData();
    /**
     * \brief Function to erase all the scores in the list
     */
    void empty();
    /**
     * \brief add a score to the list
     * \param[in] id id of the player you want to add score for
     * \param[in] weapon id of the weapon the player
     * \param[in] alive if the player is alive or not
     */
    void add(int id, int weapon, bool alive = false);
    /**
     * \brief cout a nice list of scores and players with the winner
     */
    void printScores();
    /**
     * \brief returns the winner the player with the highest score and still alive
     */
    PlayerScore getWinner();
};
#endif  //SCORE_DATA_HPP