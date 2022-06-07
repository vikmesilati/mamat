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
    // String *src_port = new String("    src-port   =    132.22.22.22/8   ");
    // String *dst_port = new String("132.22.22.21");
    // String *src_ip = new String("src-ip");
    // String *dst_ip = new String("dst-ip");
    // Ip *src = new Ip(*src_port);
    // src->set_value(*src_port);

    // cout << src->match_value(*dst_port)<<endl;
    
    
    // checking port//
    String* src_port = new String("src-port");
    String *port_rule = new String("src-port = 24 - 132");
    String *port_packet = new String("src-port=123");
    Port* src_p = new Port(*src_port);
    src_p->set_value(*port_rule);
    cout << src_p->match_value(*port_packet)<<endl;
    return 0;
}
