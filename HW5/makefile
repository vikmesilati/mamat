CXX=g++
CLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11
OBJS=main.o
EXEC=firewall.exe
RM=rm -rf *.o
LOBJS=string.o field.o ip.o port.o

#THE FIRST RULE IS INVOKED BY DEFAULT
$(EXEC): $(LOBJS) libfirewall.so libinput.so
	$(CLINK) $(CXXFLAGS) $(OBJS) -o $(EXEC) -linput -L.

#ALL OTHER RULES
# $(OBJS): libfirewall.so libinput.so main.cpp
# 	$(CXX) $(CXXFLAGS) -cpp main.cpp

libfirewall.so: $(LOBJS)
	$(CLINK) -shared $(LOBJS) -o libfirewall.so -L.

main.o: main.cpp string.h field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -cpp main.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -cpp -fpic string.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -cpp -fpic field.cpp

ip.o: ip.cpp ip.h string.h field.h
	$(CXX) $(CXXFLAGS) -cpp -fpic ip.cpp

port.o: port.cpp port.h string.h field.h
	$(CXX) $(CXXFLAGS) -cpp -fpic port.cpp

#CLEAN FILES CREATED DURING COMPILATION
clean:
	$(RM)



