#include "Creature.h"

Creature::Creature()
{
    //Sets stats common for all creatures
    fertilityAge = 120000;
    longToShortEnergyRate = 1000;
    maxAge = 1200000;
    maxGestationTime = 30000;
    regen = 500;
    stomackToLongEnergyRate = 1000;
    stomackToShortEnergyRate = 1000;
}

Creature::~Creature()
{
    //dtor
}

void Creature::adjustSpeed()
{
    AngularVector goalDir(goalPosX-posX, goalPosY-posY);
    AngularVector kineticEnergy(speed.angle, mass*speed.length*speed.length/2/DECIMALS/DECIMALS);
    uint64_t ortogonalLength = kineticEnergy.length * sin(kineticEnergy.angle - goalDir.angle);
    uint64_t force = maxLegForce *
}

void Creature::calculateDependentStats()
{
    //Sets stats dependent on other stats
    mass = muscleHead*muscleHead + muscleLegs*muscleLegs + maxShortTermEnergy*maxShortTermEnergy + maxStomackMass/10 + stomackMass + armor*armor + longTermEnergy/10;
    uint64_t oldMaxHealth = maxHealth;
    maxHealth = mass;
    mass = mass + maxHealth - oldMaxHealth;
}

void Creature::setInheritedStats(uint64_t muscleHead, uint64_t muscleLegs, uint64_t maxShortTermEnergy, uint64_t maxStomackMass, uint64_t armor)
{
    //Sets inherited stats
    this->muscleHead = muscleHead;
    this->muscleLegs = muscleLegs;
    this->maxShortTermEnergy = maxShortTermEnergy;
    this->maxStomackMass = maxStomackMass;
    this->armor = armor;
}

void Creature::setStartStats()
{
    age = fertilityAge;
    gestationTime = 0;
    goalPosX = 0;
    goalPosY = 0;
    longTermEnergy = maxShortTermEnergy;
    maxLegForce = muscleLegs;
    posX = goalPosX;
    posY = goalPosY;
    shortTermEnergy = maxShortTermEnergy;
    speed.angle = 0;
    speed.length = 0;
    stomackMass = 0;
    calculateDependentStats();
    health = maxHealth;
}
