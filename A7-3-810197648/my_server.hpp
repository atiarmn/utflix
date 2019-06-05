#ifndef __MY_SERVER__
#define __MY_SERVER__

#include "server/server.hpp"
#include "logics/database.h"
#include "logics/user.h"

class MyServer : public Server {
public:
  MyServer(int port = 5000);
};

#endif
