#include <SFML/Graphics.hpp>
#include "Entity.hpp"



Entity::Entity(std::string ID, const sf::Texture& texture, SceneNode * parent) : SceneNode(parent, ID) {

	sprite.setTexture(texture);

}

Entity::Entity(std::string ID, SceneNode * parent) : SceneNode(parent, ID) {

}

backgroundTile::backgroundTile(std::string ID, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f dimensions, SceneNode * parent) : Entity(ID, texture, parent) {

	this->position = position;
	this->dimensions = dimensions;
	sprite.setPosition(position);
	sprite.setTextureRect(sf::IntRect(0, 0, dimensions.x, dimensions.y));
}

void backgroundTile::draw(sf::RenderWindow & window) {

	window.draw(sprite);

}
