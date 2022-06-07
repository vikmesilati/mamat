#include <iostream>

#include "string.h"
#include "field.h"
#include "port.h"

//PORT Constructor
Port::Port(String val):Field(val), port_min(0), port_max(0){}

bool Port::set_value(String val){
	String *temp_ports;
	size_t num_ports;
	val.trim();//clean the string
	val.split(port_delimiter, &(temp_ports), &(num_ports));//array of strings and every string has a number part of IP
	port_min = temp_ports[1].trim().to_integer();
	port_max = temp_ports[2].trim().to_integer();

	if(port_min > port_max){
		return false; //MIN > MAX
	}
	if((port_min < 0) || (port_max > 65535)){
		return false;
	}
	return true;
}

bool Port::match_value(String value) const{
	int port_packet = value.trim().to_integer();
	if((port_min <= port_packet) && (port_max >= port_packet)){
		return true;
	}
	return false;
}

Port::~Port(){}
