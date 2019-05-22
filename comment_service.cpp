#include "comment_service.h"

void CommentService::post(Comment* comment,std::map<std::string,std::string> informations){
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	Database* database = database->get_instance();
	if(database->existed_film(film_id)){
		Film* film=database->get_film(film_id);
		if(film->deleted())
			throw NotFound();
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