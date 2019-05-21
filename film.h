#ifndef FILM_H
#define FILM_H

#include "database.h"
#include "film_service.h"
#include <map>
#include <string>
#include "user.h"

class FilmService;

class Film{
public:
	Film(std::map<std::string,std::string> informations,int _publisher_id);
	Film();
	void post(User* logedin_user);
	void delete_film(User* logedin_user,std::map<std::string,std::string> informations);
	void put(std::map<std::string,std::string> informations);
	void get(User* logedin_user,std::map<std::string,std::string> informations);
	int get_id(){return id;}
	void set_delete();
	void print_details();
protected:
	FilmService* service;
	void change_infos(std::map<std::string,std::string> informations);
	int publisher_id;
	float rate;
	std::string name;
	std::string price;
	std::string year;
	std::string length;
	std::string summary;
	std::string director;
	bool deleted;
	int id;
	int point;
};

#endif