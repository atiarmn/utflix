#include "user.h"
User::User(std::map<std::string,std::string> _informations){
	informations=_informations;
	std::boolalpha;
	std::hash<std::string> hash_pass;
	username=informations["username"];
	password=hash_pass(informations["password"]);
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
void User::add_money(int amount){
	money+=amount;
}
bool User::film_bought(int film_id){
	for(int i=0;i<purchased_films.size();i++)
		if(purchased_films[i]==film_id)
			return true;
	return false;
}
void User::read(){
	for(int i =0;i<unread_notifs.size();i++){
		read_notifs.push_back(unread_notifs[i]);
		unread_notifs[i]="";
	}
	unread_notifs.clear();
}
void User::print_unread_notifs(){
	std::cout<<"#. Notification Message"<<std::endl;
	int num=1;
	for(int i=unread_notifs.size();i>=0;i--){
		std::cout<<num<<". "<<unread_notifs[i]<<std::endl;
		num++;
	}
	read();
}
void User::print_read_notifs(int limit){
	std::cout<<"#. Notification Message"<<std::endl;
	if(limit>read_notifs.size())
		limit=read_notifs.size();
	for(int i=0 ;i<limit;i++)
		std::cout<<i+1<<". "<<read_notifs[i]<<std::endl;
}
void User::add_notif(std::string notif){
	unread_notifs.push_back(notif);
}
std::vector<int> User::get_sorted_purchased(){
	int temp;
	for(int i=0;i<purchased_films.size();i++){
		if(i+1>=purchased_films.size())
			break;
		if(purchased_films[i]>purchased_films[i+1]){
			temp=purchased_films[i];
			purchased_films[i]=purchased_films[i+1];
			purchased_films[i+1]=temp;
		}
	}
	return purchased_films;
}
