/**
* The class DrawRectangle is used to create a RectangleShape with the help of the mouse. DrawRectangle works by checking
* the current position of the mouse when the user presses left mouse-button and saving that position. It will then keep
* checking the position of the mouse until the user lets go off the left mouse-button. When this happens, then DrawRectangle
* will create a sf::VertexArray as a rectangle. The position of the sf::VertexArray will then be copied to a sf::RectangleShape.
* 
* The class DrawRectangle has a sf::Texture, sf::RectangleShape and a sf::VertexArray.
*/

#ifndef DrawRectangle_h
#define DrawRectangle_h
#include <SFML/Graphics.hpp>
#include "Collider.h"

class DrawRectangle : public sf::Drawable {
private:
	sf::VertexArray drawnVertexArray; /** VertexArray of the drawn rectangle. */
	sf::RectangleShape body; /** RectangleShape of the drawn rectangle. */
	sf::Texture texture; /** Texture of the drawn rectangle. */

	/**
	* As Lava is inheriting from sf::Drawable, which only has a pure virtual function called draw,
	* this function is created. virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	* will allow the class to be drawn in main.cpp by utilizing window.draw(lava).
	*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(body, &texture);
	}
public:
	/**
	* DrawRectangle(sf::Texture* texture) is a parameterized constructor.
	*
	* @param texture - Texture for the rectangle.
	*/
	DrawRectangle(sf::Texture* texture);

	/**
	* void createRectangleMouse(sf::RenderWindow& window, bool initValue) will create a rectangle by checking the
	* current position of the mouse.
	*
	* @param window - The current sf::Renderwindow&.
	* @param initValue - If it's the intial value of the user, which means that it's on the first left mouse-button down.
	*/
	void createRectangleMouse(sf::RenderWindow& window, bool initValue);

	/**
	* void drawVertexArray(sf::RenderWindow& window) will draw the sf::VertexArray to the screen.
	* 
	* @param window - The current sf::Renderwindow&.
	*/
	void drawVertexArray(sf::RenderWindow& window);

	/**
	* sf::RectangleShape getBody() will return the sf::RectangleShape.
	*/
	sf::RectangleShape getBody();

	/**
	* Collider getCollider() will return the RectangleShape body as a Collider-object.
	* This object will be used in the collision-detection algorithm.
	*/
	Collider getCollider();
};

#endif