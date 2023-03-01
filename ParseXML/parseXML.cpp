#include <iostream>  
#include"tinyxml2.h"  
#include <atlstr.h>
#include <thread>
#include "../include/UDP_common.h"
#pragma comment(lib, "../lib/ArincServiceStubLib.lib")
#pragma comment(lib, "../lib/socket.lib")

using namespace tinyxml2;

char* U2G(const char* utf8) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = (char*)malloc(len + 1);
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
}

typedef struct {
    void* inputValPtr;
    int inputValueLen;
}TypeValuePair;

void dealService(XMLElement* service) {
    service_addr addr;
    const int params_arr_size = 5;
    TypeValuePair params[params_arr_size];
    while (service) {
        XMLElement* param = service->FirstChildElement();
        const char* param_value, * service_name;
        const XMLAttribute* attributeOfService = service->FirstAttribute();
        service_name = U2G(attributeOfService->Value());

        int i = 0;
        while (param) {
            param_value = param->GetText();

            const XMLAttribute* type = param->FirstAttribute();
            if (strcmp(type->Value(), "double") == 0) {
                double* d = (double*)malloc(sizeof(double));
                *d = atof(param_value);
                params[i].inputValueLen = sizeof(double);
                params[i].inputValPtr = (void*)d;
            }
            else if (strcmp(type->Value(), "int") == 0) {
                int* t = (int*)malloc(sizeof(int));
                *t = atof(param_value);
                params[i].inputValueLen = sizeof(int);
                params[i].inputValPtr = (void*)t;
            }
            else if (strcmp(type->Value(), "string") == 0) {
                param_value = U2G(param_value);
                params[i].inputValueLen = strlen(param_value) + 1;
                params[i].inputValPtr = (void*)param_value;
            }
            else if (strcmp(type->Value(), "bool") == 0) {
                bool istrue = (strcmp(param_value, "true") == 0);
                bool* b = (bool*)malloc(sizeof(istrue));
                params[i].inputValueLen = sizeof(bool);
                params[i].inputValPtr = (void*)b;
            }
            param = param->NextSiblingElement();
            i++;
        }

        int tmp = get_service(service_name, addr);
        make_remote_call(tmp, addr, i,
            params[0].inputValueLen, (void*)params[0].inputValPtr,
            params[1].inputValueLen, (void*)params[1].inputValPtr,
            params[2].inputValueLen, (void*)params[2].inputValPtr,
            params[3].inputValueLen, (void*)params[3].inputValPtr,
            params[4].inputValueLen, (void*)params[4].inputValPtr);

        service = service->NextSiblingElement();

        free((void*)service_name);
        for (int j = 0; j < i; j++) {
            free(params[j].inputValPtr);
            params[j].inputValPtr = NULL;
            params[j].inputValueLen = 0;
        }
    }
}

void dealEvent(char* tmp_buf, int buf_size, XMLElement* wait) {
    char* buf = new char[buf_size];
    memcpy(buf, tmp_buf, buf_size);
    std::string type_str(buf, 1);
    //printf("数据包是%s, type_str:%s\n", buf, x.c_str());

    XMLElement* event = wait->FirstChildElement(type_str.c_str());
    XMLElement* service = event->FirstChildElement();
    dealService(service);
}

void waitEvent(XMLElement* wait, int port) {
    const int event_pkg_size = 59;
    char buf[event_pkg_size];
    sockaddr_in clnt_addr;
    SOCKET socket = socket_create();
    socket_bind(socket, port);
    while (true) {
        int recv_bytes = socket_recv(socket, buf, clnt_addr);
        if (recv_bytes > 0) {
            printf("recv_bytes：%d\n", recv_bytes);
            std::thread t(dealEvent, buf, event_pkg_size, wait);
            t.detach();
        }
    }
    socket_over(socket);
}

void parse(tinyxml2::XMLDocument* dom) {
    set_resigter_center_addr(DEFAULT_IP, 9000);
    XMLElement* root = dom->RootElement();

    XMLElement* wait = root->FirstChildElement("wait");
    std::thread threadWaitEvent(waitEvent, wait, 6666);

    XMLElement* Services = root->FirstChildElement("Services");
    XMLElement* service = Services->FirstChildElement();
    dealService(service);
    threadWaitEvent.join();
}

int main()
{
    tinyxml2::XMLDocument dom;
    dom.LoadFile("../Release/ServiceXML.xml");
    parse(&dom);
    return 0;
}