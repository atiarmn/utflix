#include "handlers.hpp"

using namespace std;

Response *ErrorHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res=new Response();
  res->setHeader("Content-Type","text/html");
  string error_msg = req->getQueryParam("error_msg");
  string new_url = req->getQueryParam("url");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body +="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="a{color:darkred;margin-left: 550px;text-align: center;}a:link {text-decoration: none;}";
  body+="a:visited {text-decoration: none;}a:hover {text-decoration: underline;}a:active {text-decoration: underline;}";
  body+="</style><head>";
  body += "<body>";
  body += "<h1 style=\"color: darkred;text-align: center;\">";
  body += error_msg;
  body += "</h1>";
  body += "<a href=\"";
  if(new_url == "homepage"){
    if(database->get_user_by_id(stoi(req->getSessionId()))->get_type())
      new_url+="?type=publisher";
    else
      new_url+="?type=user";
  }
  body += new_url;
  body += "\">";
  if(new_url=="login")
    body+="LOGIN";
  else if(new_url=="homepage?type=user"||new_url=="homepage?type=publisher")
    body+="HOMEPAGE";
  else
    body += "BACK";
  body += "</a>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}
Response *LogoutHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  if(database->is_loggedin(stoi(req->getSessionId())))
    database->logout(stoi(req->getSessionId()));
  else{
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  res = Response::redirect("/login");
  informations.clear();
  res->setSessionId("");
  return res;
}
Response *SignupHandler::callback(Request *req) {
  string redirect;
  Response *res = new Response();
  Database* database = database->get_instance();
  informations["username"] = req->getBodyParam("username"); 
  informations["password"] = req->getBodyParam("password");
  informations["age"] = req->getBodyParam("age");
  informations["email"] = req->getBodyParam("email");
  informations["publisher"] = req->getBodyParam("publisher");
  string repeat_password = req->getBodyParam("repeat_password");
  if(repeat_password!=informations["password"]){
    redirect="/error?error_msg=password+and+repeated+password+are+different&url=signup";
    res = Response::redirect(redirect);
    return res;
  }
  if(req->getSessionId()!=""){
    redirect="/error?error_msg=you+didnt+logout&url=homepage";
    res = Response::redirect(redirect);
    return res;
  }
  Signup* signup = new Signup();
  redirect=signup->post(informations);
  int id;
  id=database->find_last_user();
  res = Response::redirect(redirect);
  database->login(id);
  res->setSessionId(to_string(id));
  return res;
}
Response *LoginHandler::callback(Request *req) {
  string redirect;
  Database* database = database->get_instance();
  Response *res = new Response();
  informations["username"] = req->getBodyParam("username");
  informations["password"] = req->getBodyParam("password");
  if(req->getSessionId()!=""){
    redirect="/error?error_msg=you+didnt+logout&url=homepage";
    res = Response::redirect(redirect);
    return res;
  }
  Login* login = new Login();
  redirect=login->post(informations);
  int id=-1;
  if(database->get_user(informations["username"])!=NULL)
    id=database->get_user(informations["username"])->get_id();
  res = Response::redirect(redirect);
  if(id!=-1){
    database->login(id);
    res->setSessionId(to_string(id));
  }
  return res;
}
Response *HomepageHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  string type = req->getQueryParam("type");
  if(type=="publisher")
    res = Response::redirect("/publisherHomepage");
  if(type=="user")
    res = Response::redirect("/userHomepage");
  return res;
}
Response *PostFilmHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  informations["name"]=req->getBodyParam("name");
  informations["year"]=req->getBodyParam("year");
  informations["length"]=req->getBodyParam("length");
  informations["director"]=req->getBodyParam("director");
  informations["summary"]=req->getBodyParam("summary");
  informations["price"]=req->getBodyParam("price");
  Film* film = new Film(informations,database->get_user_by_id(stoi(req->getSessionId())));
  try{
    film->post(database->get_user_by_id(stoi(req->getSessionId())));
	  database->get_user_by_id(stoi(req->getSessionId()))->add_film(film->get_id());
  }catch(exception& ex){
    res=Response::redirect("/error?error_msg=you+cant+post+a+film&url=homepage");
    return res;
  }
  res=Response::redirect("/publisherHomepage");
  return res;
}
Response *PublishedHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res = new Response();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  res->setHeader("Content-Type","text/html");
  vector<Film*> published_films;
  string body;
  informations["director"]=req->getQueryParam("director");
  Film* film=new Film();
  try{
    published_films=film->get_published(database->get_user_by_id(stoi(req->getSessionId())),informations);
  }catch(exception& ex){
    res=Response::redirect("/error?error_msg=you+doont+have+published+films&url=homepage");
    return res;
  }
  body+="<!DOCTYPE html>";
  body+="<html>";
  body +="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 3px; margin-left: 500px;}";
  body+="h2{color:darkred;text-align: center;}";
  body+="p{color:darkred;}";
  body+=".button {border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+=".button:hover span {padding-right: 25px;}.button:hover span:after {opacity: 1;right: 0;}";
  body+="table {border-collapse: collapse;width: 100%;background-color: darkred;}";
  body+="th, td {padding: 8px;text-align: left;border-bottom: 1px solid #ddd;}tr:hover {background-color:rgb(177, 9, 0);}";
  body+="</style></head>";
  body+="<body>";
  body+="<h1>Your Films!</h1>";
  body+="<div>";
  body+="<form action=\"/search\" method=\"post\">";
  body+="<h2>Search</h2>";
  body+="<p>director:</p><input type=\"text\" name=\"director\" placeholder=\"Director\"/><br>";
  body+="<button type=\"submit\" style=\"background-color: darkred;\" class=\"button\"><span>Search</span></button>";
  body+="</form>";
  body+="</div>";
  body+="<table>";
  body+="<tr>";
  body+="<th>Name</th>";
  body+="<th>Length</th>";
  body+="<th>Price</th>";
  body+="<th>Year</th>";
  body+="<th>Rate</th>";
  body+="<th>Director</th>";
  body+="<th>Delete</th>";
  body+="</tr>";
  for(int i=0;i<published_films.size();i++){
    body+="<tr>";
    body+="<th>";
    body+=published_films[i]->get_name();
    body+="</th>";
    body+="<th>";
    body+=published_films[i]->get_length();
    body+="</th>";
    body+="<th>";
    body+=to_string(published_films[i]->get_price());
    body+="</th>";
    body+="<th>";
    body+=published_films[i]->get_year();
    body+="</th>";
    body+="<th>";
    stringstream stream;
    stream << fixed << setprecision(2) << published_films[i]->get_rate();
    body+=stream.str();
    body+="</th>";
    body+="<th>";
    body+=published_films[i]->get_director();
    body+="</th>";
    body+="<form action=\"/delete\" method=\"post\">";
    body+="<th><button name=\"film_id\" style=\"background-color: black;\" type=\"submit\" class=\"button\" value=\"";
    body+=to_string(published_films[i]->get_id());
    body+="\"><span>Delete</span></button></th>";
    body+="</form>";
    body+="</tr>";
  }
  body+="</table></div></body></html>";
  res->setBody(body);
  return res;
}
Response *DeleteFilmHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res=new Response();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  informations["film_id"]=req->getBodyParam("film_id");
  Film* film = new Film();
  film->delete_film(informations);
  res = Response::redirect("/publishedFilms");
  return res;
}
Response *SearchFilmHandler::callback(Request *req){
  string director = req->getBodyParam("director");
  Response *res = new Response();
  string redirect;
  redirect += "/publishedFilms?director=";
  redirect += director;
  res=Response::redirect(redirect);
  return res;
}
Response *ProfileHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  vector<Film*> purchased_films;
  string body;
  informations["director"]=req->getQueryParam("director");
  Film* film=new Film();
  purchased_films=film->get_purchased(database->get_user_by_id(stoi(req->getSessionId())));
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body +="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+="h1{color:darkred;text-align: center;}";
  body+="p{color:darkred;}";
  body+=".button {border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+=".button:hover span {padding-right: 25px;}.button:hover span:after {opacity: 1;right: 0;}";
  body+="table {border-collapse: collapse;width: 100%;background-color: darkred;}";
  body+="th, td {padding: 8px;text-align: left;border-bottom: 1px solid #ddd;}tr:hover {background-color:rgb(177, 9, 0);}";
  body+="</style></head>";
  body+="<body>";
  body+="<div>";
  body+="<h1>Your Films!</h1>";
  body+="</div>";
  body+="<table>";
  body+="<tr>";
  body+="<th>Name</th>";
  body+="<th>Length</th>";
  body+="<th>Price</th>";
  body+="<th>Year</th>";
  body+="<th>Rate</th>";
  body+="<th>Director</th>";
  body+="<th>Details</th>";
  body+="</tr>";
  for(int i=0;i<purchased_films.size();i++){
    body+="<tr>";
    body+="<th>";
    body+=purchased_films[i]->get_name();
    body+="</th>";
    body+="<th>";
    body+=purchased_films[i]->get_length();
    body+="</th>";
    body+="<th>";
    body+=to_string(purchased_films[i]->get_price());
    body+="</th>";
    body+="<th>";
    body+=purchased_films[i]->get_year();
    body+="</th>";
    body+="<th>";
    stringstream stream;
    stream << fixed << setprecision(2) << purchased_films[i]->get_rate();
    body+=stream.str();
    body+="</th>";
    body+="<th>";
    body+=purchased_films[i]->get_director();
    body+="</th>";
    body+="<form action=\"/showDetails\" method=\"get\">";
    body+="<th><button name=\"film_id\" class=\"button\" style=\"background-color:black\" type=\"submit\" value=\"";
    body+=to_string(purchased_films[i]->get_id());
    body+="\"><span>ShowDetails</span></button></th></form>";
    body+="</tr>";
  }
  body+="</table>";
  body+="<div>";
  body+="<form action=\"/addMoney\" method=\"post\">";
  body+="<input type=\"number\" name=\"amount\" min=\"1\" placeholder=\"Amount\"/><br>";
  body+="<button type=\"submit\" class=\"button\" style=\"background-color:darkred\" ><span>add</span></button>";
  body+="</form></div></body></html>";
  res->setBody(body);
  return res;
}
Response *RateHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res = new Response();
  Rate* rate = new Rate();
  informations["score"]=req->getBodyParam("score");
  informations["film_id"]=req->getBodyParam("film_id");
  try{
    rate->post(database->get_user_by_id(stoi(req->getSessionId())),informations); 
  }catch(exception& ex){
    res=Response::redirect("/error?error_msg=film+is+deleted&url=profile");
    return res;
  }
  string body;
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body+="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+=".button {background-color:darkred;border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+="</style><head>";
  body+="<body>";
  body+="<div>";
  body+="<h1 style=\"color: darkred;text-align: center;\">thanks</h1>";
  body+="<form action=\"/showDetails\" method=\"get\">";
  body+="<th><button name=\"film_id\" class=\"button\" type=\"submit\" value=\"";
  body+=informations["film_id"];
  body+="\"><span>OK</span></button></th></form>";
  body+="</div></body></html>";
  res->setBody(body);
  return res; 
}
Response *AddMoneyHandler::callback(Request *req){
  Database* database = database->get_instance();
  informations["amount"] = req->getBodyParam("amount");
  Response *res = new Response();
  Money* money = new Money();
	money->post_user(database->get_user_by_id(stoi(req->getSessionId())),informations);
  string body;
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body+="<body>";
  body+="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+=".button {background-color:darkred; border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+="</style><head>";
  body+="<div>";
  body+="<h1 style=\"color: darkred;text-align: center;\">you have";
  body+=to_string(database->get_user_by_id(stoi(req->getSessionId()))->get_money());
  body+="</h1>";
  body+="<form action=\"/profile\" method=\"get\">";
  body+="<button type=\"submit\" class=\"button\"><span>OK</span></button>";
  body+="</form>";
  body+="</div></body></html>";
  res->setBody(body);
  return res;
}
Response *CanBuyFilmHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  vector<Film*> films;
  string body;
  Film* film=new Film();
  films=film->get_films(database->get_user_by_id(stoi(req->getSessionId())));
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body +="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+="h1{color:darkred;text-align: center;}";
  body+="p{color:darkred;}";
  body+=".button {border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+=".button:hover span {padding-right: 25px;}.button:hover span:after {opacity: 1;right: 0;}";
  body+="table {border-collapse: collapse;width: 100%;background-color: darkred;}";
  body+="th, td {padding: 8px;text-align: left;border-bottom: 1px solid #ddd;}tr:hover {background-color:rgb(177, 9, 0);}";
  body+="</style></head>";
  body+="<body>";
  body+="<div>";
  body+="<h1>Films You Can Buy!</h1></div>";
  body+="<table>";
  body+="<tr>";
  body+="<th>Name</th>";
  body+="<th>Length</th>";
  body+="<th>Price</th>";
  body+="<th>Year</th>";
  body+="<th>Rate</th>";
  body+="<th>Director</th>";
  body+="<th>Details</th>";
  body+="</tr>";
  for(int i=0;i<films.size();i++){
    body+="<tr>";
    body+="<th>";
    body+=films[i]->get_name();
    body+="</th>";
    body+="<th>";
    body+=films[i]->get_length();
    body+="</th>";
    body+="<th>";
    body+=to_string(films[i]->get_price());
    body+="</th>";
    body+="<th>";
    body+=films[i]->get_year();
    body+="</th>";
    body+="<th>";
    stringstream stream;
    stream << fixed << setprecision(2) << films[i]->get_rate();
    body+=stream.str();
    body+="</th>";
    body+="<th>";
    body+=films[i]->get_director();
    body+="</th>";
    body+="<form action=\"/showDetails\" method=\"get\">";
    body+="<th><button name=\"film_id\" class=\"button\" style=\"background-color:black\" type=\"submit\" value=\"";
    body+=to_string(films[i]->get_id());
    body+="\"><span>ShowDetails</span></button></th></form>";
    body+="</tr>";
  }
  body+="</table></body></html>";
  res->setBody(body);
  return res;
}
Response *DetailsHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res=new Response();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  string film_id = req->getQueryParam("film_id");
  int count=1;
  Film *film = database->get_film(stoi(film_id));
  vector<Film*> recommend_films;
  FilmService *service = new FilmService();
  string body;
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body +="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+="h1{color:darkred;text-align: center;}";
  body+="p{color:darkred;}";
  body+=".button {border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+=".button:hover span {padding-right: 25px;}.button:hover span:after {opacity: 1;right: 0;}";
  body+="table {border-collapse: collapse;width: 100%;background-color: darkred;}";
  body+="th, td {padding: 8px;text-align: left;border-bottom: 1px solid #ddd;}tr:hover {background-color:rgb(177, 9, 0);}";
  body+="</style></head>";
  body+="<body>";
  body+="<div>";
  body+="<h1>Details of Film:</h1></div>";
  body+="<table>";
  body+="<tr>";
  body+="<th>Name</th>";
  body+="<th>Length</th>";
  body+="<th>Price</th>";
  body+="<th>Year</th>";
  body+="<th>Summary</th>";
  body+="<th>Director</th>";
  body+="<th>Rate</th>";
  if(!database->get_user_by_id(stoi(req->getSessionId()))->film_bought(film->get_id()))
    body+="<th>Buy</th>";
  else{
    body+="<th>Score the film</th>";
    body+="<th>Add comment</th>";
  }
  body+="</tr>";
  body+="<tr>";
  body+="<th>";
  body+=film->get_name();
  body+="</th>";
  body+="<th>";
  body+=film->get_length();
  body+="</th>";
  body+="<th>";
  body+=to_string(film->get_price());
  body+="</th>";
  body+="<th>";
  body+=film->get_year();
  body+="</th>";
  body+="<th>";
  body+=film->get_summary();
  body+="</th>";
  body+="<th>";
  body+=film->get_director();
  body+="</th>";
  body+="<th>";
  stringstream stream;
  stream << fixed << setprecision(2) << film->get_rate();
  body+=stream.str();
  body+="</th>";
  if(!database->get_user_by_id(stoi(req->getSessionId()))->film_bought(film->get_id())){
    body+="<form action=\"/buy\" method=\"post\">";
    body+="<th><button name=\"film_id\" class=\"button\" style=\"background-color:black\" type=\"submit\" value=\"";
    body+=to_string(film->get_id());
    body+="\"><span>Buy</span></button></th>";
    body+="</form>";
  }
  else{
    body+="<form action=\"/rate\" method=\"post\">";
    body+="<th><input type=\"number\" name=\"score\" min=\"0\" max=\"10\" placeholder=\"score\"/>";
    body+="<button name=\"film_id\" class=\"button\" style=\"background-color:black\" type=\"submit\" value=\"";
    body+=to_string(film->get_id());
    body+="\"><span>Score</span></button></th></form>";
    body+="<form action=\"/comment\" method=\"post\">";
    body+="<th><input type=\"text\" name=\"comment\" placeholder=\"Your Comment\" required>";
    body+="<button name=\"film_id\" type=\"submit\" class=\"button\" style=\"background-color:black\" value=\"";
    body+=to_string(film->get_id());
    body+="\"><span>Post</span></button></th></form>";
  }
  body+="</tr>";
  body+="</table>";
  body+="<div><h1>Comments!</h1></div>";
  body+="<table><tr>";
  body+="<th>comment id</th>";
  body+="<th>content</th></tr>";
  vector<Comment*> comments=film->get_comments();
	for(int i=0;i<comments.size();i++){
		body+="<tr><th>";
    body+=to_string(comments[i]->get_id());
    body+="</th><th>";
		body+=comments[i]->get_content();
    body+="</th></tr>";
	}
  body+="</table><div><h1>Recommended Films!</h1></div><table>";
  body+="<tr>";
  body+="<th>Name</th>";
  body+="<th>Length</th>";
  body+="<th>Director</th>";
  body+="<th>Details</th>";
  body+="</tr>";
  for(int i=0;i<(service->recommend(film->get_id())).size();i++)
		recommend_films.push_back(service->recommend(film->get_id())[i]);
	for(int i=0;i<recommend_films.size();i++){
		if(count>4)
			break;
		if(recommend_films[i]->get_id()==film->get_id() ||
			recommend_films[i]->deleted() || 
			database->get_user_by_id(stoi(req->getSessionId()))->film_bought(recommend_films[i]->get_id())){
			continue;
		}
    body+="<tr><th>";
		body+=recommend_films[i]->get_name();
    body+="</th><th>";
		body+=recommend_films[i]->get_length();
    body+="</th><th>";
		body+=recommend_films[i]->get_director();
    body+="</th>";
    body+="<form action=\"/showDetails\" method=\"get\">";
    body+="<th><button name=\"film_id\" class=\"button\" style=\"background-color:black\" type=\"submit\" value=\"";
    body+=to_string(recommend_films[i]->get_id());
    body+="\"><span>ShowDetails</span></button></th></form>";
    body+="</tr>";
		count++;	
	}
  body+="</body></html>";
  res->setBody(body);
  return res;
}
Response *CommentHandler::callback(Request *req){
  Response *res = new Response();
  Database* database = database->get_instance();
  informations["content"]=req->getBodyParam("comment");
  informations["film_id"]=req->getBodyParam("film_id");
  Comment* comment = new Comment(informations["content"],stoi(req->getSessionId()));
  try{
	  comment->post(database->get_user_by_id(stoi(req->getSessionId())),informations);
  }catch(exception& ex){
    res=Response::redirect("/error?error_msg=film+is+deleted&url=profile");
    return res;
  }
  string body;
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body+="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+=".button {background-color:darkred; border:none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+="</style><head>";
  body+="<body>";
  body+="<div>";
  body+="<h1 style=\"color: darkred;text-align: center;\">thanks</h1>";
  body+="<form action=\"/showDetails\" method=\"get\">";
  body+="<th><button name=\"film_id\" class=\"button\" type=\"submit\" value=\"";
  body+=informations["film_id"];
  body+="\"><span>OK</span></button></th></form>";
  body+="</form>";
  body+="</div></body></html>";
  res->setBody(body);
  return res; 
}
Response *BuyFilmHandler::callback(Request *req){
  Database* database = database->get_instance();
  Response *res=new Response();
  if(!database->is_loggedin(stoi(req->getSessionId()))){
    res = Response::redirect("/error?error_msg=you+are+not+login&url=login");
    return res;
  }
  informations["film_id"]=req->getBodyParam("film_id");
  Buy *buy = new Buy();
  try{
    buy->post(database->get_user_by_id(stoi(req->getSessionId())),informations);
  }catch(exception &ex){
     res=Response::redirect("/error?error_msg=you+dont+have+enough+money&url=details");
     return res;
  }
  string body;
  res->setHeader("Content-Type","text/html");
  body+="<!DOCTYPE html>";
  body+="<html>";
  body+="<head><style> body  {background-image: url(\"static/projection-05.jpg\");";
  body+="background-repeat: no-repeat;background-attachment: fixed;background-position: center;background-size: cover;}";
  body+="div {background-color:black; padding: 1%; max-width: 300px; border-radius: 1px; margin-left: 500px;}";
  body+=".button {background-color:darkred; border:none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;display: inline-block;}";
  body+=".button span {cursor: pointer;display: inline-block;position: relative;transition: 0.5s;}";
  body+=".button span:after {content: '\\00bb';position: absolute;opacity: 0;top: 0;right: -20px;transition: 0.5s;}";
  body+="</style><head>";
  body+="<body>";
  body+="<div>";
  body+="<h1 style=\"color: darkred;text-align: center;\">thanks</h1>";
  body+="<form action=\"/showDetails\" method=\"get\">";
  body+="<th><button name=\"film_id\" class=\"button\" type=\"submit\" value=\"";
  body+=informations["film_id"];
  body+="\"><span>OK</span></button></th></form>";
  body+="</form>";
  body+="</div></body></html>";
  res->setBody(body);
  return res;
}