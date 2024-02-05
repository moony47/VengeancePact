#pragma once
#include <SFML/System.hpp>

static struct GridGenerator {
    static sf::Vector2f cartesianToIsometricTransform(const sf::Vector2f& cartesianPosition, const float size);
    static sf::Vector2f isometricToCartesianTransform(const sf::Vector2f& isometricPosition, const float size);
    static sf::Vector2f mouseToIsometric(const sf::Vector2i& mouseCoords);
    static sf::Vector2f cellSelector(const sf::Vector2f cartesianCell, int corner);
    static sf::Vector2f mouseCellCalc(const sf::Vector2f mouseCoord);
    static int isInsideTriangle(sf::Vector2f mousePos);
    static sf::Vector2f isometricToScreenPosition(sf::Vector2f isometricPosition);
};


