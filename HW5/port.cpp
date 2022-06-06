#include <iostream>

#include "string.h"
#include "field.h"
#include "port.h"

//IP Constructor
Port::Port(String val):Field(val){
	val.trim();//clean the string
	val.split(this->port_delimiter, &(this->port_parts), &(this->num_port_parts));//array of strings and every string has a number part of IP
	for(size_t i = 0; i < this->num_port_parts; i++){
		this->port_parts[i].trim();
	}
}

bool Port::set_value(String val){
	for(int i=0; i<2; i++){
		if((this->port_parts[i].to_integer() < 0) || (this->num_port_parts > 65535)){
			return false;
		}
	}
	return true;
}

bool Port::match_value(String value) const{
	for (int i=0; i< 2; i++){
		if(!(this->port_parts[i].equals(value))){
			return false;
		}
	}
	return true;
}

Port::~Port(){
	delete[] this->port_parts;
}
