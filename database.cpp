#include "database.h"

Database* Database::instance = 0;

Database* Database::get_instance() {
      if (instance == 0)
      	instance = new Database();
      return instance;
}
std::vector<Film*> Database::get_all_films(){
	return this->films;
}
std::vector<User*> Database::get_all_uesers(){
	return this->users;
}
void Database::add_film(Film* film){
	(this->films).push_back(film);
}
void Database::add_user(User* user){
	(this->users).push_back(user);
}
Film* Database::get_film(int film_id){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_id()==film_id)
			return films[i];
}

int Database::find_last_user(){
	return users.size();
}
bool Database::existed_username(std::string username){
	for(int i=0;i<users.size();i++)
		if(users[i]->get_username()==username)
			return true;
	return false;
}
bool Database::existed_user_id(int user_id){
	for(int i=0;i<users.size();i++)
		if(i+1==user_id)
			return true;
	return false;
}
bool Database::existed_film(int film_id){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_id()==film_id)
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
User* Database::get_user_by_id(int id){
	for(int i=0;i<users.size();i++)
		if(i+1==id)
			return users[i];
	throw NotFound();
}
int Database::find_last_film(){
	return films.size();
}
void Database::add_network_money(int money){
	network_money+=money;
}
void Database::set_publisher_money(User* logedin_user){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_publisher_id()==logedin_user->get_id())
			for(int j=0;j<users.size();j++){
				if(users[j]->film_bought(films[i]->get_id())){
					if(films[i]->get_type()=="weak"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.2);
						logedin_user->add_money(films[i]->get_price()*(0.8));
					}
					if(films[i]->get_type()=="avarage"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.1);
						logedin_user->add_money(films[i]->get_price()*(0.9));
					}
					if(films[i]->get_type()=="good"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.05);
						logedin_user->add_money(films[i]->get_price()*(0.95));
					}
				}
			}
}
Database::Database() {}
