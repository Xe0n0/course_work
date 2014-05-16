#Lab2 IPv4 收发实验

1000012926

吴昊天

## 实验目的

IPv4 协议是互联网的核心协议,它保证了网络节点(包括网络设备和主机)在网络层能够按照标准协议互相通信。IPv4 地址唯一标识了网络节点。 在我们日常使用的计算机的主机协议栈中,IPv4 协议必不可少,它能够接收网络中传送给本机的分组,同时也能根据上层协议的要求将报文封装为 IPv4 分组发送出去。

本实验通过设计实现主机协议栈中的 IPv4 协议,让学生深入了解网络层协议的基本原理,学习 IPv4 协议基本的分组接收和发送流程。












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

```

#### 接受分组

要检查的内容：

* 版本号
* ihl 的最小值
* ttl 值
* dst_addr 是否是本机地址
* checksum 的值，20个Byte 分成 2Byte 的十组，相加后再把高 2Byte 加到低 2Byte 上，这个值应该是 0xffff

关键代码

```
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

```

#### 发送分组

注意 checksum 的算法要先忽略 checksum 所在的 2Byte，求和所有其他的 2Byte 组，然后把高 2Byte 加到低 2Byte 上直到没有进位，最后再取反。

关键代码

```
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
    
```

### 实验结果

要注意头中超过 1Byte 的字段都是需要转换字节序的