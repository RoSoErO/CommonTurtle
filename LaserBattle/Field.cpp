#include "Field.hpp"
#include "Entity.hpp"
#include "Player.hpp"


#define tileDimensions sf::Vector2f (15.f, 15.f)  //tile Dimensions I suspect

void Field::fieldInit(const std::string & FieldInit) {

	FileReader reader(FieldInit);
	std::string s = reader.readLine();

	while (s != "?<>?") {
		s = reader.readLine();
	}

	backgroundInit(reader);
	playerInit(reader);

	sf::Vector2f position(playingField.width / 2, playingField.height / 2);
	SceneNode * fieldEntities = sceneRoot.findNodeById("FieldEntities");
	Ball * ball = new Ball("ball", textures.at("Ball").getResource(), position, fieldEntities);
	fieldEntities->attachChild(ball);
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
	int width = 0;
	int height = 0;
	bool field = false;

	while (s != "?<>?") {

		int x = 0;

		if (!s.empty()) {

			for (std::string::iterator it = s.begin(); it != s.end(); it++) {

				int nr = *it - '0';
				std::string id = tilemap.at(nr);

				if (playingField.top == 0 && id != "Water") {
					playingField.top = y;
					playingField.left = x;
					width += tileDimensions.x;
				}
				else if (id != "Water" && playingField.width == 0) {
					width += tileDimensions.x;
				}

				if (id != "Water") field = true;

				backgroundTile * tile = new backgroundTile(id, textures.at(id).getResource(), sf::Vector2f(x, y), tileDimensions, background);
				background->attachChild(tile);
				x += tileDimensions.x;
			}
			fieldDimensions.x = x / tileDimensions.x;
			playingField.width = width;
			y += tileDimensions.y;
			if (field) {
				height += tileDimensions.y;
				field = false;
			}
		}

		s = reader.readLine();

	}

	fieldDimensions.y = y / tileDimensions.y;
	playingField.height = height;
}

void Field::playerInit(FileReader & reader) {

	FieldNode * entities = new FieldNode(&sceneRoot, "FieldEntities", sf::Vector2f(playingField.left, playingField.top), this);
	sceneRoot.attachChild(entities);
	this->fieldEntities = entities;
	std::string s;
	s = reader.readLine();

	while (s != "?<>?") {

		if (!s.empty()) {

			int pos = s.find_first_of('?');
			std::string sSub = s.substr(0, pos);
			std::string key = sSub;
			sSub = s.substr(pos + 2);
			std::string filepath = sSub;
			ResourceHolder <sf::Texture> texture;
			texture.loadFromFile(filepath);
			textures.insert(std::make_pair(key, texture));


		}

		s = reader.readLine();
	}

	s = reader.readLine();

	while (s != "?<>?") {

		if (s == "<?") {

			s = reader.readLine();
			Player * player = new Player("Player", entities);
			entities->attachChild(player);


			while (s != "?>") {

				if (!s.empty()) {

					int pos = s.find_first_of(':');
					std::string code = s.substr(0, pos);

					if (code == "Name") {

						std::string name = s.substr(pos + 2);
						player->setName(name);
					}

					else if (code == "Race") {

						std::string race = s.substr(pos + 2);
						player->setRace(race, textures.at(race).getResource());
					}

					else if (code == "Position") {

						int posX = s.find_first_of('x');
						int posY = s.find_first_of('y');
						int posXstop = s.find_first_of('?');
						int posYstop = s.find_first_of('?', posXstop + 1);
						std::string subSx = s.substr(posX + 3, posXstop - (posX + 3));
						std::string subSy = s.substr(posY + 3, posYstop - (posY + 3));

						sf::Vector2f position;
						int xo = subSx.front() - 48;
						position.y = (float)(subSy.front() - 48) / (float)(subSy.back() - 48);
						position.x = (float)(subSx.front() - 48) / (float)(subSx.back() - 48);

						position.y = (playingField.height * position.y);
						position.x = (playingField.width * position.x);

						player->setPosition(position);
					}
				}
				s = reader.readLine();
			}

		}

		s = reader.readLine();
	}
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

FieldNode * Field::getFieldEntities() {

	return fieldEntities;
}

void Field::updateField(sf::Time timestep) {

	fieldEntities->update(timestep);
}