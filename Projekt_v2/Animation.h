/**
* The animation-class represents the animation of any object. It utilizes for example the imageCount, which checks
* how many pictures is in the x-axis and y-axis of the sprite, i.e. sf::Vector2u(3, 9) will represent 3 pictures in
* x-axis and 9 pictures in y-axis.
*/

#ifndef Animation_H
#define Animation_H
#include <SFML/Graphics.hpp>

class Animation{
private:
	sf::Vector2u imageCount; /** How many pictures in the x - axis and y - axis of the sprite */
	sf::Vector2u currentImage; /** What the current image is. */
	float totalTime; /** How long the animation has been going for. */
	float switchTime; /** When the current picture should we switched. */
	sf::IntRect uvRect; /** How big the sprite-picture is. */
public:
	/**
	* Parameterized constructor.
	*
	* @param texture - Texture of the animation.
	* @param imageCount - How many pictures in the x-axis and y-axis of the sprite, i.e. sf::Vector2u(3, 9) will represent
	* 3 pictures in x-axis and 9 pictures in y-axis.
	* @param switchTime - How long until the animation should switch to next picture.
	*/
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

	/**
	* void update(int row, float deltaTime, bool faceRight) will update the animation of the player.
	*
	* @param row - The row of the animation in the sprite.
	* @param deltaTime - utilizing a clock to get a timer.
	* @param faceRight - What way the player is facing.
	*/
	void update(int row, float deltaTime, bool faceRight);

	/**
	* sf::IntRect getuvRect() will return the private sf::IntRect.
	*/
	sf::IntRect getuvRect();
};

#endif