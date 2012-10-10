// a wrapper class for EtherShield

extern "C" {
	#include "enc28j60.h"
	#include "ip_arp_udp_tcp.h"
 
}
#include "EtherShield.h"

//constructor
EtherShield::EtherShield(){
}

uint16_t EtherShield::ES_fill_tcp_data_p(uint8_t *buf,uint16_t pos, const prog_char *progmem_s){
	return fill_tcp_data_p(buf, pos, progmem_s);
}

uint16_t EtherShield::ES_fill_tcp_data(uint8_t *buf,uint16_t pos, const char *s){
	return fill_tcp_data(buf,pos, s);
}


void EtherShield::ES_enc28j60Init(uint8_t* macaddr){
	enc28j60Init(macaddr);

}
void EtherShield::ES_enc28j60clkout(uint8_t clk){
	enc28j60clkout(clk);
}

void EtherShield::ES_enc28j60PhyWrite(uint8_t address, uint16_t data){
	enc28j60PhyWrite(address,  data);
}

uint16_t EtherShield::ES_enc28j60PacketReceive(uint16_t len, uint8_t* packet){
	return enc28j60PacketReceive(len, packet);
}


void EtherShield::ES_init_ip_arp_udp_tcp(uint8_t *mymac,uint8_t *myip,uint8_t wwwp){
	init_ip_arp_udp_tcp(mymac,myip,wwwp);
}

uint8_t EtherShield::ES_eth_type_is_arp_and_my_ip(uint8_t *buf,uint16_t len){
	return eth_type_is_arp_and_my_ip(buf,len);
}

void EtherShield::ES_make_arp_answer_from_request(uint8_t *buf){
	make_arp_answer_from_request(buf);
}

uint8_t EtherShield::ES_eth_type_is_ip_and_my_ip(uint8_t *buf,uint16_t len){
	return eth_type_is_ip_and_my_ip(buf, len);
}


void EtherShield::ES_make_echo_reply_from_request(uint8_t *buf,uint16_t len){
	make_echo_reply_from_request(buf,len);
}

void EtherShield::ES_make_tcp_synack_from_syn(uint8_t *buf){
	make_tcp_synack_from_syn(buf);
}	

void EtherShield::ES_init_len_info(uint8_t *buf){
	init_len_info(buf);
}

uint16_t EtherShield::ES_get_tcp_data_pointer(void){
	return get_tcp_data_pointer();
}

void EtherShield::ES_make_tcp_ack_from_any(uint8_t *buf){
	make_tcp_ack_from_any(buf);
}

void EtherShield::ES_make_tcp_ack_with_data(uint8_t *buf,uint16_t dlen){
	make_tcp_ack_with_data(buf,dlen);
}

void EtherShield::ES_make_arp_request(uint8_t *buf, uint8_t *server_ip){
	make_arp_request(buf, server_ip);
}

uint8_t EtherShield::ES_arp_packet_is_myreply_arp ( uint8_t *buf ){
	return arp_packet_is_myreply_arp (buf);
}

void EtherShield::ES_tcp_client_send_packet(uint8_t *buf,uint16_t dest_port, uint16_t src_port, uint8_t flags, uint8_t max_segment_size, 
	uint8_t clear_seqck, uint16_t next_ack_num, uint16_t dlength, uint8_t *dest_mac, uint8_t *dest_ip){
	
	tcp_client_send_packet(buf, dest_port, src_port, flags, max_segment_size, clear_seqck, next_ack_num, dlength,dest_mac,dest_ip);
}

uint16_t EtherShield::ES_tcp_get_dlength( uint8_t *buf ){
	return tcp_get_dlength(buf);
}












