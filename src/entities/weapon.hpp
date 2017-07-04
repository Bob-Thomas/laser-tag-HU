//
// Created by robbie on 3-7-2017.
//

#ifndef LASER_WEAPON_HPP
#define LASER_WEAPON_HPP


class Weapon {
private:
    const char* name;
    int damage;
    int cooldownInMilliSeconds;
public:
    Weapon(const char* name, int damage, int cooldownInSeconds);
    const char * getName() const;
    int getDamage() const;
    int getCooldownInMilliSeconds() const;
};


#endif //LASER_WEAPON_HPP
