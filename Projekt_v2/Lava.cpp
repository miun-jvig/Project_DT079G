/**
* The lava-class is an object that is rising with a consistent speed decided by the user. When the lava collides with the player,
* then the game ends.
*/

#include "Lava.h"

Lava::Lava(sf::Texture* texture, float speed) : body(sf::Vector2f(10000.0f, 150.0f)) {
	body.setTexture(texture); /* Sets the texture of the lava. */
	body.setPosition(-3000.0f, 1920 / 2.0f); /* Sets the position of the lava. */
}

void Lava::update(float deltaTime) {
	speed.y -= 9.810f * deltaTime; /* Sets the speed of the lava. */
	body.move(speed * deltaTime); /* Moves the lava. */
}

Collider Lava::getCollider() {
	return Collider(body);
}