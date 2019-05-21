#include "buy.h"

void Buy::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id))
		logedin_user->buy_film(film_id);
	else
		throw NotFound();
}