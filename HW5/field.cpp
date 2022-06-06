#include <iostream>


#include "field.h"
#include "string.h"

//PUBLIC
//Copy from given Pattern to the private part
Field::Field(String pattern){
	this->pattern=pattern;///////field.pattern' is not OK 
}

//Delete the copied string
Field::~Field(){//stack(no allocate)
	
}

/* Returns true iff "packet" matches "this" */
bool Field::match(String packet){
	return true;
}



