CXX=g++
CLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11 
OBJS=main.o
EXEC=firewall.exe
RM=rm -rf $(EXEC) libfirewall.so *.o 
LOBJS=string.o field.o ip.o port.o

#THE FIRST RULE IS INVOKED BY DEFAULT
$(EXEC): $(OBJS) libfirewall.so 
	$(CLINK) $(CXXFLAGS) $(OBJS) -o $(EXEC) -linput -lfirewall -L.

#ALL OTHER RULES
$(OBJS): main.cpp string.h field.h ip.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

libfirewall.so: $(LOBJS)
	$(CLINK) -shared $(LOBJS) -o libfirewall.so 

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
