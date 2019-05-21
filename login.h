#ifndef LOGIN_H
#define LOGIN_H

#include <map>
#include "exception.h"
#include "database.h"

class Login{
public:
	User* post(std::map<std::string,std::string> informations);
};
#endif