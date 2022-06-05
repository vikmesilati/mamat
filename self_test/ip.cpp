#include <iostream>

#include "string.h"
#include "field.h"
#include "ip.h"

//IP Constructor
IP::IP(String val){
	this.trim();//clean the string
	this.split(this->delimiters, this->ip_parts, this->num_ip_parts);//array of strings and every string has a number part of IP
}

bool IP::set_value(String val){
	if(this->num_ip_parts[5] < 0 || this->num_ip_parts[5] > 32){
		return false;
	}
	for(int i=0; i<4; i++){//the fifth is mask
		if((this->num_ip_parts[i] < 0) || (this->num_ip_parts[i] > 255)){
			return false;
		}
		int byte_part=8*(i+1);
		if((this->num_ip_parts[5] < byte_part) && (this->num_ip_parts[i] != 0){
			num_ip_parts[i] = 0; //mask don't care
		}
	}
	return true;
}

bool IP:match_value(String value){
	int max_care = this->num_ip_parts[5];
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

IP::~IP(){
	delete[] this->ip_parts;
}
