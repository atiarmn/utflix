#ifndef USER_H
#define USER_H

#include "database.h"
#include "exception.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>

#define USER 0
#define PUBLISHER 1

class Database;

class User{
public:
	User(std::map<std::string,std::string> _informations);
	User();
	void get_login();
	void buy_film(int film_id,int price);
	void follow_publisher(int pub_id);
	std::string get_username();
	std::string get_password();
	void add_money(int amount);
	int get_type(){return type;}
	int get_id(){return id;}
	int get_money(){return money;}
	bool film_bought(int film_id);
	bool existed_follower(int pub_id);
	virtual void add_film(int film_id){throw PermissionDen();}
	virtual void delete_film(int film_id){throw PermissionDen();}
	virtual bool find_film(int film_id){throw PermissionDen();}
	virtual void add_follower(int user_id){}
protected:
	int type;
	int id;
	bool login;
	int money;
	std::string age;
	std::string username;
	std::string password;
	std::string email;
	std::map<std::string,std::string> informations;
	std::vector<int> purchased_films;
	std::vector<int> followed_publishers;
};

#endif