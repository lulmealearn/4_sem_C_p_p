#pragma once
#include <SFML/Graphics.hpp>

class Widget {
public:
    virtual ~Widget() = default;
    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual void draw() const = 0;
};
