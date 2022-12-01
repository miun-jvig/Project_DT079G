/**
* The class Collider is an object-detection class, which will sense whether or not
* an object is touching another. This is done by utilizing AABB for collision detection.
*
* The collision detection works by getting the middle position of both of the objects, and
* then calculating the length to any of the corners.
*/

#ifndef Collider_H
#define Collider_H
#include <SFML/Graphics.hpp>

class Collider {
private:
	sf::RectangleShape& body; /** Body of the collider. */
public:
	/** 
	* Parameterized constructor.
	* @param body - reference to a RectangleShape.
	*/
	Collider(sf::RectangleShape& body);  

	/**
	* bool checkCollision(Collider& other, sf::Vector2f& direction, float push) will check whether or not an object is
	* touching another object.
	* 
	* @param other - another collider.
	* @param direction - what direction (using sf::Vector2f) the player was moving until collision.
	* @param push - whether or not the object should be pushed by the player.
	*/
	bool checkCollision(Collider& other, sf::Vector2f& direction, float push);

	/**
	* void move(float dx, float dy) move the body of the collided objects.
	* 
	* @param dx - x-direction.
	* @param dy - y-direction.
	*/
	void move(float dx, float dy);
	sf::Vector2f getSize() { return body.getSize(); } /** Returning size of the RectangleShape body. */
	sf::Vector2f getPosition() { return body.getPosition(); } /** Returning position of the RectangleShape body. */
	sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; } /** Returning half the size of the RectangleShape body. */
};

#endif