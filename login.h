#ifndef LOGIN_H
#define LOGIN_H

#include <map>
#include <functional>
#include "exception.h"
#include "database.h"

class Login{
public:
	User* post(User* logedin_user,std::map<std::string,std::string> informations);
};
#endif