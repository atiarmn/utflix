#include "buy.h"

void Buy::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		int price=(database->get_film(film_id))->get_price();
		if(logedin_user->get_money() < price)
			throw BadRequest();
		if(database->get_film(film_id)->deleted())
			throw NotFound();
		logedin_user->buy_film(film_id,price);
		database->add_network_money(price);
	}
	else
		throw NotFound();
}