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
std::vector<Film*> FilmService::get_films(User* logedin_user){
	Database* database = database->get_instance();
	std::vector<Film*> films;
	for(int i=0;i<(database->get_sorted_films_by_id().size());i++)
		if(database->get_sorted_films_by_id()[i]->get_price()<=logedin_user->get_money() 
		&& !database->get_sorted_films_by_id()[i]->deleted()
		&& !logedin_user->film_bought(database->get_sorted_films_by_id()[i]->get_id())){
			films.push_back(database->get_sorted_films_by_id()[i]);
		}
	return films;
}
std::vector<Film*> FilmService::get_published_films(User* logedin_user,std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	std::vector<Film*> published_films;
	int num=1;
	std::string director;
	director=informations["director"];
	for(int i=0;i<(database->get_all_users()).size();i++){
		if((database->get_all_users())[i]->get_id()!=logedin_user->get_id())
			continue;
		if(!((database->get_all_users())[i]->get_type()))
			continue;
		for(int j=0;j<(database->get_sorted_films_by_id().size());j++){
			if(database->get_sorted_films_by_id()[j]->get_publisher_id()!=logedin_user->get_id())
				continue;
			if(database->get_sorted_films_by_id()[j]->check_director(director) &&
			!(database->get_sorted_films_by_id()[j]->deleted())){
				published_films.push_back(database->get_sorted_films_by_id()[j]);
			}
		}
	}
	return published_films;
}
void FilmService::delete_film(std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film=database->get_film(film_id);
		film->set_delete();
		database->remove_from_recommend(film_id);
	}
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
void FilmService::print(Film* film,int num){
	std::cout<<num<<". ";
	std::cout<<film->get_id()<<" | ";
	std::cout<<film->get_name()<<" | ";
	std::cout<<film->get_length()<<" | ";
	std::cout<<film->get_price()<<" | ";
	std::cout<<std::setprecision(2)<<film->get_rate()<<" | ";
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
	}
}
std::vector<Film*> FilmService::recommend(int film_id){
	Database* database = database->get_instance();
	std::vector<Film*> recommend_films;
	for(int i=database->recommend(film_id).size()-1;i>=0;i--)
		recommend_films.push_back(database->get_film(database->recommend(film_id)[i]));
	return recommend_films;	
}
std::vector<Film*> FilmService::get_purchased(User* logedin_user){
	Database* database = database->get_instance();
	std::vector<Film*> purchased_films;
	for(int i=0;i<(logedin_user->get_sorted_purchased()).size();i++){
		purchased_films.push_back(database->get_film(logedin_user->get_sorted_purchased()[i]));
	}
	return purchased_films;
}