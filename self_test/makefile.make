CXX=g++
CLINK=$(CXX)
CXXFLAGS=-g -Wall -std=c++11
OBJS=main.o
EXEC=firewall.exe
RM=rm -rf $(EXEC) libfirewall.so *.o
LOBJS=string.o field.o ip.o port.o

#THE FIRST RULE IS INVOKED BY DEFAULT
$(EXEC): $(OBJS) libfirewall.so linput.so
	$(CLINK) $(CXXFLAGS) $(OBJS) -o $(EXEC) -linput -lfirewall -L.

#ALL OTHER RULES
$(OBJS): libfirewall.so libinput.so main.cpp
	$(CXX) $(CXXFLAGS) -cpp main.cpp

libfirewall.so: $(OBJS)
	$(CLINK) -shared $(LOBJS) -o libfirewall.so

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



