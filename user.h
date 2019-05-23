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

	std::string get_username();
	std::string get_password();

	int get_type(){return type;}
	int get_id(){return id;}
	int get_money(){return money;}
	std::string get_email(){return email;}

	void get_login();
	void buy_film(int film_id,int price);
	void follow_publisher(int pub_id);
	void add_money(int amount);
	void print_unread_notifs();
	void print_read_notifs(int limit);
	void add_notif(std::string notif);

	bool film_bought(int film_id);
	bool existed_follower(int pub_id);

	virtual void add_film(int film_id){throw PermissionDen();}
	virtual void delete_film(int film_id){throw PermissionDen();}
	virtual bool find_film(int film_id){throw PermissionDen();}
	virtual void add_follower(int user_id){}
	virtual void send_notif_to_followers(){}
	virtual std::vector<int> get_followers(){throw PermissionDen();}
protected:
	void read();
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
	std::vector<std::string> unread_notifs;
	std::vector<std::string> read_notifs;
};

#endif