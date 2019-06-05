#include "signup.h"


std::string Signup::post(std::map<std::string,std::string> informations){
	Database* database = database->get_instance();
	if(database->existed_username(informations["username"]))
			return "/error?error_msg=Username+exists&url=/signup";
	if(informations["publisher"]=="true"){
		User* new_user = new Publisher(informations);
		database->add_user(new_user);
		return "/homepage?type=publisher";
	}
	else {
		User* new_user = new User(informations);
		database->add_user(new_user);
		return "/homepage?type=user";
	}
}