#include "rate.h"

void Rate::post(User* logedin_user,std::map<std::string,std::string> informations){
	Film* film = new Film();
	if(logedin_user->film_bought(std::stoi(informations["film_id"],nullptr,0)))
		film->post_rate(logedin_user,informations);
	else
		throw PermissionDen();
}