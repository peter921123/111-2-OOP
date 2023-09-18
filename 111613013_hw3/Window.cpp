#include "Window.h"

#include <termios.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "View.h"


using namespace std;


void Window::render() {
    system("clear");

    renderFrame();

    for (int i=0; i<views.size(); i++) {
	char** copy_canva = views[i]->render();
	//int pos_x = views[i]->posX + 1;
	int pos_y = views[i]->posY + 1;
	int c_sizeY = views[i]->sizeY;
	int c_sizeX = views[i]->sizeX;
	
	for (int idx_y=0; idx_y<c_sizeY; idx_y++, pos_y++) {
		for(int idx_x=0, pos_x = views[i]->posX + 1; idx_x<c_sizeX; idx_x++, pos_x++) {
			  canvas[pos_y][pos_x] = copy_canva[idx_y][idx_x];
		}
	}
	
    }

    for (int i=0; i<sizeY; i++) {
	for (int j=0; j<sizeX; j++) {
		cout << canvas[i][j];
	}
	cout << endl;
    }
    
    // TODO: Render the window
}

// You don't have to modify
void Window::run() {
    struct termios ter;
    tcgetattr(0, &ter);
    ter.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &ter);

    render();
    while (!exit) {
        char key;
        key = cin.get();
        if (key == 27) {
            key = cin.get();
            if (key == 91) {
                key = cin.get();
                ArrowKey arrowKey;
                if (key == 65) {
                    arrowKey = ArrowKey::UP;
                } else if (key == 66) {
                    arrowKey = ArrowKey::DOWN;
                } else if (key == 67) {
                    arrowKey = ArrowKey::RIGHT;
                } else if (key == 68) {
                    arrowKey = ArrowKey::LEFT;
                }
                onArrowKeyPress(arrowKey);
            }
        } else if (key == 10) {
            onEnterPress();
        } else {
            onNormalKeyPress(key);
        }
        render();
    }
}

// Constructor
Window::Window(int sizeX, int sizeY):sizeX(sizeX+2), sizeY(sizeY+2) {
	canvas = new char* [sizeY+2];
	for (int i=0; i<sizeY+2; i++) {
		canvas[i] = new char [sizeX+2];
	}
}

Window::~Window() {
	for (int i=0; i<sizeY; i++) {
		delete [] canvas[i];
	}
	delete [] canvas;

}

// Add a new view to the window in provided position
void Window::addView(View* view, int posX, int posY) {
	views.push_back(view);
	view->setPos(posX, posY);
	view->setWindow(this);
}

// Set exit to true;
void Window::setExit() {
	exit = true;
}

// Return selectedView
View* Window::getSelectedView() {
	return selectedView;
}

// Set the selectView
void Window::selectView(View* view) {
	selectedView = view;
}

// Button Controller
void Window::onArrowKeyPress(ArrowKey key) {
	if(selectedView == nullptr) {
		int i = 0;
		/*
		while (selectedView == nullptr and 2 + i < views.size()) {
			selectedView == views[2 + i];
		}*/
		selectedView = views[2];
		return;
	}

	
	View* temp = nullptr;
	if (key == ArrowKey::UP) {
		
		int min_dis_x = 10000;
		int min_dis_y = 10000;
		for (int i=0; i<views.size(); i++) {
			if (!views[i]->isSelectable()) 
				continue;

			if (views[i] != selectedView) {
				int dis_x = abs(views[i]->getPosX() - selectedView->getPosX());
				int dis_y = selectedView->getPosY() - views[i]->getPosY(); //right -> wanted-x > selected-x
				if (dis_y == min_dis_y) {
					if(dis_x < min_dis_x) {
						temp = views[i];
						min_dis_x = dis_x;
					}
				}
				if (dis_y > 0 and dis_y < min_dis_y) {
					min_dis_y = dis_y;
					min_dis_x = dis_x;
					temp = views[i];
				}
			}
		}
	}else if (key == ArrowKey::DOWN) {

		int min_dis_x = 10000;
		int min_dis_y = 10000;
		for (int i=0; i<views.size(); i++) {
			if (!views[i]->isSelectable()) 
				continue;

			if (views[i] != selectedView) {
				int dis_x = abs(views[i]->getPosX() - selectedView->getPosX());
				int dis_y = views[i]->getPosY() - selectedView->getPosY(); //right -> wanted-x > selected-x
				if (dis_y == min_dis_y) {
					if(dis_x < min_dis_x) {
						temp = views[i];
						min_dis_x = dis_x;
					}
				}
				if (dis_y > 0 and dis_y < min_dis_y) {
					min_dis_y = dis_y;
					min_dis_x = dis_x;
					temp = views[i];
				}
			}
		}
	}else if (key == ArrowKey::RIGHT) {
		int min_dis_x = 10000;
		int min_dis_y = 10000;
		for (int i=0; i<views.size(); i++) {
			if (!views[i]->isSelectable()) 
				continue;

			if (views[i] != selectedView) {
				int dis_y = abs(views[i]->getPosY() - selectedView->getPosY());
				int dis_x = views[i]->getPosX() - selectedView->getPosX(); //right -> wanted-x > selected-x
				if (dis_x == min_dis_x) {
					if(dis_y < min_dis_y) {
						temp = views[i];
						min_dis_y = dis_y;
					}
				}
				if (dis_x > 0 and dis_x < min_dis_x) {
					min_dis_x = dis_x;
					min_dis_y = dis_y;
					temp = views[i];
				}
			}
		}
	}else if (key == ArrowKey::LEFT) {	
		int min_dis_x = 10000;
		int min_dis_y = 10000;
		for (int i=0; i<views.size(); i++) {
			if (!views[i]->isSelectable()) 
				continue;

			if (views[i] != selectedView) {
				int dis_y = abs(views[i]->getPosY() - selectedView->getPosY());
				int dis_x = selectedView->getPosX() - views[i]->getPosX(); //left -> wanted-x <  selected-x
				if (dis_x == min_dis_x) {
					if(dis_y < min_dis_y) {
						temp = views[i];
						min_dis_y = dis_y;
					}
				}
				if (dis_x > 0 and dis_x < min_dis_x) {
					min_dis_x = dis_x;
					min_dis_y = dis_y;
					temp = views[i];
				}
			}
		}
	}

	if(temp != nullptr) {
		selectView(temp);
	}

	return;
}

void Window::onNormalKeyPress(char key) {
	if(selectedView != nullptr) {
		selectedView->onInputKey(key);
	}
}

void Window::onEnterPress() {
	if(selectedView != nullptr) {
		selectedView->onClick();
	}
}

void Window::renderFrame() {
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

void Window::fillCanvas(char key) {
	for (int i=1; i<sizeY-1; i++) {
		for (int j=1; j<sizeX-1; j++) {
			canvas[i][j] = key;
		}
	}
}
