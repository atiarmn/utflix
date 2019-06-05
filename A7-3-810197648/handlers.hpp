#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>
#include "logics/login.h"
#include "logics/signup.h"
#include "logics/film.h"
#include "logics/money.h"
#include "logics/buy.h"
#include "logics/rate.h"
#include "logics/comment.h"

class ErrorHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class LoginHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class HomepageHandler : public RequestHandler {
  Response *callback(Request *);
};

class LogoutHandler : public RequestHandler {
  Response *callback(Request *);
};

class PostFilmHandler : public RequestHandler {
  Response *callback(Request *);
};

class PublishedHandler : public RequestHandler {
  Response *callback(Request *);
};

class DeleteFilmHandler : public RequestHandler {
  Response *callback(Request *);
};

class SearchFilmHandler : public RequestHandler {
  Response *callback(Request *);
};

class ProfileHandler : public RequestHandler {
  Response *callback(Request *);
};

class AddMoneyHandler : public RequestHandler {
  Response *callback(Request *);
};

class CanBuyFilmHandler : public RequestHandler {
  Response *callback(Request *);
};

class DetailsHandler : public RequestHandler {
  Response *callback(Request *);
};

class BuyFilmHandler : public RequestHandler {
  Response *callback(Request *);
};

class RateHandler : public RequestHandler {
  Response *callback(Request *);
};

class CommentHandler : public RequestHandler {
  Response *callback(Request *);
};

#endif
