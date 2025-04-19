#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "widget.hpp"

class Button : public Widget {
private:
    sf::Color mDefaultColor{179, 230, 255};
    sf::Color mHoverColor{128, 212, 255};
    sf::Color mPressedColor{0, 136, 204};
    sf::RectangleShape mShape;
    sf::Text mText;
    bool mIsPressed{false};
    sf::RenderWindow& mRenderWindow;

public:
    Button(sf::RenderWindow& window, sf::FloatRect rect, sf::Font& font, const sf::String& textData)
        : mRenderWindow{window} {
        mShape.setPosition({rect.left, rect.top});
        mShape.setSize({rect.width, rect.height});
        mShape.setFillColor(mDefaultColor);

        mText.setFont(font);
        mText.setString(textData);
        mText.setFillColor(sf::Color::Black);
        mText.setCharacterSize(30);
        
        auto calculateOptimalFontSize = [this]() {
            float widthFraction = 0.6f;
            float heightFraction = 0.4f;
            sf::FloatRect textBounds = mText.getLocalBounds();
            float widthRatio = mShape.getSize().x / textBounds.width * widthFraction;
            float heightRatio = mShape.getSize().y / textBounds.height * heightFraction;
            return static_cast<unsigned>(std::min(widthRatio, heightRatio) * mText.getCharacterSize();
        };
        
        mText.setCharacterSize(calculateOptimalFontSize());
        centerText();
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::MouseMoved)
            onMouseMove(event);
        else if (event.type == sf::Event::MouseButtonPressed)
            onMousePressed(event);
        else if (event.type == sf::Event::MouseButtonReleased)
            return onMouseReleased(event);
        return false;
    }

    void draw() const override {
        mRenderWindow.draw(mShape);
        mRenderWindow.draw(mText);
    }

private:
    void centerText() {
        sf::FloatRect textBounds = mText.getLocalBounds();
        mText.setOrigin(textBounds.left + textBounds.width/2.0f, textBounds.top + textBounds.height/2.0f);
        mText.setPosition(mShape.getPosition() + mShape.getSize()/2.0f);
    }

    void onMouseMove(const sf::Event& event) {
        if (mIsPressed) return;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
        mShape.setFillColor(mShape.getGlobalBounds().contains(mousePos) ? mHoverColor : mDefaultColor);
    }

    void onMousePressed(const sf::Event& event) {
        if (event.mouseButton.button != sf::Mouse::Left) return;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (mShape.getGlobalBounds().contains(mousePos)) {
            mIsPressed = true;
            mShape.setFillColor(mPressedColor);
        }
    }

    bool onMouseReleased(const sf::Event& event) {
        if (!mIsPressed) return false;
        mIsPressed = false;
        sf::Vector2f mousePos = mRenderWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        bool clicked = mShape.getGlobalBounds().contains(mousePos);
        mShape.setFillColor(clicked ? mHoverColor : mDefaultColor);
        return clicked;
    }
};
