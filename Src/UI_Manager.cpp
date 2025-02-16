#include "UI_Manager.h"

UI_Manager::UI_Manager() {

	// Inicializa las fuentes
	font_a.loadFromFile("Font/FSUPERBOLD.otf");

	// Inicializa los textos
	for (int i = 0; i < 50; i++) {
		text_i[i].setFont(font_a);
		text_i[i].setPosition(50, 200);
		text_i[i].setCharacterSize(100);
		text_i[i].setScale(.3f, .3f);
	}
	for (int i = 0; i < 5; i++) {
		text_m[i].setFont(font_a);
		text_m[i].setPosition(50, 200);
		text_m[i].setCharacterSize(100);
		text_m[i].setScale(.3f, .3f);
	}
	
	text_v.setFont(font_a);
	text_v.setPosition(50, 50);
	text_v.setCharacterSize(100);
	text_v.setScale(.3, .3);

	// Inicializa las texturas y sprites

	//Menu de Inicio
	txt_sMenu_Background.loadFromFile("Sprites/sMenu_Background.png");
	spr_sMenu_Background.setTexture(txt_sMenu_Background);
	spr_sMenu_Background.setOrigin(txt_sMenu_Background.getSize().x / 2, txt_sMenu_Background.getSize().y / 2);
	spr_sMenu_Background.setPosition(Vector2f(50, 50));

	// Menu de Pausa
	txt_Menu_Background.loadFromFile("Sprites/Menu_Background.png");
	spr_Menu_Background.setTexture(txt_Menu_Background);
	spr_Menu_Background.setOrigin(txt_Menu_Background.getSize().x / 2, txt_Menu_Background.getSize().y / 2);
	//spr_MenuBackground.setScale(.1, .1);
	spr_Menu_Background.setPosition(Vector2f(50, 50));

	// Menu de Info
	txt_iMenu_Background.loadFromFile("Sprites/iMenu_Background.png");
	spr_iMenu_Background.setTexture(txt_iMenu_Background);
	spr_iMenu_Background.setOrigin(txt_iMenu_Background.getSize().x / 2, txt_iMenu_Background.getSize().y / 2);
	spr_iMenu_Background.setPosition(Vector2f(50, 50));

	// Victoria
	txt_vScreen.loadFromFile("Sprites/vScreen.png");
	spr_vScreen.setTexture(txt_vScreen);
	spr_vScreen.setOrigin(txt_vScreen.getSize().x / 2, txt_vScreen.getSize().y / 2);
	spr_vScreen.setPosition(Vector2f(50, 50));

	//-
	rag_Shot = 0;
	gameState = 2; // 0 = Pausado | 1 = Ejecucion | 2 = Menu de Inicio | 3 = Menu de Info | 4 = Victoria

}

void UI_Manager::LoadLevel(int lvl) {

	text_i[0].setString("Ragdolls Disparados: " + std::to_string(rag_Shot));
	text_i[0].setPosition(1, 5);
	text_i[0].setScale(0.015f, 0.015f);

	text_i[1].setString("Nivel: " + std::to_string(lvl));
	text_i[1].setPosition(92, 5);
	text_i[1].setScale(0.015f, 0.015f);

	// Menu de informacion
	text_m[0].setString("MyA II");
	text_m[0].setPosition(40, 25);
	text_m[0].setScale(0.05f, 0.05f);

	text_m[1].setString("TP Final");
	text_m[1].setPosition(42.5f, 32);
	text_m[1].setScale(0.025f, 0.025f);

	text_m[2].setString("Alejandro Delati Mik");
	text_m[2].setPosition(36.5f, 38.5f);
	text_m[2].setScale(.02f, .02f);

	text_m[3].setString("v0.0.7");
	text_m[3].setPosition(44, 60);
	text_m[3].setScale(.03f, .03f);

	// Victoria
	text_v.setString("Victoria!");
	text_v.setPosition(32, 38);
	text_v.setScale(.075f, .075f);

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
		text_i[i].setColor(Color::White);
	}
}

void UI_Manager::UpdateGameState(int state) {
	gameState = state;
}

void UI_Manager::Draw_Text(RenderWindow &wnd, int lvl, int rag_shot) {
	rag_Shot = rag_shot;
	ChangeLevel(lvl);
	for (int i = 0; i < 50; i++) {
		wnd.draw(text_i[i]);
	}
}

void UI_Manager::Draw_MenuText(RenderWindow &wnd) {
	if (gameState == 3) {
		for (int i = 0; i < 5; i++) {
			wnd.draw(text_m[i]);
		}
	}
	if (gameState == 4) {
		wnd.draw(text_v);
	}
}

void UI_Manager::Draw_Menu(RenderWindow &wnd) {
	if (gameState == 2) {
		wnd.draw(spr_sMenu_Background);
	}
	else if (gameState == 0) {
		wnd.draw(spr_Menu_Background);
	}
	else if (gameState == 3) {
		wnd.draw(spr_iMenu_Background);
	}
	else if (gameState == 4) {
		wnd.draw(spr_vScreen);
	}
}

//					-| Configuracion de textos para los diferentes niveles

void UI_Manager::lvl_0() {
	/*
	text_i[2].setString("MyAII TP Final");
	text_i[2].setPosition(25, 5);
	text_i[2].setScale(0.06f, 0.06f);

	text_i[3].setString("Alejandro Delati Mik");
	text_i[3].setPosition(32, 13);
	*/
	if (gameState != 2) {

		if (rag_Shot < 6) {
			text_i[4].setString("Usa el mouse para apuntar el canon y");
			text_i[4].setPosition(1, 70);
			text_i[4].setScale(0.015f, 0.015f);

			text_i[5].setString("click izquierdo para disparar un ragdoll");
			text_i[5].setPosition(1, 72);
			text_i[5].setScale(0.015f, 0.015f);

			text_i[6].setString("la potencia del disparo depende de la distancia");
			text_i[6].setPosition(1, 74);
			text_i[6].setScale(0.015f, 0.015f);

			text_i[7].setString("entre el canon y la posicion del mouse.");
			text_i[7].setPosition(1, 76);
			text_i[7].setScale(0.015f, 0.015f);
		}

		if (rag_Shot > 1 && rag_Shot < 6) {
			text_i[8].setString("Presiona Z para hacer zoom en el ultimo ragdoll disparado.");
			text_i[8].setPosition(1, 62);
			text_i[8].setScale(0.015f, 0.015f);
		}

		if (rag_Shot > 3 && rag_Shot < 6) {
			text_i[9].setString("Presiona R para reiniciar el nivel actual.");
			text_i[9].setPosition(1, 54);
			text_i[9].setScale(0.015f, 0.015f);
		}

		if (rag_Shot > 5) {
			text_i[4].setString("Tu objetivo es hacer llegar solo un ragdoll");
			text_i[4].setPosition(1, 40);
			text_i[4].setScale(0.015f, 0.015f);
			text_i[4].setColor(Color::Green);

			text_i[5].setString("a la zona delimitada por un rectangulo verde para");
			text_i[5].setPosition(1, 42);
			text_i[5].setScale(0.015f, 0.015f);
			text_i[5].setColor(Color::Green);

			text_i[6].setString("poder pasar al siguiente nivel.");
			text_i[6].setPosition(1, 44);
			text_i[6].setScale(0.015f, 0.015f);
			text_i[6].setColor(Color::Green);

			text_i[7].setString("Salida");
			text_i[7].setPosition(81.75, 35);
			text_i[7].setScale(0.03f, 0.03f);
			text_i[7].setColor(Color::Green);
		}

	}

}

void UI_Manager::lvl_1() {



}

void UI_Manager::lvl_2() {

	

}

void UI_Manager::lvl_3() {

	

}