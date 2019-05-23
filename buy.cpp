#include "buy.h"

void Buy::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	User* publisher;
	std::string notif;
	if(database->existed_film(film_id)){
		int price=(database->get_film(film_id))->get_price();
		if(logedin_user->get_money() < price)
			throw PermissionDen();
		if(database->get_film(film_id)->deleted())
			throw NotFound();
		publisher=database->get_user_by_id((database->get_film(film_id))->get_publisher_id());
		notif+="User ";
		notif+=logedin_user->get_username();
		notif+=" with id ";
		notif+=std::to_string(logedin_user->get_id());
		notif+=" buy your film ";
		notif+=database->get_film(film_id)->get_name();
		notif+=" with id ";
		notif+=std::to_string(database->get_film(film_id)->get_id());
		notif+=".";
		publisher->add_notif(notif);
		logedin_user->buy_film(film_id,price);
		database->add_network_money(price);
	}
	else
		throw NotFound();
}