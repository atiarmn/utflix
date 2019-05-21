#include "request.h"
Request::Request(){
	std::map<std::string,std::string> informations ();
}
using namespace std;
void Request::get_informations(std::map<std::string,std::string> _informations){
	informations.clear();
	informations = _informations;
}
void Request::signup(){
	Signup* signup = new Signup();
	logedin_user = new User(informations);
	logedin_user = signup->post(informations);
	std::cout<<"OK"<<std::endl;
}
void Request::login(){
	Login* login = new	Login();
	logedin_user = new User(informations);
	logedin_user = login->post(informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_money_user(){
	Money* money = new Money();
	money->post_user(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_films(){
	if(logedin_user==NULL)
		logedin_user = new User();
	Film* film = new Film(informations,logedin_user->get_id());
	film->post(logedin_user);
	logedin_user->add_film(film->get_id());
	std::cout<<"OK"<<std::endl;
}
void Request::put_films(){
	FilmService* film_service = new FilmService();
	film_service->put(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::delete_films(){
	Film* film = new Film();
	film->delete_film(logedin_user,informations);
	logedin_user->delete_film(std::stoi(informations["film_id"],nullptr,0));
	std::cout<<"OK"<<std::endl;
}