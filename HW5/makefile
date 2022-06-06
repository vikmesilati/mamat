CXX=g++
CLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 -fpic
OBJS=main.o
EXEC=firewall.exe
RM=rm -rf *.o
LOBJS=string.o field.o ip.o port.o

#THE FIRST RULE IS INVOKED BY DEFAULT
$(EXEC): $(OBJS) libfirewall.so libinput.so
	$(CLINK) $(CXXFLAGS) $(OBJS) $(LOBJS) -o $(EXEC) -linput -L.

#ALL OTHER RULES
# $(OBJS): libfirewall.so libinput.so main.cpp
# 	$(CXX) $(CXXFLAGS) -cpp main.cpp

libfirewall.so: $(LOBJS)
	$(CLINK) -shared $(LOBJS) -o libfirewall.so -L.

main.o: main.cpp string.h field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c main.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

ip.o: ip.cpp ip.h string.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h string.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

#CLEAN FILES CREATED DURING COMPILATION
clean:
	$(RM)



