#include "film.h"
Film::Film(std::map<std::string,std::string> informations,int _publisher_id){
	name=informations["name"];
	price=informations["price"];
	year=informations["year"];
	length=informations["length"];
	summary=informations["summary"];
	director=informations["director"];
	publisher_id=_publisher_id;
	deleted=false;
	if(publisher_id==0)
		throw PermissionDen();
	point=0;
	Database* database = database->get_instance();
	id=database->find_last_film()+1;
	service=new	FilmService();
}
Film::Film(){
	point=0;
	service=new	FilmService();
}
void Film::post(User* logedin_user){
	if(logedin_user==NULL)
		throw PermissionDen();
	service->post(this);
}
void Film::put(std::map<std::string,std::string> informations){
	change_infos(informations);
}
void Film::set_delete(){
	deleted=true;
}
void Film::change_infos(std::map<std::string,std::string> informations){
	if(informations["name"]!="\0")
			name=informations["name"];
	if(informations["price"]!="\0")
		price=informations["price"];
	if(informations["year"]!="\0")
		year=informations["year"];
	if(informations["length"]!="\0")
		length=informations["length"];
	if(informations["summary"]!="\0")
		summary=informations["summary"];
	if(informations["director"]!="\0")
		director=informations["director"];
}
void Film::delete_film(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw PermissionDen();
	service->delete_film(informations);
}


