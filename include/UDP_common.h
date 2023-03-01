#pragma  once

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") 
#include <stdio.h>
#include "socket.h"

#if defined(__cplusplus)
extern "C" {
#endif
#define buffer_size  512
#define  LENGTH 64
#define  DATA_LENGTH 50
#define  STRING_LENGTH 30
#define COLLISION_DIS 9.0
#define DEFAULT_DANGER_DIS 60
#define EVENT_DATA_LEN_MAX 1000
#define DEFAULT_IP "127.0.0.1"
#define MAX_SERVICE_NAME_LENGTH 32
#define MAX_IP_LENGTH 32
#define LENGTH_64 64
#define STOP_STR "stop" // 导弹是否命中目标的标志
#define INIT_PRINT_INFO "-----未添加时间戳的信息为初始化及注册资源服务信息，其余信息为运行信息-----\n"
#define BUF_SIZE 512

 
//1武器资源 2传感资源 3计算资源 4存储资源 5通信资源 资源未分类";
//11.导弹引导服务 12.导弹打击服务 13.飞控服务
//21.探测服务 
//31.编队服务 32.态势分析服务 33.态势决策服务 
//41.存储服务 42.读取服务
//51.通信服务 
    typedef struct {
        double x;
        double y;
    }pos;
    typedef struct
    {
        void* return_val;
        int    return_size;
    } return_type;
    typedef struct arg
    {
        void* arg_val;
        int  arg_size;
        struct arg* next;
    } arg_type;
    typedef return_type(*fp_type)(const int, arg_type*);
    typedef struct
    {
        char ip[LENGTH];
        int port;
        int S_number;
        int C_number;
        SOCKET this_client;
    }service_addr;
    struct equipment
    {
        int E_state;//状态：1不存在、2正常、3暂停、4待删除
        int E_number;//	代表服务的全局编号
        int E_type; //	资源类型
        char E_name[LENGTH];//	
    };
    struct resource
    {
        int R_type; //资源类型（1.武器资源 2.传感资源 3.计算资源 4.存储资源 5.通信资源）
        int E_number;//代表服务的全局编号
        int R_number;//代表服务的全局编号
        char E_name[LENGTH];//
        char R_name[LENGTH];//	
        char R_IR[LENGTH];//
        service_addr R_location; //IP+PORT
        char R_description[LENGTH];//资源介绍
        char R_model[LENGTH];//资源型号
        int R_state;//
        int R_ConfigState;//配置状态（1.未配置 2.配置完成3.配置异常）
        int R_OperateState;//操作状态（1.备用状态 2运行中 3.检修中）
        int R_Communication;//资源通信协议（1.DDS 2.RPC）
        int para_A;
        double para_B;
        double para_C;
        double para_D;
        double para_E;
        double para_F;
    };
    struct service
    {
        int E_number;//	资源编号
       // char E_name[LENGTH_64];//
        int R_number;//
      //  char R_name[LENGTH_64];//	
        int S_state;//状态：1不存在、2正常、3暂停、4待删除

        int S_number;//	SNO代表服务的全局编号
        int S_type; //	STY代表服务类型。
        //
        //char S_source[MAX_SERVICE_NAME_LENGTH];//SC代表服务来源，包含了提供服务资源的名称和编号两部分内容。

        char S_name[LENGTH];//	SN表示服务名称。
       // int S_extern; //		SE是服务标识的可扩展区域，用于动态扩展服务标识的长度
        int para_A; int para_B; //2、SQ，服务质量(响应时间,利用率，并发时间)(机密性，完整性，可用性)(可靠性，可维护性)
        service_addr S_location; //ST 展示了服务的注册位置。
        char S_introduce[LENGTH];//服务介绍
        //SIO
        int n_params;//输入参数个数
        fp_type fp;//SI代表服务接口
        //SF代表服务功能
        char R_name[LENGTH];//
        char E_name[LENGTH];//

        //
        const char* proc_name;
    };


    struct UDP_message //(59)
    {
        int message_number;//报文编号（4） 无法解析的外部符号

        char message_type;//报文类型（1）
        char sharding_all;//总分片（1）
        char sharding_this;//分片号（1）
        char message_data[DATA_LENGTH];//报文内容（50）
    };
    struct equipment_registe
    {
        char E_state;//（1） 
        char E_type;//（1）
        char E_name[STRING_LENGTH];//（30）      
    };
    struct resource_registe
    {
        int  E_number;//（4）
        int R_ip;//（4）
        short  R_port;//（2）
        char R_state;//（1） 
        char R_type;//（1）
        char R_name[STRING_LENGTH];//（30）      
    };
    struct server_registe
    {
        int  R_number;//（4）
        unsigned int S_ip;//（4）
        unsigned short  S_port;//（2）
        char S_state;//（1） 
        char S_type;//（1）
        char S_name[STRING_LENGTH];//（30）      
    };
    struct return_message
    {
        int number;//（4） 
        char  state;//（1）
    };
    struct addr_ask
    {
        char S_name[STRING_LENGTH];//（30）
    };
    struct addr_return
    {
        int  S_number;//（4）
        int  C_number;//（4）
        unsigned int ip;
        unsigned short port;
    };
    struct call_message
    {
        unsigned char black[DATA_LENGTH];//（50）  
    };
    struct call_return
    {
        unsigned char black[DATA_LENGTH];//（50）  
    };
    struct server_information
    {
        int  S_number;//（4）
        int para_A;
        int para_B;
        char S_introduce[STRING_LENGTH];
    };
    struct heart_information
    {
        int  S_number;//（4）
        int  C_number;//（4）
    };

   
    unsigned int ipTint(char* ipstr);
    char* ipTstr(unsigned int ipint, char* ip);
    //传输代码
    SOCKET socket_create();
    int socket_bind(SOCKET socket, int port);
    int socket_send(SOCKET socket, char* ip, int nPort, char* pData);
    int socket_recv(SOCKET socket, char* buff, sockaddr_in& client);
    int socket_over(SOCKET sClient);
    int UDP_serialize(SOCKET socket, char message_type, char sharding_all, char sharding_this, int message_number, char* message_data, service_addr& pService);
    int register_deserialize(SOCKET socket, char message_type, char sharding_all, char sharding_this);
    int addr_deserialize(SOCKET socket, service_addr& service_array);
    int call_deserialize(SOCKET socket, unsigned char* return_val, sockaddr_in& client);
    int return_deserialize(SOCKET socket, unsigned char* return_val);
    unsigned char* int_serialize(unsigned char* buffer, int value);

    //UDP通信测试
    int test_client();
    int test_server2();
   

    //添加函数
    int get_name(const char* name, const char* property, char* output_ip);
    int registe_equipment(char E_state, char E_type, const char* E_name);
    int registe_resource(int E_number, int R_state, int R_type, const char* R_name,
        const char* R_description, const char* R_model, int R_ConfigState, int R_OperateState, int R_Communication,
        int para_A, double para_B, double para_C, double para_D, double para_E, double para_F);
    int registe_service(int R_number, int S_state, int S_type,
        int para_A, int para_B, const char* S_name, const char* S_introduce, int n_params, fp_type fp);
    int get_service(const char* service_name, service_addr& service_array);
    return_type make_remote_call(int S_number, service_addr& pService, const int nparams, ...);
    return_type multiply_call(unsigned char* multiply, int S_number, service_addr& pService, const int nparams, ...);
    int set_resigter_center_addr(const char* ip, const int port);
    void connect_center(const char* ip, const int port);
    void launch_server();


#if defined(__cplusplus)
}
#endif
