#pragma once

#ifdef SERVICEMANAGELIB_EXPORTS
#define SERVICE_API __declspec(dllexport)//宏定义导出的一个规约
#else
#define SERVICE_API  __declspec(dllimport)
#endif

#define PARAM_NAME_LENGTH 32
#define SERVICE_NAME_LENGTH 64
#define IR_LENGTH 32
#define MAX_CLENTS 128
#define TIMESTAMR_LENGTH 64
#define  MAX_IR_LENGTH 32
#define  LENGTH_32 64
#define  LENGTH_64 64
#define  MAX_NAME_LENGTH 64
#define  LENGTH 64
#define  UDP_LENGTH 59
#define  DATA_LENGTH 50
#define  STRING_LENGTH 30

//服务状态：1不存在、2正常、3暂停、4待删除
#define SERVICE_NOT_EXIST 1
#define SERVICE_QUERY_SUCCESS 2
#define SERVICE_PAUSE         3
#define SERVICE_DELETE       4



typedef struct {
	char ip[32];
	int port;
}_service_addr;

typedef struct
{
	char ip[32];
	int port;
	int S_number;//1	SNO代表服务的全局编号
	int type;//type 0删除 1, 唤醒、运行 2.挂起、暂停
	int times;//调用次数
	int CN;
} EndPointInfo;//


typedef struct
{
	char name[SERVICE_NAME_LENGTH];
	char ip[IR_LENGTH];
	int port;
	int type;//type 0删除 1, 唤醒、运行 2.挂起、暂停
	int times;//调用次数
}ServiceInfo;//last

typedef struct
{
	char name[SERVICE_NAME_LENGTH];
	char ip[IR_LENGTH];
	int port;
	int kind;//资源类型
	int type;//type 0删除 1, 唤醒、运行 2.挂起、暂停
	char lastTime[TIMESTAMR_LENGTH];//上次交互时间
	char  service_addr[128];//调用信息（ip+port+name）
}ClientInfo;//last


struct Equipment
{
	int E_number;
	char E_state;//2
	char E_type;//（1）
	char E_name[SERVICE_NAME_LENGTH];//	
	char E_IP[SERVICE_NAME_LENGTH];//	
	int TokenOfRes;//资源编号辅助
};
struct Resource
{
	int E_number;
	char E_name[LENGTH_64];//
	int R_state;//1正常运行 2挂起
	int R_number;//	代表服务的全局编号
	int R_type; //	资源类型
	 //1武器资源 2传感资源 3计算资源 4存储资源 5通信资源
	char R_IP[LENGTH_32];//
	char R_name[LENGTH_32];//
	int TokenOfSer;//服务编号辅助	
};
struct Service
{
	//服务标识（SID）可定义为如下形式的五元组：SID=(SNO,STY,SC,SH,SE)
	int S_number;//	1、SNO，服务的全局编号
	int S_type; //	2、STY，代表服务类型
	//11.导弹引导服务 12.导弹打击服务 13.飞控服务
	//21.探测服务 
	//31.编队服务 32.态势分析服务 33.态势决策服务 
	//41.存储服务 42.读取服务
	//51.通信服务 


	//3、SC,代表服务来源，包含了提供服务设备和资源的名称和编号
	int E_number;
	char E_name[MAX_NAME_LENGTH];
	int R_number;
	char R_name[MAX_NAME_LENGTH];
	char S_name[MAX_NAME_LENGTH];//	4、SN 表示服务名称
   // char S_extern[LENGTH_32];//5、SE 是服务标识的可扩展区域，用于动态扩展服务标识的长度

   //服务行为描述（SBD）可定义为形如SBD=(ST,SQ,SI/O,SI, SF)的五元组
	_service_addr S_location; //1、 ST，展示了服务的注册位置。
	int para_A; int para_B; //2、SQ，服务质量(响应时间,利用率，并发时间)(机密性，完整性，可用性)(可靠性，可维护性)
	//3、SIO  
	int n_params;//参数个数
	//fp_type S_interface;//4、SI，代表服务接口(存放于服务端)
	char S_introduce[LENGTH_32];//5、SF，代表服务功能

	//运行时数据
	int S_state;//服务状态：1不存在、2正常、3暂停、4待删除 
	int S_times;//调用次数
	char lastTime[TIMESTAMR_LENGTH];//上次心跳时间
};
struct Client
{
	int S_number;
	int C_number;
	char name[SERVICE_NAME_LENGTH];
	_service_addr service_addr;//ip+port
	_service_addr client_addr;//ip+port
	char lastTime[TIMESTAMR_LENGTH];//上次交互时间
	int state;//type 0删除 1, 唤醒、运行 2.挂起、暂停
};









typedef struct
{
	char name[SERVICE_NAME_LENGTH];
	char ip[IR_LENGTH];
	int port;
	int kind;
	int type;//type 0删除 1, 唤醒、运行 2.挂起、暂停
	char lastTime[TIMESTAMR_LENGTH];//上次交互时间
}EndPointInfo2;

typedef struct
{
	EndPointInfo client_addr;//ip+port
	char lastTime[TIMESTAMR_LENGTH];//上次交互时间
	int state;//type 0删除 1, 唤醒、运行 2.挂起、暂停
}ClientDesc;


typedef struct
{
	char name[SERVICE_NAME_LENGTH];
	EndPointInfo service_addr;
	int serviceState;//0-正常 1-暂停
	//type 0删除 1, 唤醒、运行 2.挂起、暂停
}ServiceDesc;

typedef struct
{
	ServiceDesc original;//原始数据
	int times;//调用次数
	//int number;//原始排序(不使用)
	ClientInfo* users;//调用者队列(暂不使用)
}EXserviceDesc;//传输使用



struct UDP_message //(59)
{
	int message_number;//报文编号（4）
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


#ifdef  __cplusplus
extern "C" {
#endif
	SERVICE_API int StartServer(int port);//启动服务管理中心
	SERVICE_API int PrintServiceInfo(char* buffer, int buflen);//获取服务信息(字符串)
	SERVICE_API int GetServiceClients(ServiceDesc service, ClientDesc* clients, int* clientNum);//查询指定服务的调用者信息
	//SERVICE_API int GetServicesList(ServiceDesc* serviceList,int* num);//1查询全部服务信息(结构化)
	//SERVICE_API int GetClientList(ClientInfo* clientList, int* num);//2查询全部客户端信息(结构化)

	SERVICE_API int getClientList(ClientInfo* clientList, int* num);//last查询全部客户端信息(结构化)
	SERVICE_API int getServiceList(ServiceInfo* serviceList, int* num);//last查询全部服务信息(结构化)

	SERVICE_API int Equipment_List(Equipment* equipmentList, int* num);
	SERVICE_API int Service_List(Service* serviceList, int* num);
	SERVICE_API int Resource_List(Resource* resourceList, int* num);
	SERVICE_API int Client_List(Client* clientList, int* num);
	SERVICE_API int DelService(int S_number);//删除服务
	SERVICE_API int PauseService(int S_number);//暂停服务
	SERVICE_API int ResumeService(int S_number);//继续服务
	SERVICE_API int ExchangeAll(int token);
	//
	SERVICE_API int test_client20();
#ifdef  __cplusplus
}
#endif
