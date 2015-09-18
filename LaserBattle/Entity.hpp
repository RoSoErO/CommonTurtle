#ifndef ENTITY_GUARD
#define ENTITY_GUARD



#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"


class Entity : public SceneNode {  // extends Scenenode

protected:  // so it is inherited

	sf::Sprite sprite;

public:

	Entity(std::string ID, const sf::Texture& texture, SceneNode * parent);
	Entity(std::string Id, SceneNode * parent);
};

class backgroundTile : public Entity {

protected:

	sf::Vector2f position;
	sf::Vector2f dimensions;

public:

	backgroundTile(std::string ID, const sf::Texture& texture, sf::Vector2f position, sf::Vector2f dimensions, SceneNode * parent);
	void draw(sf::RenderWindow & window);

};

#endif // !ENTITY_GUARD