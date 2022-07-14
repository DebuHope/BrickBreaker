//======================================================================================
// ステージ管理
// 制作：向出創
//======================================================================================
#include "Stage.h"
#include "DEnemy.h"
#include "Item.h"
#include "Player.h"
#include "Object.h"
#include "Endroll.h"

#define	CENTER	(0.0f)
#define	LEFT	(-50.0f)
#define	RIGHT	(50.0f)
#define	MAXLEFT		(-80.0f)
#define	MAXRIGHT	(80.0f)
#define ENEMYRANGE	(600.0f)

void SetStage()
{
	switch (GetSceneNo())
	{
	case SCENE_STAGE1_1:

		//SetSign(XMFLOAT3(-140.0f, 0.0f, 1000.0f), XMFLOAT3(0.0f, -35.0f, 0.0f));
		//SetItem(XMFLOAT3(CENTER, 0.0f, 1500.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 1700.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 1900.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 2100.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 2300.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 2500.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 2700.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 2900.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 3100.0f), 0);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 3300.0f), 0);

		//SetItem(XMFLOAT3(LEFT, 0.0f, 4000.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 4200.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 4400.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 4600.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 4800.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 5000.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 5200.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 5400.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 5600.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 5800.0f), 0);

		//SetItem(XMFLOAT3(RIGHT, 0.0f, 6500.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 6700.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 6900.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 7100.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 7300.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 7500.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 7700.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 7900.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 8100.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 8300.0f), 0);

		//SetDEnemy(XMFLOAT3(25.0f, 0.0f, 11000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(75.0f, 0.0f, 11000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-25.0f, 0.0f, 12000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-75.0f, 0.0f, 12000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-75.0f, 0.0f, 13000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(25.0f, 0.0f, 13000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(75.0f, 0.0f, 14000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-25.0f, 0.0f, 14000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);

		//SetItem(XMFLOAT3(RIGHT, 0.0f, 9400.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 9500.0f), 0);
		//SetItem(XMFLOAT3(RIGHT, 0.0f, 9600.0f), 0);	// 33
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1);
		//SetItem(XMFLOAT3(RIGHT, 50.0f, 9850.0f), 1); // 43

		//SetItem(XMFLOAT3(LEFT, 0.0f, 10650.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10700.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10750.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10800.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10850.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10900.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 10950.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 11000.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 11050.0f), 0);
		//SetItem(XMFLOAT3(LEFT, 0.0f, 11100.0f), 0);	// 53

		//SetItem(XMFLOAT3(-20.0f, 0.0f, 11550.0f), 0);
		//SetItem(XMFLOAT3(-20.0f, 0.0f, 11650.0f), 0);
		//SetItem(XMFLOAT3(-20.0f, 0.0f, 11750.0f), 0);
		//SetItem(XMFLOAT3(-20.0f, 0.0f, 11850.0f), 0);
		//SetItem(XMFLOAT3(-20.0f, 0.0f, 11950.0f), 0);

		//SetItem(XMFLOAT3(20.0f, 0.0f, 12600.0f), 0);
		//SetItem(XMFLOAT3(20.0f, 0.0f, 12700.0f), 0);
		//SetItem(XMFLOAT3(20.0f, 0.0f, 12800.0f), 0);
		//SetItem(XMFLOAT3(20.0f, 0.0f, 12900.0f), 0);
		//SetItem(XMFLOAT3(20.0f, 0.0f, 13000.0f), 0);	// 63

		//SetItem(XMFLOAT3(CENTER, 0.0f, 14800.0f), 1);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 14800.0f), 1);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 14800.0f), 1);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 14800.0f), 1);
		//SetItem(XMFLOAT3(CENTER, 0.0f, 14800.0f), 1);	// 68

		//SetUEnemy(XMFLOAT3(80.0f, 0.0f, 15500.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(-80, 0.0f, 15500.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(20.0f, 0.0f, 16000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(-20, 0.0f, 16000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);

		//SetDEnemy(XMFLOAT3(75.0f, 0.0f, 17000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-25.0f, 0.0f, 17000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-75.0f, 0.0f, 17000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(25.0f, 0.0f, 17000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);

		//SetUEnemy(XMFLOAT3(75.0f, 0.0f, 18000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(-25.0f, 0.0f, 18000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(-75.0f, 0.0f, 18000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(25.0f, 0.0f, 18000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);

		//SetItem(XMFLOAT3(-70, 0.0f, 19000.0f), 0);
		//SetItem(XMFLOAT3(70, 0.0f, 20000.0f), 0); // 70

		//SetAllEnemyType(XMFLOAT2(0, 27), XMFLOAT4(8, 4, 4, 4), 24000.0f);
		//SetItem(XMFLOAT3(0, 0.0f, 23400.0f), 0);
		//SetItem(XMFLOAT3(40, 0.0f, 24000.0f), 0);
		//SetItem(XMFLOAT3(80, 50.0f, 24500.0f), 0);
		//SetAllEnemyType(XMFLOAT2(1, 27), XMFLOAT4(3, 3, 3, 3), 27000.0f);
		//SetItem(XMFLOAT3(-80, 0.0f, 25750.0f), 0);
		//SetItem(XMFLOAT3(-40, 50.0f, 26350.0f), 0);
		//SetItem(XMFLOAT3(0, 0.0f, 27000.0f), 0);
		//SetItem(XMFLOAT3(40, 50.0f, 27500.0f), 0);	// 77
		//SetHole(XMFLOAT3(-70.0f, 0.1f, 23000.0f), XMFLOAT3(1.0f, 1.0f, 1.0f));
		//SetHole(XMFLOAT3(-30.0f, 0.1f, 25000.0f), XMFLOAT3(1.5f, 1.5f, 1.5f));

		//SetDEnemy(XMFLOAT3(-100.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-200.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-300.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-400.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-500.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-600.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-700.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-800.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-900.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-1000.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-1100.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-1200.0f, 0.0f, 30000.0f), XMFLOAT3(1.5f, 0.0f, 0.0f), 0);

		//SetCar(XMFLOAT3(-50.0f, 0.0f, 32000.0f), XMFLOAT3(0.0f, 0.0f, -12.0f), 0);
		//SetCar(XMFLOAT3(-50.0f, 0.0f, 32300.0f), XMFLOAT3(0.0f, 0.0f, -12.0f), 1);
		//SetItem(XMFLOAT3(90, 0.0f, 30200.0f), 0);
		//SetItem(XMFLOAT3(40, 0.0f, 30500.0f), 0);
		//SetHole(XMFLOAT3(-50.0f, 0.1f, 31200.0f), XMFLOAT3(1.5f, 1.5f, 1.5f));
		//SetUEnemy(XMFLOAT3(70.0f, 0.0f, 32500.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(50.0f, 0.0f, 32700.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetItem(XMFLOAT3(-50, 50.0f, 31200.0f), 1);
		//SetItem(XMFLOAT3(-50, 50.0f, 31200.0f), 1);
		//SetItem(XMFLOAT3(-50, 50.0f, 31200.0f), 1);
		//SetItem(XMFLOAT3(-50, 50.0f, 31200.0f), 1);
		//SetItem(XMFLOAT3(-50, 50.0f, 31200.0f), 1);	// 84

		//SetCar(XMFLOAT3(-50.0f, 0.0f, 34000.0f), XMFLOAT3(0.0f, 0.0f, -12.0f), 1);
		//SetCar(XMFLOAT3(-50.0f, 0.0f, 34300.0f), XMFLOAT3(0.0f, 0.0f, -12.0f), 0);

		//SetDEnemy(XMFLOAT3(90, 0.0f, 34000.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(90, 0.0f, 34050.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(90, 0.0f, 34100.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetItem(XMFLOAT3(90, 0.0f, 32600.0f), 0);
		//SetItem(XMFLOAT3(90, 0.0f, 32650.0f), 0);
		//SetItem(XMFLOAT3(90, 0.0f, 32700.0f), 0);

		//SetDEnemy(XMFLOAT3(0, 0.0f, 34500.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(0, 0.0f, 34550.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(0, 0.0f, 34600.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetItem(XMFLOAT3(0, 0.0f, 33100.0f), 0);
		//SetItem(XMFLOAT3(0, 0.0f, 33150.0f), 0);
		//SetItem(XMFLOAT3(0, 0.0f, 33200.0f), 0);	// 90

		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35000.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35025.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35050.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35075.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35100.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35125.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35150.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetDEnemy(XMFLOAT3(-90, 0.0f, 35175.0f), XMFLOAT3(0.0f, 0.0f, -7.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33500.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33550.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33600.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33650.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33700.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33750.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33800.0f), 0);
		//SetItem(XMFLOAT3(-90, 0.0f, 33850.0f), 0);	// 98

		//SetUEnemy(XMFLOAT3(30.0f, 0.0f, 36500.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(80.0f, 0.0f, 36500.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-30.0f, 0.0f, 36800.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-80.0f, 0.0f, 36800.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(0.0f, 0.0f, 37100.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(-90.0f, 0.0f, 37100.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(50.0f, 0.0f, 37400.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-20.0f, 0.0f, 37400.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(50.0f, 0.0f, 37700.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetUEnemy(XMFLOAT3(0.0f, 0.0f, 37700.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(0.0f, 0.0f, 38000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);
		//SetDEnemy(XMFLOAT3(-50.0f, 0.0f, 38000.0f), XMFLOAT3(0.0f, 0.0f, -5.0f), 0);

		//SetUEnemy(XMFLOAT3(100.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(200.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(300.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(400.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(500.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(600.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(700.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(800.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(900.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(1000.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(1100.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(1200.0f, 0.0f, 38500.0f), XMFLOAT3(-2.5f, 0.0f, 0.0f), 0);

		//SetUEnemy(XMFLOAT3(-100.0f, 0.0f, 39500.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-200.0f, 0.0f, 39550.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(-300.0f, 0.0f, 39600.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-400.0f, 0.0f, 39650.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(-500.0f, 0.0f, 39700.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-600.0f, 0.0f, 39750.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(-700.0f, 0.0f, 39800.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-800.0f, 0.0f, 39850.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(-900.0f, 0.0f, 39900.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-1000.0f, 0.0f, 39950.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetUEnemy(XMFLOAT3(-1100.0f, 0.0f, 40000.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);
		//SetDEnemy(XMFLOAT3(-1200.0f, 0.0f, 40050.0f), XMFLOAT3(2.5f, 0.0f, 0.0f), 0);

		//SetItem(XMFLOAT3(0.0f, 0.0f, 41000.0f), 0);
		//SetItem(XMFLOAT3(0.0f, 0.0f, 41200.0f), 0);

		break;
	}
}