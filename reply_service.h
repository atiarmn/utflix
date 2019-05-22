#ifndef REPLY_SERVICE_H
#define REPLY_SERVICE_H

#include <map>
#include <string>
#include "user.h"
#include "comment.h"
#include "film.h"
#include "exception.h"

class User;

class ReplyService{
public:
	void post(User* logedin_user,std::map<std::string,std::string> informations);
};

#endif