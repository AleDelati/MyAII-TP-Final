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

	rag_Shot = 0;

}

void UI_Manager::LoadLevel(int lvl) {

	text_i[0].setString("Ragdolls Disparados: " + std::to_string(rag_Shot));
	text_i[0].setPosition(1, 5);
	text_i[0].setScale(0.015f, 0.015f);

	text_i[1].setString("Nivel: " + std::to_string(lvl));
	text_i[1].setPosition(92, 5);
	text_i[1].setScale(0.015f, 0.015f);

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

void UI_Manager::Draw_Text(RenderWindow &wnd, int lvl, int rag_shot) {
	rag_Shot = rag_shot;
	ChangeLevel(lvl);
	for (int i = 0; i < 50; i++) {
		wnd.draw(text_i[i]);
	}
}

//					-| Configuracion de textos para los diferentes niveles

void UI_Manager::lvl_0() {

	text_i[2].setString("MyAII TP Final");
	text_i[2].setPosition(25, 5);
	text_i[2].setScale(0.06f, 0.06f);

	text_i[3].setString("Alejandro Delati Mik");
	text_i[3].setPosition(32, 13);

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
		text_i[4].setString("Tu objetivo es hacer llegar al menos un ragdoll");
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

void UI_Manager::lvl_1() {



}

void UI_Manager::lvl_2() {

	

}

void UI_Manager::lvl_3() {

	

}