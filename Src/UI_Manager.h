#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class UI_Manager {

public:

	UI_Manager();

	void LoadLevel(int lvl);
	void ChangeLevel(int lvl);
	void ClearLevel();
	void UpdateGameState(int state);

	void Draw_Text(RenderWindow &wnd, int lvl, int rag_shot);
	void Draw_MenuText(RenderWindow &wnd);
	void Draw_Menu(RenderWindow &wnd);

	void lvl_0();
	void lvl_1();
	void lvl_2();
	void lvl_3();

private:

	Font font_a;
	Text text_i[50];
	Text text_m[5];
	Text text_v;

	// Menu de Inicio
	Texture txt_sMenu_Background;
	Sprite spr_sMenu_Background;

	// Menu de Pausa
	Texture txt_Menu_Background;
	Sprite spr_Menu_Background;

	// Menu de Info
	Texture txt_iMenu_Background;
	Sprite spr_iMenu_Background;

	// Victoria
	Texture txt_vScreen;
	Sprite spr_vScreen;

	int rag_Shot;
	int gameState;
};