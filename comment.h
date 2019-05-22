#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "comment_service.h"
#include "user.h"

class User;
class CommentService;

class Comment{
public:
	Comment(std::string _content);
	Comment(){}
	void post(User* logedin_user,std::map<std::string,std::string> informations);
	void delete_comment(User* logedin_user,std::map<std::string,std::string> informations);
	void set_id(int _id);
	int get_id(){return id;}
	std::string get_content(){return content;}
private:
	CommentService* service;
	std::string content;
	int id;
};

#endif