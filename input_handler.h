#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "request.h"
#include "exception.h"
#include <regex>

class InputHandler{
public:
	InputHandler();
	void run();
private:
	void handle();
	void post();
	void put();
	void delete_func();
	void get();
	void check_email(std::string email);
	void check_num(std::string number);
	void get_informations();
	std::vector<std::string> input;
	std::map<std::string,std::string> informations;
	Request* request;
};

#endif