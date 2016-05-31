CC=g++ -g -Wall


all: go

go: RoboteqDevice.o test_connection.cpp
	$(CC) RoboteqDevice.o test_connection.cpp -o go

RoboteqDevice.o: RoboteqDevice.cpp RoboteqDevice.h
	$(CC) -c RoboteqDevice.cpp

clean:
	rm *.o go
