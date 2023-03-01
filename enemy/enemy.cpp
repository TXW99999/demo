#include "../include/UDP_common.h"
#pragma comment(lib, "../lib/ArincServiceStubLib.lib")
#pragma comment(lib, "../lib/socket.lib")

typedef struct {
	double x;
	double y;
}Enemy;

Enemy enemy;

pos p;

void initEnemy(Enemy* u, double x, double y) {
	u->x = x;
	u->y = y;
}

return_type getPosService(const int nparams, arg_type* args) {
	p.x = enemy.x;
	p.y = enemy.y;
	return_type res{ &p, sizeof(p) };
	return res;
}

int main() {
	set_resigter_center_addr(DEFAULT_IP, 9000);
	connect_center(DEFAULT_IP, 1301);
	int E_number = 0, R_number = 0;
	E_number = registe_equipment(2, 0, "Enemy");
	R_number = registe_resource(E_number, 2, 2, "R_Enemy", "dsagfesrgg", "dsagfesrgg", 1, 1, 1, 1, 1, 1, 1, 1, 1);
	registe_service(R_number, 2, 21, 0, 0, "Enemy位置", "Enemy位置信息", 0, getPosService);
	initEnemy(&enemy, 50, 0);

	while (true) {
		launch_server();
	}
	return 0;
}