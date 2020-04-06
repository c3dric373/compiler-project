#include <vector>
#include <string>
#include <iostream>

class Erreur {

public:
    void addErrorMessage(std::string message);
	bool getError();
	std::string getMessage();

private:
	bool error=false;
	std::string errorMessage;
};

