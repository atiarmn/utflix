#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include "film.h"

class User;
class Film;

class Database{
public:
	static Database* get_instance();
	std::vector<Film*> get_all_films();
	std::vector<User*> get_all_uesers();
	void add_film(Film* film);
	void add_user(User* user);
	int find_last_film();
	int find_last_user();
	bool existed_username(std::string username);
	bool existed_film(int film_id);
	bool correct_password(std::string username,std::string password);
	User* get_user(std::string username);
	Film* get_film(int film_id);
private:
	static Database* instance;
	std::vector<Film*> films;
	std::vector<User*> users;
	Database();
};

#include "user.h"

#endif