#include <iostream>
#include "string.h"
#include "field.h"
#include "port.h"

using namespace std;

#define PORT_MIN_VAL 0
#define PORT_MAX_VAL 65535

/**
 * @brief Constructor to the Port class, saves the string type
 * @param String val - The field type string {dst-port,src-port}
 */
Port::Port(String val):Field(val), port_min(0), port_max(0){
	this->pat = val;
}



/**
 * @brief Set the legal values of given Port string
 * @param String val - The field type string {dst-port,src-port}
 * @return true if the Port is legal
 */
bool Port::set_value(String val){
	String *temp_ports;
	size_t num_ports;
	String *val_arr;
	size_t val_size;
	val.trim().split("=",&val_arr,&val_size);
	val.trim().split(port_delimiter, &(temp_ports), &(num_ports));
	if(pat.equals(val_arr[0])){
		port_min = temp_ports[2].trim().to_integer();
		port_max = temp_ports[3].trim().to_integer();
		delete[] temp_ports;
		delete[] val_arr;
		if(port_min > port_max){
			/* MIN > MAX */
			return false; 
		}
		if((port_min < PORT_MIN_VAL) || (port_max > PORT_MAX_VAL)){
			return false;
		}
		return true;
	}
	delete[] temp_ports;
	delete[] val_arr;
	return false;
}



/**
 * @brief Check if the Port fields in packet matches the pattern
 * @param String value - The Port of the packet {dst-port,src-port}
 * @Returns true iff "value" in the range of this  */
bool Port::match_value(String value) const{
	String *val_arr;
	size_t val_size;
	value.trim().split("=",&val_arr,&val_size);
	String packet_type = val_arr[0];
	int port_packet = val_arr[1].trim().to_integer();
	bool is_match = pat.equals(packet_type);
	delete[] val_arr;
	if((port_min <= port_packet) && (port_max >= port_packet) && is_match){
		return true;
	}
	return false;
}



/**
 * @brief Check if Port packet matches Port pattern(Rule)
 * @param String packet - Packets that have fields {dst-port,src-port}
 * @returns Returns true iff "packet" in the range of "this" 
 */
bool Port::match(String value){
	return this->match_value(value);
}


/**
 * @brief Destructor to the Port class, does nothing{no heap in constructor}
 */
Port::~Port(){}
