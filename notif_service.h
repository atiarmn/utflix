#ifndef NOTIF_SERVICE_H
#define NOTIF_SERVICE_H

#include "user.h"
#include "exception.h"

class User;

class NotifService{
public:
	void get_notifications(User* logedin_user);
	void get_notifications_read(User* logedin_user,std::map<std::string,std::string> informations);
};

#endif