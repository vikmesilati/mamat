#include <iostream>
#include "field.h"
#include "string.h"
using namespace std;

/**
 * @brief Constructor to the Field class, saves the string type
 * @param String pattern - The field type string {dst-ip,src-port...}
 */
Field::Field(String pattern){
	this->pattern=pattern.trim();
}




/**
 * @brief Destructor to the Field class, does nothing{no heap in constructor}
 */
Field::~Field(){}



/**
 * @brief Check if packet matches pattern(Rule)
 * @param String packet - Packets that have fields {dst-ip,src-port...}
 * @returns Returns true iff "packet" matches "this" 
 */
bool Field::match(String packet){
	String temp;
	String *out;
	size_t packet_size;
	packet.trim().split(",",&out,&packet_size);
	for(size_t i = 0; i < packet_size; i++){
		if(this->match_value(out[i])){
			delete[] out;
			return true;
		}
	}
	return false;
}



