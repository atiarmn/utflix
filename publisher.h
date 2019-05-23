#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "user.h"
#include <vector>
#include <string>
#include <iostream>

class Publisher:public User{
public:
	Publisher(std::map<std::string,std::string> _informations):User(_informations){type=PUBLISHER;}

	void add_film(int film_id);
	void add_follower(int user_id);
	void delete_film(int film_id);
	void send_notif_to_followers();
		
	std::vector<int> get_followers(){return followers;}

	bool find_film(int film_id);
private:
	void sort_followers();
	std::vector<int> posted_films;	
	std::vector<int> followers;	
};

#endif