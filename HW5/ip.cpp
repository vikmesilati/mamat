#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "ip.h"

using namespace std;

#define BINARY_BITS 8
#define MASK_MIN_VAL 0
#define MASK_MAX_VAL 32
#define IP_MAX_VAL 255
#define IP_MIN_VAL 0
#define PACKET_IP_SPLIT 5



/**
 * @brief Constructor to the Ip class, saves the string type
 * @param String val - The field type string {dst-ip,src-ip}
 */
Ip::Ip(String val):Field(val){
	this->pat = val;
}


/**
 * @brief Change the given number to binary base
 * @param num - Number in the Ip  
 * @return out - A string that has the binary base of num
 * @note Binary base is the numbers '0' and '1'
 */
char* Ip::int_to_bit(int num) const{
	char *out = new char[BINARY_BITS];
	for(int i = 0 ; i < BINARY_BITS ; i++){
        if(num%2){
            out[BINARY_BITS-i-1] = '1';
        }
        else{
            out[BINARY_BITS-i-1] = '0';
        }
        num = num/2;
    }
	return out;
}


/**
 * @brief Set the legal values of given Ip string
 * @param String val - The field type string {dst-ip,src-ip} 
 * @return true if the Ip is legal
 */
bool Ip::set_value(String val){
	String *out;
	size_t num;
	val.trim().split(delimiters,&out,&num);
	if(pat.equals(out[0])){
		/* Mask and field type are irrelvent here (-2) */
		char *rule = new char[BINARY_BITS * (num-2)];
		memset(rule,0,BINARY_BITS*(num-2));
		/* Check the Mask value */
		size_t mask_val = out[num-1].to_integer();
		if(mask_val < MASK_MIN_VAL || mask_val > MASK_MAX_VAL){
			delete[] out;
			delete[] rule;
			return false;
		}
		for(size_t i=1; i < num - 1; i++){
			size_t temp_ip_num = out[i].to_integer();
			if((temp_ip_num < IP_MIN_VAL) || (temp_ip_num > IP_MAX_VAL)){
				delete[] out;
				delete[] rule;
				return false;
			}
			char* temp = int_to_bit(out[i].trim().to_integer());
			strcat(rule,temp);
			delete[] temp;
		}
		mask = new char[BINARY_BITS * (num-2)];
		mask_size = out[num-1].to_integer();
		memcpy(mask,rule,mask_size);
		delete[] out;
		delete[] rule;
		return true;
	}
	delete[] out;
	return false;
}




/**
 * @brief Check if the Ip fields in packet matches the pattern
 * @param String value - The Ip of the packet {dst-ip,src-ip} 
 * @Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
       matches 1.1.*.*) */
bool Ip::match_value(String value) const{
	String *out;
	size_t num;
	value.trim().split(delimiters,&out,&num);
	if(num < PACKET_IP_SPLIT){return false;}
	char *val = new char[BINARY_BITS * (num-1)];
	memset(val,0,BINARY_BITS*(num-1));
	for(size_t i=1; i < num; i++){
		size_t temp_ip_num = out[i].to_integer();
		if((temp_ip_num < IP_MIN_VAL) || (temp_ip_num > IP_MAX_VAL)){
			return false;
		}
		char* temp = int_to_bit(out[i].trim().to_integer());
		strcat(val,temp);
		delete[] temp;
	}
	/* In the first index there is the Ip type */
	String temp = out[0];
	char *rule = new char[strlen(val)+1];
	memcpy(rule,val,mask_size);
	String *str_rule = new String(rule);
	bool res = str_rule->equals(mask) && pat.equals(temp);
	delete str_rule;
	delete[] rule;
	delete[] out;
	delete[] val;
	return  res;
}


/**
 * @brief Check if Ip packet matches Ip pattern(Rule)
 * @param String packet - Packets that have fields {dst-ip,src-ip}
 * @returns Returns true iff "packet" matches "this" 
 */
bool Ip::match(String packet){
	return this->match_value(packet);
}



/**
 * @brief Destructor to the Ip class, does nothing{no heap in constructor}
 */
Ip::~Ip(){}

