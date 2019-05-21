#include "publisher.h"

void Publisher::add_film(int film_id){
	posted_films.push_back(film_id);
}
void Publisher::add_follower(int user_id){
	followers.push_back(user_id);
}
void Publisher::delete_film(int film_id){
	posted_films.erase(posted_films.begin()+film_id-1);
}