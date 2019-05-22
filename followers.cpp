#include "followers.h"

void Followers::post(User* logedin_user, std::map<std::string,std::string> informations){
	int user_id=std::stoi(informations["user_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_user_id(user_id)){
		User* user = database->get_user_by_id(user_id);
		if(user->get_type()){
			if(logedin_user->existed_follower(user_id))
				throw BadRequest();
			logedin_user->follow_publisher(user_id);
			user->add_follower(logedin_user->get_id());
		}
		else
			throw NotFound();
	}
	else
		throw NotFound();
}