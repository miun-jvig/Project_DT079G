/**
* The class player represents the Player-object, which essentially is a RectangleShape with an animation and a texture.
* The player-class uses composition as it has another class as a private variable (Animation).
*
* The player is able to move in x- and y-directions. The player has a speed, a jump height and a velocity.
*/

#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	body(sf::Vector2f(100.0f, 150.0f)),
	animation(texture, imageCount, switchTime),
	speed(speed), row(0), faceRight(true),
	jumpHeight(jumpHeight), canJump(true),
	alive(true) {
	body.setTexture(texture); /* Sets the texture of the player. */
	body.setOrigin(body.getSize() / 2.0f); /* Sets the origin of the player. */
}

void Player::death() {
	alive = false;
}

bool Player::isAlive() {
	return alive;
}

void Player::update(float deltaTime) {
	velocity.x *= 0.0f; /* Every time the player is updated, the speed on the x-axis is set to zero. */
	velocity.y += 981.0f * deltaTime; /* To get a sense of gravity. */

	/*
	* If player is alive, then keep current animation. If not, then show the death-animation.
	*/
	if (alive) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			velocity.x -= speed; /* Move the player left. */
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			velocity.x += speed; /* Move the player right. */
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
			canJump = false; /* Can't jump during an already pending jump. */
			/*
			* Using the formula -sqrt(2.0f * gravity * jumpHeight), but changing from 9.81f to 981.0f as we are
			* counting pixels.
			*/
			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); 
		}

		if (velocity.x == 0.0f) {
			row = 0; /* Row 0 contains the idle animation. */
		}
		else {
			row = 1; /* Row 1 contains the running animation. */
			if (velocity.x > 0.0f) {
				faceRight = true;
			}
			else {
				faceRight = false;
			}
		}
		if (!canJump) {
			row = 2; /* Row 0 contains the jumping animation. */
		}
	}
	else {
		row = 8; /* Row 0 contains the death animation. */
	}
	animation.update(row, deltaTime, faceRight); /* void update(int row, float deltaTime, bool faceRight) will update the animation of the player. */
	body.setTextureRect(animation.getuvRect()); /* Set the texture rect to be the same as for the animation. */
	body.move(velocity * deltaTime);
}

sf::Vector2f Player::getPosition() {
	return body.getPosition();
}

Collider Player::getCollider() {
	return Collider(body);
}

void Player::onCollision(sf::Vector2f direction) {
	if (direction.x < 0.0f) {
		velocity.x = 0.0f; /* Collision on the left. */
	}
	else if(direction.x > 0.0f) {
		velocity.x = 0.0f; /* Collision on the right. */
	}

	if (direction.y > 0.0f) {		
		velocity.y = 0.0f; /* Collision on the bottom. */
		canJump = true; /* As player collides with the floor, user can jump again. */
	}
	else if (direction.y < 0.0f) {
		velocity.y = 0.0f; /* Collision on the top. */
	}
}