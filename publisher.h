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
private:
	std::vector<int> post_films;	
	std::vector<int> followers;	
};

#endif