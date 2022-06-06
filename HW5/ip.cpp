#include <iostream>

#include <regex>
#include "string.h"
#include "field.h"
#include "ip.h"

using namespace std;

//IP Constructor
Ip::Ip(String val):Field(val){
	val = val.trim();//clean the string
	val.split(this->delimiters, &(this->ip_parts), &(this->num_ip_parts));//array of strings and every string has a number part of IP
	for(size_t i = 0; i < this->num_ip_parts; i++){
		this->ip_parts[i] = this->ip_parts[i].trim();
	}
}

char* Ip::int_to_bit(int num){
	char *out = new char[4];
	for(int i = 0 ; i < 4 ; i++){
        if(num%2){
            out[4-i-1] = '1';
        }
        else{
            out[4-i-1] = '0';
        }
        num = num/2;
    }
	return out;
}

bool Ip::set_value(String val){
	char *rule = new char[4 * (num_ip_parts-2)];
	if(ip_parts[num_ip_parts-1].to_integer() < 0 || ip_parts[num_ip_parts-1].to_integer() > 32){//Check the last string 
		return false;
	}
	for(size_t i=1; i < num_ip_parts - 1; i++){//the fifth is mask
		if((ip_parts[i].to_integer() < 0) || (ip_parts[i].to_integer() > 255)){
			return false;
		}
		strcat(rule,int_to_bit(ip_parts[i].to_integer()));
	}
	mask_size = ip_parts[num_ip_parts-1].to_integer();
	memcpy(mask,rule,mask_size);
	mask = rule;
	delete rule;
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
