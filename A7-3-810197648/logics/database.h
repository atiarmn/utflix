#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <utility>
#include "film.h"

class User;
class Film;

class Database{
public:
	~Database();
	
	static Database* get_instance();

	void add_film(Film* film);
	void add_user(User* user);
	void add_network_money(int money);
	void set_publisher_money(User* logedin_user);
	void add_to_recommends(User* logedin_user,int film_id);
	void remove_from_recommend(int film_id);
	void login(int id);
	void logout(int id);
	
	int find_last_film();
	int find_last_user();

	float get_network_money(){return network_money;}

	bool existed_username(std::string username);
	bool existed_film(int film_id);
	bool correct_password(std::string username,std::string password);
	bool existed_user_id(int user_id);
	bool is_loggedin(int id);
	
	User* get_user_by_id(int id);
	User* get_user(std::string username);
	Film* get_film(int film_id);
	Film* best_film();
	
	std::vector<Film*> get_sorted_films_by_id();
	std::vector<User*> get_all_users();
	std::vector<int> recommend(int film_id);
private:
	static Database* instance;
	void sort_films_by_id();
	float network_money;
	std::vector<std::vector<int> > recommend_matrix;
	std::vector<Film*>sorted_films;
	std::vector<Film*> films;
	std::vector<User*> users;
	std::vector<int> loggedin_users;
	Database();
};

#include "user.h"

#endif