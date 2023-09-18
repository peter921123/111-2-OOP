#include "Button.h"
#include <iostream>

Button::Button(int sizeX, int sizeY, string text): View(sizeX, sizeY){
	this->text = text;
	selectable = true;
}

string Button::getText() { return text; }

void Button::onClick() {
	onClickListener(this);
}

char** Button::render() {
	renderFrame();

	int mid_y = (sizeY - 1 ) / 2;
	//int mid_x = (sizeX - 1 ) / 2;

	if (isSelected()){
		fillCanvas('#');
	}
	int num_of_space = (sizeX - text.size() - 2) / 2;
	

	for (int idx=0, pos=num_of_space+1; idx<text.size(); idx++, pos++) {
		canvas[mid_y][pos] = text[idx];
	}
/*
	for (int i=0; i<sizeY; i++) {
		for (int j=0; j<sizeX; j++) {
			cout << canvas[i][j];
		}
		cout << endl;
	}
*/
	return canvas;
}
