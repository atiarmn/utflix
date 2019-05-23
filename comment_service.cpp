#include "comment_service.h"

void CommentService::post(Comment* comment,std::map<std::string,std::string> informations,User* logedin_user){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	User* publisher;
	if(database->existed_film(film_id)){
		Film* film=database->get_film(film_id);
		if(film->deleted())
			throw NotFound();
		std::string notif;
		publisher=database->get_user_by_id(film->get_publisher_id());
		notif+="User ";
		notif+=logedin_user->get_username();
		notif+=" with id ";
		notif+=std::to_string(logedin_user->get_id());
		notif+=" comment on your film ";
		notif+=film->get_name();
		notif+=" with id ";
		notif+=std::to_string(film->get_id());
		notif+=".";
		publisher->add_notif(notif);
		film->post_comment(comment);
		comment->set_id(film->get_comment_id());
	}
	else
		throw NotFound();

}
void CommentService::delete_comment(std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film=database->get_film(film_id);
		if(film->deleted())
			throw NotFound();
		film->delete_comment(std::stoi(informations["comment_id"],nullptr,0));
	}
	else
		throw NotFound();
}