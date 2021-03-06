/*
 * stats.h
 *
 *  Created on: May 7, 2020
 *      Author: AdeelZahid
 */

#ifndef STATS_H_
#define STATS_H_

#include "Shape.h"
#include "Interface.h"
#include <fstream>
#include <string>
#include <SFML/Audio.hpp>
class stats: public Shape {
	sf::Music music;
	int currentScreen ;
	sf::Text text ;
	sf::Font font ;
	sf::Sprite s ;
	int noResult ;
	int scoret1 ,scoret2;
	string readScore1[3] , readScore2[3] ;
	sf::Texture option1 ;
	sf::Texture option2 ;
	sf::Texture option3 ;
	sf::Texture option4 ;
	sf::Texture end1 ;
	sf::Texture instruc;
	sf::Texture about;
	sf::Texture side;
	sf::Sprite sp;
	Interface *game;
	int readWritePermission;
	int readWritePermission2;
	int menueOption ;

	int startMusic ;
public:
	void draw(sf::RenderWindow &window) ;
	void draw2(sf::RenderWindow &window) ;
	stats();
	virtual ~stats();
	void setGame(Interface &game) ;
	int getCurrentScreen() const;
	void updateCurrentScreen() ;
	void readFromFile();
	void savetoFile();
	void setCurrentScreen(int currentScreen);
	int getReadWritePermission() const;
	void setReadWritePermission(int readWritePermission);
	int getMenueOption() const;
	void menueOptionReduce();
	void menueOptionIncrement();
	int getReadWritePermission2() const;
	void setReadWritePermission2(int readWritePermission2);
	int getNoResult() const;
	void setNoResult(int noResult);
	void setMenueOption(int menueOption);
	int getStartMusic() const;
	void setStartMusic(int startMusic);
};

#endif /* STATS_H_ */
