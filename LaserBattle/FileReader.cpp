#include "FileReader.hpp"
#include <string>

FileReader::FileReader(const std::string & filepath) {

	IS.open(filepath);
	if (!IS.is_open()) {

		//error handling
	}

}

std::string FileReader::readLine() {

	std::string response;
	if (!std::getline(IS, response)) {
		return "EOF";
	}
	else {
		return response;
	}
}

char FileReader::readToken() {

	if (IS.peek() == std::char_traits<char>::eof()) {
		return std::char_traits<char>::eof();
	}
	else {
		return IS.get();
	}
}
