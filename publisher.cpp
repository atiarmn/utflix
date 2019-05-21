#include "publisher.h"

void Publisher::add_film(int film_id){
	post_films.push_back(film_id);
}
void Publisher::add_follower(int user_id){
	followers.push_back(user_id);
}