#include "user.h"
User::User(std::map<std::string,std::string> _informations){
	informations=_informations;
	username=informations["username"];
	password=informations["password"];
	email=informations["email"];
	age=informations["age"];
	money = 0;
	Database* database = database->get_instance();
	id=database->find_last_user()+1;
	if(informations["publisher"]=="true")
		type=PUBLISHER;
	else
		type=USER;
}
User::User(){
	id=0;
}
void User::get_login(){
	login=true;
}
void User::buy_film(int film_id,int price){
	if(film_bought(film_id))
		return;
	money-=price;
	purchased_films.push_back(film_id);
}

void User::follow_publisher(int pub_id){
	followed_publishers.push_back(pub_id);
}
bool User::existed_follower(int pub_id){
	for(int i =0 ;i <followed_publishers.size();i++)
		if(followed_publishers[i]==pub_id)
			return true;
	return false;
}
std::string User::get_username(){
	return username;
}
std::string User::get_password(){
	return password;
}
void User::add_money(int amount){
	money+=amount;
}
bool User::film_bought(int film_id){
	for(int i=0;i<purchased_films.size();i++)
		if(purchased_films[i]==film_id)
			return true;
	return false;
}

