#include "buy.h"

void Buy::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	User* publisher;
	std::string notif;
	database->add_to_recommends(logedin_user,film_id);
	if(database->existed_film(film_id)){
		int price=(database->get_film(film_id))->get_price();
		if(logedin_user->get_money() < price)
			throw BadRequest();
		logedin_user->buy_film(film_id,price);
		database->add_network_money(price);
	}
}