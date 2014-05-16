#include "sysInclude.h"
#include <map>
using namespace std;

extern void fwd_LocalRcv(char *pBuffer, int length);

extern void fwd_SendtoLower(char *pBuffer, int length, unsigned int nexthop);

extern void fwd_DiscardPkt(char *pBuffer, int type);

extern unsigned int getIpv4Address( );


struct ip_header_t {
    uint8_t  ver_ihl;  // 4 bits version and 4 bits internet header length
    uint8_t  tos;
    uint16_t total_length;
    uint16_t id;
    uint16_t flags_fo; // 3 bits flags and 13 bits fragment-offset
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t   src_addr;
    uint32_t   dst_addr;

    uint8_t ihl();
    uint8_t ver();
}__attribute__((packed));

uint8_t ip_header_t::ihl() {
    return (ver_ihl & 0x0F);
}
uint8_t ip_header_t::ver() {
    return ver_ihl >> 4;
}

typedef map<int32_t, int32_t> routes_map;

routes_map table;

void stud_Route_Init(){
        table.clear();
}

void stud_route_add(stud_route_msg *proute) {
        table[ntohl(proute->dest)] = ntohl(proute->nexthop);
}

int stud_fwd_deal(char *pBuffer, int length){

  ip_header_t *iph = (ip_header_t *)pBuffer;

  if( iph->ttl <= 0 ){
    fwd_DiscardPkt(pBuffer, STUD_FORWARD_TEST_TTLERROR);
    return 1;
  }

  uint32_t dest = ntohl(iph->dst_addr);
  if( dest == getIpv4Address() ){
    fwd_LocalRcv(pBuffer, length);
    return 0;
  }

  routes_map::iterator it;
  it = table.find(dest);

  if( it == table.end() ){
    fwd_DiscardPkt(pBuffer, STUD_FORWARD_TEST_NOROUTE);
    return 1;
  }
  char * newbuffer = new char[length];
  memcpy(newbuffer, pBuffer, length);

  ip_header_t *new_iph = (ip_header_t *)newbuffer;

  new_iph->ttl--;

  uint8_t ihl = iph->ihl();

  uint32_t sum = 0;
  for( int i = 0; i < 2 * ihl; i++ ){
      if( i == 5 ){
          continue;
      }
      uint16_t tmp = htons(*(uint16_t *)&newbuffer[2*i]);
      sum += tmp;
  }
  while(true){
    uint16_t carrier = sum >> 16;
    if( carrier == 0 ){
      break;
    }
    sum = (uint16_t)sum + carrier;
  }

  new_iph->checksum = htons(sum ^ 0xffff);

  fwd_SendtoLower(newbuffer, length, it->second);

  return 0;
}

