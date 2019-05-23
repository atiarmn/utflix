#include "film_service.h"

void FilmService::post(Film* new_film,User* logedin_user){
	Database* database = database->get_instance();
	database->add_film(new_film);
	logedin_user->send_notif_to_followers();
}

void FilmService::put(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw PermissionDen();
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id) && logedin_user->find_film(film_id)){
		(database->get_film(film_id))->put(informations);
	}
	else
		throw NotFound();
}
void FilmService::delete_film(std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film=database->get_film(film_id);
		film->set_delete();
	}
	else 
		throw NotFound(); 	
}
void FilmService::get(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film = database->get_film(film_id);	
		if(film->deleted())
			throw NotFound();
		film->print_details(logedin_user);
	}
	else
		throw NotFound();
}
void FilmService::search(std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	std::string name,director,price;
	int min_rate,min_year,max_year,num=1;
	name=informations["name"];
	if(informations["min_rate"]=="\0")
		min_rate=0;
	else
		min_rate=std::stoi(informations["min_rate"],nullptr,0);
	if(informations["min_year"]=="\0")
		min_year=0;
	else
		min_year=std::stoi(informations["min_year"],nullptr,0);
	price=informations["price"];
	if(informations["max_year"]=="\0")
		max_year=0;
	else
		max_year=std::stoi(informations["max_year"],nullptr,0);
	director=informations["director"];
	std::cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<std::endl;
	for(int i=0;i<(database->get_all_users()).size();i++){
		if(!((database->get_all_users())[i]->get_type()))
			continue;
		for(int j=0;j<(database->get_sorted_films((database->get_all_users())[i]).size());j++){
			if(database->get_sorted_films((database->get_all_users())[i])[j]->check_name(name) &&
			database->get_sorted_films((database->get_all_users())[i])[j]->check_rate(min_rate) &&
			database->get_sorted_films((database->get_all_users())[i])[j]->check_min_year(min_year)&&
			database->get_sorted_films((database->get_all_users())[i])[j]->check_max_year(max_year)&&
			database->get_sorted_films((database->get_all_users())[i])[j]->check_price(price)&&
			database->get_sorted_films((database->get_all_users())[i])[j]->check_director(director)){
				print(database->get_sorted_films((database->get_all_users())[i])[j],num);
				num++;
			}

		}
	}
}
void FilmService::print(Film* film,int num){
	std::cout<<num<<". ";
	std::cout<<film->get_id()<<" | ";
	std::cout<<film->get_name()<<" | ";
	std::cout<<film->get_length()<<" | ";
	std::cout<<film->get_price()<<" | ";
	std::cout<<film->get_rate()<<" | ";
	std::cout<<film->get_year()<<" | ";
	std::cout<<film->get_director()<<" | "<<std::endl;
}
void FilmService::rate(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	int score = std::stoi(informations["score"],nullptr,0);
	User* publisher;
	std::string notif; 
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film = database->get_film(film_id);
		if(film->deleted())
			throw NotFound();
		film->set_rate(logedin_user->get_id(),score);
		publisher=database->get_user_by_id((database->get_film(film_id))->get_publisher_id());
		notif+="User ";
		notif+=logedin_user->get_username();
		notif+=" with id ";
		notif+=std::to_string(logedin_user->get_id());
		notif+=" rate your film ";
		notif+=database->get_film(film_id)->get_name();
		notif+=" with id ";
		notif+=std::to_string(database->get_film(film_id)->get_id());
		notif+=".";
		publisher->add_notif(notif);
	}
	else
		throw NotFound();
}
std::vector<Film*> FilmService::recommend(User* logedin_user){
	Database* database = database->get_instance();
	return database->get_sorted_films(logedin_user);
}