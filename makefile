CC=g++
CCFLAGS=-std=c++11
LIBS=-lm

volimage: VolImage.o Driver.o
		$(CC) $(CCFLAGS) VolImage.o Driver.o -o volimage $(LIBS)
		
VolImage.o: VolImage.cpp VolImage.h
				$(CC) $(CCFLAGS) VolImage.cpp -c
				
Driver.o: Driver.cpp
		$(CC) $(CCFLAGS) Driver.cpp -c

		
clean: 
		@rm -f *.o
		@rm -f volimage
		
install: 
		@mv Driver -/bin
