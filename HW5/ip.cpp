#include <iostream>

#include <regex>
#include "string.h"
#include "field.h"
#include "ip.h"

using namespace std;

//IP Constructor
Ip::Ip(String val):Field(val){
	val.trim();//clean the string
	val.split(this->delimiters, &(this->ip_parts), &(this->num_ip_parts));//array of strings and every string has a number part of IP
	for(size_t i = 0; i < this->num_ip_parts; i++){
		this->ip_parts[i].trim();
	}
}

bool Ip::set_value(String val){
	if(this->ip_parts[this->num_ip_parts-1].to_integer() < 0 || this->ip_parts[this->num_ip_parts-1].to_integer() > 32){//Check the last string 
		return false;
	}
	for(size_t i=0; i < this->num_ip_parts - 2; i++){//the fifth is mask
		if((this->ip_parts[i].to_integer() < 0) || (this->ip_parts[i].to_integer() > 255)){
			return false;
		}
		int byte_part=8*(i+1);
		if(this->ip_parts[this->num_ip_parts-1].to_integer() < byte_part){
			ip_parts[i] = "0"; //mask don't care
		}
	}
	return true;
}

bool Ip::match_value(String value) const{
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
