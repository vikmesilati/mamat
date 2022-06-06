
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
    String *arr = new String[size_arr];
    // size = size_arr;
    char *token2;
    for(int m = 0; m < size_arr ; m++){
        arr[m] = String();
    }
    int i = 0;
    token2 = strtok(temp, delimiters);
    while( token2 != NULL || i < size_arr ) {
        arr[i]=token2;
        token2 = strtok(NULL, delimiters);
        i++;
    }
    *output = arr;
    delete token2;
    delete token1;
    delete temp;
    delete temp2;
}

int String::to_integer() const{
    try{
        int temp = atoi(this->data);
        return temp;
    }
    catch(exception err){
        return 0;
    }
}

String String::trim() const{
    char *start, *end;
    String *temp = new String(*this);
    start = temp->data;
    while (*start && *start == ' ') start++;
    memmove(temp->data, start, strlen(start) + 1);
    end = temp->data + this->length - 1;
    while (*end && *end == ' ') end--;
    *(end + 1) = '\0';
    return *temp;
}

int main(){
    String *temp;
    String *temp2 = new String("a,b,c,d,h,v,k");
    size_t i = 0;
    temp2->split(",",&temp,&i);
    delete[] temp;
    return 0;
}