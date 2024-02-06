#pragma once
#include <array>
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include <list>

#include "MapCell.h"

struct QuadTree {
    virtual void f() {};

    unsigned int depth;
    sf::FloatRect quadRect;
    std::array<QuadTree*, 4> children;

    QuadTree(const sf::FloatRect _rect, const unsigned int _depth)
        : depth(_depth), quadRect(_rect), children{ nullptr, nullptr, nullptr, nullptr } {}

    ~QuadTree() {
        delete[] & children;
    }
};

struct QuadTreeCell : public QuadTree {
    ~QuadTreeCell() {
        delete[] & cellIter;
        delete[] & agentIters;
    }

    std::vector<MapCell>::iterator cellIter;
    std::vector<std::list<Agent>::iterator> agentIters;

    QuadTreeCell(const sf::FloatRect _rect, const unsigned int _depth, const std::vector<MapCell>::iterator& _iter)
        : QuadTree(_rect, _depth), cellIter(_iter), agentIters(std::vector<std::list<Agent>::iterator>()) {}
};

struct QuadTreeNav : public QuadTree {
    ~QuadTreeNav() {
    }

    std::vector<QuadTreeNav*> neighbours;
    float walkability;

    QuadTreeNav(const sf::FloatRect _rect, const unsigned int _depth, const float _walkability = 1.f)
        : QuadTree(_rect, _depth), walkability(_walkability), neighbours({ nullptr, nullptr, nullptr, nullptr }) {}

    void setNeighbours(std::vector<QuadTreeNav*> _neighbours) { neighbours = _neighbours; }

    //For use by MovementManager
    bool visited = false;
    QuadTreeNav* prev = nullptr;
    float g = FLT_MAX, h = 0;

    void initialiseNavNode(float _h) {
        visited = true;
        h = _h;
    }
};