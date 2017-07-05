/**
 * \file      arsenal.hpp
 * \author    Robbie Valkenburg
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "arsenal.hpp"

Weapon Arsenal::getWeaponById(int id) const {
    return weapons[id];
}