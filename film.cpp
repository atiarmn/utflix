#include "film.h"
Film::Film(std::map<std::string,std::string> informations,int _publisher_id){
	name=informations["name"];
	price=informations["price"];
	year=informations["year"];
	length=informations["length"];
	summary=informations["summary"];
	director=informations["director"];
	publisher_id=_publisher_id;
	rate=0;
	is_deleted=false;
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
	is_deleted=true;
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
void Film::get_detail(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw PermissionDen();
	int film_id=std::stoi(informations["film_id"],nullptr,0);
	service->get(informations);
}
void Film::print_details(){
	std::cout<<"Details of Film "<<name<<std::endl;
	std::cout<<"Id = "<<id<<std::endl;
	std::cout<<"Director = "<<director<<std::endl;
	std::cout<<"Length = "<<length<<std::endl;
	std::cout<<"Year = "<<year<<std::endl;
	std::cout<<"Summary = "<<summary<<std::endl;
	std::cout<<"Director = "<<director<<std::endl;
	std::cout<<"Rate = "<<rate<<std::endl;
	std::cout<<"Price = "<<price<<"\n"<<std::endl;
	std::cout<<"Comments"<<std::endl;
	for(int i=0;i<comments.size();i++){
		std::cout<<comments[i]->get_id()<<" ";
		std::cout<<comments[i]->get_content()<<std::endl;
	}

}
void Film::set_rate(int _rate){
	rate=(_rate+rate)/2;
}
void Film::post_rate(std::map<std::string,std::string> informations){
	service->rate(informations);
}
void Film::post_comment(Comment* new_comment){
	comments.push_back(new_comment);
}
int Film::get_comment_id(){
	return comments.size();
}
void Film::delete_comment(int comment_id){
	comments.erase(comments.begin()+comment_id-1);
}
