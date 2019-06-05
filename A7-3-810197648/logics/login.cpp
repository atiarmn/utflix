#include "login.h"
#include "../server/server.hpp"

std::string Login::post(std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	std::hash<std::string> hash_pass;
	std::boolalpha;
	std::string password;
	password=hash_pass(informations["password"]);
	if(database->existed_username(informations["username"])){
		if(database->correct_password(informations["username"],password))
			if(database->get_user(informations["username"])->get_type())
				return "/homepage?type=publisher";
			else
				return "/homepage?type=user";
		else
			return "/error?error_msg=Password+is+incorrect&url=login";
	}
	else 
		return "/error?error_msg=Username+doesnt+exist&url=login";
}