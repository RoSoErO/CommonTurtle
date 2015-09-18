#ifndef FileReader_GUARD
#define FILEREADER_GUARD

#include <iostream>
#include <fstream>

class FileReader {

private:

	std::ifstream IS;

public:
	FileReader(const std::string & filepath);
	std::string readLine();
	char readToken();


};

#endif // !FileReader_GUARD