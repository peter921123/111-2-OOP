#include "View.h"
#include "Window.h"
#include "iostream"

std::vector<View*> View::views;

// Public Function
// Constructor and Destructor
View::View (int sizeX, int sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	canvas = new char* [sizeY];
	for (int i=0; i<sizeY; i++) {
		canvas[i] = new char [sizeX];
	}
	views.push_back(this);
}

View::~View () {
	
	for (int i=0; i<sizeY; i++) {
		delete [] canvas[i];
	}

	delete [] canvas;
}

// Getters
int View::getSizeX() {
	return sizeX;
}

int View::getSizeY() {
	return sizeY;
}

bool View::isSelectable() {
	return selectable;
}

// Return if window->selectedView is same as self
bool View::isSelected() {
	return window->getSelectedView() == this;
}

// Callback function ptr setters
void View::setOnClickListener(void (*listener)(View*)) {
	onClickListener = listener;
}

void View::setOnChangeListener(void (*listener)(View*)) {
	onChangeListener = listener;
}

// Delete all created View in views, call at the end of main() 
void View::deleteAllView() {
	for (int i=0; i<views.size(); i++) {
		delete views[i];
	}
}

// Protected Function

// Setter
void View::setPos(int posX, int posY) {
	this->posX = posX;
	this->posY = posY;
}

void View::setWindow(Window* window) {
	this->window = window;
}

// Getter
int View::getPosX() { return posX; }

int View::getPosY() { return posY; }

// Call window render()
void View::rerenderWindow() {
	window->render();
}

// Handler
void View::onClick() {}

void View::onChange() {}

void View::onInputKey(char key) {}

void View::renderFrame() {

	canvas[0][0] = '+';
	canvas[0][sizeX-1] = '+';
	canvas[sizeY-1][0] = '+';
	canvas[sizeY-1][sizeX-1] = '+';

	for (int i=1; i<sizeX-1; i++) {
		canvas[0][i] = '-';
		canvas[sizeY-1][i] = '-';
	}
	for (int i=1; i<sizeY-1; i++) {
		canvas[i][0] = '|';
		canvas[i][sizeX-1] = '|';
	}
	fillCanvas(' ');
	
	
}

void View::fillCanvas(char key) {
	for (int i=1; i<sizeY-1; i++) {
		for (int j=1; j<sizeX-1; j++) {
			canvas[i][j] = key;
		}
	}
}
