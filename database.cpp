#include "database.h"

Database* Database::instance = 0;

Database* Database::get_instance() {
      if (instance == 0)
      	instance = new Database();
      return instance;
}
// std::vector<Film*> Database::get_films(){
// 	return this->films;
// }
std::vector<User*> Database::get_all_uesers(){
	return this->users;
}
// void Database::add_film(Film* film){
// 	(this->films).push_back(film);
// }
void Database::add_user(User* user){
	(this->users).push_back(user);
}
// Film* Database::search_film(int film_id){
// 	for(int i=0;i<films.size();i++)
// 		if(films[i]->get_id()==film_id)
// 			return films[i];
// }
// void Database::delete_film(int film_id){
// 	for(int i=0;i<films.size();i++)
// 		if(films[i]->get_id()==film_id)
// 			films.erase(films.begin()+i);
// }
int Database::find_last_user(){
	return users.size();
}
bool Database::existed_username(std::string username){
	for(int i=0;i<users.size();i++)
		if(users[i]->get_username()==username)
			return true;
	return false;
}
bool Database::correct_password(std::string username,std::string password){
	for(int i=0;i<users.size();i++)
		if(users[i]->get_username()==username && users[i]->get_password()==password)
			return true;
	return false;
}
User* Database::get_user(std::string username){
	for(int i=0;i<users.size();i++)
		if(users[i]->get_username()==username)
			return users[i];
}
void Database::add_money_user(std::string username , int amount){
	get_user(username)-
}
Database::Database() {}
