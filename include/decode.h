#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PID_RESERVED 0x0
#define PID_OUT	     0x1
#define PID_IN	     0x9
#define PID_SOF	     0x5
#define PID_SETUP    0xD
#define PID_DATA0    0x3
#define PID_DATA1    0xB
#define PID_DATA2    0x7
#define PID_MDATA    0xF
#define PID_ACK	     0x2
#define PID_NAK      0xA
#define PID_STALL    0xE
#define PID_NYET     0x6
#define PID_PRE	     0xC
#define PID_ERR	     0xC
#define PID_SPLIT    0x8
#define PID_PING     0x4

#define PID_TYPE_SPECIAL   0
#define PID_TYPE_TOKEN     1
#define PID_TYPE_HANDSHAKE 2
#define PID_TYPE_DATA      3


const char *pid_str[] = {"RESERVED", "OUT", "ACK", "DATA0", "PING", "SOF", "NYET", "DATA2", "SPLIT", "IN", "NAK", "DATA1", "ERR/PRE", "SETUP", "STALL", "MDATA"};

struct usb_packet_s {
  unsigned long long int timestamp;
  unsigned char pid;
  unsigned char addr;
  unsigned char ep;
  unsigned short crc;
  unsigned short frameno;
  unsigned char data[1024];
  unsigned int dlen;
};

void print_pkt(struct usb_packet_s *pkt)
{
  int i;
  printf("TIMESTAMP; %llu PID: %s (%02x) ADDR: %02X ENDPOINT: %d CRC: %04X FRAME_NUMBER: %d DATA_LEN: %d\n",pkt->timestamp, pid_str[pkt->pid & 0xF], pkt->pid, pkt->addr, pkt->ep, pkt->crc, pkt->frameno, pkt->dlen);
  if(pkt->dlen){
    for(i=0;i<pkt->dlen;i++){
      printf("%02x ", pkt->data[i]);
    }
    printf("\n");
  }
}



struct usb_packet_s decode_usb(char *buf, int dlen)
{
	int i;
	int len;
	unsigned long long int timestamp;
	unsigned char *data;
	unsigned char pid;
	unsigned char pid_type;
	struct usb_packet_s pkt;
	memcpy(&len, buf, sizeof(int));
	memcpy(&timestamp, buf + sizeof(int), 8);
	data = static_cast<unsigned char*>(static_cast<void *>(buf)) + 12;
	if((data[0] & 0xf) != (~(data[0] >> 4) & 0xf) ){
		printf("packet error !\n");
        return usb_packet_s();
	}


	pid = data[0] & 0xF;
	pid_type = pid & 0x3;


	memset(&pkt, 0, sizeof(struct usb_packet_s));
	pkt.timestamp = timestamp;
	pkt.pid = data[0];

	switch(pid_type){  
		case PID_TYPE_SPECIAL:

			switch(pid){
				case PID_PRE:
				case PID_SPLIT:
				case PID_PING:
					break;
			}
			break;

		case PID_TYPE_TOKEN:
			pkt.crc = data[2] >> 3;
			switch(pid){
				case PID_OUT:
				case PID_IN:
				case PID_SETUP:
					pkt.addr = data[1] &0x7f;
					pkt.ep = ((data[2] & 0x7) << 1) | (( data[1] & 0x80) >> 7);
					break;
				case PID_SOF:
					pkt.frameno = data[1] | ((data[2] & 0x7) << 8);
					break;
			}
			break;

		case PID_TYPE_HANDSHAKE:

			switch(pid){
				case PID_ACK:
				case PID_NAK:
				case PID_STALL:
				case PID_NYET:
					break;
			}
			break;

		case PID_TYPE_DATA:

			memcpy(pkt.data, data+1, len - 3);
			pkt.dlen = len - 3;
			pkt.crc = data[len - 2] | (data[len - 1] << 8);
			switch(pid){
				case PID_DATA0:
				case PID_DATA1:
				case PID_DATA2:
				case PID_MDATA:
					break;
			}
			break;
	}
    //print_pkt(&pkt);

    return pkt;
}

#endif
