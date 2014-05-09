//1000012926
//WU Haotian
#include "sysInclude.h"

extern void ip_DiscardPkt(char* pBuffer,int type);

extern void ip_SendtoLower(char*pBuffer,int length);

extern void ip_SendtoUp(char *pBuffer,int length);

extern unsigned int getIpv4Address();

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

int stud_ip_recv(char *pBuffer, uint16_t length)
{
    ip_header_t *iph = (ip_header_t *)pBuffer;
    // Check version
    if( iph->ver() != 4 ){
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_VERSION_ERROR);
        return 1;
    }
    // Check IHL
    if( iph->ihl() < 5 ){
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_HEADLEN_ERROR);
        return 1;
    }
    // Check TTL
    if( iph->ttl <= 0 ){
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_TTL_ERROR);
        return 1;
    }
    // Check IP address
    uint32_t dst_addr = getIpv4Address();
    if( dst_addr != ntohl(iph->dst_addr) && dst_addr != 0xffffffff ){
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_DESTINATION_ERROR);
        return 1;
    }
    // Check checksum
    uint32_t checksum = 0;
    for( int i = 0; i < 10; i++ ){
        uint16_t tmp = *((unsigned short*) & pBuffer[i*2]);
        uint16_t unit = ntohs(tmp);
        checksum += unit;
    }
    uint16_t carrier = checksum >> 16;
    uint16_t verify_result = (uint16_t)checksum + carrier;
    if( verify_result != 0xffff ){
        ip_DiscardPkt(pBuffer, STUD_IP_TEST_CHECKSUM_ERROR);
        return 1;
    }
    // Everything is ok, send to upper level
    ip_SendtoUp(pBuffer, length);
    return 0;
}

int stud_ip_Upsend(char *pBuffer, unsigned short len, unsigned int srcAddr,
                                   unsigned int dstAddr, byte protocol, byte ttl)
{

    ip_header_t *iph = new ip_header_t();
    char * header = (char *)iph;

    // Version and IHL
    header[0] = 0x45;
    // Total length
    iph->total_length = htons(len + 20);
    // TTL
    iph->ttl = ttl;
    // Protocol
    iph->protocol = protocol;
    // Src IP and Dst IP
    iph->src_addr = htonl(srcAddr);
    iph->dst_addr = htonl(dstAddr);

    // Checksum
    uint32_t sum = 0;
    for (int i = 0; i < 10; i++ ){
        if ( i == 5 ) continue;
        uint16_t tmp = *((uint32_t *)&header[i*2]);
        sum += tmp;
    }
    while (true){
        uint16_t carrier = sum >> 16;
        if( carrier == 0 ){
            break;
        }
        sum = (uint16_t)sum + carrier;
    }

    iph->checksum = sum ^ 0xffff;

    // Create the packet
    char* packet = new char[20+len];
    memcpy(packet, header, sizeof(ip_header_t));
    memcpy(&packet[20], pBuffer, len);

    ip_SendtoLower(packet, len+20);
    return 0;
}

