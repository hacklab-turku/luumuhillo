#ifndef H_GUI
#define H_GUI

#include <string>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "typedefs.hpp"

class gui {
public:
	gui();
	void init();
	void render(ViewPtr view);
	void setPlayerPosition(int x, int y);
	void setScore(int score);

private:

	sf::Font font;
	sf::Text position;
	sf::Text score;
};


#endif
