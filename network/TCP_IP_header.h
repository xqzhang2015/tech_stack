// IP报头   
typedef struct ip  
{  
    u_int ip_v:4; //version(版本)   
    u_int ip_hl:4; //header length(报头长度)   
    u_char ip_tos;  
    u_short ip_len;  
    u_short ip_id;  
    u_short ip_off;  
    u_char ip_ttl;  
    u_char ip_p;  
    u_short ip_sum;  
    struct in_addr ip_src;  
    struct in_addr ip_dst;  
} IP_HEADER;

// TCP报头结构体   
typedef struct tcphdr   
{  
    u_short th_sport; // 16 bits
    u_short th_dport; // 16 bits  
    u_int th_seq; // 32 bits
    u_int th_ack; // 32 bits
    u_int th_off:4;  
    u_int th_x2:4;  
    u_char th_flags;  
    u_short th_win;  
    u_short th_sum;  
    u_short th_urp;  
} TCP_HEADER;  
#define TH_FIN 0x01   
#define TH_SYN 0x02   
#define TH_RST 0x04   
#define TH_PUSH 0x08   
#define TH_ACK 0x10   
#define TH_URG 0x20   

// UDP报头结构体
typedef struct udphdr   
{  
    u_short uh_sport;  
    u_short uh_dport;  
    u_short uh_ulen;  
    u_short uh_sum;  
} UDP_HEADER;  

/*********************************************/  
/*********************************************/
//tcp与ip生成的报头   
typedef struct packet_tcp   
{  
    struct ip ip;  
    struct tcphdr tcp;  
    u_char data[MAXDATA];  
}TCP_IP;  

//udp与ip生成的报头   
typedef struct packet_udp   
{  
    struct ip ip;  
    struct udphdr udp;  
}UDP_IP;
