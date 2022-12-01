/**
* The class DrawRectangle is used to create a RectangleShape with the help of the mouse. DrawRectangle works by checking
* the current position of the mouse when the user presses left mouse-button and saving that position. It will then keep
* checking the position of the mouse until the user lets go off the left mouse-button. When this happens, then DrawRectangle
* will create a sf::VertexArray as a rectangle. The position of the sf::VertexArray will then be copied to a sf::RectangleShape.
*
* The class DrawRectangle has a sf::Texture, sf::RectangleShape and a sf::VertexArray.
*/

#include "DrawRectangle.h"
#include <iostream>

DrawRectangle::DrawRectangle(sf::Texture* texture) : drawnVertexArray(sf::Quads, 4) {
	body.setTexture(texture); /* Sets the texture of the rectangle. */
}

sf::RectangleShape DrawRectangle::getBody() {
	return body;
}

void DrawRectangle::createRectangleMouse(sf::RenderWindow& window, bool initValue) {
	sf::Vector2f pos2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))); /* Gets the current position of the mouse. */
	sf::Vector2f startPos = drawnVertexArray[0].position; /* Start-position of the mouse. */
	sf::Vector2f mousePosition = drawnVertexArray[2].position; /* Current position of the mouse. */
	
	/*
	* If it's the first left mouse-click of the user, then initValue is true. When this happens, every position of the sf::VertexArray (4)
	* will be filled with the start-position of the mouse. When the user releases the mouse, then this function is called again with initValue
	* being false. This causes the positions 1, 2 and 3 to update to the new positions to create a rectangle.
	*/
	if (initValue) {
		for (int i = 0; i < 4; i++) {
			drawnVertexArray[i].position = pos2f;
		}		
	}
	else {
		drawnVertexArray[1].position.x = pos2f.x;
		drawnVertexArray[2].position = pos2f;
		drawnVertexArray[3].position.y = pos2f.y;
	}
	body.setPosition(startPos); /* Sets the sf::RectangleShape to the mouse starting-position. */

	/*
	* If we are on negative x- and y-axis, then set the position of the sf::RectangleShape to current position of the mouse.
	* The size of the body will be set accordingly to create a rectangle. 
	*/
	if (mousePosition.x < startPos.x && mousePosition.y < startPos.y) {
		body.setPosition(mousePosition);
		body.setSize(sf::Vector2f(startPos.x - mousePosition.x, startPos.y - mousePosition.y));
	}
	/*
	* If we are on negative x-axis.
	*/
	else if (mousePosition.x < startPos.x) {
		body.setPosition(mousePosition.x, startPos.y);
		body.setSize(sf::Vector2f(startPos.x - mousePosition.x, mousePosition.y - startPos.y));

	}
	/*
	* If we are on negative y-axis.
	*/
	else if (mousePosition.y < startPos.y) {
		body.setPosition(startPos.x, mousePosition.y);
		body.setSize(sf::Vector2f(mousePosition.x - startPos.x, startPos.y - mousePosition.y));
	}
	else {
		body.setSize(sf::Vector2f(mousePosition.x - startPos.x, mousePosition.y - startPos.y));
	}
}

void DrawRectangle::drawVertexArray(sf::RenderWindow& window) {
	window.draw(drawnVertexArray);
}

Collider DrawRectangle::getCollider() {
	return Collider(body);
}