#pragma once
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>

class Agent {
private:
    std::string unit;
    int health;
    int morale;

public:
    Agent(float _x, float _y);
    ~Agent();

    void setUnit(const std::string& agentUnit);
    void setStance(const std::string& agentStance);
    void setHealth(int agentHealth);
    void setMorale(int agentMorale);
    void setPinned(bool agentPinned);
    void setAmmo(int agentAmmo);

    float x, y;
    sf::Texture* texture;

    std::string getUnit() const;
    std::string getStance() const;
    int getHealth() const;
    int getMorale() const;
    bool isPinned() const;
    int getAmmo() const;
};
