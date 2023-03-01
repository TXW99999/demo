#include "../include/UDP_common.h"
#pragma comment(lib, "../lib/ArincServiceStubLib.lib")
#pragma comment(lib, "../lib/socket.lib")
#include <thread>

return_type default_return;

return_type detectService(const int nparams, arg_type* args) {
	unsigned char buf[BUF_SIZE];
	service_addr addr;
	int num = get_service("Enemy位置", addr);
	// 为什么这里需要使用multiply_call，因为这里需要使用返回值信息，为了防止多线程引起的“脏数据”问题，单独开辟一个
	// buf用于接受返回值，从而不会有“脏数据”出现
	return_type ans = multiply_call(buf, num, addr, 0);
	pos* p = (pos*)ans.return_val;
	if (p != NULL) {
		printf("探测到Enemy:(%.2f, %.2f)\n", p->x, p->y);
		printf("Plane向Enemy当前位置发射导弹\n");
		int num = get_service("Plane发射导弹", addr);
		double speed = 10;
		// 为什么这里不适用multiply_call，因为这里不需要返回值的信息，不需要考虑多线程竞争返回值buf
		make_remote_call(num, addr, 3, sizeof(p->x), (void*)&(p->x), sizeof(p->y), (void*)&(p->y), sizeof(speed), (void*)&speed);
	}
	return default_return;
}

int main() {
	set_resigter_center_addr(DEFAULT_IP, 9000);
	connect_center(DEFAULT_IP, 1201);
	int E_number = 0, R_number = 0;
	E_number = registe_equipment(2, 0, "Radar");
	R_number = registe_resource(E_number, 2, 2, "R_Radar", "dsagfesrgg", "dsagfesrgg", 1, 1, 1, 1, 1, 1, 1, 1, 1);
	registe_service(R_number, 2, 21, 0, 0, "Radar探测Enemy位置", "Radar探测Enemy位置信息", 0, detectService);

	while (true) {
		launch_server();
	}
	return 0;
}