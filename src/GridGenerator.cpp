#include "GridGenerator.h"
#include <iostream>

sf::Vector2f GridGenerator::cartesianToIsometricTransform(const sf::Vector2f& cartesianPosition, const float size) {
    sf::Vector2f isometricPosition;
    isometricPosition.x = size * (cartesianPosition.x - cartesianPosition.y);
    isometricPosition.y = size * (cartesianPosition.x + cartesianPosition.y) / 2.f;
    return isometricPosition;
}

sf::Vector2f GridGenerator::isometricToCartesianTransform(const sf::Vector2f& isometricPosition, const float size) {
    sf::Vector2f cartesianPosition;
    cartesianPosition.x = (2.f * isometricPosition.y + isometricPosition.x) / (2 * size);
    cartesianPosition.y = (2.f * isometricPosition.y - isometricPosition.x) / (2 * size);
    return cartesianPosition;
}


//sf::Vector2f GridGenerator::mouseToIsometric(const sf::Vector2i& mouseCoords)
//{
//    std::cout << "HERE5";
//    const float spriteDimension = 100.0f;
//    float det = 1.0f / (1 * 0.5 - 0 * -1);
//    sf::Vector2f isometricCoords;
//    isometricCoords.x = (mouseCoords.x / spriteDimension) - 8 * (mouseCoords.y / spriteDimension);
//    isometricCoords.y = 8 * (mouseCoords.x / spriteDimension) + (mouseCoords.y / spriteDimension);
//    return isometricCoords;
//}
//
//
//sf::Vector2f GridGenerator::cellSelector(const sf::Vector2f cartesianCell, int corner)
//{
//    std::cout << "HERE4";
//    sf::Vector2f selectedCell;
//    const sf::Vector2f origin = { 1,0 };
//    selectedCell.x = (cartesianCell.y - origin.y) + (cartesianCell.x - origin.x);
//    selectedCell.y = (cartesianCell.y - origin.y) - (cartesianCell.x - origin.x);
//    if (corner == 1) selectedCell.x = selectedCell.x - 1;
//    if (corner == 2) selectedCell.y = selectedCell.y - 1;
//    if (corner == 3) selectedCell.x = selectedCell.x + 1;
//    if (corner == 4) selectedCell.y = selectedCell.y + 1;
//    return selectedCell;
//}
//
//sf::Vector2f GridGenerator::mouseCellCalc(const sf::Vector2f mouseCoord)
//{
//    std::cout << "HERE3";
//    sf::Vector2f mouseCellPosition;
//    int tileWidth = 100;
//    int tileHeight = 50;
//    mouseCellPosition.x = ((int)mouseCoord.x - 50) % tileWidth;
//    mouseCellPosition.y = (int)mouseCoord.y % tileHeight;
//    return mouseCellPosition;
//}
//
//int GridGenerator::isInsideTriangle(sf::Vector2f mousePos)
//{
//    std::cout << "HERE2";
//    sf::Vector2f A(50.f, 0.f);
//    sf::Vector2f B(100.f, 25.f);
//    sf::Vector2f C(50.f, 50.f);
//    sf::Vector2f D(0.f, 25.f);
//
//    sf::Vector2f directionAD = A - D;
//    sf::Vector2f vectorToMouseAD = mousePos - A;
//    float crossProductAD = directionAD.x * vectorToMouseAD.y - directionAD.y * vectorToMouseAD.x;
//    if (crossProductAD <= 0.f) return 1;
//
//    sf::Vector2f directionAB = A - B;
//    sf::Vector2f vectorToMouseAB = mousePos - A;
//    float crossProductAB = directionAB.x * vectorToMouseAB.y - directionAB.y * vectorToMouseAB.x;
//    if (crossProductAB > 0.f) return 2;
//
//    sf::Vector2f directionBC = B - C;
//    sf::Vector2f vectorToMouseBC = mousePos - B;
//    float crossProductBC = directionBC.x * vectorToMouseBC.y - directionBC.y * vectorToMouseBC.x;
//    if (crossProductBC > 0.f) return 3;
//
//    sf::Vector2f directionCD = C - D;
//    sf::Vector2f vectorToMouseCD = mousePos - C;
//    float crossProductCD = directionCD.x * vectorToMouseCD.y - directionCD.y * vectorToMouseCD.x;
//    if (crossProductCD > 0.f) return 4;
//
//    return 0;
//}
//
//sf::Vector2f GridGenerator::isometricToScreenPosition(sf::Vector2f isometricPosition)
//{
//    std::cout << "HERE1";
//
//    const float tileWidth = 100.0f;
//    const float tileHeight = 50.0f;
//    float screenX = (isometricPosition.x - isometricPosition.y) * 0.5f * tileWidth;
//    float screenY = (isometricPosition.x + isometricPosition.y) * 0.5f * tileHeight;
//    sf::Vector2f screenPosition(screenX, screenY);
//    return screenPosition;
//}