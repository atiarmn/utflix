#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <string>
#include <vector>
#include <map>

class InputHandler{
public:
	InputHandler();
	void run();
private:
	void handle();
	void post();
	void put();
	void delete();
	void get();
	void check_email();
	void get_informations();
	std::vector<string> input;
	map<string,string> informations;
	Request* request;
};

#endif INPUT_HANDLER_H