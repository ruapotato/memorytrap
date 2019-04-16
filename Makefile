CC		=	g++
CFLAGS	=	-O3 -march=native -lprocps -Wall 

all: memorytrap
	

run: all
	echo "+++++ Running Example: +++++"
	./memorytrap
	./memorytrap 500

memorytrap : main.cpp
	$(CC) $< $(CFLAGS) -o $@
