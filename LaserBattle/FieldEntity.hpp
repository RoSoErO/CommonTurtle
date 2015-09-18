#ifndef FIELDENTITY_GUARD
#define FIELDENTITY_GUARD

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SceneNode.hpp"



class FieldEntity : public FieldNode {

protected:  // so it is inherited

	sf::Sprite sprite;

public:

	FieldEntity(std::string ID, const sf::Texture& texture, SceneNode * parent);
	FieldEntity(std::string Id, SceneNode * parent);
};


class Player;

class Ball : public FieldEntity {

protected:

	Player * pickedUpBy;
	sf::Vector3f position;
	sf::IntRect dimensions;
	sf::Vector3f velocity;

public:

	Ball(std::string ID, const sf::Texture& texture, sf::Vector2f initPosition, SceneNode * parent);
	Ball(std::string ID, const sf::Texture& texture, Player * pickedUpBy, SceneNode * parent);
	void setVelocity(sf::Vector3f velocity);
	sf::Vector3f getPosition();
	void draw(sf::RenderWindow & window);
	sf::Vector2f pos3Dto2D();

};








#endif // !FIELDENTITY_GUARD



