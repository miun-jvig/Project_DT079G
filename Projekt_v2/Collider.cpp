/**
* Contains all the functions for class Collider.
*
* The collider is an object-detection class, which will sense whether or not
* an object is touching another. This is done by utilizing AABB for collision detection.
*
* The collision detection works by getting the middle position of both of the objects, and
* then calculating the length to any of the corners.
*
*/

#include "Collider.h"
#include <iostream>

Collider::Collider(sf::RectangleShape& body) : body(body) {
	
}

void Collider::move(float dx, float dy) {
	body.move(dx, dy); /* Moves the sf::RectangleShape according to the input-values. */
}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float push) {
	/*
	* As we need the center of the body for the AABB-algorithm we need to make sure that we have the correct origin.
	* sf::Vector2f otherPosition = other.body.getTransform().transformPoint(other.getHalfSize()) will check the "other"-collider,
	* in this case being the sf::VertexArray, and then transform its origin from the top-left corner (which is standard for sf::VertexArray)
	* into the middle of the sf::VertexArray.
	*/
	sf::Vector2f otherPosition = other.body.getTransform().transformPoint(other.getHalfSize());	
	sf::Vector2f otherHalfSize = other.getHalfSize(); /* Gets the half-size of the second collider. */
	sf::Vector2f thisPosition = getPosition(); /* Gets the position of the first collider. */
	sf::Vector2f thisHalfSize = getHalfSize(); /* Gets the half-size of the first collider. */

	float deltaX = otherPosition.x - thisPosition.x; /* Calculates the delta between the centers of the two colliders. */
	float deltaY = otherPosition.y - thisPosition.y; /* Calculates the delta between the centers of the two colliders. */
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	/*
	* Checks whether or not the two colliders collided with each other.
	* 
	* if intersectX or intersectY is positive, then objects are not touching, but if they are negative, then the objects are
	* colliding.
	*/
	if (intersectX < 0.0f && intersectY < 0.0f) {
		push = std::min(std::max(push, 0.0f), 1.0f); /* To be able to push the object. */
		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				move(intersectX * (1.0f - push), 0.0f);
				other.move(-intersectX * push, 0.0f);
				/*
				* The direction the colliders are moving. This is used in the Player.h-class to make sure that jumping
				* is reset upon hitting the ground, as well as stopping the player when hitting an object.
				*/
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				move(-intersectX * (1.0f - push), 0.0f);
				other.move(intersectX * push, 0.0f);
				/*
				* The direction the colliders are moving. This is used in the Player.h-class to make sure that jumping
				* is reset upon hitting the ground, as well as stopping the player when hitting an object.
				*/
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (deltaY > 0.0f) {
				move(0.0f, intersectY * (1.0f - push));
				other.move(0.0f, -intersectY * push);
				/*
				*The direction the colliders are moving.This is used in the Player.h - class to make sure that jumping
				* is reset upon hitting the ground, as well as stopping the player when hitting an object.
				*/
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				move(0.0f, -intersectY * (1.0f - push));
				other.move(0.0f, intersectY * push);
				/*
				*The direction the colliders are moving.This is used in the Player.h - class to make sure that jumping
				* is reset upon hitting the ground, as well as stopping the player when hitting an object.
				*/
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true; /* COLLIDED. */
	}
	return false; /* NOT COLLIDED. */
}