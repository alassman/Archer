CC=g++ -g -Wall


all: test

test: Archer.o test_class.cpp
	$(CC) Robot.o RoboteqDevice.o Archer.o test_class.cpp -o go

Archer.o: Archer.cpp Archer.h Robot.o RoboteqDevice.o ErrorCodes.h Constants.h
	$(CC) -c Archer.cpp

Robot.o: Robot.cpp Robot.h
	$(CC) -c Robot.cpp

RoboteqDevice.o: RoboteqDevice.cpp RoboteqDevice.h
	$(CC) -c RoboteqDevice.cpp

test_query: RoboteqDevice.o test_query.cpp
	$(CC) RoboteqDevice.o test_query.cpp -o go

test_command: RoboteqDevice.o test_command.cpp
	$(CC) RoboteqDevice.o test_command.cpp -o go

test_connection: RoboteqDevice.o test_connection.cpp
	$(CC) RoboteqDevice.o test_connection.cpp -o go

clean:
	rm *.o go