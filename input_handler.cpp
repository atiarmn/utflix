#include "input_handler.h"

InputHandler::InputHandler(){
	Request* new_request = new Request();
}
void InputHandler::run(){
	string line;
	while(getline(cin,line)){
		int spaceFlag=0;
		for(int i=0;i<line.size();i++){
			if(line[i]!=' '){
				spaceFlag=0;
				input[j]+=line[i];
			}
			else{
				if(spaceFlag!=1){
					j++;
					spaceFlag=1;
				}
			}
		}
	handle();
	}
}
void InputHandler::get_informations(){
	int start=3;
	if(input[2]=="read")
		start++;
	for(int i=start;i<input.size();i+=2)
		if(information[input[i]]=='\0')
			map[input[i]]=input[i+1];
		else
			throw BadRequest();
}
void InputHandler::handle(){
	get_informations();
	if(input[0]=="POST")
		post();
	if(input[0]=="GET")
		get();
	if(input[0]=="DELETE")
		delete();
	if(input[0]=="PUT")
		put();
	if(input[0]!="POST" && input[0]!="GET" && input[0]!="DELETE" && input[0]!= "PUT")
		throw BadRequest();
}
void check_email(std::string email){
	const std::regex email_pattern
		("(\\W+)(\\.|_)?(\\W*)@(\\W+)(\\.(\\W+))+");
		if(!std::regex_match(email,email_pattern))
			throw BadRequest();
}
void check_num(std::string num){
	for(int i=0;i<num.size();i++)
		if(num[i]>57 || num[i]<48)
			throw BadRequest();
}
void InputHandler::post(){
	if(input[1]=="signup"){
		if(informations["email"]=="\0" || informations["password"]=="\0" || 
			informations["age"]=="\0" || informations["username"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_email(informations["email"]);
		check_num(informations["age"]);
		request->signup();
	}
	if(input[1]=="login"){
		if(informations["username"]=="\0" || informations["password"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->login();
	}
	if(input[1]=="films"){
		if(informations["name"]=="\0" || informations["year"]=="\0" || informations["length"]=="\0" || 
			informations["price"]=="\0" || informations["summary"]=="\0" || informations["director"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["year"]);
		request->post_films();
	}
	if(input[1]=="money"){
		if(input[2]!="?")
			request->post_money_publisher();
		else if(input[3]=="amount")
			request->post_money_user()
		else
			throw BadRequest();
	}
	if(input[1]=="replies"){
		if(informations["film_id"]=="\0" || informations["comment_id"]=="\0" || informations["content"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->post_replies();
	}
	if(input[1]=="followers"){
		if(informations["user_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->post_followers();
	}
	if(input[1]=="buy"){
		if(informations["film_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->post_buy();
	}
	if(input[1]=="rate"){
		if(informations["film_id"]=="\0" || informations["score"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["score"]);
		request->post_rate();
	}
	if(input[1]=="comments"){
		if(informations["film_id"]=="\0" || informations["content"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->post_comments();
	}
}
void InputHandler::put(){
	if(input[1]=="films"){
		if(informations["film_id"]=="\0" || input[2]!="?")
		request->put_films();
	}
}
void InputHandler::get(){
	if(input[1]=="followers")
		request->get_followers();
	if(input[1]=="films"){
		if(input[2]!="?")
			throw BadRequest();
		if(input.size()==3)
			request->get_films_find();
		if(input[3]=="film_id")
			request->get_films_details();
		else
			request->get_films_find();
	}
	if(input[1]=="published"){
		if(input[2]!="?")
			throw BadRequest();
		request->get_published();
	}
	if(input[1]=="purchased"){
		if(input[2]!="?")
			throw BadRequest();
		request->get_purchased();
	}
	if(input[1]=="notification"){
		if(input[2]=="read"){
			if(input[3]!="?" || informations["limit"]=="\0")
				throw BadRequest();
			request->get_notification_read();
		}
		request->get_notification();
	}
}
void InputHandler::delete(){
	if(input[1]=="films"){
		if(informations["film_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->delete_films();
	}
	if(input[1]=="comments"){
		if(informations["film_id"]=="\0" || informations["comment_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		request->delete_comments();
	}
}