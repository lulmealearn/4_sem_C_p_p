#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "widget.hpp"

class Slider : public Widget {
private:
    sf::RectangleShape mTrackShape;
    sf::RectangleShape mThumbShape;
    bool mIsPressed{false};
    sf::RenderWindow& mRenderWindow;

public:
    Slider(sf::RenderWindow& window, sf::Vector2f centerPos, sf::Vector2f trackSize, sf::Vector2f thumbSize)
        : mRenderWindow{window} {
        mTrackShape.setSize(trackSize);
        mTrackShape.setOrigin(trackSize / 2.0f);
        mTrackShape.setPosition(centerPos);
        mTrackShape.setFillColor({200, 200, 220});

        mThumbShape.setSize(thumbSize);
        mThumbShape.setOrigin(thumbSize / 2.0f);
        mThumbShape.setPosition(centerPos);
        mThumbShape.setFillColor({150, 150, 240});
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            return onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            onMouseReleased();
        return false;
    }

    void draw() const override {
        mRenderWindow.draw(mTrackShape);
        mRenderWindow.draw(mThumbShape);
    }

    // ... остальные методы Slider остаются без изменений ...
};
