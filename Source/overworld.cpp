﻿#include <iostream>
#include "sfml.h"
#include "overworld.h"
#include "constants.h"
#include "game.h"

namespace Harley
{
    Overworld::Overworld ()
    {
        tiles.load("Resources/anais.png");
        map.load_chunks("Resources/beauve", 1440, 960, 3, 3);
        movingRight = false;
        movingUp = false;
        movingLeft = false;
        movingDown = false;
        speed = BASE_SPEED;
    }

    void Overworld::redraw(sf::RenderWindow& window, Player& character)
    {
        int startX = std::max(0, (character.getTileX()/TILE_SIZE)-(TILE_WIDTH+1)/2);
        int startY = std::max(0, (character.getTileY()/TILE_SIZE)-(TILE_HEIGHT+1)/2);
        int endX = std::min(map.width(), startX+TILE_WIDTH);
        int endY = std::min(map.height()-1, startY+TILE_HEIGHT);
        startX = endX - TILE_WIDTH;
        startY = endY - TILE_HEIGHT;
        int centerX = std::max(std::min(character.getTileX(), map.width()*TILE_SIZE-SCREEN_WIDTH/2), SCREEN_WIDTH/2);
        int centerY = std::max(std::min(character.getTileY(), map.height()*TILE_SIZE-SCREEN_HEIGHT/2), SCREEN_HEIGHT/2);
        // std::cout << endX << ", " << endY << ", " << character->getTileX() / TILE_SIZE << ", " << character->getTileY() / TILE_SIZE << std::endl;
        for (int i = startX; i <= endX; i++) {
        	for (int j = startY; j <= endY; j++) {
        		int tile = map.tileAt(i, j);
                tiles.renderTile(tile, (TILE_SIZE*i)-centerX + SCREEN_WIDTH/2, (TILE_SIZE*j)-centerY+SCREEN_HEIGHT/2, window);
        	}
        }
        // character->next_animation();
        sf::Sprite sprite = character.direction(movingRight-movingLeft, movingDown-movingUp);
        sprite.setPosition((character.getTileX()-centerX+SCREEN_WIDTH/2)*SCALE, (character.getTileY()-centerY+SCREEN_HEIGHT/2)*SCALE);
        window.draw(sprite);
    }

    void Overworld::startUp(){
        movingUp = true;
        movingDown = false;
        if (movingLeft || movingRight) {
            speed = DIAGONAL_SPEED;
        }
    }

    void Overworld::startDown(){
        movingDown = true;
        movingUp = false;
        if (movingLeft || movingRight) {
            speed = DIAGONAL_SPEED;
        }
    }

    void Overworld::startLeft(){
        movingLeft = true;
        movingRight = false;
        if (movingUp || movingDown) {
            speed = DIAGONAL_SPEED;
        }
    }

    void Overworld::startRight ()
    {
        movingRight = true;
        movingLeft = false;
        if (movingUp || movingDown) {
            speed = DIAGONAL_SPEED;
        }
    }

    void Overworld::stopUp(){
        movingUp = false;
        speed = BASE_SPEED;
    }

    void Overworld::stopDown(){
        movingDown = false;
        speed = BASE_SPEED;
    }

    void Overworld::stopLeft(){
        movingLeft = false;
        speed = BASE_SPEED;
    }

    void Overworld::stopRight ()
    {
        movingRight = false;
        speed = BASE_SPEED;
    }

    void Overworld::slowDown(){
        multiplier = 1;
    }

    void Overworld::speedUp(){
        multiplier = 2;
    }

    void Overworld::handleKeyDown(sf::Event::KeyEvent event){
        switch(event.code){
            case sf::Keyboard::W:
                startUp();
                break;
            case sf::Keyboard::S:
                startDown();
                break;
            case sf::Keyboard::A:
                startLeft();
                break;
            case sf::Keyboard::D:
                startRight();
                break;
            case sf::Keyboard::LShift:
                speedUp();
        }
    }

    void Overworld::handleKeyUp(sf::Event::KeyEvent event){
        switch(event.code){
            case sf::Keyboard::W:
                stopUp();
                break;
            case sf::Keyboard::S:
                stopDown();
                break;
            case sf::Keyboard::A:
                stopLeft();
                break;
            case sf::Keyboard::D:
                stopRight();
                break;
            case sf::Keyboard::LShift:
                slowDown();
        }
    }

    void Overworld::update(Player& character, Game& game){
        if (movingUp) {
            character.moveUpTile (speed);
        } else if (movingDown) {
            character.moveDownTile (speed);
        }

        if (movingRight) {
            character.moveRightTile (speed);
        } else if (movingLeft) {
            character.moveLeftTile (speed);
        }
    }
}

