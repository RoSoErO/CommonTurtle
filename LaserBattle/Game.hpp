#ifndef GAME_GUARD
#define GAME_GUARD

class Game {

private:
	sf::RenderWindow mWindow;
	Field gameField; // not liking field, but works temporarily. Read gameworld
	sf::View mView; // camera

public:
	Game();
	void run(); // game loop

private:
	void render();
	void processInput();
	void update(sf::Time TimePerFrame);

};

#endif // !GAME_GUARD
