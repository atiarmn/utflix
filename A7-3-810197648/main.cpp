#include "handlers.hpp"
#include "my_server.hpp"
#include "logics/exception.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/static/projection-05.jpg",new ShowImage("static/projection-05.jpg"));
    server.get("/",new ShowPage("static/home.html"));
    server.get("/signup",new ShowPage("static/signup.html"));
    server.post("/signup",new SignupHandler());
    server.get("/login", new ShowPage("static/login.html"));
    server.get("/error",new ErrorHandler());
    server.get("/publishedFilms",new PublishedHandler());
    server.get("/profile",new ProfileHandler());
    server.get("/canBuyFilms",new CanBuyFilmHandler());
    server.get("/showDetails",new DetailsHandler());
    server.get("/bought",new ShowPage("static/bought.html"));
    server.get("/userHomepage",new ShowPage("static/user_homepage.html"));
    server.get("/publisherHomepage",new ShowPage("static/publisher_homepage.html"));
    server.get("/homepage",new HomepageHandler());
    server.get("/postfilm",new ShowPage("static/postfilm.html"));

    server.post("/login", new LoginHandler());
    server.post("/delete",new DeleteFilmHandler());
    server.post("/search",new SearchFilmHandler());
    server.post("/addMoney",new AddMoneyHandler());
    server.post("/rate",new RateHandler());
    server.post("/comment",new CommentHandler());
    server.post("/buy",new BuyFilmHandler());
    server.post("/postfilm",new PostFilmHandler());
    server.post("/logout",new LogoutHandler());

    server.run();
    
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
