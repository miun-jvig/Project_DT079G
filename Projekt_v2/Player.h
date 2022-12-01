/**
* The class player represents the Player-object, which essentially is a RectangleShape with an animation and a texture.
* The player-class uses composition as it has another class as a private variable (Animation).
* 
* The player is able to move in x- and y-directions. The player has a speed, a jump height and a velocity.
*/

#ifndef Player_H
#define Player_H
#include "Animation.h"
#include "DrawRectangle.h"
#include "Collider.h"

class Player : public sf::Drawable {
private:
	sf::RectangleShape body; /** Body of the player. */
	Animation animation; /** Animation of the player. */
	sf::Texture playerTexture; /** Texture of the player. */

	unsigned int row; /** Row of the sprite to make sure that the correct animation is used. */
	float speed; /** Speed of the player. */
	bool faceRight; /** Which way the player faces. This boolean is here to make sure that the animation looks correct. */
	bool canJump; /** Whether or not the player can jump. */
	bool alive; /** Whether or not the player is alive. */
	float jumpHeight; /** How high the player can jump. */
	sf::Vector2f velocity; /** Velocity of the player. */

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
	* Parameterized constructor.
	* 
	* @param texture - Texture of the player.
	* @param imageCount - How many pictures in the x-axis and y-axis of the sprite, i.e. sf::Vector2u(3, 9) will represent
	* 3 pictures in x-axis and 9 pictures in y-axis.
	* @param switchTime - How long until the animation should switch to next picture.
	* @param speed - The speed of the player.
	* @param jumpHeight - How high the player can jump.
	*/
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);

	/**
	* void update(float deltaTime) will update the position of the RectangleShape body of the player.
	*
	* @param deltaTime - utilizing a clock to get a timer.
	*/
	void update(float deltaTime);

	/**
	* void onCollision(sf::Vector2f direction) will check where the player collided with an object.
	* If the player collided with the floor, then canJump will be set to true.
	*
	* @param direction - What direction the player was coming from.
	*/
	void onCollision(sf::Vector2f direction);

	/**
	* void death() will check whether or not the player collided with the lava. If the player collided with lava,
	* then bool alive will be set to false.
	*/
	void death();

	/**
	* bool isAlive() will return whether or not the player is alive.
	*/
	bool isAlive();

	/**
	* Collider getCollider() will return the RectangleShape body as a Collider-object.
	* This object will be used in the collision-detection algorithm.
	*/
	Collider getCollider();

	/**
	* sf::Vector2f getPosition() will return the position of the RectangleShape body.
	*/
	sf::Vector2f getPosition();
};

#endif