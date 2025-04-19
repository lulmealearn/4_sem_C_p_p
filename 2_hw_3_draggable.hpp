#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "widget.hpp"

class Draggable : public Widget {
private:
    sf::RectangleShape mShape;
    bool mIsDragged{false};
    sf::Vector2f mOffset{0.0f, 0.0f};
    sf::RenderWindow& mRenderWindow;

public:
    Draggable(sf::RenderWindow& window, sf::Vector2f pos, sf::Vector2f size, sf::Color color)
        : mRenderWindow{window} {
        mShape.setPosition(pos);
        mShape.setSize(size);
        mShape.setFillColor(color);
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
            return onMousePressed(mousePos);
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            onMouseReleased();
        }
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
            onMouseMoved(mousePos);
        }
        return false;
    }

    void draw() const override {
        mRenderWindow.draw(mShape);
    }

    // ... остальные методы Draggable остаются без изменений ...
};
