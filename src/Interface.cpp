/*
 * Interface.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: AdeelZahid
 */

#include "Interface.h"
#include "Collision.hpp"
Interface::Interface(int size, int ratio) { // @suppress("Class members should be properly initialized")

	gunshot.loadFromFile("shot.ogg");
	hitone.loadFromFile("hitone.ogg");
	hittwo.loadFromFile("hittwo.ogg");
	gameOver = false;
	srand(time(NULL));
	if (!this->pauseMessage.loadFromFile("Pause.png")) {
		cout << "Pause message not loaded" << endl;
	}
	pause.setTexture(pauseMessage);
	changeStateDelay = 0;
	this->currentMaze = 1;
	startDelay = 0;
	screenFactor = ratio;
	brickcounter = 0;
	this->sizeofcoordinates = size / screenFactor;
	coordinates = new int*[sizeofcoordinates];
	for (int i = 0; i < sizeofcoordinates; i++) {
		coordinates[i] = new int[sizeofcoordinates];
	}
	for (int i = 0; i < sizeofcoordinates; i++) {
		for (int j = 0; j < sizeofcoordinates; j++) {
			coordinates[i][j] = 0;
		}
	}
//	bricks.setObjectsize(screenFactor); // set the size of the bricks
	bricks.initialise(sizeofcoordinates);

	tankcount = 2;
	tanks = new Tank[tankcount];
	//coordinates[2][2] = 2;
	if (!texture1.loadFromFile("Asset 2.png")) { // Asset 11
		std::cout << "Image Loading failed" << std::endl;
		getchar();
	}
	tanks[0].tank.setTexture(texture1);

	if (!texture2.loadFromFile("Asset 1.png")) {
		std::cout << "Image Loading failed" << std::endl;
		getchar();
	}

	tanks[1].tank.setTexture(texture2);

	///from bulletcollisionwithwall()
	img.create(screenFactor, screenFactor, sf::Color::Blue);
	temp.loadFromImage(img);
	temp1.setTexture(temp);
	if (!t.loadFromFile("msg.png")) {
		cout << "Unable to load the message box" << endl;
	}
	s.setTexture(t);
	shapeCount = 3 + tankcount;

	drawables = new Shape *[shapeCount];
	shapeCount = 0 ;
	drawables[shapeCount] = &bricks ;
	shapeCount++ ;

	for (int i = 0 ; i<tankcount ;i ++)
	{
		drawables[shapeCount] = &tanks[i] ;
		shapeCount++ ;
	}

	drawables[shapeCount] = &destruction ;
	shapeCount++ ;

	drawables[shapeCount] = &mine ;
	shapeCount++ ;

}
void Interface::maze1() {
	//left most coloumn
	int first = 0;
	brickcounter = 0;
	for (int i = 1; i < this->sizeofcoordinates; i++) {
		coordinates[0][i] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(0, i); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;
	}
	//last brick of horizontal row act as a vertical wall and vice versa
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "end";
	//top most row
	first = 0;
	for (int j = 0; j < this->sizeofcoordinates; j++) {
		coordinates[j][0] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(j, 0);
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 14] = "end";
	bricks.orientation[brickcounter - 15] = "end";
	bricks.orientation[brickcounter - 16] = "end";
	bricks.orientation[brickcounter - 23] = "end";
	bricks.orientation[brickcounter - 24] = "end";
	//bottom most row
	first = 0;
	for (int k = 1; k < this->sizeofcoordinates; k++) {
		coordinates[k][sizeofcoordinates - 1] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates - 1); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "end";

	bricks.orientation[brickcounter - 22] = "end";
	bricks.orientation[brickcounter - 23] = "end";
	bricks.orientation[brickcounter - 24] = "end";
	first = 0;
	//right most coloum
	for (int l = 1; l < this->sizeofcoordinates; l++) {
		coordinates[sizeofcoordinates - 1][l] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates - 1, l);
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 21] = "end";
	bricks.orientation[brickcounter - 10] = "end";
	bricks.orientation[brickcounter - 11] = "end";
	bricks.orientation[brickcounter - 15] = "end";
	bricks.orientation[brickcounter - 16] = "end";
	bricks.orientation[brickcounter - 20] = "end";


	bricks.orientation[brickcounter - 24] = "vertical";
	bricks.orientation[brickcounter - 25] = "end";
	bricks.orientation[brickcounter - 26] = "end";
	bricks.orientation[brickcounter - 5] = "end";
	bricks.orientation[sizeofcoordinates - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 6] = "end";
	first = 0;
	//for first vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if ((m >= 0 && m < this->sizeofcoordinates / 3) || m > 2 * (this->sizeofcoordinates / 3)) {
			coordinates[sizeofcoordinates / 4][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 4, m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first+1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - 4] = "end";
	bricks.orientation[brickcounter - 5] = "end";
	bricks.orientation[brickcounter - 9] = "horizontal";
	first = 0;
	//for second vertical line from left
	for (int n = 1; n < this->sizeofcoordinates; n++) {
		if (n < this->sizeofcoordinates / 3) {
			coordinates[sizeofcoordinates / 2][n] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 2, n);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 1] = "horizontal";

	for (int i = 0; i < brickcounter; i++)
	{
		if (bricks.brick[i].getPosition().x == ((sizeofcoordinates - 15)*screenFactor) && bricks.brick[i].getPosition().y == ((sizeofcoordinates - 5)*screenFactor))
		{
			bricks.orientation[i] = "end";
			cout << "True";
		}
	}
	first = 0;
	for (int n = 1; n < this->sizeofcoordinates; n++) {
		if ((n > this->sizeofcoordinates / 2) && n <= (5 * (this->sizeofcoordinates / 6))) {
			coordinates[sizeofcoordinates / 2][n] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 2, n);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	//1st horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 4) && k < this->sizeofcoordinates) {
			coordinates[k][sizeofcoordinates / 6] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates / 6);
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//2nd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 4) && k < this->sizeofcoordinates) {
			coordinates[k][sizeofcoordinates / 3] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates / 3);
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//3rd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 4) && k < this->sizeofcoordinates) {
			coordinates[k][sizeofcoordinates / 2] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates / 2);
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//4th horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 4) && k < this->sizeofcoordinates) {
			coordinates[k][2 * (sizeofcoordinates / 3)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 2 * (sizeofcoordinates / 3));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//5th horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 4) && k < this->sizeofcoordinates) {
			coordinates[k][5 * (sizeofcoordinates / 6)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 5 * (sizeofcoordinates / 6));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	first = 0;
		for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k >= this->sizeofcoordinates / 4 && k < this->sizeofcoordinates * 0.52) {
			coordinates[k][5 * (sizeofcoordinates / 6)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 5 * (sizeofcoordinates / 6));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first + 1] = "end";
}
void Interface::maze2()  {
	//left most coloumn
	int first = 0;
	brickcounter = 0;
	for (int i = 1; i < this->sizeofcoordinates; i++) {
		coordinates[0][i] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(0, i); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;
	}
	//last brick of horizontal row act as a vertical wall and vice versa
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first + 1] = "end";
	bricks.orientation[brickcounter - 11] = "end";
	bricks.orientation[brickcounter - 16] = "end";
	bricks.orientation[brickcounter - 9] = "end";
	bricks.orientation[brickcounter - 18] = "end";
	bricks.orientation[brickcounter - 17] = "end";
	bricks.orientation[brickcounter - 10] = "end";
	//top most row
	first = 0;
	for (int j = 0; j < this->sizeofcoordinates; j++) {
		coordinates[j][0] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(j, 0);
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 25] = "end";
	bricks.orientation[brickcounter - 15] = "end";
	bricks.orientation[brickcounter - first] = "end";

	//bottom most row
	first = 0;
	for (int k = 1; k < this->sizeofcoordinates; k++) {
		coordinates[k][sizeofcoordinates - 1] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates - 1); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 4] = "end";
	bricks.orientation[brickcounter - 5] = "end";
	bricks.orientation[brickcounter - 24] = "end";
	bricks.orientation[brickcounter - 25] = "end";
	bricks.orientation[brickcounter - 6] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter] = "end";
	first = 0;
	//right most coloum
	for (int l = 1; l < this->sizeofcoordinates; l++) {
		coordinates[sizeofcoordinates - 1][l] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates - 1, l);
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "vertical";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter] = "end";
	first = 0;
	//1st horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 4 * (this->sizeofcoordinates / 6) && k <= 5 * (this->sizeofcoordinates / 6)) {
			coordinates[k][sizeofcoordinates / 7] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, int(sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "vertical";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	//2nd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > (this->sizeofcoordinates / 2) && k <= 4 * (this->sizeofcoordinates / 6)) {
			coordinates[k][2 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 2 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 5 * (this->sizeofcoordinates / 6)) {
			coordinates[k][2 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 2 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//3rd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > (this->sizeofcoordinates / 2) && k <= 2 * (this->sizeofcoordinates / 3)) {
			coordinates[k][3 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 3 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first+1] = "end";
	first = 0;
		for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k < (this->sizeofcoordinates / 6)) {
			coordinates[k][3 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 3 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - first] = "end";
		first = 0;
	//4th horizontal line from top
		for (int k = 0; k < this->sizeofcoordinates; k++) {
			if (k > (this->sizeofcoordinates / 6) && k <= 2 * (this->sizeofcoordinates / 6)) {
				coordinates[k][4 * (sizeofcoordinates / 7)] = 1;
				bricks.getBrick()[brickcounter].setPosition(k, 4 * (sizeofcoordinates / 7));
				bricks.orientation[brickcounter] = "horizontal";
				brickcounter++;
				first++;
			}
		}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - first] = "end";
		first = 0;
		for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 5)) {
			coordinates[k][4 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 4 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - 4] = "end";
		bricks.orientation[brickcounter - first] = "end";
		first = 0;
	//5th horizontal line from top
		for (int k = 0; k < this->sizeofcoordinates; k++) {
			if (k <= (this->sizeofcoordinates / 6)) {
				coordinates[k][5 * (sizeofcoordinates / 7)] = 1;
				bricks.getBrick()[brickcounter].setPosition(k, 5 * (sizeofcoordinates / 7));
				bricks.orientation[brickcounter] = "horizontal";
				brickcounter++;
				first++;
			}
		}
		bricks.orientation[brickcounter - 1] = "horizontal";
		bricks.orientation[brickcounter - first] = "end";
		bricks.orientation[brickcounter - first+1] = "end";
		first = 0;
		for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k <= 4 * (this->sizeofcoordinates / 6) && k > 2 * (this->sizeofcoordinates / 6)) {
			coordinates[k][5 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 5 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - 6] = "end";
		bricks.orientation[brickcounter - first] = "end";
		first = 0;
	//6th horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > (this->sizeofcoordinates / 6) && k <= 3 * (this->sizeofcoordinates / 6)) {
			coordinates[k][6 * (sizeofcoordinates / 7)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 6 * (sizeofcoordinates / 7));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "vertical";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	//for first vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= (this->sizeofcoordinates / 7)) {
			coordinates[sizeofcoordinates / 6][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 6, m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
		bricks.orientation[brickcounter - first] = "end";
		bricks.orientation[brickcounter - first+1] = "end";
		bricks.orientation[brickcounter - 1] = "vertical";
		first = 0;
		for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m > 2 * (this->sizeofcoordinates / 7) && m <= 3 * (this->sizeofcoordinates / 7)) {
			coordinates[sizeofcoordinates / 6][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 6, m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - 2] = "end";
		bricks.orientation[brickcounter - first] = "vertical";
		first = 0;
		for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m >= 6 * (this->sizeofcoordinates / 7)) {
			coordinates[sizeofcoordinates / 6][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates / 6, m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}

	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	first = 0;
	//for second vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 4 * (this->sizeofcoordinates / 7) && m > (this->sizeofcoordinates / 7)) {
			coordinates[2 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(2 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//for third vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 3 * (this->sizeofcoordinates / 7)) {
			coordinates[3 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(3 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		for (int m = 0; m < this->sizeofcoordinates; m++) {
			if (m <= 5 * (this->sizeofcoordinates / 7) && m > 4 * (this->sizeofcoordinates / 7)) {
				coordinates[3 * (sizeofcoordinates / 6)][m] = 1;
				bricks.getBrick()[brickcounter].setPosition(3 * (sizeofcoordinates / 6), m);
				bricks.orientation[brickcounter] = "vertical";
				brickcounter++;
				first++;
			}
		}

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "vertical";
	first = 0;
	//for 4th vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 2 * (this->sizeofcoordinates / 7) && m >= (this->sizeofcoordinates / 7)) {
			coordinates[4 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(4 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - first] = "end";
		for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m < 6 * (this->sizeofcoordinates / 7) && m > 5 * (this->sizeofcoordinates / 7)) {
			coordinates[4 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(4 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;

		}
	}
		bricks.orientation[brickcounter - 1] = "vertical";
		bricks.orientation[brickcounter - first] = "end";

	//for 5th vertical line  from left
	first = 0;
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 4 * (this->sizeofcoordinates / 7) && m > 3 * (this->sizeofcoordinates / 7)) {
			coordinates[5 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(5 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - first] = "vertical";
		first = 0;
		for (int m = 0; m < this->sizeofcoordinates; m++) {
			if (m > 4 * (this->sizeofcoordinates / 7) && m <= 5 * (this->sizeofcoordinates / 7)) {
				coordinates[5 * (sizeofcoordinates / 6)][m] = 1;
				bricks.getBrick()[brickcounter].setPosition(5 * (sizeofcoordinates / 6), m);
				bricks.orientation[brickcounter] = "vertical";
				brickcounter++;
				first++;
			}
		}
		bricks.orientation[brickcounter - 1] = "horizontal";
		bricks.orientation[brickcounter - first] = "end";
		first = 0;
		for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m > 6 * (this->sizeofcoordinates / 7)) {
			coordinates[5 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(5 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
		bricks.orientation[brickcounter - 1] = "end";
		bricks.orientation[brickcounter - 2] = "end";
		bricks.orientation[brickcounter - first] = "horizontal";
	}
}
void Interface::maze3() {
	//left most column
	int first = 0;
	brickcounter = 0;
	for (int i = 1; i < this->sizeofcoordinates; i++) {
		coordinates[0][i] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(0, i); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;
	}
	//last brick of horizontal row act as a vertical wall and vice versa
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	//top most row
	first = 0;
	for (int j = 0; j < this->sizeofcoordinates; j++) {
		coordinates[j][0] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(j, 0);
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 26] = "end";
	bricks.orientation[brickcounter - 11] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first+1] = "end";

	//bottom most row
	first = 0;
	for (int k = 1; k < this->sizeofcoordinates; k++) {
		coordinates[k][sizeofcoordinates - 1] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates - 1); //  array of bricks and its orientation are parallel
		bricks.orientation[brickcounter] = "horizontal";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 30] = "end";
	bricks.orientation[brickcounter - 15] = "end";
	bricks.orientation[brickcounter - 26] = "end";
	bricks.orientation[brickcounter - 25] = "end";
	bricks.orientation[brickcounter - 16] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter-2] = "end";
	first = 0;
	//right most coloum
	for (int l = 1; l < this->sizeofcoordinates; l++) {
		coordinates[sizeofcoordinates - 1][l] = 1; // 1 is the  token for a brick
		bricks.getBrick()[brickcounter].setPosition(sizeofcoordinates - 1, l);
		bricks.orientation[brickcounter] = "vertical";
		brickcounter++;
		first++;

	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter-25] = "end";
	bricks.orientation[brickcounter - 24] = "end";
	first = 0;
	//1st horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > (this->sizeofcoordinates / 6) && k < (this->sizeofcoordinates / 3)) {
			coordinates[k][sizeofcoordinates / 5] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, int(sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "horizontal";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 5 * (this->sizeofcoordinates / 6)) {
			coordinates[k][sizeofcoordinates / 5] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, sizeofcoordinates / 5);
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "horizontal";
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	first = 0;
	//2nd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 2 * (this->sizeofcoordinates / 6) && k < 3 * (this->sizeofcoordinates / 6)) {
			coordinates[k][2 * (sizeofcoordinates / 5)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 2 * (sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "horizontal";
	bricks.orientation[brickcounter - 1] = "end";
	first = 0;
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 4 * (this->sizeofcoordinates / 6) && k <= 5 * (this->sizeofcoordinates / 6)) {
			coordinates[k][2 * (sizeofcoordinates / 5)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 2 * (sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "horizontal";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;

	//3rd horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > (this->sizeofcoordinates / 6) && k <= 2 * (this->sizeofcoordinates / 6)) {
			coordinates[k][3 * (sizeofcoordinates / 5)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 3 * (sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - 1] = "end";
	first = 0;
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 6) && k <= 5 * (this->sizeofcoordinates / 6)) {
			coordinates[k][3 * (sizeofcoordinates / 5)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 3 * (sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "horizontal";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;

	//4th horizontal line from top
	for (int k = 0; k < this->sizeofcoordinates; k++) {
		if (k > 3 * (this->sizeofcoordinates / 6) && k <= 4 * (this->sizeofcoordinates / 6)) {
			coordinates[k][4 * (sizeofcoordinates / 5)] = 1;
			bricks.getBrick()[brickcounter].setPosition(k, 4 * (sizeofcoordinates / 5));
			bricks.orientation[brickcounter] = "horizontal";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "horizontal";
	bricks.orientation[brickcounter - 1] = "end";
	first = 0;

	//for first vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 2 * (this->sizeofcoordinates / 5) ) {
			coordinates[(sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition((sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
	bricks.orientation[brickcounter - 1] = "vertical";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first+1] = "end";
	first = 0;
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m > 4 * (this->sizeofcoordinates / 5)) {
			coordinates[(sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition((sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - first] = "vertical";
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - 2] = "end";
	first = 0;

	//for second vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m > 3 * (this->sizeofcoordinates / 5)) {
			coordinates[2 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(2 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;

	//for third vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 3 * (this->sizeofcoordinates / 5) && m > (this->sizeofcoordinates / 5)) {
			coordinates[3 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(3 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "horizontal";
	first = 0;
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m >= 4 * (this->sizeofcoordinates / 5)) {
			coordinates[3 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(3 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	first = 0;
	//for fourth vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m <= 2 * (this->sizeofcoordinates / 5)) {
			coordinates[4 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(4 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;
		}
	}
	bricks.orientation[brickcounter - 1] = "end";
	bricks.orientation[brickcounter - first] = "end";
	bricks.orientation[brickcounter - first+1] = "end";
	first = 0;
	//for fifth vertical line  from left
	for (int m = 0; m < this->sizeofcoordinates; m++) {
		if (m > 3 * (this->sizeofcoordinates / 5) && m <= 4 * (this->sizeofcoordinates / 5)) {
			coordinates[5 * (sizeofcoordinates / 6)][m] = 1;
			bricks.getBrick()[brickcounter].setPosition(5 * (sizeofcoordinates / 6), m);
			bricks.orientation[brickcounter] = "vertical";
			brickcounter++;
			first++;

		}
	}
	bricks.orientation[brickcounter - 1] = "horizontal";
	bricks.orientation[brickcounter - first] = "end";
}
int** Interface::getCoordinates() {
	return coordinates;
}

int Interface::getPause() const {
	return startDelay;
}

TankDestroyed& Interface::getDestruction() {
	return destruction;
}

void Interface::setDestruction(TankDestroyed &destruction) {
	this->destruction = destruction;
}

void Interface::setPause(int pause) {
	this->startDelay = pause;
}

Tank*& Interface::getTanks() {
	return tanks;
}

int Interface::getSize() const {
	return sizeofcoordinates;
}

Interface::~Interface() {
	delete[] this->coordinates;
}

void Interface::drawMaze() {
	//draw all maze here
	int mazeNumber = currentMaze;
/*
	if (mazeNumber == 1 )
		mazeNumber = 2 ;
	else if (mazeNumber == 2)
		mazeNumber = 1 ;
	*/
	if (mazeNumber == 1) {
		maze1();
	} else if (mazeNumber == 2) {
		maze2();
	} else if (mazeNumber == 3) {
		maze3();
	}

	for (int i = 0; i < brickcounter; i++) {
		bricks.getBrick()[i].setPosition(int(bricks.getBrick()[i].getPosition().x) * screenFactor, int(bricks.getBrick()[i].getPosition().y) * screenFactor);
	}

	if (mazeNumber == 1) {
		tanks[0].tank.setPosition(20 * screenFactor, 20 * screenFactor);
		tanks[1].tank.setPosition(2 * screenFactor, 2 * screenFactor);
	} else if (mazeNumber == 2) {
		tanks[0].tank.setPosition(screenFactor * 3, screenFactor * 2);
		tanks[1].tank.setPosition(22 * screenFactor, 20 * screenFactor);
		tanks[0].tank.setRotation(0);
		tanks[1].tank.setRotation(0);

	} else if (mazeNumber == 3) {
		tanks[0].tank.setPosition(screenFactor * 3, screenFactor * 3);
		tanks[0].tank.setRotation(180);
		tanks[1].tank.setRotation(0);
		tanks[1].tank.setPosition(27 * screenFactor, 25 * screenFactor);

	}
	this->mine.setGame(this);
	this->bricks.setBrickCounter(this->brickcounter);
	mine.setResetMines(1);
	mine.setMineCoordinates();
	int x, y;
	for (int i = 0; i < brickcounter; i++) {
		x = bricks.brick[i].getPosition().x;
		y = bricks.brick[i].getPosition().y;
		x = x / screenFactor;
		y = y / screenFactor;
		coordinates[x][y] = 1;
	}

//	fix();
//	//brickcounter = 0 ;
//	for (int i = 0; i < this->sizeofcoordinates; i++) {
//		for (int j = 0; j < this->sizeofcoordinates; j++) {
//			if (coordinates[i][j] == 1) {
//				cout << coordinates[i][j];
////				bricks.brick[brickcounter].setPosition(sf::Vector2f(i*screenFactor,j*screenFactor));
//				//			brickcounter++;
//			} else
//				cout << "- ";
//
//		}
//		cout << endl;
//	}
/*
	for (int i = 0 ; i<brickcounter ;i++)
	{
		if (int( bricks.brick[i].getPosition().x)%this->screenFactor != 0 || int(bricks.brick[i].getPosition().y)%this->screenFactor != 0)
		{
			cout<<"Crap"<<endl;
		}
	}
	*/




}
void Interface::mirror(int **a, int **b, int x) {
	for (int i = 0; i < x; i++) {                       //prepare array's image data
		for (int j = 0; j < x; j++) {
			b[i][j] = a[(x - 1) - i][j];        // logic for array's image
		}
	}
}
void Interface::roteste90(int **a, int **b, int n, int m) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			b[i][j] = a[n - j - 1][i];

}

int Interface::getCurrentMaze() const {
	return currentMaze;
}

void Interface::setCurrentMaze(int currentMaze) {
	this->currentMaze = currentMaze;
}

void Interface::fix() {
	int **arr = new int*[sizeofcoordinates];
	for (int i = 0; i < sizeofcoordinates; i++) {
		arr[i] = new int[sizeofcoordinates];
	}
	mirror(coordinates, arr, sizeofcoordinates);
	for (int j = 0; j < sizeofcoordinates; j++) {
		for (int k = 0; k < sizeofcoordinates; k++) {

			coordinates[j][k] = arr[j][k];
		}
	}

	for (int i = 1; i <= 1; i++) {
		roteste90(coordinates, arr, sizeofcoordinates, sizeofcoordinates);
		for (int j = 0; j < sizeofcoordinates; j++) {
			for (int k = 0; k < sizeofcoordinates; k++) {

				coordinates[j][k] = arr[j][k];
			}
		}
	}
}
void Interface::display(sf::RenderWindow &window) {
	for (int i = 0; i<shapeCount ;i++)
	{
		drawables[i]->draw(window);
	}
}
bool Interface::collisionTankWall(int tankNumber) {
	for (int i = 0; i < brickcounter; i++) {
		temp.loadFromImage(img);
		temp1.setTexture(temp);
		temp1.setPosition(bricks.brick[i].getPosition());

		if (Collision::PixelPerfectTest(tanks[tankNumber].tank, temp1))
//		if ( tanks[tankNumber].tank.getGlobalBounds().intersects(bricks.getBrick()[i].getGlobalBounds() ))
				{
			//cout<<"COLLISION"<<endl ;
			return true;
		}
	}
	//cout<<"No collision"<<endl ;
	return false;
}
void Interface::moveTank(string direction, int tankNumber) {


	sf::Sprite *temp = &this->tanks[tankNumber].getTank();
	float distance = 10; //distance to be moved // controls the speed of movement
	//the key factors for movement is the direction of the movement and the angle at which the tank is rotated
	if (direction == "Up") {
		int angle = temp->getRotation();
		switch (angle) {
		case 0:
			temp->move(+0, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(0, +distance);
			break;
		case 45:
			temp->move(+distance, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, +distance);
			break;
		case 90:
			temp->move(+distance, 0);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, 0);
			break;
		case 135:
			temp->move(+distance, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, -distance);
			break;
		case 180:
			temp->move(0, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(0, -distance);
			break;
		case 225:
			temp->move(-distance, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, -distance);
			break;
		case 270:
			temp->move(-distance, 0);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, 0);
			break;
		case 315:
			temp->move(-distance, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, distance);
			break;

		}
	} else if (direction == "Down") {
		int angle = temp->getRotation();
		switch (angle) {
		case 0:
			temp->move(+0, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(0, -distance);
			break;
		case 45:
			temp->move(-distance, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, -distance);
			break;
		case 90:
			temp->move(-distance, 0);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, 0);
			break;
		case 135:
			temp->move(-distance, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(distance, distance);
			break;
		case 180:
			temp->move(0, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(0, distance);
			break;
		case 225:
			temp->move(distance, -distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, distance);
			break;
		case 270:
			temp->move(distance, 0);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, 0);
			break;
		case 315:
			temp->move(distance, distance);
			if (this->collisionTankWall(tankNumber)) // if colliding then do the reverse and move back to the same coordiantes
				temp->move(-distance, -distance);
			break;

		}
	} else if (direction == "Right") {
		temp->rotate(45);
		if ((this->collisionTankWall(tankNumber)))
			temp->rotate(-45);
	} else if (direction == "Left") {
		temp->rotate(-45);
		if ((this->collisionTankWall(tankNumber)))
			temp->rotate(+45);
	}

	cout<<"Tank : "<<tankNumber<<" \nCoordinates  ("<<this->tanks[tankNumber].tank.getPosition().x<<" , "<<this->tanks[tankNumber].tank.getPosition().y<<")"<<endl;
	cout<<"Rotation: "<<tanks[tankNumber].tank.getRotation()<<endl<<endl<<endl;

}


void Interface::destroyBullet() {//function call is controlled by the timer in main.cpp
	// destroy a bullet based on its own timer or status
	for (int i = 0; i < this->tankcount; i++) {
		for (int j = 0; j < this->tanks[i].firedbullets; j++) {
			for (int a = 1; a <= tanks[i].firedbullets; a++) {
				this->tanks[i].bullets[a - 1] = this->tanks[i].bullets[a];
			}
			tanks[i].firedbullets--;

		}
	}

}

void Interface::fire(int tankNumber) {
	if (tanks[tankNumber].firedbullets <= 5) {
		sound.setBuffer(gunshot);
		sound.play();
		this->tanks[tankNumber].bullets[tanks[tankNumber].firedbullets].startTimer();

		tanks[tankNumber].bullets[tanks[tankNumber].firedbullets].bullet.setRotation(tanks[tankNumber].tank.getRotation()); //set same rotation as that of the tank

//		cout<<"Bullets Remaining"<<tanks[tankNumber].firedbullets <<endl;
		//	cout<<tanks[tankNumber].tank.getPosition().x<<","<<tanks[tankNumber].tank.getPosition().y<<endl ;
		tanks[tankNumber].bullets[tanks[tankNumber].firedbullets].bullet.setPosition(tanks[tankNumber].tank.getPosition());	// set the same position as that of tank
		//cout<<tanks[tankNumber].bullets[tanks[tankNumber].firedbullets].bullet.getPosition().x<<","<<tanks[tankNumber].bullets[tanks[tankNumber].firedbullets].bullet.getPosition().x<<endl<<endl;
		tanks[tankNumber].setFiredbullets(tanks[tankNumber].getFiredbullets() + 1);

	this->moveBullets();
	}
	//	cout << "All bullets used" << endl;

	//code to move the current bullet one step forward
}
void Interface::moveBullets() {//function call is controlled by the timer in main.cpp

	BulletscollisionWithWalls();
	//	cout<<"Moving bullets"<<endl ;
	//move all bullets for all tanks
	for (int i = 0; i < this->tankcount; i++) {
		for (int j = 0; j < this->tanks[i].firedbullets; j++) {

			//	code the logic for movement of bullets based on their rotation angle .. logic is same as that of movement of tank
			sf::Sprite *temp = &this->tanks[i].bullets[j].getBullet();
			float distance = 10;
			int angle = temp->getRotation();

			//cout << "Angle is" << temp->getRotation()<<endl;
			float x = 0, y = 0;
			switch (angle) {
			case 0:
				x = temp->getPosition().x;
				y = temp->getPosition().y - distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 45:

				x = temp->getPosition().x + distance;
				y = temp->getPosition().y - distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 90:

				x = temp->getPosition().x + distance;
				y = temp->getPosition().y;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 135:

				x = temp->getPosition().x + distance;
				y = temp->getPosition().y + distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 180:

				x = temp->getPosition().x;
				y = temp->getPosition().y + distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 225:

				x = temp->getPosition().x - distance;
				y = temp->getPosition().y + distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 270:

				x = temp->getPosition().x - distance;
				y = temp->getPosition().y;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			case 315:

				x = temp->getPosition().x - distance;
				y = temp->getPosition().y - distance;
				temp->setPosition(sf::Vector2f(x, y));
				break;
			default:
				cout << "No Angle Matching " << endl;
			}

			//now check collision of the bullet with the walls
//					BulletscollisionWithWalls();

			if (this->tanks[i].bullets[j].CheckBulletTimeout()) {
				destroyBullet();
			}

		}
	}

}
void Interface::BulletscollisionWithTank() {
	bool collided = false;
	for (int i = 0; i < tankcount; i++) {
		for (int j = 0; j < tanks[i].firedbullets && collided == false; j++) {
			if (Collision::PixelPerfectTest(tanks[i].bullets[j].bullet, tanks[i].tank)) {
				collided = 1;
				tanks[1 - i].score += 20;
				tanks[i].lives -= 1;
				//	cout << "Friendly FIre Lives for tank " << (i + 1) << ":" << tanks[i].lives << endl;
				destruction.start = 1;
				if (tanks[i].lives <= 0) {
					sound.setBuffer(hittwo);
					sound.play();
					tanks[i].status = 0;
					DestroyBullet2();
				}
				else{
					sound.setBuffer(hitone);
					sound.play();
				}
				destruction.flames.setPosition(tanks[i].tank.getPosition());
				destruction.flames.setRotation(tanks[i].tank.getRotation());
				tanks[i].bullets[j].RemoveBullet = 1;
				destroyBullet();
				//cout << "-\tScore Update: \t-" << endl;
				//cout << "Tank [1]: " << tanks[0].score << "\tTank [2]: " << tanks[1].score << endl;
			}

		}
	}
	collided = false;
	for (int i = 0; i < tankcount; i++) {
		for (int j = 0; j < tanks[1 - i].firedbullets && collided == false; j++) {
			if (Collision::PixelPerfectTest(tanks[1 - i].bullets[j].bullet, tanks[i].tank)) {
				collided = 1;
				tanks[i].lives -= 1;
				//cout << "Enemy FIre Lives for tank " << (i + 1) << ":" << tanks[i].lives << endl;
				tanks[1 - i].score += 40;
				if (tanks[i].lives <= 0) {
					tanks[i].status = 0;
					DestroyBullet2();
					sound.setBuffer(hittwo);
					sound.play();
				}
				else
				{
					sound.setBuffer(hitone);
					sound.play();
				}
				destruction.start = 1;
				destruction.flames.setPosition(tanks[i].tank.getPosition());
				tanks[1 - i].bullets[j].RemoveBullet = 1;
				destroyBullet();
				cout << "-\tScore Update: \t-" << endl;
				cout << "Tank [1]: " << tanks[0].score << "\tTank [2]: " << tanks[1].score << endl;

			}
		}
	}
	if (changeStateDelay == 0) {
		for (int i = 0; i < tankcount; i++) {
			if (tanks[i].lives <= 0) {
				currentMaze++;
				changeStateDelay = 1;
				mine.setResetMines(true);
				if (currentMaze > 3) {
					gameOver = true;
					currentMaze = 1;
				}
			}
		}
	}
	if (currentMaze > 3) {
		cout << "Game End" << endl;
		this->gameOver = true;
		currentMaze = 1;
	}
	if (changeStateDelay == 4) {
		drawMaze();
		changeStateDelay = 0;
	}

}
void Interface::DestroyBullet2() {
	for (int i = 0; i < tankcount; i++) {
		for (int j = 0; j < 40; j++) {
			tanks[i].bullets[j].bullet.setPosition(sf::Vector2f(-1000, -1000));
		}
	}
}
void Interface::BulletscollisionWithWalls() {
	for (int i = 0; i < this->brickcounter; i++) {
		for (int j = 0; j < tankcount; j++) {
			for (int k = 0; k < tanks[j].getFiredbullets(); k++) {
				temp1.setPosition(bricks.brick[i].getPosition());

				if (Collision::PixelPerfectTest(tanks[j].bullets[k].bullet, temp1)) {
//					cout<<temp1.getPosition().x/screenFactor<<","<<temp1.getPosition().y/screenFactor<<endl;		getchar();
					sf::Sprite *temp = &this->tanks[j].bullets[k].getBullet();
					float x = 0, y = 0;
					int angle = temp->getRotation();
					switch (angle) {
					case 0:
						temp->rotate(180);
						temp->setPosition(temp->getPosition().x, temp->getPosition().y + screenFactor);
						break;
					case 45:

						if (bricks.orientation[i] == "vertical") {
							temp->rotate(-90);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y - screenFactor);
						}
						if (bricks.orientation[i] == "horizontal") {
							temp->rotate(90);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y + screenFactor);
						}
						if (bricks.orientation[i] == "end") {
							temp->rotate(180);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y + screenFactor);

						}
						break;
					case 90:
						temp->rotate(-180);
						temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y);
						break;
					case 135:

						if (bricks.orientation[i] == "vertical") {
							temp->rotate(90);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y + screenFactor);
						}
						if (bricks.orientation[i] == "horizontal") {
							temp->rotate(-90);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y - screenFactor);
						}
						if (bricks.orientation[i] == "end") {
							temp->rotate(180);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y - screenFactor);

						}
						break;
					case 180:
						temp->rotate(180);
						temp->setPosition(temp->getPosition().x, temp->getPosition().y - screenFactor);
						break;
					case 225:
						if (bricks.orientation[i] == "vertical") {
							temp->rotate(-90);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y + screenFactor);
						}
						if (bricks.orientation[i] == "horizontal") {
							temp->rotate(90);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y - screenFactor);
						}
						if (bricks.orientation[i] == "end") {
							temp->rotate(180);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y - screenFactor);

						}
						break;
					case 270:
						temp->rotate(180);
						temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y);
						break;
					case 315:

						if (bricks.orientation[i] == "vertical") {
							temp->rotate(90);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y - screenFactor);
						}
						if (bricks.orientation[i] == "horizontal") {
							temp->rotate(-90);
							temp->setPosition(temp->getPosition().x - screenFactor, temp->getPosition().y + screenFactor);
						}
						if (bricks.orientation[i] == "end") {
							temp->rotate(180);
							temp->setPosition(temp->getPosition().x + screenFactor, temp->getPosition().y + screenFactor);

						}
						break;
					}

				}
			}

		}
	}

}
int Interface::getChangeStateDelay() const {
	return changeStateDelay;
}
void Interface::forcedReset()
{

		this->currentMaze = 1 ;
		for (int i = 0; i < this->tankcount; i++) {
			//cout << "Lives for Tank " << (i + 1) << ": " << tanks[i].lives << endl;
			if (tanks[i].lives <= 0) {
				for (int i = 0; i < tankcount; i++) {
					tanks[i].lives = 2;
					tanks[i].firedbullets = 0;
					tanks[i].status = 1;
				}
			}

		this->drawMaze();
 		tanks[0].tank.setPosition(20 * screenFactor, 20 * screenFactor);
 		tanks[0].tank.setRotation(0);
 		tanks[1].tank.setRotation(0);
		tanks[1].tank.setPosition(2 * screenFactor, 2 * screenFactor);
		mine.setCollisionWithTank(false);
		//mine.getClock()->restart();
	}

}
void Interface::reset() {
	if (changeStateDelay == 4) {
		for (int i = 0; i < this->tankcount; i++) {
			//cout << "Lives for Tank " << (i + 1) << ": " << tanks[i].lives << endl;
			if (tanks[i].lives <= 0) {
				for (int i = 0; i < tankcount; i++) {
					tanks[i].lives = 2;
					tanks[i].firedbullets = 0;
					tanks[i].status = 1;
				}
			}
		}
		mine.setCollisionWithTank(false);
		//mine.getClock()->restart();
	}

}
void Interface::setChangeStateDelay(int changeStateDelay) {
	this->changeStateDelay = changeStateDelay;
	reset();
}

void Interface::Maze_Change_And_Pause_Message(sf::RenderWindow &window) {

	s.setPosition(sf::Vector2f(150, 250));
	pause.setPosition(sf::Vector2f(150, 250));
	if (startDelay == 1)
		window.draw(pause);
	else {
		if (this->gameOver == false)
			window.draw(s);

	}

}

void Interface::BombscollisionWithTank() {
	bool collided = false;
	for (int i = 0; i < tankcount && collided == false; i++) {
		for (int j = 0; j < 4; j++) {
			if (mine.isCollisionWithTank() == false) {
				if (Collision::PixelPerfectTest(mine.getMine()[j], tanks[i].tank)) {
					sound.setBuffer(hittwo);
					sound.play();
					collided = 1;
					tanks[1 - i].score += 20;
					tanks[i].lives = 0;
					//cout << "Mine destroyed" << (i + 1) << ":" << tanks[i].lives << endl;
					destruction.start = 1;
					mine.setCollisionWithTank(true);
					if (tanks[i].lives <= 0)
						tanks[i].status = 0;
					collided = true;
					destruction.flames.setPosition(tanks[i].tank.getPosition());
					destruction.flames.setRotation(tanks[i].tank.getRotation());
					cout << "-\tScore Update: \t-" << endl;
					cout << "Tank [1]: " << tanks[0].score << "\tTank [2]: " << tanks[1].score << endl;

				}
			}

		}
	}
	if (changeStateDelay == 0) {
		for (int i = 0; i < tankcount; i++) {
			if (tanks[i].lives <= 0) {
				mine.setResetMines(true);
				currentMaze++;
				changeStateDelay = 1;
				if (currentMaze > 3) {
					gameOver = true;
					currentMaze = 1;
				}

			}
		}
	}
	if (currentMaze > 3) {
		gameOver = true;
		cout << "Game End" << endl;
		currentMaze = 1;
	}
	if (changeStateDelay == 4) {
		drawMaze();
		changeStateDelay = 0;
	}

}

bool Interface::isGameOver() const {
	return gameOver;
}

void Interface::setGameOver(bool gameOver) {
	this->gameOver = gameOver;
}

 Mines& Interface::getMine()  {
	return mine;
}
