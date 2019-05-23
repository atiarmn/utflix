#ifndef COMMENT_H
#define COMMENT_H

#include <string>
#include "comment_service.h"
#include "user.h"

class User;
class CommentService;

class Comment{
public:
	Comment(std::string _content,int _user_id);
	Comment(){}
	void post(User* logedin_user,std::map<std::string,std::string> informations);
	void delete_comment(User* logedin_user,std::map<std::string,std::string> informations);
	void set_id(int _id);
	int get_user_id(){return user_id;}
	int get_id(){return id;}
	void post_reply(std::string content);
	int replies_num(){return replies.size();}
	std::string get_content(){return content;}
	std::string get_reply(int reply_id){return replies[reply_id];}
private:
	CommentService* service;
	std::vector<std::string> replies;
	std::string content;
	int id;
	int user_id;
};

#endif