#include <SFML/Graphics.hpp>
#include "Field.hpp"

#include "Game.hpp"

#define TimePerFrame sf::seconds (1.f/ 60.f)
#define cameraMovement sf::Vector2f (100.f,100.f)


int main() {
	Game game;
	game.run();
}

/*
This constructor sets the size of the renderwindow, the init file that generates the world (background only currently), and sets the cameras center and size
*/
Game::Game() : mWindow(sf::VideoMode(640, 480), "Strategic Sports Game"), gameField("FieldInit.txt") {

	sf::Vector2f dimensions = gameField.getFieldSize();
	mView.setCenter(dimensions.x / 2, dimensions.y / 2);
	mView.setSize(dimensions.x, dimensions.y);
	mWindow.setView(mView);
}

/*
Fixed Timestep, 60 fps
*/
void Game::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		processInput();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			update(TimePerFrame);
		}

		render();
	}
}

void Game::render() {

	mWindow.clear();
	gameField.drawField(mWindow);
	mWindow.display();

}
/*
Currently only handles window closing
*/
void Game::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime) {

	gameField.updateField(elapsedTime);

	// remember, real time input, update or processInput
}

