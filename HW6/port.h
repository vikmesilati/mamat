#ifndef PORT_H
#define PORT_H

#include "field.h"
#include "string.h"

class Port : public Field{
private:
	const char *port_delimiter = "-=";
	String pat;
public:
	int port_min;
	int port_max;


	/**
 	 * @brief Constructor to the Port class, saves the string type
 	 * @param String val - The field type string {dst-port,src-port}
 	 */
	Port(String val);



	/**
 	 * @brief Set the legal values of given Port string
 	 * @param String val - The field type string {dst-port,src-port}
 	 * @return true if the Port is legal
	 */	
	bool set_value(String val);



	/**
 	 * @brief Check if the Port fields in packet matches the pattern
 	 * @param String value - The Port of the packet {dst-port,src-port}
 	 * @Returns true iff "value" in the range of this  */
	bool match_value(String value) const override;


	/**
 	 * @brief Check if Port packet matches Port pattern(Rule)
 	 * @param String packet - Packets that have fields {dst-port,src-port}
 	 * @returns Returns true iff "packet" in the range of "this" 
 	 */
	bool match(String packet);




	/**
 	 * @brief Destructor to the Port class, does nothing{no heap in constructor}
	 */
	~Port();
};

#endif
