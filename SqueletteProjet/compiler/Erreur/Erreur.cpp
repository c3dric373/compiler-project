#include "Erreur.h"

// Généré à partir de Erreur.h


bool Erreur::getError(){
	return error;
}

std::string Erreur::getMessage(){
	return errorMessage;
}


void Erreur::addErrorMessage(std::string message){
	error=true;
	errorMessage += message;
}
