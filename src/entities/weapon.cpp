/**
 * \file      weapon.hpp
 * \author    Robbie Valkenburg
 * \copyright Copyright (c) 2017, Lasertak
 */

#include "weapon.hpp"

Weapon::Weapon(const char *name, int damage, int cooldownInSeconds) : name(name), damage(damage), cooldownInMilliSeconds(cooldownInSeconds) {

}

const char* Weapon::getName() const {
    return name;
}

int Weapon::getDamage() const {
    return damage;
}

int Weapon::getCooldownInMilliSeconds() const {
    return cooldownInMilliSeconds;
}