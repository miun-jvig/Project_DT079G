/**
* A project created by Joel Viggesjöö on the date 2022-01-12.
* This project was done for the course Programmeringsmetodik on Mittuniversitetet Sundsvall.
* 
* Based on a guide made by Hilze Vonck (https://www.youtube.com/channel/UC8C7ncaMYnXyu-pRU0S9FLg).
*/
#include <iostream>
#include <vector>
#include "DrawRectangle.h"
#include "Player.h"
#include "Lava.h"
#include "Animation.h"

/** 
* VIEW_HEIGHT is an already set height for the view that is used by the player.
*/
static const float VIEW_HEIGHT = 1920.0f; 

/**
* void resizeView(const sf::RenderWindow& window, sf::View& view) will make sure that the program works good on all monitors.
* This function will make sure that the player-model won't be stretched out if the window is resized.
*/
void resizeView(const sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = static_cast<float>(window.getSize().x / static_cast<float>(window.getSize().y)); // Get aspect ratio
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
	// DECLARATIONS
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Box Jumper", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
	sf::RectangleShape floor(sf::Vector2f(500.0f, 200.0f));
	std::vector<DrawRectangle> boxVector;
	sf::Clock clock;
	sf::Font arial;
	sf::Texture playerTexture;
	sf::Texture boxTexture;	
	sf::Texture floorTexture;
	sf::Texture lavaTexture;
	sf::Text deathText;	
	deathText.setFont(arial);
	deathText.setStyle(sf::Text::Bold);
	deathText.setCharacterSize(500);
	
	// TEXTURES
	arial.loadFromFile("arial.ttf");
	playerTexture.loadFromFile("sprite.png");
	boxTexture.loadFromFile("crate.png");
	floorTexture.loadFromFile("floor.png");
	lavaTexture.loadFromFile("lava.png");
	floor.setTexture(&floorTexture);
	playerTexture.setSmooth(true);
	boxTexture.setSmooth(true);
	
	// DECLARATIONS
	DrawRectangle box(&boxTexture);
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 100.f, 200.0f);
	Lava lava(&lavaTexture, 10.0f);
	Collider floorCollide(floor); /** Collider created to make sure that the player can collide with the floor. */
	Collider lavaCollider = lava.getCollider(); /** Collider created to make sure that the player can collide with the lava. */
	floor.setPosition(player.getPosition().x - 500.0f, player.getPosition().y + 60.0f); // Sets the position of the floor depending on where the player is.

	float deltaTime = 0.0f; // Start-value which will be used to increment time using a clock.
	bool isMoving = false; // Whether or not the user is moving the mouse.

	while (window.isOpen()) {
		/**
		* deltaTime is used in both the animation and the movement of the player. Every time the while-loop restarts, then this timer
		* is reset.
		*/
		deltaTime = clock.restart().asSeconds();
		/**
		* The if-statement below is created to avoid a bug which happens when you move the RenderWindow very fast. In rare cases, this would
		* cause the player to instantly fall down. This if-statement makes sure that it does not happen.
		*/
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close(); // Close the window if exit is pressed by the user.
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					/**
					* void createRectangleMouse(sf::RenderWindow& window, bool initValue) will create a rectangle by checking the
					* current position of the mouse when the user presses left mouse-button and saving that position. It will then keep
					* checking the position of the mouse until the user lets go off the left mouse-button. When this happens, then createRectangleMouse
					* will create a sf::VertexArray as a rectangle. The position of the sf::VertexArray will then be copied to a sf::RectangleShape.
					*/
					box.createRectangleMouse(window, true);
					isMoving = true; // User is moving the mouse
				}
				break;
			case sf::Event::MouseMoved:
				if (isMoving) {
					/**
					* While mouse is moving, keep checking the position to draw a sf::VertexArray that will be transformed into a sf::RectangleShape.
					*/
					box.createRectangleMouse(window, false);
				}
				break;
			case sf::Event::MouseButtonReleased:
				isMoving = false; // User stopped moving the mouse
				/**
				* Push back the current box into a vector. This is to make sure that every drawn sf::RectangleShape will be drawn and that it will stay
				* on the sf::RenderWindow.
				*/
				boxVector.push_back(box);
			case sf::Event::Resized:
				/*
				* Utilizing the function resizeView(window, view) to make sure that no issues arise when resizing the window.
				*/
				resizeView(window, view);
				break;
			default:
				break;
			}
		}
		/**
		* Both update-functions will update the position of the RectangleShape body of the player/lava.
		*/
		player.update(deltaTime);
		lava.update(deltaTime);

		sf::Vector2f direction; // what direction the player is currently facing.

		/**
		* If the player collided with the lava, then call the death()-function. This will call the text
		* "Game over!" and the game is done.
		*/
		if (player.getCollider().checkCollision(lavaCollider, direction, 0.0f)) {			
			player.death();
		}
		
		/**
		* Checks if the player collided with the floor, while also giving the direction it collided.
		*/
		player.getCollider().checkCollision(floorCollide, direction, 0.0f);		
		player.onCollision(direction);

		/**
		* Checks if the player collided with mouse-created boxes, while also giving the direction it collided.
		* This will check every mouse-created box in the boxVector.
		*/
		for (auto& e : boxVector) {
			Collider tmp = e.getCollider();
			if (player.getCollider().checkCollision(tmp, direction, 0.0f)) {
				player.onCollision(direction);
			}			
		}

		view.setCenter(player.getPosition()); /** Sets the center of view to be on the center of the player. */
		window.clear(sf::Color(150, 150, 150)); /** Sets the background to a gray colour. */
		window.setView(view); /** Sets the view to be on the center of the player. */

		// DRAW AREA		
		box.drawVertexArray(window); /** Draw the boxes made by the user. */
		window.draw(lava); /** Draw the lava. */
		window.draw(floor); /** Draw the floor. */

		/**
		* Draw every box created by the user.
		*/
		for (auto e : boxVector) {
			window.draw(e);
		}
		window.draw(player); /** Draw the player. */

		/**
		* If the player dies, then write out the text "Game over!".
		*/
		if (!player.isAlive()) {
			sf::FloatRect textRect = deathText.getLocalBounds();
			deathText.setString("Game over!");
			deathText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			deathText.setPosition(sf::Vector2f(view.getCenter()));			
			window.draw(deathText);
		}
		// END OF DRAW AREA
		window.display();
	}
	return 0;
}

