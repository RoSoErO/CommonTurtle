#ifndef GAME_GUARD
#define GAME_GUARD

#include <SFML/Graphics.hpp>
class Game {

private:
	sf::RenderWindow mWindow;


public:
	Game();
	void run(); // game loop

private:
	void render();
	void processInput();
	void update(sf::Time TimePerFrame);

};

#endif // !GAME_GUARD
