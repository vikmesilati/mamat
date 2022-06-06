#include <iostream>

#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"

int main(int argc, char **argv){
    // if(check_args(argc, argv) == 0){
    //     exit(1);
    // }
    String *src_port = new String("src-port");
    String *dst_port = new String("dst_port");
    String *src_ip = new String("src-ip");
    String *dst_ip = new String("dst-ip");
    Port *src = new Port(*src_port);
    return 0;
}