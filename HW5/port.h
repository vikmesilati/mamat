#ifndef PORT_H
#define PORT_H

#include "field.h"
#include "string.h"

class Port : public Field{
private:
	String *port_parts;
	size_t num_port_parts;//2 parts port
	const char *port_delimiter = "-";
public:
	Port(String val);
	bool set_value(String val);
	bool match_value(String value) const override;
	~Port();
};

#endif
