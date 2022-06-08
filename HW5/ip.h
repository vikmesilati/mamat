#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip : public Field{
private:
	const char *delimiters = "./=";
	char *mask;
	int mask_size;
	char* int_to_bit(int num) const;
	bool match_value(String value) const override;
	String pat;
public:
	Ip(String val);
	bool set_value(String val);
	bool match (String packet);
	~Ip();
};

#endif
