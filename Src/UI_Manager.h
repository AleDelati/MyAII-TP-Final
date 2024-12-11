#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class UI_Manager {

public:

	UI_Manager();

	void LoadLevel(int lvl);
	void ChangeLevel(int lvl);
	void ClearLevel();

	void Draw_Text(RenderWindow &wnd, int lvl, int rag_shot);

	void lvl_0();
	void lvl_1();
	void lvl_2();
	void lvl_3();

private:

	Font font_a;
	Text text_i[50];

	int rag_Shot;
};