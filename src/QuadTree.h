#pragma once
#include <array>
#include "SFML/Graphics/Rect.hpp"
#include <vector>
#include <list>

struct QuadTree {
    virtual void f() {};

    unsigned int depth;
    sf::IntRect quadRect;
    std::array<QuadTree*, 4> children;

    QuadTree(const sf::IntRect& rect, const unsigned int& depth)
        : depth(depth), quadRect(rect), children{ nullptr, nullptr, nullptr, nullptr } {}

    ~QuadTree() {
        for (QuadTree* child : children)
            delete[] child;
    }
};

struct QuadTreeLeaf : public QuadTree {
    std::vector<MapCell>::iterator cellIter;
    std::vector<std::list<Agent>::iterator> agentIters;

    QuadTreeLeaf(const sf::IntRect& rect, const unsigned int& depth, std::vector<MapCell>::iterator& _iter)
        : QuadTree(rect, depth), cellIter(_iter), agentIters(std::vector<std::list<Agent>::iterator>()) {}
};