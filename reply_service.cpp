#include "reply_service.h"

void ReplyService::post(User* logedin_user,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	int comment_id=std::stoi(informations["comment_id"],nullptr,0);
	if(!(logedin_user->get_type()))
		throw PermissionDen();
	if(logedin_user->find_film(film_id)){
		Database* database = database->get_instance();
		Film* film=database->get_film(film_id);
		Comment* comment=film->find_comment(comment_id);
		comment->post_reply(informations["content"]);
}
	else
		throw NotFound();
}