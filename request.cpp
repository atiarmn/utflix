#include "request.h"
Request::Request(){
	std::map<std::string,std::string> informations ();
	Database* database = database->get_instance();
	std::map<std::string,std::string> admin_informations;
	admin_informations["username"]="admin";
	admin_informations["password"]="admin";
	admin = new User(admin_informations);
	database->add_user(admin);
}
Request::~Request(){
	delete logedin_user;
	delete admin;
}
void Request::get_informations(std::map<std::string,std::string> _informations){
	informations.clear();
	informations = _informations;
}
void Request::signup(){
	Signup* signup = new Signup();
	logedin_user = signup->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::login(){
	Login* login = new	Login();
	logedin_user = login->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_money_user(){
	Money* money = new Money();
	money->post_user(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_films(){
	Film* film = new Film(informations,logedin_user);
	film->post(logedin_user);
	logedin_user->add_film(film->get_id());
	std::cout<<"OK"<<std::endl;
}
void Request::put_films(){
	FilmService* film_service = new FilmService();
	film_service->put(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::delete_films(){
	Film* film = new Film();
	logedin_user->delete_film(std::stoi(informations["film_id"],nullptr,0));
	film->delete_film(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::get_films_detail(){
	Film* film = new Film();
	film->get_detail(logedin_user,informations);
}
void Request::post_buy(){
	Buy* buy= new Buy();
	buy->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_followers(){
	Followers* followers = new Followers();
	followers->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_rate(){
	Rate* rate = new Rate();
	rate->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_comments(){
	Comment* comment = new Comment(informations["content"],logedin_user->get_id());
	comment->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::delete_comments(){
	Comment* comment = new Comment();
	comment->delete_comment(logedin_user,informations);
	std::cout<<"OK"<<std::endl;	
}
void Request::post_replies(){
	ReplyService* reply_service = new ReplyService ();
	reply_service->post(logedin_user,informations);
	std::cout<<"OK"<<std::endl;
}
void Request::post_money_publisher(){
	Money* money = new Money();
	money->post_publisher(logedin_user);
	std::cout<<"OK"<<std::endl;
}
void Request::get_notifications(){
	NotifService* notif_service = new NotifService();
	notif_service->get_notifications(logedin_user);
}
void Request::get_notifications_read(){
	NotifService* notif_service = new NotifService();
	notif_service->get_notifications_read(logedin_user,informations);
}
void Request::get_followers(){
	Followers* followers = new Followers();
	followers->get(logedin_user);
}
void Request::get_films_find(){
	Film* film = new Film();
	film->get_films(logedin_user,informations);
}
void Request::get_published(){
	Film* film = new Film();
	film->get_published(logedin_user,informations);
}
void Request::get_purchased(){
	Film* film = new Film();
	film->get_purchased(logedin_user,informations);
}
void Request::logout(){
	Logout* logout = new Logout();
	logedin_user=logout->post(logedin_user);
	std::cout<<"OK"<<std::endl;
}
void Request::get_money(){
	Money* money = new Money();
	money->get(logedin_user);
}