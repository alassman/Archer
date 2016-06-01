CC=g++ -g -Wall


all: go

go: RoboteqDevice.o test_query.cpp
	$(CC) RoboteqDevice.o test_query.cpp -o go

RoboteqDevice.o: RoboteqDevice.cpp RoboteqDevice.h
	$(CC) -c RoboteqDevice.cpp

test_query: RoboteqDevice.o test_query.cpp
	$(CC) RoboteqDevice.o test_query.cpp -o go

test_command: RoboteqDevice.o test_command.cpp
	$(CC) RoboteqDevice.o test_query.cpp -o go

test_connection: RoboteqDevice.o test_connection.cpp
	$(CC) RoboteqDevice.o test_query.cpp -o go

clean:
	rm *.o go
