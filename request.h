#ifndef REQUEST_H
#define REQUEST_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "signup.h"
#include "film.h"
#include "user.h"
#include "film_service.h"
#include "exception.h"
#include "login.h"
#include "money.h"
#include "buy.h"
#include "followers.h"
#include "rate.h"
#include "comment.h"
#include "comment_service.h"
#include "reply_service.h"
#include "notif_service.h"

class Request{
public:
	Request();
	~Request();
	void get_informations(std::map<std::string,std::string> _informations);
	void signup();
	void login();
	void post_money_user();
	void post_films();
	void put_films();
	void delete_films();
	void get_films_detail();
	void post_buy();
	void post_followers();
	void post_rate();
	void post_comments();
	void delete_comments();
	void post_replies();
	void post_money_publisher();
	void get_notifications();
	void get_notifications_read();
	void get_followers();
	void get_films_find();
	void get_published();
	void get_purchased();
private:
	std::map<std::string, std::string> informations;
	User* logedin_user;
};

#endif