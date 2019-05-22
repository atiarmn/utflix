#ifndef FILM_H
#define FILM_H

#include "database.h"
#include "film_service.h"
#include <map>
#include <string>
#include "user.h"
#include "comment.h"

class FilmService;
class Comment;

class Film{
public:
	Film(std::map<std::string,std::string> informations,int _publisher_id);
	Film();
	void post(User* logedin_user);
	void delete_film(User* logedin_user,std::map<std::string,std::string> informations);
	void put(std::map<std::string,std::string> informations);
	void get_detail(User* logedin_user,std::map<std::string,std::string> informations);
	void post_rate(std::map<std::string,std::string> informations);
	int get_id(){return id;}
	void delete_comment(int comment_id);
	int get_price(){return std::stoi(price,nullptr,0);}
	void set_delete();
	bool deleted(){return is_deleted;}
	void set_rate(int _rate);
	void print_details();
	void post_comment(Comment* new_comment);
	int get_comment_id();
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
	std::vector<Comment*> comments;
	bool is_deleted;
	int id;
	int point;
};

#endif