#include <SFML/Graphics.hpp>
#include "FieldEntity.hpp"
#include "Player.hpp"

#define ballDimensions sf::IntRect (0,0,15,15);


FieldEntity::FieldEntity(std::string ID, const sf::Texture& texture, SceneNode * parent) : FieldNode(parent, ID,
	dynamic_cast<FieldNode*> (parent)->getRelativePosition(), dynamic_cast<FieldNode*> (parent)->getFieldRef()) {

	sprite.setTexture(texture);

}

FieldEntity::FieldEntity(std::string ID, SceneNode * parent) : FieldNode(parent, ID,
	dynamic_cast<FieldNode*> (parent)->getRelativePosition(), dynamic_cast<FieldNode*> (parent)->getFieldRef()) {

}

Ball::Ball(std::string ID, const sf::Texture& texture, sf::Vector2f initPosition, SceneNode * parent) : FieldEntity(ID, texture, parent) {

	this->position = sf::Vector3f(initPosition.x + relativePosition.x, initPosition.y + relativePosition.y, 0);
	sprite.setPosition(this->pos3Dto2D());
	this->dimensions = ballDimensions;

}

Ball::Ball(std::string ID, const sf::Texture& texture, Player * pickedUpBy, SceneNode * parent) :FieldEntity(ID, texture, parent) {

	this->pickedUpBy = pickedUpBy;
}

sf::Vector3f Ball::getPosition() {

	return position;
}

void Ball::draw(sf::RenderWindow & window) {

	if (pickedUpBy) {

		pickedUpBy->drawBallEffect();
	}
	else {

		window.draw(sprite);
	}
}

sf::Vector2f Ball::pos3Dto2D() {

	return sf::Vector2f(position.x, position.y);
}