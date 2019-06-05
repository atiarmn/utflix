#include "database.h"

Database* Database::instance = 0;

Database* Database::get_instance() {
      if (instance == 0)
      	instance = new Database();
      return instance;
}
Database::~Database(){
	delete instance;
}
void Database::add_film(Film* film){
	(this->films).push_back(film);
	sorted_films.push_back(film);
	for(int i =0;i<recommend_matrix.size();i++)
		recommend_matrix[i].push_back(0);
	std::vector<int> new_film(films.size(),0);
	recommend_matrix.push_back(new_film);
}
void Database::add_user(User* user){
	(this->users).push_back(user);
}
Film* Database::get_film(int film_id){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_id()==film_id)
			return films[i];
}

int Database::find_last_user(){
	return users.size();
}
bool Database::existed_username(std::string username){
	for(int i=0;i<users.size();i++)
		if(users[i]->get_username()==username)
			return true;
	return false;
}
bool Database::existed_user_id(int user_id){
	for(int i=0;i<users.size();i++)
		if(i+1==user_id)
			return true;
	return false;
}
bool Database::existed_film(int film_id){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_id()==film_id)
			return true;
	return false;
}
bool Database::correct_password(std::string username,std::string password){
	for(int i=0;i<users.size();i++){
		if(users[i]->get_username()==username && users[i]->get_password()==password)
			return true;
	}
	return false;
}
User* Database::get_user(std::string username){
	for(int i=0;i<users.size();i++){
		if(users[i]->get_username()==username)
			return users[i];
	}
	return NULL;
}
User* Database::get_user_by_id(int id){
	for(int i=0;i<users.size();i++)
		if(i+1==id)
			return users[i];
	return NULL;
}
int Database::find_last_film(){
	return films.size();
}
void Database::add_network_money(int money){
	network_money+=money;
}
void Database::set_publisher_money(User* logedin_user){
	for(int i=0;i<films.size();i++)
		if(films[i]->get_publisher_id()==logedin_user->get_id())
			for(int j=0;j<users.size();j++){
				if(users[j]->film_bought(films[i]->get_id())){
					if(films[i]->get_type()=="weak"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.2);
						logedin_user->add_money(films[i]->get_price()*(0.8));
					}
					if(films[i]->get_type()=="avarage"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.1);
						logedin_user->add_money(films[i]->get_price()*(0.9));
					}
					if(films[i]->get_type()=="good"){
						network_money -=films[i]->get_price();
						network_money+=films[i]->get_price()*(0.05);
						logedin_user->add_money(films[i]->get_price()*(0.95));
					}
				}
			}
}
void Database::sort_films_by_id(){
	Film* temp = new Film();
	for(int i=0;i<sorted_films.size();i++){
		if(i+1>=sorted_films.size())
			break;
		if((sorted_films[i]->get_id())>(sorted_films[i+1]->get_id())){
			temp=sorted_films[i];
			sorted_films[i]=sorted_films[i+1];
			sorted_films[i+1]=temp;
		}
	}
}
std::vector<int> Database::recommend(int film_id){
	std::vector<int> weight_of_edges;
	for(int i=0;i<recommend_matrix[film_id-1].size();i++)
		weight_of_edges.push_back(recommend_matrix[film_id-1][i]);
	std::vector<std::pair<int,int>> copy_weights;
	for(int j=0;j<recommend_matrix[film_id-1].size();j++)
		copy_weights.push_back(std::make_pair(recommend_matrix[film_id-1][j],j+1));
	std::sort(copy_weights.begin(),copy_weights.end());
	std::vector<int> recommend_films;
	std::pair <int,int> temp; 
	for(int j=0;j<copy_weights.size();j++){
		for(int i=0;i<copy_weights.size();i++){
			if(copy_weights[i].first==copy_weights[i+1].first && copy_weights[i].second<copy_weights[i+1].second){
				temp=copy_weights[i];
				copy_weights[i]=copy_weights[i+1];
				copy_weights[i+1]=temp;
			}	
		}
	}
	for(int i=0;i<copy_weights.size();i++)
		recommend_films.push_back(copy_weights[i].second);
	return recommend_films;
}
void Database::login(int id){
	loggedin_users.push_back(id);
}
void Database::logout(int id){
	for(int i =0; i < loggedin_users.size();i++){
		if(loggedin_users[i]==id)
			loggedin_users.erase(loggedin_users.begin()+i-1);
	}
}
bool Database::is_loggedin(int id){
	for(int i =0;i<loggedin_users.size();i++)
		if(loggedin_users[i]==id)
			return true;
	return false;
}
std::vector<Film*> Database::get_sorted_films_by_id(){
	sort_films_by_id();
	return sorted_films;
}
std::vector<User*> Database::get_all_users(){
	return this->users;
}
void Database::add_to_recommends(User* logedin_user,int new_film_id){
	for(int i=0;i<recommend_matrix.size();i++){
		if(logedin_user->film_bought(i+1)){
			if(new_film_id==i)
				continue;
			recommend_matrix[i][new_film_id-1]++;
			recommend_matrix[new_film_id-1][i]++;
		}
	}
}
void Database::remove_from_recommend(int film_id){
	for(int i=0;i<recommend_matrix.size();i++){
		recommend_matrix[i][film_id-1]=0;
		recommend_matrix[film_id-1][i]=0;
	}
}
Database::Database() {}
