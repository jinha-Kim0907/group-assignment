//초안
#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

ObjectID pickax, enhanceBtn;
SceneID enhance;
int axLevel = 1;
int money = 0, enhanceMoney = 200;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown) {
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) showObject(object);
	return object;
}

void gameInit() {
	srand(unsigned(time(NULL)));
	enhance = createScene("enhance");
	enhanceBtn = createObject("Images/enhanceBtn.jpg", enhance, 800, 400, true);
	pickax = createObject("Images/pickax1.jpg", enhance, 200, 200, true);
	scaleObject(pickax, 0.3f);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == enhanceBtn) {
		if (money >= enhanceMoney) {
			money -= enhanceMoney;
			int probNum = rand() % 10 + 1;      //확률 조정?
			if (probNum % 2 == 0) {				//강화성공의 경우
				axLevel++;
				char buf[50];
				sprintf(buf, "Images/pickax%d.jpg", axLevel);
				setObjectImage(pickax, buf);
				showMessage("Success!!");
				enhanceMoney *= 2;              //단계별 강화비용 조작
			}
			else showMessage("Fail!!");
			if (axLevel == 10) hideObject(enhanceBtn);
		}
		else showMessage("You have not enough Money!!!!");
	}
}

int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, true);
	setMouseCallback(mouseCallback);

	gameInit();

	startGame(enhance);
}