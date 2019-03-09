#include "modules.h"

void modules_init(void)
{
	gimbal_init();
	shoot_init();
}
void modules_task(void)
{
	gimbal_tast(1);
	shoot_task(1);
}