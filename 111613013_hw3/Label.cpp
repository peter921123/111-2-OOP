#include "Label.h"
#include <iostream>

Label::Label(int sizeX, int sizeY, string output,
	Alignment alignment): View(sizeX, sizeY){
	this->output = output;
	this->alignment = alignment;
	selectable = false;
}

void Label::setOutput(string output) {
	this->output = output;
	//onChange();
	rerenderWindow();
}

void Label::setAlignment(Alignment alignment) {
	this->alignment = alignment;
	//onChange();
	rerenderWindow();
}

string Label::getOutput() { return output; }

char** Label::render() {
	renderFrame();

	//std::cout << output << std::endl;

	int mid_y = (sizeY - 1 ) / 2;
	
	int num_of_space = (sizeX - output.size() - 2) / 2;
	
	if(alignment == Alignment::CENTER) {
		for (int idx=0, pos=num_of_space+1; idx<output.size(); idx++, pos++) {
			canvas[mid_y][pos] = output[idx];
		}
	}else if (alignment == Alignment::LEFT) {
		for (int idx=0, pos=1; idx<output.size(); idx++, pos++) {
			canvas[mid_y][pos] = output[idx];
		}

	}else if (alignment == Alignment::RIGHT) {
		for (int idx=output.size()-1, pos=sizeX-2; idx>=0; idx--, pos--) {
			canvas[mid_y][pos] = output[idx];
		}
	}

	return canvas;		
}
