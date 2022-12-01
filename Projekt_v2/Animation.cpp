/**
* Animation.cpp contains functions for the class Animation.
*/

#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) :
	imageCount(imageCount), switchTime(switchTime), totalTime(0.0f) {
	uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x); /* Gets the width for the sf::IntRect by checking the size of the texture together with the imageCount. */
	uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y); /* Gets the height for the sf::IntRect by checking the size of the texture together with the imageCount. */
}

void Animation::update(int row, float deltaTime, bool faceRight) {
	currentImage.y = row; /* Updates the sf::Vector2u currentImage according to what row is sent from the Player.h. */
	totalTime += deltaTime;	 /* Increment totalTime with the deltaTime that is a timer. */

	/*
	* If the total time passed is more than the switch time given by the user, then switch image.
	* Also checks if the current image is bigger than the image count, and in that case resets
	* the current image back to 0.
	*/
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}
	uvRect.top = currentImage.y * uvRect.height; /* Setting top offset of the sf::IntRect. */
	if (faceRight) {
		uvRect.left = currentImage.x * uvRect.width; /* Setting left offset of the sf::IntRect. */
		uvRect.width = abs(uvRect.width); /* abs(uvRect.width) is used to make sure we work with positive values. */
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width); /* abs(uvRect.width) is used to make sure we work with positive values. */
		uvRect.width = -abs(uvRect.width); /* abs(uvRect.width) is used to make sure we work with positive values. */
	}
}

sf::IntRect Animation::getuvRect() {
	return uvRect; /* Returns the sf::IntRect uvRect */
}