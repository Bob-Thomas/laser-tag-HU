//
// Created by robbie on 3-7-2017.
//

#ifndef LASER_ARSENAL_HPP
#define LASER_ARSENAL_HPP

#include "weapon.hpp"

class Arsenal {
private:
    const Weapon weapons [3] = {
            {"F40 LaserSpray", 7, 1},
            {"BeamGunner", 14, 2},
            {"SonicBlaster", 35, 4}
    };
public:
    Weapon getWeaponById(int id) const;
};


#endif //LASER_ARSENAL_HPP
