#pragma once
#define MIN_SIZE 5
#define MAX_SIZE 50
#define MAX_HEIGHT 2

class Map
{
	Texture* tileTexture;
	Rect mapRect;
	map <int, vector<vector<Tile*>>> mapTile;
	int sizeX;
	int sizeY;
	int curHeight;
	POINT baseFrame;

	HBRUSH brush;
	HBRUSH oldBrush;

	friend class MapManager;

	void Create();
	void Destroy();

	void AddRow();
	void AddCol();

	void DelRow();
	void DelCol();

	void SetTile();
public:
	Map(Texture* tileTexture, int sizeX = MIN_SIZE, int sizeY = MIN_SIZE, POINT baseFrame = { 0, 0 });
	~Map();

	void Update();
	void Render();
	void SetRect(float left, float top, float right, float bottom);
	void AddSize(float value);
	void SubSize(float value);
	Rect* GetRect() { return &mapRect; }
	POINT GetFrame(Vector2 pos);
	void MoveCenter(Vector2 center);

	void SetLayerFrame(int layer, POINT frame);

	void AttackMap(Vector2 pos);
};