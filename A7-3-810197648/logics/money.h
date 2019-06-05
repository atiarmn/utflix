#include <map>
#include <string>
#include <iostream>
#include "user.h"
#include "exception.h"

class Money{
public:
	void post_publisher(User* logedin_user);
	void post_user(User* logedin_user,std::map<std::string,std::string> informations);
	void get(User* logedin_user);
};