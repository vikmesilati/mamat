
#include <iostream>
#include <cstring>
#include "string.h"
using namespace std;


/**
 * @brief Initiates an empty string
 */
String::String(){
    data = new char[1];
    data[0] = '\0';
    length = 0;
}



/**
 * @brief Initiates string from other string
 */
String::String(const String &str){
    data = new char[str.length + 1];
    strcpy(data, str.data);
    data[str.length] = '\0';
    length = str.length;
}


/**
 * @brief Initiates a string from char array
 */
String::String(const char *str){
    if(str == nullptr){
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
    else{
        data = new char[strlen(str) + 1];
        strcpy(data,str);
        data[strlen(str)] = '\0';
        length = strlen(str);
    }
}




String::~String(){
    delete[] data;
}




/**
 * @brief Changes this from String
 */
String& String::operator=(const String &rhs){
    if(this == &rhs){
        return *this;
    }
    delete this->data;
    this->data = new char[rhs.length + 1];
    strcpy(this->data,rhs.data);
    this->length = rhs.length;
    return *this;
}



/**
 * @brief Changes this from char array
 */
String& String::operator=(const char *str){
    if(this->data != NULL){
        delete this->data;
    }
    this->data = new char[strlen(str) + 1];
    strcpy(this->data,str);
    this->length = strlen(str);
    return *this;
}


/**
 * @brief Returns true iff the contents of this equals to the
 * contents of rhs
 */
bool String::equals(const String &rhs) const{
    if(strcmp(this->data,rhs.data) == 0 && this->length == rhs.length){
        return true;
    }
    return false;
}




/**
 * @brief Returns true iff the contents of this equals to rhs
 */
bool String::equals(const char *rhs) const{
    if(strcmp(this->data,rhs) == 0 && this->length == strlen(rhs)){
        return true;
    }
    return false;
}




/**
 * @brief Splits this to several sub-strings according to delimiters.
 * Allocates memory for output that the user must delete (using delete[]).
 * @note Does not affect this.
 * @note If "output" is set to NULL, do not allocated memory, only
 * compute "size".
 */
void String::split(const char *delimiters, String **output,
                    size_t *size) const{
    char *token1;
    char *temp = new char[this->length + 1];
    char *temp2 = new char[this->length + 1];
    strcpy(temp,this->data);
    strcpy(temp2,this->data);
    size_t size_arr = 0;
    token1 = strtok(temp2, delimiters);
    while( token1 != NULL ) {
        size_arr++;
        token1 = strtok(NULL, delimiters);
    }
    *size = size_arr;
    if(output != NULL){
   	 	String *arr = new String[size_arr];
   	 	char *token2;
   	 	for(size_t m = 0; m < size_arr ; m++){
    		arr[m] = String();
    	}
    	size_t i = 0;
    	token2 = strtok(temp, delimiters);
   		while( token2 != NULL || i < size_arr ) {
        	arr[i]=token2;
        	token2 = strtok(NULL, delimiters);
       		i++;
    	}
    	*output = arr;
     	delete[] temp;
     	delete[] temp2;
     }
}



/**
 * @brief Try to convert this to an integer. Returns 0 on error.
 */
int String::to_integer() const{
    try{
        int temp = stoi(this->data);
        return temp;
    }
    catch(exception &err){
        return 0;
    }
}



/**
 * @brief Remove any leading or trailing white-spaces.
 * Does not change this.
 */
String String::trim() const{
    char *start, *end;
    char *temp = new char[strlen(data)+1];
    strcpy(temp,data);
    start = temp;
    while (*start && (*start == ' ' || *start == ',')) start++;
    memmove(temp, start, strlen(start) + 1);
    end = temp + strlen(temp) - 1;
    while (*end && (*end == ' ' || *end == ',')) end--;
    *(end + 1) = '\0';
    
    char* d = start;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*start && (*start++ = *d++));
    
    String *ret = new String(temp);
    delete[] temp;
    return *ret;
}
