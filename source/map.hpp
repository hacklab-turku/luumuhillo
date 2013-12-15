#ifndef H_MAP
#define H_MAP

#define MAP_SIZE_X 512
#define MAP_SIZE_Y 512
#include "typedefs.hpp"

class map 
{
public:
	map();
	void render(ViewPtr view);
	char getCellData(int x, int y);
	bool isSolid(int x, int y);
	void generate();
	void work();
	void setDrawGrid(bool draw) {drawGrid = draw;}


private:
	char world[MAP_SIZE_X][MAP_SIZE_Y];
	bool drawGrid;

};





#endif
