#include <map>
#include "film.h"
#include "user.h"

class User;

class Rate{
public:
	void post(User* logedin_user,std::map<std::string,std::string> informations);
};
