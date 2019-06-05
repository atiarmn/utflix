#ifndef LOGIN_H
#define LOGIN_H

#include <map>
#include <functional>
#include "exception.h"
#include "database.h"

class Login{
public:
	std::string post(std::map<std::string,std::string> informations);
};
#endif