#include "notif_service.h"

void NotifService::get_notifications(User* logedin_user){
	if(logedin_user==NULL)
		throw BadRequest();
	logedin_user->print_unread_notifs();
}
void NotifService::get_notifications_read(User* logedin_user,std::map<std::string,std::string> informations){
	if(logedin_user==NULL)
		throw BadRequest();
	int limit = std::stoi(informations["limit"],nullptr,0);
	logedin_user->print_read_notifs(limit);
}