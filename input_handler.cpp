#include "input_handler.h"
#include <iostream>

InputHandler::InputHandler(){
	request = new Request();
}
void InputHandler::run(){
	std::string line;
	while(std::getline(std::cin,line)){
		std::string temp;
		int spaceFlag=0;
		int j=0;
		for(int i=0;i<line.size()+1;i++){
			if(line[i]!=' ' && line[i]!='\0'){
				spaceFlag=0;
				temp+=line[i];
			}
			else{
				if(spaceFlag!=1){
					input.push_back(temp);
					temp="";
					spaceFlag=1;
				}
			}
		}
		try{
			get_informations();
			request->get_informations(informations);
			handle();
		}catch(std ::exception& ex){
			std::cerr<<ex.what()<<std::endl;
		}
		informations.clear();
		for(int i=0;i<input.size();i++)
			input[i]="";
		input.clear();
	}
}
void InputHandler::get_informations(){
	int start=3;
	if(input[2]=="read")
		start++;
	for(int i=start;i<input.size();i+=2){
		if(informations[input[i]]=="\0" )
			informations[input[i]]=input[i+1];
		else{
			throw BadRequest();
		}
	}
}
void InputHandler::handle(){
	if(input[0]=="POST")
		post();
	if(input[0]=="GET")
		get();
	if(input[0]=="DELETE")
		delete_func();
	if(input[0]=="PUT"){
		put();
	}
	if(input[0]!="POST" && input[0]!="GET" && input[0]!="DELETE" && input[0]!= "PUT")
		throw BadRequest();
}
void InputHandler::check_email(std::string email){
	const std::regex email_pattern
		("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		if(!std::regex_match(email,email_pattern)){
			throw BadRequest();
		}
}
void InputHandler::check_num(std::string num){
	for(int i=0;i<num.size();i++)
		if(num[i]>57 || num[i]<48){
			throw BadRequest();
		}
}
void InputHandler::post(){
	int input_error_flag=0;
	if(input[1]=="signup"){
		if(informations["email"]=="\0" || informations["password"]=="\0" || 
			informations["age"]=="\0" || informations["username"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_email(informations["email"]);
		check_num(informations["age"]);
		input_error_flag=1;
		request->signup();
	}
	if(input[1]=="login"){
		if(informations["username"]=="\0" || informations["password"]=="\0" || input[2]!="?")
			throw BadRequest();
		input_error_flag=1;
		request->login();
	}
	if(input[1]=="films"){
		if(informations["name"]=="\0" || informations["year"]=="\0" || informations["length"]=="\0" || 
			informations["price"]=="\0" || informations["summary"]=="\0" || informations["director"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["year"]);
		check_num(informations["price"]);
		input_error_flag=1;
		request->post_films();
	}
	if(input[1]=="money"){
		if(input[2]!="?")
			request->post_money_publisher();
		else if(input[3]=="amount"){
			check_num(informations["amount"]);
			request->post_money_user();
		}
		else
			throw BadRequest();
		input_error_flag=1;
	}
	if(input[1]=="replies"){
		if(informations["film_id"]=="\0" || informations["comment_id"]=="\0" || informations["content"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		check_num(informations["comment_id"]);
		request->post_replies();
		input_error_flag=1;
	}
	if(input[1]=="followers"){
		if(informations["user_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["user_id"]);
		request->post_followers();
		input_error_flag=1;
	}
	if(input[1]=="buy"){
		if(informations["film_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		request->post_buy();
		input_error_flag=1;
	}
	if(input[1]=="rate"){
		if(informations["film_id"]=="\0" || informations["score"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		check_num(informations["score"]);
		request->post_rate();
		input_error_flag=1;
	}
	if(input[1]=="comments"){
		if(informations["film_id"]=="\0" || informations["content"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		request->post_comments();
		input_error_flag=1;
	}
	if(input_error_flag==0)
		throw NotFound();
}
void InputHandler::put(){
	int input_error_flag=0;
	if(input[1]=="films"){
		if(informations["film_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		request->put_films();
		input_error_flag=1;
	}
	if(input_error_flag==0)
		throw BadRequest();
}
void InputHandler::get(){
	int input_error_flag=0;
	if(input[1]=="followers"){
		input_error_flag=1;
		request->get_followers();
	}
	if(input[1]=="films"){
		if(input[2]!="?")
			throw BadRequest();
		if(input.size()==3)
			request->get_films_find();
		if(input[3]=="film_id"){
			check_num(informations["film_id"]);
			request->get_films_detail();
		}
		else
			request->get_films_find();
		input_error_flag=1;
	}
	if(input[1]=="published"){
		if(input[2]!="?")
			throw BadRequest();
		request->get_published();
	}
	if(input[1]=="purchased"){
		if(input[2]!="?")
			throw BadRequest();
		input_error_flag=1;
		request->get_purchased();
	}
	if(input[1]=="notification"){
		if(input[2]=="read"){
			if(input[3]!="?" || informations["limit"]=="\0")
				throw BadRequest();
			check_num(informations["limit"]);
			request->get_notification_read();
		}
		input_error_flag=1;
		request->get_notification();
	}
	if(input_error_flag==0)
		throw NotFound();
}
void InputHandler::delete_func(){
	int input_error_flag=0;
	if(input[1]=="films"){
		if(informations["film_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		request->delete_films();
		input_error_flag=1;
	}
	if(input[1]=="comments"){
		if(informations["film_id"]=="\0" || informations["comment_id"]=="\0" || input[2]!="?")
			throw BadRequest();
		check_num(informations["film_id"]);
		check_num(informations["comment_id"]);
		request->delete_comments();
		input_error_flag=1;
	}
	if(input_error_flag==0)
		throw NotFound();
}