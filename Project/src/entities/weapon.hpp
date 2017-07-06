/**
 * \file      weapon.hpp
 * \author    Robbie Valkenburg
 * \brief     Class that will store information for a single weapon.
 * \copyright Copyright (c) 2017, Lasertak
 */

#ifndef LASER_WEAPON_HPP
#define LASER_WEAPON_HPP

/**
 * \brief class that holds weapon information id,damage,cooldown
 */
class Weapon {
private:
    /// Name of the weapon.
    const char* name;
    /// Amount of damage that the weapon will do.
    int damage = 0;
    /// Cooldown in milliseconds for the gun to shoot again.
    int cooldownInMilliSeconds = 0;
public:
    /*
     * \brief Constructor for class.
     * \param   Name of the gun.
     * \param   Damage that the gun can offer.
     * \param   Cooldown for next shot.
     */
    Weapon(const char* name, int damage, int cooldownInMilliSeconds);

    /*
     * @return The name of the gun.
     */
    const char * getName() const;

    /*
     * @return Damage of the gun.
     */
    int getDamage() const;

    /*
     * @return Cooldown in milliseconds.
     */
    int getCooldownInMilliSeconds() const;
};


#endif //LASER_WEAPON_HPP
