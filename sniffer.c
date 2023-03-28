sniffer.c
#include "sniffer.h"
// Global variables
int count_printed;
captured and printed till now
char protocol[15] = "all"; char source_ip[40] = ""; char destination_ip[40] =
on
char source_MAC[40] = "";
char destination_MAC[40] = '"'"'; 
pack packet_struct[MAX_PACKETS];
packet for MAX_PACKETS number of packets
int main(int argc, char **argv)
{
// declaration of variables
int rawsock;
descriptor
int len:
packet
int proto;
int state = 1;
till state != 0
char buffer[MAXLENGTH];
struct sockaddr 11 sll;
sock address
struct ifreq req;
int t;
struct timeval tv1,tv2;
count_printed = 0;
if (strcmp(protocol,"all")==0)
proto = ETH_P_ALL;

if (strcmp(protocol,"ipv4")==0 || strcmp(protocol,"ipv4|udp")==0 ||strcmp(protocol,"ipv4|tcp")==0 || strcmp(protocol,"ipv4|icmp") == 0)
proto = ETH_P_IP;
if (strcmp(protocol,"ipv6") == 0 || strcmp(protocol,"ipv6|udp") == 0 || strcmp(protocol,"ipv6|tcp") == 0 || strcmp(protocol,"ipv6|icmp") == 0) 

proto = ETH_P_IPV6;
if (strcmp(protocol,"arp") == 0) 
proto = ETH_P_ARP;
if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(proto)))== -1)
{
perror("Error in creating raw socket: ");
exit(-1);
}
bzero(&sll, sizeof(sll));
bzero(&req, sizeof(req));
strncpy((char *)req.ifr_name, argv[1], IFNAMSIZ);
if((ioctl(rawsock, SIOCGIFINDEX, &req)) == -1)
{
printf("Error while retrieving Interface index !\n");
exit(-1);
}
sll.sll_family = AF_PACKET;
sll.sll_ifindex = req.ifr_ifindex;
sll.sll_protocol = htons(proto);
{
perror("Error binding raw socket to interface\n");
exit(-1);
}
while(state)
{
if((len = recvfrom(rawsock, buffer, MAXLENGTH, 0, NULL, NULL)) == -1)
{
perror("Recv from returned -1: ");
exit(-1);
}
// Time after capturing the packet
else
{
gettimeofday(&tv2, NULL);
if (count_printed == MAX_PACKETS)
state = 0;
sprintf(packet_struct[count_printed].less_relevant,"Frame Size :%d bytes \n",len);
t = PrintPacketInformation(buffer, len);
if (t)
{
packet_struct[count_printed].size = len;
packet_struct[count_printed].index = count_printed + 1;
packet_struct[count_printed].arrival_time = ((double) (tv2.tv_usec - tv1.tv_usec)/1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
Printpacket();
Printhexdump(buffer,len);
count_printed ++;
}
else
{
bzero(packet_struct,sizeof(pack));
}
}
bzero(buffer,MAXLENGTH);
}
shutdown(rawsock,2);
return 0;
}
