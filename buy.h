#include <map>
#include <string>
#include "database.h"
#include "user.h"
#include "exception.h"
class User;

class Buy{
public:
	void post(User* logedin_user,std::map<std::string,std::string> informations);
};
