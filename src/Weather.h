#pragma once
#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

class Weather {
public:
    struct Cloud {
        sf::Vector2f pos = sf::Vector2f(0, 0);
        sf::Vector2f pos2 = sf::Vector2f(0, 0);
        sf::Vector2f pos3 = sf::Vector2f(0, 0);
        float size = 0;
    };

public:
    void initCloudShader() {
        if (!cloudShader.loadFromFile("resources/shaders/spotlight.vert", "resources/shaders/cloudShadows.frag"))
            std::cerr << "[SHADER][CAMERA] Failed to load cloud shader";
    }

    void cloudShaderUpdate() {
        sf::Vector2f poss[20];
        sf::Vector2f pos2s[20];
        sf::Vector2f pos3s[20];
        float sizes[20];
        for (int i = 0; i < 20; i++) {
            poss[i] = clouds[i].pos;
            pos2s[i] = clouds[i].pos + clouds[i].pos2;
            pos3s[i] = clouds[i].pos + clouds[i].pos3;
            sizes[i] = clouds[i].size * scale;
        }

        cloudShader.setUniformArray("cloudPos", poss, 20);
        cloudShader.setUniformArray("cloudPos2", pos2s, 20);
        cloudShader.setUniformArray("cloudPos3", pos3s, 20);
        cloudShader.setUniformArray("cloudSize", sizes, 20);
    }

    sf::Shader* getCloudShader(sf::Texture& _texture) {
        cloudShader.setUniform("texture", _texture);
        return &cloudShader; 
    }

    void setCloud(unsigned int index, sf::Vector2f _pos, sf::Vector2f _pos2, sf::Vector2f _pos3, float _size) { clouds[index] = { _pos, _pos2, _pos3, _size }; }
    void moveCloud(unsigned int index, sf::Vector2f _pos) { clouds[index].pos += _pos; }
    void scaleClouds(float _scale) { scale = _scale; }

private:
    std::array<Cloud, 20> clouds;
    sf::Shader cloudShader;
    float scale = 1.f;
};