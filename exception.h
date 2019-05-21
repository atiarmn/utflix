#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>


class BadRequest:public std::exception{
public:
	virtual const char* what() const throw () {return "Bad Request";}
};
class NotFound:public std::exception{
public:
	virtual const char* what() const throw () {return "Not Found";}
};
class PermissionDen:public std::exception{
	virtual const char* what() const throw () {return "Permission Denied";}
};
#endif