#include "shoot.h"
#include "motor.h"
#include "dshot.h"
#include "drv_tim.h"
#include "dbus.h"
struct M2006 toggleBullet_up;
struct M2006 toggleBullet_down;

void shoot_init(void)
{
	setDshotValue(0);
}
short shoot_delay = 0;
short shoot_speed = 800;
void shoot_task(unsigned char model)
{
	if(getRCData().rc.s1 == 1)
	{
		setDshotValue(shoot_speed);
	}
}