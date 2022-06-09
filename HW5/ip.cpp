#include <iostream>

#include <regex>
#include "string.h"
#include "field.h"
#include "ip.h"

using namespace std;

//IP Constructor
Ip::Ip(String val):Field(val){
	this->pat = val;
}

char* Ip::int_to_bit(int num) const{
	char *out = new char[8];
	for(int i = 0 ; i < 8 ; i++){
        if(num%2){
            out[8-i-1] = '1';
        }
        else{
            out[8-i-1] = '0';
        }
        num = num/2;
    }
	return out;
}

bool Ip::set_value(String val){
	String *out;
	size_t num;
	val.trim().split(delimiters,&out,&num);
	if(pat.equals(out[0])){
		char *rule = new char[8 * (num-2)];
		memset(rule,0,8*(num-2));
		if(out[num-1].to_integer() < 0 || out[num-1].to_integer() > 32){//Check the last string 
			delete[] out;//////
			delete[] rule;/////
			return false;
		}
		for(size_t i=1; i < num - 1; i++){//the fifth is mask
			if((out[i].to_integer() < 0) || (out[i].to_integer() > 255)){
				delete[] out;///////////////
				delete[] rule;//////
				return false;
			}
			char* temp = int_to_bit(out[i].trim().to_integer());
			strcat(rule,temp);
			delete[] temp;//////////
		}
		mask = new char[8 * (num-2)];
		mask_size = out[num-1].to_integer();
		memcpy(mask,rule,mask_size);
		delete[] out;/////////////////
		delete[] rule;////////
		//delete[] mask;//////
		return true;
	}
	delete[] out;
	return false;
}

bool Ip::match_value(String value) const{
	String *out;
	size_t num;
	value.trim().split(delimiters,&out,&num);
	if(num < 5){return false;}////////
	char *val = new char[8 * (num-1)];/////
	memset(val,0,8*(num-1));///////////
	for(size_t i=1; i < num; i++){//the fifth is mask////////
		if((out[i].to_integer() < 0) || (out[i].to_integer() > 255)){
			return false;
		}
		char* temp = int_to_bit(out[i].trim().to_integer());
		strcat(val,temp);
		delete[] temp;//////////////////
	}
	String temp = out[0];
	char *rule = new char[strlen(val)+1];

	memcpy(rule,val,mask_size);
	String *str_rule = new String(rule);
	bool res = str_rule->equals(mask) && pat.equals(temp);
	delete str_rule;////////
	delete[] rule;///////
	delete[] out;
	delete[] val;
	return  res;

}

bool Ip::match(String packet){
	return this->match_value(packet);
}

Ip::~Ip(){}

