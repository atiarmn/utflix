#ifndef FILM_SERVICE_H
#define FILM_SERVICE_H

#include "film.h"
#include <string>
#include <map>
#include "database.h"
#include "exception.h"
#include "user.h"

class Film;
class User;

class FilmService{
public:
	void post(Film* new_film);
	void put(User* logedin_user,std::map<std::string,std::string> informations);
	void delete_film(std::map<std::string,std::string> informations);
	void get(std::map<std::string,std::string> informations){}
};

#endif