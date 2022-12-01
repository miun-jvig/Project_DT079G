/**
* The class Lava is a basic platform that will continuously rise until it eventually hits the player.
* When the RectangleShape body hits the player, then an object-collision will occur with the class
* Collider.h
*/

#ifndef Lava_H
#define Lava_H
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Lava : public sf::Drawable {
private:
	sf::RectangleShape body; /** Body of the lava. */
	sf::Texture lavaTexture; /** Texture of the lava. */
	sf::Vector2f speed; /** Speed of the lava. */

	/**
	* As Lava is inheriting from sf::Drawable, which only has a pure virtual function called draw,
	* this function is created. virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	* will allow the class to be drawn in main.cpp by utilizing window.draw(lava).
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(body);
	}
public:
	/**
	* Lava(sf::Texture* texture, float speed) is a parameterized constructor.
	*
	* @param texture - texture for the lava.
	* @param speed - how fast the lava rises.
	*/
	Lava(sf::Texture* texture, float speed);

	/**
	* void update(float deltaTime) will update the position of the RectangleShape body of the lava.
	*
	* @param deltaTime - utilizing a clock to get a timer.
	*/
	void update(float deltaTime);

	/**
	* Collider getCollider() will return the RectangleShape body as a Collider-object.
	* This object will be used in the collision-detection algorithm.
	*/
	Collider getCollider();
};

#endif