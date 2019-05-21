#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include <string>
#include <iostream>
#include "signup.h"
#include "film.h"
#include "user.h"
#include "film_service.h"
#include "exception.h"
#include "login.h"
#include "money.h"
#include <map>

class Request{
public:
	Request();
	void get_informations(std::map<std::string,std::string> _informations);
	void signup();
	void login();
	void post_money_user();
	void post_films();
	void put_films();
	void delete_films();
	void post_money_publisher(){}
	void get_followers(){}
	void get_published(){}
	void post_replies(){}
	void delete_comments(){}
	void post_followers(){}
	void get_films_find(){}
	void get_films_detail(){}
	void post_buy(){}
	void post_rate(){}
	void post_comments(){}
	void get_purchased(){}
	void get_notification(){}
	void get_notification_read(){}
private:
	std::map<std::string, std::string> informations;
	User* logedin_user;
};

#endif