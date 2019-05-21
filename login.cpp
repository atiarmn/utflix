#include "login.h"

User* Login::post(std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	if(database->existed_username(informations["username"])){
		if(database->correct_password(informations["username"],informations["password"]))
			return database->get_user(informations["username"]);
		else
			throw BadRequest();
	}
	else 
		throw NotFound();
}