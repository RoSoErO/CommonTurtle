#ifndef PLAYER_GUARD
#define PLAYER_GUARD


#include "FieldEntity.hpp"

class Player : public FieldEntity {

protected:

	sf::Vector2f position;
	sf::Vector2f dimensions;
	float velocity;
	std::string name;
	std::string race;
	std::string goal;
	Ball * ball;

public:

	Player(std::string ID, SceneNode * parent);
	void draw(sf::RenderWindow & window);
	void setName(std::string name);
	void setRace(std::string race, const sf::Texture & texture);
	void setPosition(sf::Vector2f);
	void setGoal();
	void drawBallEffect();
	void setBall(Ball * ball);
	void update(sf::Time timestep);


};




#endif // !PLAYER_GUARD