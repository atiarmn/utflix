#ifndef SIGNUP_H
#define SIGNUP_H

#include "database.h"
#include "publisher.h"
#include "exception.h"
#include "user.h"
#include <string>
#include <iostream>
#include <map>

class Signup{
public:
	User* post(User* logedin_user,std::map<std::string,std::string> informations);	
};
#endif
