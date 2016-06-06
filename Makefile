OBJS = Robot.o Archer.o RoboteqDevice.o MathFunctions.o
CC = g++
CFLAGS = -Wall -static
TARGET = main
FILENAME = test_connection.cpp

all: $(TARGET)
$(TARGET): $(OBJS) $(FILENAME)
	$(CC) $(CFLAGS) $(OBJS) $(FILENAME) -o $@ 
Robot.o: Robot.cpp Robot.h
	$(CC) $(CFLAGS) -c Robot.cpp 
Archer.o: Archer.cpp Archer.h Robot.o RoboteqDevice.o ErrorCodes.h Constants.h
	$(CC) $(CFLAGS) -c Archer.cpp
RoboteqDevice.o: RoboteqDevice.cpp RoboteqDevice.h ErrorCodes.h
	$(CC) $(CFLAGS) -c RoboteqDevice.cpp
MathFunctions.o: MathFunctions.cpp MathFunctions.h
	$(CC) $(CFLAGS) -c MathFunctions.cpp
clean:
	\rm *.o $(TARGET) 