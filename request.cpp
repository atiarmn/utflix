#include "request.h"
Request::Request(){
	std::map<std::string,std::string> informations ();
}
using namespace std;
void Request::get_informations(std::map<std::string,std::string> _informations){
	informations.clear();
	informations = _informations;
}
void Request::signup(){
	Signup* signup = new Signup();
	signup->post(informations);
	std::cout<<"OK"<<std::endl;
	logedin_user = new User(informations);
}
void Request::login(){
	Login* login = new	Login();
	logedin_user = new User(informations);
	logedin_user = login->post(informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_money_user(){
	Money* money = new Money();
	money->post_user(logedin_user,informations);
	std::cout<<"OK"<<std::endl;

}