#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip : public Field{
private:
	String val;
	String **ip_parts;
	size_t num_ip_parts;
	const char delimiters[3] = {'.', '/', '\0'};
public:
	Ip(String val);
	bool set_value(String val);
	bool match_value(String value);
	~Ip();
};

