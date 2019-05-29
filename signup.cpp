#include "signup.h"


User* Signup::post(User* logedin_user,std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	if(logedin_user!=NULL)
		throw BadRequest();
	if(database->existed_username(informations["username"]))
		throw BadRequest();
	if(informations["publisher"]=="true"){
		User* new_user = new Publisher(informations);
		database->add_user(new_user);
		return new_user;
	}
	else if(informations["publisher"]=="false" || informations["publisher"]=="\0"){
		User* new_user = new User(informations);
		database->add_user(new_user);
		return new_user;
	}
	else
		throw BadRequest();
}