#include <map>
#include <string>
#include <vector>

#include "user.h"
#include "exception.h"
#include "database.h"
class Followers{
public: 
	void post(User* logedin_user, std::map<std::string,std::string> informations);
	void get(User* logedin_user);
};
