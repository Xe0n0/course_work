# IPv4 协议转发实验

1000012926

吴昊天

## 实验目的

通过前面的实验,我们已经深入了解了 IPv4 协议的分组接收和发送处理流程。本实验需要将实验模块的角色定位从通信两端的主机转移到作为中 间节点的路由器上,在 IPv4 分组收发处理的基础上,实现分组的路由转发功能。
网络层协议最为关注的是如何将 IPv4 分组从源主机通过网络送达目的主机,这个任务就是由路由器中的 IPv4 协议模块所承担。路由器根据自身所获得的路由信息,将收到的 IPv4 分组转发给正确的下一跳路由器。如此逐跳地对分组进行转发,直至该分组抵达目的主机。IPv4 分组转发是路由器最为重要的功能。
本实验设计模拟实现路由器中的 IPv4 协议,可以在原有 IPv4 分组收发实验的基础上,增加 IPv4 分组的转发功能。对网络的观察视角由主机转移到路由器中,了解路由器是如何为分组选择路由,并逐跳地将分组发送到目的主机。本实验中也会初步接触路由表这一重要的数据结构,认识路由器是 如何根据路由表对分组进行转发的。
## 实验要求在前面 IPv4 分组收发实验的基础上,增加分组转发功能。具体来说,对于每一个到达本机的 IPv4 分组,根据其目的 IPv4 地址决定分组的处理行为,对该分组进行如下的几类操作:
1. 向上层协议上交目的地址为本机地址的分组;2. 根据路由查找结果,丢弃查不到路由的分组;3. 根据路由查找结果,向相应接口转发不是本机接收的分组。
## 实验内容
实验内容主要包括:
###  设计路由表数据结构。设计路由表所采用的数据结构。要求能够根据目的 IPv4 地址来确定分组处理行为(转发情况下需获得下一跳的 IPv4 地址。
###  IPv4 分组的接收和发送。
对前面实验(IP 实验)中所完成的代码进行修改,在路由器协议栈 的 IPv4 模块中能够正确完成分组的接收和发送处理。具体要求不做改 变,参见“IP 实验”。
###  IPv4 分组的转发
对于需要转发的分组进行处理,获得下一跳的 IP 地址,然后调用 发送接口函数做进一步处理。## 实验过程

本次实验需要实现三个函数

1. stud_fwd_deal
	
	处理收到的 IP 分组的函数
	
2. stud_route_add

	向路由表中添加路由信息的函数
	
3. stud_Route_Init

	初始化路由表的函数
	
这三个函数都与路由表紧密相关。可以采用 STL 中的 unordered_map 维护路由表信息，它本身是一个 hash，但是实验平台的编译环境不支持 C++11 标准，因此我采用了 map 数据结构，这是一个平衡二叉树的结构，查找的速度是对数时间，已经很快了。具体的数据结构为

	typedef map<uint32_t, uint32_t> routes_map;
	
初始化路由表只需要把表清空即可。添加路由表项也非常简单

	table[dst] = next_hop;
	
这里要注意的是 dst 和 next_hop 要从 stud_route_msg 的网络字节序转换而来。完整的初始化及添加路由信息代码：

	void stud_Route_Init(){
        table.clear();
	}
	
	void stud_route_add(stud_route_msg *proute) {
	        table[ntohl(proute->dest)] = ntohl(proute->nexthop);
	}

剩下的 stud_fwd_deal 也很简单，唯一要注意的还是字节序。在减少 ttl 之后重新计算 checksum 即可。这里复用之前的 ip_header_t 结构

	int stud_fwd_deal(char *pBuffer, int length){

	  ip_header_t *iph = (ip_header_t *)pBuffer;
	  
	  //判断分组的 ttl 还有效
	  if( iph->ttl <= 0 ){
	    fwd_DiscardPkt(pBuffer, STUD_FORWARD_TEST_TTLERROR);
	    return 1;
	  }
	
	  //是否是本机
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
	
