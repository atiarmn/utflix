#ifndef FILM_SERVICE_H
#define FILM_SERVICE_H

#include "film.h"
#include <string>
#include <map>
#include <iomanip>
#include "database.h"
#include "exception.h"
#include "user.h"

class Film;
class User;

class FilmService{
public:
	void post(Film* new_film,User* logedin_user);
	void put(User* logedin_user,std::map<std::string,std::string> informations);
	void delete_film(std::map<std::string,std::string> informations);
	void get(User* logedin_user,std::map<std::string,std::string> informations);
	void rate(User* logedin_user,std::map<std::string,std::string> informations);
	void search(User* logedin_user,std::map<std::string,std::string> informations,std::string input);
	void get_purchased(User* logedin_user,std::map<std::string,std::string> informations);
	std::vector<Film*> recommend(int film_id);
	void print(Film* film,int num);
};

#endif