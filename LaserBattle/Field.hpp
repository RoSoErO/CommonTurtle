#ifndef FIELD_GUARD
#define FIELD_GUARD

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FileReader.hpp"
#include "ResourceHolder.hpp"
#include "SceneNode.hpp"
#include "Entity.hpp"
#include "FieldEntity.hpp"


class Field {

private:
	/*
	Uses ResourceHolder, a template class to hold any resources. The name of the texture is the key of the map.
	*/
	std::map <std::string, ResourceHolder <sf::Texture>> textures;
	SceneNode sceneRoot; // The root of the sceneNode system, the first draw called is called on this root. 
	sf::Vector2i fieldDimensions; // How many tiles there is in x,y direction

public:

	void fieldInit(const std::string & worldInit);
	void drawField(sf::RenderWindow & gWindow);
	Field(const std::string & worldInit);
	void backgroundInit(FileReader & reader);
	sf::Vector2f getFieldSize();
	FieldNode * getFieldEntities();
	void updateField(sf::Time timestep);



};

#endif // !WORLD_GUARD