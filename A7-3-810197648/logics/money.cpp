#include "money.h"

void Money::post_publisher(User* logedin_user){
	if(logedin_user==NULL)
		throw BadRequest();
	if(!logedin_user->get_type())
		throw BadRequest();
	Database* database = database->get_instance();
	database->set_publisher_money(logedin_user);
}
void Money::post_user(User* logedin_user,std::map<std::string,std::string> informations){
	int amount=std::stoi(informations["amount"],nullptr,0);
	logedin_user->add_money(amount);
}
void Money::get(User* logedin_user){
	Database* database = database->get_instance();
	if(logedin_user==NULL)
		throw BadRequest();
	if(logedin_user->get_id()!=0)
		std::cout<<logedin_user->get_money()<<std::endl;
	else 
		std::cout<<database->get_network_money()<<std::endl;
}