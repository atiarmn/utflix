#include "exception.h"
#include "user.h"

class User;

class Logout{
public:
	User* post(User* logedin_user);
};
