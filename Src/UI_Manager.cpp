#include "UI_Manager.h"

UI_Manager::UI_Manager() {

	// Inicializa las fuentes
	font_a.loadFromFile("Font/FSUPERBOLD.otf");
	font_b.loadFromFile("Font/Space.otf");

	// Inicializa los textos
	for (int i = 0; i < 50; i++) {
		text_i[i].setFont(font_a);
		text_i[i].setPosition(50, 200);
		text_i[i].setCharacterSize(100);
		text_i[i].setScale(.3f, .3f);
	}

}

void UI_Manager::LoadLevel(int lvl) {

	switch (lvl) {
	case 0:
		lvl_0();
		break;
	case 1:
		lvl_1();
		break;
	case 2:
		lvl_2();
		break;
	case 3:
		lvl_3();
		break;
	}

}

void UI_Manager::ChangeLevel(int lvl) {
	ClearLevel();
	LoadLevel(lvl);
}

void UI_Manager::ClearLevel() {
	for (int i = 0; i < 50; i++) {
		text_i[i].setString("");
		text_i[i].setPosition(50, 200);
		text_i[i].setCharacterSize(100);
		text_i[i].setScale(.03f, .03f);
	}
}

void UI_Manager::Draw_Text(RenderWindow &wnd, int lvl) {
	ChangeLevel(lvl);
	for (int i = 0; i < 50; i++) {
		wnd.draw(text_i[i]);
	}
}

//					-| Configuracion de textos para los diferentes niveles

void UI_Manager::lvl_0() {

	text_i[0].setString("MyAII TP Final");
	text_i[0].setPosition(25, 5);
	text_i[0].setScale(0.06f, 0.06f);

	text_i[1].setString("Alejandro Delati Mik");
	text_i[1].setPosition(32, 13);


}

void UI_Manager::lvl_1() {

}

void UI_Manager::lvl_2() {

}

void UI_Manager::lvl_3() {

}