#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip : public Field{
private:
	String *ip_parts;
	size_t num_ip_parts;
	const char *delimiters = "./=";
public:
	Ip(String val);
	bool set_value(String val);
	bool match_value(String value) const override;
	~Ip();
};

#endif
