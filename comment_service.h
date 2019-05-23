#ifndef COMMENT_SERVICE_H
#define COMMENT_SERVICE_H

#include <map>
#include <string>
#include "comment.h"
#include "database.h"
#include "exception.h"
#include "film.h"
#include "user.h"

class Comment;
class User;

class CommentService{
public:
	void post(Comment* comment,std::map<std::string,std::string> informations,User* logedin_user);
	void delete_comment(std::map<std::string,std::string> informations);
};

#endif