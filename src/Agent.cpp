#include "Agent.h"

Agent::Agent(float _x, float _y)
    : unit(""), health(0), morale(0), x(_x), y(_y) {
    texture = new sf::Texture();
    texture->loadFromFile("resources/images/agents/HDman.png");
    texture->generateMipmap();
}

Agent::~Agent() {}

std::string Agent::getUnit() const {
    return unit;
}

void Agent::setUnit(const std::string& newUnit) {
    unit = newUnit;
}

int Agent::getHealth() const {
    return health;
}

void Agent::setHealth(int newHealth) {
    health = newHealth;
}

int Agent::getMorale() const {
    return morale;
}

void Agent::setMorale(int newMorale) {
    morale = newMorale;
}
