Contacts: FinalAssignment3.o contactfunctions.o
	g++ FinalAssignment3.o contactfunctions.o -o Contacts

FinalAssignment3.o: FinalAssignment3.cpp
	g++ -c FinalAssignment3.cpp

contactfunctions.o: contactfunctions.cpp
	g++ -c contactfunctions.cpp

clean:
	rm *.o Contacts