#include "comment.h"

Comment::Comment(std::string _content){
	service = new CommentService();
	content=_content;
}
void Comment::post(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user->film_bought(std::stoi(informations["film_id"],nullptr,0)))
		service->post(this,informations);
	else 
		throw BadRequest();
}
void Comment::set_id(int _id){
	id=_id;
}
void Comment::delete_comment(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user->get_type()){
		if(logedin_user->find_film(std::stoi(informations["film_id"],nullptr,0)))
			service->delete_comment(informations);
		else
			throw BadRequest();
	}
	else
		throw PermissionDen();
}
void Comment::post_reply(std::string content){
	replies.push_back(content);
}