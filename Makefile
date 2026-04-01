CC = g++
CFLAGS = -g -Wall

TARGET = main.exe

OBJS = main.o Matrix.o Linearsystem.o Gaussian.o Lu.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(CFLAGS) -c Matrix.cpp

Linearsystem.o: Linearsystem.cpp Linearsystem.h
	$(CC) $(CFLAGS) -c Linearsystem.cpp

Gaussian.o: Gaussian.cpp Gaussian.h
	$(CC) $(CFLAGS) -c Gaussian.cpp

Lu.o: Lu.cpp Lu.h
	$(CC) $(CFLAGS) -c Lu.cpp

clean:
	del *.o main.exe