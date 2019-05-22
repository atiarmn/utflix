#include <map>
#include "film.h"
#include "user.h"

class User;

class Rate{
public:
	void post(User* user,std::map<std::string,std::string> informations);
};
