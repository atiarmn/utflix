#include "logout.h"

User* Logout::post(User* logedin_user){
	if(logedin_user==NULL)
		throw BadRequest();
	else
		return NULL;
}