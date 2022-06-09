#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip : public Field{
private:
	const char *delimiters = "./=";
	char *mask;
	int mask_size;
	
	/**
	 * @brief Change the given number to binary base
	 * @param num - Number in the Ip  
	 * @return out - A string that has the binary base of num
	 * @note Binary base is the numbers '0' and '1'
	 */
	char* int_to_bit(int num) const;


	/**
	 * @brief Check if the Ip fields in packet matches the pattern
 	 * @param String value - The Ip of the packet {dst-ip,src-ip} 
 	 * @Returns true iff "value" matches the value of this (e.g., if 1.1.1.1
       matches 1.1.*.*) */
	bool match_value(String value) const override;
	String pat;
public:


	/**
 	 * @brief Constructor to the Ip class, saves the string type
 	 * @param String val - The field type string {dst-ip,src-ip}
	 */
	Ip(String val);
	

	/**
 	 * @brief Set the legal values of given Ip string
	 * @param String val - The field type string {dst-ip,src-ip} 
	 * @return true if the Ip is legal
 	 */
	bool set_value(String val);


	/**
 	 * @brief Check if Ip packet matches Ip pattern(Rule)
 	 * @param String packet - Packets that have fields {dst-ip,src-ip}
 	 * @returns Returns true iff "packet" matches "this" 
	 */
	bool match (String packet);


	/**
	 * @brief Destructor to the Ip class, does nothing{no heap in constructor}
 	 */
	~Ip();
};

#endif
