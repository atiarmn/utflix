#include "login.h"

User* Login::post(User* logedin_user,std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	if(logedin_user!=NULL)
		throw BadRequest();
	std::hash<std::string> hash_pass;
	std::boolalpha;
	std::string password;
	password=hash_pass(informations["password"]);
	if(database->existed_username(informations["username"])){
		if(database->correct_password(informations["username"],password)){
			return database->get_user(informations["username"]);
		}
		else
			throw BadRequest();
	}
	else 
		throw NotFound();
}