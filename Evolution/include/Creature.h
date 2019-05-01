#ifndef CREATURE_H
#define CREATURE_H

#include <stdint.h>
#include "AngularVector.h"

#ifndef DECIMALS
#define DECIMALS 1000
#endif

class Creature
{
    public:
        Creature();
        virtual ~Creature();
        void adjustSpeed();
        void calculateDependentStats();
        void setInheritedStats(uint64_t muscleHead, uint64_t muscleLegs, uint64_t maxShortTermEnergy, uint64_t maxStomackMass, uint64_t armor);
        void setStartStats();

    protected:

    private:
        uint64_t age;                               //s
        uint64_t armor;                             //W
        uint64_t fertilityAge;                      //s
        uint64_t gestationTime;                     //s
        uint64_t goalPosX;                          //m
        uint64_t goalPosY;                          //m
        uint64_t health;                            //HP
        uint64_t longTermEnergy;                    //J
        uint64_t longToShortEnergyRate;             //J/s
        uint64_t mass;                              //Kg
        uint64_t maxAge;                            //s
        uint64_t maxGestationTime;                  //s
        uint64_t maxHealth;                         //HP
        uint64_t maxLegForce;                       //W
        uint64_t maxShortTermEnergy;                //J
        uint64_t maxStomackMass;                    //Kg
        uint64_t muscleHead;                        //W
        uint64_t muscleLegs;                        //W
        uint64_t posX;                              //m
        uint64_t posY;                              //m
        uint64_t regen;                             //%/s
        uint64_t shortTermEnergy;                   //J
        AngularVector speed;                        //m/s
        uint64_t stomackMass;                       //Kg
        uint64_t stomackToLongEnergyRate;           //J/s
        uint64_t stomackToShortEnergyRate;          //J/s
};

#endif // CREATURE_H
