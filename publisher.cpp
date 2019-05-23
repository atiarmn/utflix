#include "publisher.h"

void Publisher::add_film(int film_id){
	posted_films.push_back(film_id);
}
void Publisher::send_notif_to_followers(){
	Database* database = database->get_instance();
	std::string notif;
	notif+="Publisher ";
	notif+=username;
	notif+=" with id ";
	notif+=std::to_string(id);
	notif+=" register new film.";
	for(int i =0;i<followers.size();i++){
		std::cout<<i<<std::endl;
		(database->get_user_by_id(followers[i]))->add_notif(notif);
	}
}
void Publisher::sort_followers(){
	int temp;
	for(int i=0;i<followers.size();i++){
		if(i+1==followers.size())
			break;
		if(followers[i]>followers[i+1]){
			temp=followers[i];
			followers[i]=followers[i+1];
			followers[i+1]=temp;
		}
	}
}
void Publisher::add_follower(int user_id){
	followers.push_back(user_id);
	sort_followers();
}
void Publisher::delete_film(int film_id){
	for(int i=0;i<posted_films.size();i++)
		if(posted_films[i]==film_id){
			posted_films.erase(posted_films.begin()+film_id-1);
			return;
		}
	throw NotFound();
}
bool Publisher::find_film(int film_id){
	for(int i=0;i<posted_films.size();i++)
		if(posted_films[i]==film_id)
			return true;
	return false;
}