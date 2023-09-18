#include "TextInput.h"
#include <iostream>

TextInput::TextInput(int sizeX, int sizeY, string input): View(sizeX, sizeY) {
	this->input = input;
	selectable = true;
}

string TextInput::getInput() { return input; }

void TextInput::onInputKey(char key) {
	if(input.size() < sizeX-2)
		input += string(1, key);
	onChangeListener(this);
}

char** TextInput::render() {
	renderFrame();
	
	int mid_y = (sizeY - 1 ) / 2;
	
	if(isSelected()) {
		for(int i=1; i<sizeX-1; i++) {
			canvas[0][i] = '=';
			canvas[sizeY-1][i] = '=';
		}

		canvas[mid_y][0] = '[';
		canvas[mid_y][sizeX-1] = ']';
	}

	
	for (int idx=0, pos=1; idx<input.size(); idx++, pos++) {
		canvas[mid_y][pos] = input[idx];
		
		/*
		if (idx == input.size()-1) {
			pos++;
			for(; pos<sizeX-1; pos++){
				canvas[mid_y][pos] = ' ';
			}
		}*/ //seems useless XP
	}

	return canvas;	
}	
