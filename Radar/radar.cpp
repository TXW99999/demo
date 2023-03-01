#include "../include/UDP_common.h"
#pragma comment(lib, "../lib/ArincServiceStubLib.lib")
#pragma comment(lib, "../lib/socket.lib")
#include <thread>

return_type default_return;

return_type detectService(const int nparams, arg_type* args) {
	unsigned char buf[BUF_SIZE];
	service_addr addr;
	int num = get_service("Enemyλ��", addr);
	// Ϊʲô������Ҫʹ��multiply_call����Ϊ������Ҫʹ�÷���ֵ��Ϣ��Ϊ�˷�ֹ���߳�����ġ������ݡ����⣬��������һ��
	// buf���ڽ��ܷ���ֵ���Ӷ������С������ݡ�����
	return_type ans = multiply_call(buf, num, addr, 0);
	pos* p = (pos*)ans.return_val;
	if (p != NULL) {
		printf("̽�⵽Enemy:(%.2f, %.2f)\n", p->x, p->y);
		printf("Plane��Enemy��ǰλ�÷��䵼��\n");
		int num = get_service("Plane���䵼��", addr);
		double speed = 10;
		// Ϊʲô���ﲻ����multiply_call����Ϊ���ﲻ��Ҫ����ֵ����Ϣ������Ҫ���Ƕ��߳̾�������ֵbuf
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
	registe_service(R_number, 2, 21, 0, 0, "Radar̽��Enemyλ��", "Radar̽��Enemyλ����Ϣ", 0, detectService);

	while (true) {
		launch_server();
	}
	return 0;
}