#include <iostream>

#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
using namespace std;

int main(int argc, char **argv){
    // if(check_args(argc, argv) == 0){
    //     exit(1);
    // }
    String *src_port = new String("    src-port   =    132.22.22.22/8   ");
    String *dst_port = new String("132.22.22.21");
    String *src_ip = new String("src-ip");
    String *dst_ip = new String("dst-ip");
    Ip *src = new Ip(*src_port);
    src->set_value(*src_port);
    
    cout << src->match_value(*dst_port);
    return 0;
}