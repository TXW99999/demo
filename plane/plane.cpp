#include "../include/UDP_common.h"
#pragma comment(lib, "../lib/ArincServiceStubLib.lib")
#pragma comment(lib, "../lib/socket.lib")
#include <math.h>
#include <thread>

typedef struct {
	double x;
	double y;
}Missile;

Missile missile;

return_type default_return;

void initMissile(Missile* m, double x, double y) {
	m->x = x;
	m->y = y;
}

void launchMissile(Missile* m, double x, double y, double speed) {
	if (x == m->x && y == m->y) {
		printf("当前位置已是目标位置，无需继续飞行\n");
		return;
	}
	double speedX = (x - m->x) / sqrt((x - m->x) * (x - m->x) + (y - m->y) * (y - m->y)) * speed;
	double speedY = (y - m->y) / sqrt((x - m->x) * (x - m->x) + (y - m->y) * (y - m->y)) * speed;
	
	while (m->x != x || m->y != y) {
		printf("导弹当前位置:(%.2f, %.2f)\n", m->x, m->y);
		double dis = sqrt((m->x - x) * (m->x - x) + (m->y - y) * (m->y - y));
		if (dis <= COLLISION_DIS) {
			break;
		}
		m->x += speedX;
		m->y += speedY;
		Sleep(1000);
	}
	m->x = x;
	m->y = y;
	printf("导弹已经飞行到目标位置:(%.2f, %.2f)\n", x, y);
}

return_type launchMissileService(const int nparams, arg_type* args) {
	printf("launchMissileService\n");
	double x = *(double*)args->arg_val;
	double y = *(double*)args->next->arg_val;
	double speed = *(double*)args->next->next->arg_val;
	
	std::thread t(launchMissile, &missile, x, y, speed);
	t.detach();
	return default_return;
}

int main() {
	set_resigter_center_addr(DEFAULT_IP, 9000);
	connect_center(DEFAULT_IP, 1101);
	int E_number = 0, R_number = 0;
	E_number = registe_equipment(2, 0, "Plane");
	R_number = registe_resource(E_number, 2, 2, "R_Plane", "dsagfesrgg", "dsagfesrgg", 1, 1, 1, 1, 1, 1, 1, 1, 1);
	registe_service(R_number, 2, 21, 0, 0, "Plane发射导弹", "Plane发射导弹", 3, launchMissileService);
	initMissile(&missile, 0, 0);

	while (true) {
		launch_server();
	}
	return 0;
}