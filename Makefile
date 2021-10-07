CC = g++
CX = gcc
CFLAGS = -c -O3 -std=c++11 -Wall -I.
LDFLAGS = -lpthread -ldl
SOURCES = quiz.cpp
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS += sqlite3.o
OBJECTS := $(addprefix objects/,$(OBJECTS))

EXECUTABLE = quiz

all: objects $(SOURCES) $(EXECUTABLE)

objects:
	@mkdir -p objects

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

objects/sqlite3.o : sqlite3.c
	$(CX) -o $@ -c -O3 -Wall -I. $^

objects/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf objects/*.o $(EXECUTABLE)
