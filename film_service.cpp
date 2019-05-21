#include "film_service.h"

void FilmService::post(Film* new_film){
	Database* database = database->get_instance();
	database->add_film(new_film);
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
void FilmService::get(std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film = database->get_film(film_id);	
		film->print_details();
	}
}
