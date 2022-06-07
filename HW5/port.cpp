#include <iostream>

#include "string.h"
#include "field.h"
#include "port.h"
using namespace std;
//PORT Constructor
Port::Port(String val):Field(val), port_min(0), port_max(0){}

bool Port::set_value(String val){
	String *temp_ports;
	size_t num_ports;
	val.trim();//clean the string
	val.split(port_delimiter, &(temp_ports), &(num_ports));//array of strings and every string has a number part of IP
	port_min = temp_ports[2].trim().to_integer();
	port_max = temp_ports[3].trim().to_integer();
	delete[] temp_ports;
	if(port_min > port_max){
		return false; //MIN > MAX
	}
	if((port_min < 0) || (port_max > 65535)){
		return false;
	}
	return true;
}

bool Port::match_value(String value) const{
	String *val_arr;
	size_t val_size;
	value.trim().split("=",&val_arr,&val_size);
	String packet_type = val_arr[0];
	int port_packet = val_arr[1].trim().to_integer();
	bool is_match = this->Field::match(packet_type);
	delete[] val_arr;
	if((port_min <= port_packet) && (port_max >= port_packet) && is_match){
		return true;
	}
	return false;
}

bool Port::match(String value) const{
	return this->match_value(value);
}
Port::~Port(){}
