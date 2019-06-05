CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp logics/signup.h logics/login.h logics/film.h logics/money.h logics/buy.h logics/rate.h
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/signup.o: logics/signup.cpp logics/signup.h logics/database.h logics/exception.h logics/user.h logics/publisher.h
	$(CC) -c logics/signup.cpp -o $(BUILD_DIR)/signup.o

$(BUILD_DIR)/database.o: logics/database.cpp logics/database.h logics/user.h logics/film.h
	$(CC) -c logics/database.cpp -o $(BUILD_DIR)/database.o

$(BUILD_DIR)/user.o: logics/user.cpp logics/user.h logics/database.h logics/exception.h
	$(CC) -c logics/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/publisher.o: logics/publisher.cpp logics/publisher.h logics/user.h
	$(CC) -c logics/publisher.cpp -o $(BUILD_DIR)/publisher.o

$(BUILD_DIR)/login.o: logics/login.cpp logics/login.h logics/exception.h logics/database.h
	$(CC) -c logics/login.cpp -o $(BUILD_DIR)/login.o

$(BUILD_DIR)/money.o: logics/money.cpp logics/money.h logics/user.h logics/exception.h
	$(CC) -c logics/money.cpp -o $(BUILD_DIR)/money.o

$(BUILD_DIR)/film.o: logics/film.cpp logics/film.h logics/film_service.h logics/database.h logics/user.h logics/comment.h
	$(CC) -c logics/film.cpp -o $(BUILD_DIR)/film.o

$(BUILD_DIR)/film_service.o: logics/film_service.cpp logics/film_service.h logics/film.h logics/database.h logics/exception.h logics/user.h
	$(CC) -c logics/film_service.cpp -o $(BUILD_DIR)/film_service.o

$(BUILD_DIR)/buy.o: logics/buy.cpp logics/buy.h logics/exception.h logics/user.h logics/database.h
	$(CC) -c logics/buy.cpp -o $(BUILD_DIR)/buy.o

$(BUILD_DIR)/rate.o: logics/rate.cpp logics/rate.h logics/film.h logics/user.h
	$(CC) -c logics/rate.cpp -o $(BUILD_DIR)/rate.o

$(BUILD_DIR)/comment.o: logics/comment.cpp logics/comment.h logics/user.h logics/comment_service.h
	$(CC) -c logics/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/comment_service.o: logics/comment_service.cpp logics/comment_service.h logics/comment.h logics/database.h logics/exception.h logics/film.h logics/user.h
	$(CC) -c logics/comment_service.cpp -o $(BUILD_DIR)/comment_service.o
myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/signup.o $(BUILD_DIR)/database.o $(BUILD_DIR)/user.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/login.o $(BUILD_DIR)/money.o $(BUILD_DIR)/film.o $(BUILD_DIR)/film_service.o $(BUILD_DIR)/buy.o $(BUILD_DIR)/rate.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/comment_service.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/signup.o $(BUILD_DIR)/database.o $(BUILD_DIR)/user.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/login.o $(BUILD_DIR)/money.o $(BUILD_DIR)/film.o $(BUILD_DIR)/film_service.o $(BUILD_DIR)/buy.o $(BUILD_DIR)/rate.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/comment_service.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
