#include "rate.h"

void Rate::post(std::map<std::string,std::string> informations){
	Film* film = new Film();
	film->post_rate(informations);
}