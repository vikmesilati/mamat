#ifndef PORT_H
#define PORT_H

#include "field.h"
#include "string.h"

class PORT : public Field{
private:
	String **port_parts;
	int num_port_parts[2];//2 parts port
	const char port_delimiter[1] = {'-'};
public:
	PORT(String val);
	bool set_value(String val);
	bool match_value(String value);
	~PORT();
};
