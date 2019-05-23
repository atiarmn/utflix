#include "followers.h"

void Followers::post(User* logedin_user, std::map<std::string,std::string> informations){
	int user_id=std::stoi(informations["user_id"],nullptr,0);
	Database* database = database->get_instance();
	if(logedin_user==NULL)
		throw BadRequest();
	if(database->existed_user_id(user_id)){
		User* user = database->get_user_by_id(user_id);
		if(user->get_type()){
			if(logedin_user->existed_follower(user_id))
				throw BadRequest();
			logedin_user->follow_publisher(user_id);
			user->add_follower(logedin_user->get_id());
			std::string notif;
			notif+="User ";
			notif+=logedin_user->get_username();
			notif+=" with id ";
			notif+=std::to_string(logedin_user->get_id());
			notif+=" follow you.";
			user->add_notif(notif);
		}
		else
			throw NotFound();
	}
	else
		throw NotFound();
}
void Followers::get(User* logedin_user){
	if(logedin_user==NULL)
		throw PermissionDen();
	if(!(logedin_user->get_type()))
		throw PermissionDen();
	Database* database = database->get_instance();
	std::cout<<"List of Followers"<<std::endl;
	std::cout<<"#. User Id | User Username | User Email"<<std::endl;
	for(int i=0;i<(logedin_user->get_followers()).size();i++){
		std::cout<<i+1<<". "<<database->get_user_by_id((logedin_user->get_followers())[i])->get_id()<<" | ";
		std::cout<<database->get_user_by_id((logedin_user->get_followers())[i])->get_username()<<" | ";
		std::cout<<database->get_user_by_id((logedin_user->get_followers())[i])->get_email()<<" | "<<std::endl;
	}
}
