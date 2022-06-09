#include <iostream>

#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"
using namespace std;


/**
 * @brief Find the packets that match the given rules and print them
 * @param argc The number of inputs, which is the rules "1" 
 * @param argv We get the rules as a string
 * @return 0
 */
int main(int argc, char **argv){
   if(check_args(argc, argv) != 0){
       exit(1);
     }

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
    	parse_input(*psrc);
    }
    if(is_dst_port){
    	parse_input(*dsrc);
    }
    if(is_src_ip){
    	parse_input(*ipsrc);
    }
    if(is_dst_ip){
    	parse_input(*ipdst);
    }

 	delete src_port;
 	delete dst_port;
	delete src_ip;
	delete dst_ip;
	delete psrc;
	delete dsrc;
	delete ipsrc;
	delete ipdst;

    return 0;
}
