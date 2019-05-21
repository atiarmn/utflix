#include "money.h"

void Money::post_user(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw BadRequest();
	int amount=std::stoi(informations["amount"],nullptr,0);
	logedin_user->add_money(amount);
}