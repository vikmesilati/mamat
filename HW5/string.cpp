
#include <iostream>
#include <cstring>
#include "string.h"
using namespace std;

String::String(){
    data = new char[1];
    data[0] = '\0';
    length = 0;
}

String::String(const String &str){
    data = new char[str.length + 1];
    strcpy(data, str.data);
    data[str.length] = '\0';
    length = str.length;
}

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

String& String::operator=(const char *str){
    if(this->data != NULL){
        delete this->data;
    }
    this->data = new char[strlen(str) + 1];
    strcpy(this->data,str);
    this->length = strlen(str);
    return *this;
}

bool String::equals(const String &rhs) const{
    if(strcmp(this->data,rhs.data) == 0 && this->length == rhs.length){
        return true;
    }
    return false;
}

bool String::equals(const char *rhs) const{
    if(strcmp(this->data,rhs) == 0 && this->length == strlen(rhs)){
        return true;
    }
    return false;
}

void String::split(const char *delimiters, String **output, size_t *size) const{
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
     	delete[] temp;/////////
     	delete[] temp2;////////////
     }
}

int String::to_integer() const{
    try{
        int temp = stoi(this->data);
        return temp;
    }
    catch(exception &err){
        return 0;
    }
}

String String::trim() const{
    char *start, *end;
    char *temp = new char[strlen(data)+1];//////////////
    strcpy(temp,data);
    start = temp;
    while (*start && (*start == ' ' || *start == ',')) start++;
    memmove(temp, start, strlen(start) + 1);
    end = temp + strlen(temp) - 1;
    while (*end && (*end == ' ' || *end == ',')) end--;
    *(end + 1) = '\0';
    String *ret = new String(temp);
    delete[] temp;////////////
    return *ret;
}
