#include <iostream>

#include "string.h"
#include "field.h"
#include "port.h"

//IP Constructor
PORT::PORT(String val){
	this.trim();//clean the string
	this.split(this->port_delimiter, this->port_parts, this->num_port_parts);//array of strings and every string has a number part of IP
}

bool PORT::set_value(String val){
	for(int i=0; i<2; i++){
		if((this->num_port_parts[i] < 0) || (this->num_port_parts[i] > 65535)){
			return false;
		}
	}
}

bool PORT:match_value(String value){
	for (int i=0; i< 2; i++){
		if(!(this->port_parts[i].equals(value))){
			return false;
		}
	}
	return true;
}

PORT::~PORT(){
	delete[] this->port_parts;
}
