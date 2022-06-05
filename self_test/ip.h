#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class IP : public Field{
private:
	String **ip_parts;
	int num_ip_parts[5];//4 parts ip and 1 part for mask number
	const char delimiters[2] = {'.', '/'};
public:
	IP(String val);
	bool set_value(String val);
	bool match_value(String value);
	~IP();
};

