/**
 * \file      arsenal.hpp
 * \author    Robbie Valkenburg
 * \brief     Class for getting weapon information.
 * \copyright Copyright (c) 2017, Lasertak
 */

#ifndef LASER_ARSENAL_HPP
#define LASER_ARSENAL_HPP

#include "weapon.hpp"

class Arsenal {
private:
    /// A list of Weapons that the player can use during game.
    const Weapon weapons [3] = {
            {"F40 LaserSpray", 7, 1},
            {"BeamGunner", 14, 2},
            {"SonicBlaster", 35, 4}
    };
public:
    /// Get a single instance of a Weapon class by id.
    Weapon getWeaponById(int id) const;
};


#endif //LASER_ARSENAL_HPP
