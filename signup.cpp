#include "signup.h"


void Signup::post(std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	if(database->existed_username(informations["username"]))
		throw BadRequest();
	if(informations["publisher"]=="true"){
		User* new_user = new Publisher(informations);
		database->add_user(new_user);
	}
	else if(informations["publisher"]=="false" || informations["publisher"]=="\0"){
		User* new_user = new User(informations);
		database->add_user(new_user);
	}
	else
		throw BadRequest();
}