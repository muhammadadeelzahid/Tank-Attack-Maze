/*
 * Mines.h
 *
 *  Created on: May 6, 2020
 *      Author: AdeelZahid
 */

#ifndef MINES_H_
#define MINES_H_
#include "Shape.h"

class Mines: public Shape {
	sf::Texture t;
	sf::Sprite mine[2] ;
	sf::Clock *clock ;
	bool CollisionWithTank ;
public:
	void draw(sf::RenderWindow &window) ;
	Mines();
	virtual ~Mines();
	sf::Clock* getClock() const;
	 sf::Sprite* getMine() ;
	const sf::Texture& getT() const;
	void setT(const sf::Texture &t);
	bool isCollisionWithTank() const;
	void setCollisionWithTank(bool collisionWithTank);
};

#endif /* MINES_H_ */