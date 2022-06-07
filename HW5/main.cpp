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

    String *src_port = new String("src-port");
    String *dst_port = new String("dst-port");
    String *src_ip = new String("src-ip");
    String *dst_ip = new String("dst-ip");
    String *input = new String(argv[1]);

    Port *psrc = new Port(*src_port);
    Port *dsrc = new Port(*dst_port);
    Ip *ipsrc = new Ip(*src_ip);
    Ip *ipdst = new Ip(*dst_ip);
    bool is_src_port = psrc->set_value(*input);
    bool is_dst_port = dsrc->set_value(*input);
    bool is_dst_ip = ipdst->set_value(*input);
    bool is_src_ip = ipsrc->set_value(*input);

    if(is_src_port){
    	cout << "src-port" << endl;
    	// parse_input(*psrc);
    }
    if(is_dst_port){
    	cout << "dst-port" << endl;
    	// parse_input(*dsrc);
    }
    if(is_src_ip){
    	cout << "src-ip" << endl;
    	// parse_input(*ipsrc);
    }
    if(is_dst_ip){
    	cout << "dst-ip" << endl;
    	// parse_input(*ipdst);
    }

 

    // checking port//
    // String* src_port = new String("src-port");
    // String *port_rule = new String("src-port = 130 - 132");
    // String *port_packet = new String("src-port=131");
    // Port* src_p = new Port(*src_port);
    // src_p->set_value(*port_rule);
    // cout << src_p->match(*port_packet)<<endl;
    return 0;
}
