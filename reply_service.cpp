#include "reply_service.h"

void ReplyService::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	int comment_id=std::stoi(informations["comment_id"],nullptr,0);
	std::string notif;
	if(!(logedin_user->get_type()))
		throw PermissionDen();
	if(logedin_user->find_film(film_id)){
		Database* database = database->get_instance();
		Film* film=database->get_film(film_id);
		Comment* comment=film->find_comment(comment_id);
		comment->post_reply(informations["content"]);
		notif+="Publisher ";
		notif+=logedin_user->get_username();
		notif+=" with id ";
		notif+=std::to_string(logedin_user->get_id());
		notif+=" reply to your comment.";
		(database->get_user_by_id(comment->get_user_id()))->add_notif(notif);
}
	else
		throw NotFound();
}