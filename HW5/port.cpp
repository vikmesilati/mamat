#include <iostream>

#include "string.h"
#include "field.h"
#include "port.h"

//IP Constructor
Port::Port(String val):Field(val){
	this->val.trim();//clean the string
	this->val.split(this->port_delimiter, &(this->port_parts), &(this->num_port_parts));//array of strings and every string has a number part of IP
}

bool Port::set_value(String val){
	for(int i=0; i<2; i++){
		if((this->port_parts[i].to_integer() < 0) || (this->num_port_parts > 65535)){
			return false;
		}
	}
}

bool Port::match_value(String value){
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
