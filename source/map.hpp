#ifndef H_MAP
#define H_MAP

#define MAP_SIZE_X 512
#define MAP_SIZE_Y 512


class map 
{
public:
	map();
	void render();
	char getCellData(int x, int y);
	bool isSolid(int x, int y);
	void generate();


private:
	char world[MAP_SIZE_X][MAP_SIZE_Y];

};





#endif
