#include <iostream>

#include <regex>
#include "field.h"
#include "string.h"
using namespace std;

//PUBLIC
//Copy from given Pattern to the private part
Field::Field(String pattern){
	this->pattern=pattern.trim();///////field.pattern' is not OK 
}

//Delete the copied string
Field::~Field(){//stack(no allocate)
	
}

/* Returns true iff "packet" matches "this" */
bool Field::match(String packet){
	return pattern.equals(packet);
}



