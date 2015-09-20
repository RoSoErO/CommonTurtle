#include "Field.hpp"
#include "Entity.hpp"
#include "Player.hpp"


#define tileDimensions sf::Vector2f (15.f, 15.f) // size in pixels for each tile

void Field::fieldInit(const std::string & FieldInit) {

	FileReader reader(FieldInit);
	std::string s = reader.readLine();

	while (s != "?<>?") {
		s = reader.readLine();
	}

	backgroundInit(reader);


}

void Field::backgroundInit(FileReader & reader) {

	SceneNode * background = new SceneNode(&sceneRoot, "Background");
	sceneRoot.attachChild(background);
	std::string s;
	std::map <int, std::string> tilemap;
	s = reader.readLine();

	while (s != "?<>?") {

		if (!s.empty()) {

			int pos = s.find_first_of('?');
			std::string sSub = s.substr(0, pos);
			int key = atoi(sSub.c_str());
			int pos2 = s.find_first_of('?', pos + 1);
			sSub = s.substr(pos + 2, pos2 - (pos + 2));
			tilemap.insert(std::make_pair(key, sSub));
			std::string filepath = s.substr(pos2 + 2);
			ResourceHolder <sf::Texture> texture;
			texture.loadFromFile(filepath);
			textures.insert(std::make_pair(sSub, texture));
		}

		s = reader.readLine();

	}

	s = reader.readLine();
	int y = 0;

	while (s != "?<>?") {

		int x = 0;

		if (!s.empty()) {

			for (std::string::iterator it = s.begin(); it != s.end(); it++) {

				int nr = *it - '0';
				std::string id = tilemap.at(nr);

				backgroundTile * tile = new backgroundTile(id, textures.at(id).getResource(), sf::Vector2f(x, y), tileDimensions, background);
				background->attachChild(tile);
				x += tileDimensions.x;
			}
			fieldDimensions.x = x / tileDimensions.x;
			y += tileDimensions.y;

		}

		s = reader.readLine();

	}

	fieldDimensions.y = y / tileDimensions.y;
}

void Field::drawField(sf::RenderWindow & gWindow) {

	sceneRoot.draw(gWindow);
}

Field::Field(const std::string & FieldInit) : sceneRoot(nullptr, "SceneRoot"), fieldDimensions(0.f, 0.f) {

	this->fieldInit(FieldInit);


}

sf::Vector2f Field::getFieldSize() {

	return sf::Vector2f(fieldDimensions.x * tileDimensions.x, fieldDimensions.y * tileDimensions.y);
}

/*
FieldNode * Field::getFieldEntities() {

	return fieldEntities;
}

void Field::updateField(sf::Time timestep) {

	fieldEntities->update(timestep);
}
*/