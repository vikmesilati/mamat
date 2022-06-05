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
    if (&str == nullptr) {
        data = new char[1];
        data[0] = '\0';
        length = 0;
    }
 
    else {
        data = new char[str.length + 1];
        strcpy(data, str.data);
        data[str.length] = '\0';
        length = str.length;
    }
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
    cout << "here" << endl;
    delete this->data;
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
    strcpy(temp,this->data);
    int size_arr = 0;
    token1 = strtok(this->data, delimiters);

    while( token1 != NULL ) {
        size_arr++;
        token1 = strtok(NULL, delimiters);
    }
    char *token2;
    *output = (String*)malloc(sizeof(String) * (size_arr));
    int i = 0;
    token2 = strtok(temp, delimiters);
    while( token2 != NULL || i < size_arr ) {
        output[i]=new String(token2);
        token2 = strtok(NULL, delimiters);
        i++;
    }
    for(int k = 0; k < size_arr ; k++){
        cout << output[k]->data << endl;
    }
    delete token2;
    delete token1;
    delete temp;
}

int String::to_integer() const{
    try{
        int temp = stoi(this->data);
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
    String **temp;
    String *temp2 = new String("a,b,c,d,h,v,k");
    size_t *i = 0;
    temp2->split(",",temp,i);
    // delete[] &temp;
}