CC = g++ --std=c++11

all: 1.out

1.out: main.o input_handler.o request.o signup.o database.o user.o publisher.o login.o money.o
	$(CC) main.o input_handler.o request.o database.o user.o publisher.o signup.o login.o money.o -o 1.out

main.o: main.cpp input_handler.h
	$(CC) -c main.cpp -o main.o

input_handler.o: input_handler.cpp input_handler.h request.h exception.h
	$(CC) -c input_handler.cpp -o input_handler.o

request.o: request.cpp request.h exception.h signup.h user.h login.h money.h
	$(CC) -c request.cpp -o request.o

signup.o: signup.cpp signup.h database.h exception.h user.h publisher.h
	$(CC) -c signup.cpp -o signup.o

database.o: database.cpp database.h user.h
	$(CC) -c database.cpp -o database.o

user.o: user.cpp user.h database.h
	$(CC) -c user.cpp -o user.o

publisher.o: publisher.cpp publisher.h user.h
	$(CC) -c publisher.cpp -o publisher.o

login.o: login.cpp login.h exception.h database.h
	$(CC) -c login.cpp -o login.o

money.o: money.cpp money.h user.h exception.h
	$(CC) -c money.cpp -o money.o

.PHONY: clean
clean:
	rm *.o
	rm 1.out