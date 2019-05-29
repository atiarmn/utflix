#include "film.h"
Film::Film(std::map<std::string,std::string> informations,User* logedin_user){
	if(logedin_user==NULL)
		throw PermissionDen();
	name=informations["name"];
	price=informations["price"];
	year=informations["year"];
	length=informations["length"];
	summary=informations["summary"];
	director=informations["director"];
	publisher_id=logedin_user->get_id();
	rate=0;
	is_deleted=false;
	point=0;
	Database* database = database->get_instance();
	id=database->find_last_film()+1;
	service=new	FilmService();
}
Film::Film(){
	point=0;
	service=new	FilmService();
}
Film::~Film(){
	delete service;
}
void Film::post(User* logedin_user){
	if(logedin_user==NULL)
		throw PermissionDen();
	service->post(this,logedin_user);
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
	service->get(logedin_user,informations);
}
void Film::get_films(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw PermissionDen();
	service->search(logedin_user,informations,"films");
}
void Film::get_published(User* logedin_user,std::map<std::string,std::string> informations){
	if(!(logedin_user->get_type()))
		throw PermissionDen();
	service->search(logedin_user,informations,"published");
}
void Film::get_purchased(User* logedin_user,std::map<std::string,std::string> informations){
	service->get_purchased(logedin_user,informations);
}
void Film::print_details(User* logedin_user){
	int count=1;
	std::cout<<"Details of Film "<<name<<std::endl;
	std::cout<<"Id = "<<id<<std::endl;
	std::cout<<"Director = "<<director<<std::endl;
	std::cout<<"Length = "<<length<<std::endl;
	std::cout<<"Year = "<<year<<std::endl;
	std::cout<<"Summary = "<<summary<<std::endl;
	std::cout<<"Rate = "<<rate<<std::endl;
	std::cout<<"Price = "<<price<<"\n"<<std::endl;
	std::cout<<"Comments"<<std::endl;
	for(int i=0;i<comments.size();i++){
		std::cout<<comments[i]->get_id()<<" ";
		std::cout<<comments[i]->get_content()<<" ";
		for(int j=0;j<comments[i]->replies_num();j++)
			std::cout<<comments[i]->get_reply(j)<<std::endl;
	}
	std::cout<<"\n";
	std::cout<<"Recommendation Film"<<std::endl;
	std::cout<<"#. Film Id | Film Name | Film Length | Film Director"<<std::endl;
	std::vector<Film*> recommend_films;
	for(int i=0;i<(service->recommend(id)).size();i++)
		recommend_films.push_back(service->recommend(id)[i]);
	for(int i=0;i<recommend_films.size();i++){
		if(count>4)
			break;
		if(recommend_films[i]->get_id()==id ||
			recommend_films[i]->deleted() || 
			logedin_user->film_bought(recommend_films[i]->get_id())){
			continue;
		}
		std::cout<<count<<". ";
		std::cout<<recommend_films[i]->get_id()<<" | ";
		std::cout<<recommend_films[i]->get_name()<<" | ";
		std::cout<<recommend_films[i]->get_length()<<" | ";
		std::cout<<recommend_films[i]->get_director()<<std::endl;
		count++;

		
	}
}
void Film::set_type(std::string _type){
	type=_type;
}
void Film::set_rate(int user_id,int _rate){
	rates[user_id]=_rate;
	rate=0;
	for(auto it = rates.begin();it!=rates.end();it++)
		rate=(rate+rates[it->first]);
	rate=rate/rates.size();
}
void Film::post_rate(User* logedin_user,std::map<std::string,std::string> informations){
	service->rate(logedin_user,informations);
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
Comment* Film::find_comment(int comment_id){
	for(int i=0;i<comments.size();i++)
		if(comments[i]->get_id()==comment_id)
			return comments[i];
	throw NotFound();
}
bool Film::check_name(std::string _name){
	if(_name=="\0")
		return true;
	else if(name==_name)
		return true;
	else
		return false;
}
bool Film::check_rate(int min_rate){
	if(min_rate==0)
		return true;
	else if(rate>=min_rate)
		return true;
	else
		return false;
}
bool Film::check_price(std::string _price){
	if(_price=="\0")
			return true;
	else if(price==_price)
			return true;
	else
			return false;
}
bool Film::check_max_year(int max_year){
	if(max_year==0)
		return true;
	else if(std::stoi(year,nullptr,0)<=max_year)
		return true;
	else
		return false;
}
bool Film::check_min_year(int min_year){
	if(min_year==0)
		return true;
	else if(std::stoi(year,nullptr,0)>=min_year)
		return true;
	else
		return false;
}
bool Film::check_director(std::string _director){
	if(_director=="\0")
		return true;
	else if(director==_director)
		return true;
	else
		return false;
}