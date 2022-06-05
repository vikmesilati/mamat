#include <iostream>

#include "string.h"
#include "field.h"
#include "ip.h"

//IP Constructor
Ip::Ip(String val):Field(val){
	this->val.trim();//clean the string
	this->val.split(this->delimiters, &(this->ip_parts), &(this->num_ip_parts));//array of strings and every string has a number part of IP
}

bool Ip::set_value(String val){
	if(this->ip_parts[this->num_ip_parts-1].to_integer() < 0 || this->num_ip_parts > 32){//Check the last string 
		return false;
	}
	for(int i=0; i<4; i++){//the fifth is mask
		if((this->ip_parts[i].to_integer() < 0) || (this->ip_parts[i].to_integer() > 255)){
			return false;
		}
		int byte_part=8*(i+1);
		if((this->ip_parts[this->num_ip_parts-1].to_integer() < byte_part) && (this->ip_parts[i].to_integer() != 0)){
			ip_parts[i] = "0"; //mask don't care
		}
	}
	return true;
}

bool Ip::match_value(String value){
	int max_care = this->ip_parts[num_ip_parts-1].to_integer();
	int i = 0;
	while(max_care>1){
		if(this->ip_parts[i].equals(value)){
			max_care/=8;
			i++;
			continue;
		}
		return false;
	}
	return true;
}

Ip::~Ip(){
	delete[] this->ip_parts;
}
