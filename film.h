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
	void set_rate(int user_id,int _rate);
	void print_details(User* logedin_user);
	void post_comment(Comment* new_comment);
	void get_detail(User* logedin_user,std::map<std::string,std::string> informations);
	void get_films(std::map<std::string,std::string> informations);
	void post_rate(User* logedin_user,std::map<std::string,std::string> informations);
	void delete_comment(int comment_id);
	void set_delete();

	int get_id(){return id;}
	int get_price(){return std::stoi(price,nullptr,0);}
	int get_publisher_id(){return publisher_id;}
	int get_comment_id();

	float get_rate(){return rate;}

	bool deleted(){return is_deleted;}
	bool check_name(std::string _name);
	bool check_rate(int min_rate);
	bool check_price(std::string _price);
	bool check_max_year(int max_year);
	bool check_min_year(int min_year);
	bool check_director(std::string _director);

	Comment* find_comment(int comment_id);
	std::string get_director(){return director;}
	std::string get_name(){return name;}
	std::string get_length(){return length;}
	std::string get_year(){return year;}
	std::string get_type(){return type;}
protected:
	FilmService* service;
	void change_infos(std::map<std::string,std::string> informations);
	float rate;
	bool is_deleted;
	int publisher_id;
	int id;
	int point;
	std::string type;
	std::map<int,int> rates;
	std::string name;
	std::string price;
	std::string year;
	std::string length;
	std::string summary;
	std::string director;
	std::vector<Comment*> comments;
};

#endif