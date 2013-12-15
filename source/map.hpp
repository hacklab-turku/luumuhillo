#ifndef H_MAP
#define H_MAP

#define MAP_SIZE_X 512
#define MAP_SIZE_Y 512
#include "typedefs.hpp"

#define GRASS 			0
#define PLUM_TREE 		1
#define BLOOMING_PLUM_TREE 	2
#define MATURE_PLUM_TREE	3
#define BOULDER			4
#define PINE_TREE		5

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
	bool getDrawGrid() {return drawGrid;}


private:
	char world[MAP_SIZE_X][MAP_SIZE_Y];
	bool drawGrid;
	void genBoulders(int x, int y);

};





#endif
