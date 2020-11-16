#pragma once

#define SAMPLE_TILE_X 25
#define SAMPLE_TILE_Y 79
#define SAMPLE_SIZE SAMPLE_TILE_X * SAMPLE_TILE_Y

#define TILE_X 50
#define TILE_Y 50
#define TILE_SIZE TILE_X * TILE_Y

class MapToolScene : public Scene
{
	Player* player;
	Button* playBtn;

	Enemy* enemy;

private:

	Map* map;


	void CreateSampleTile();
	void CreateMap();
public:
	MapToolScene();
	~MapToolScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void ClickSample();
	void ClickMap();

	void Save();
	void Load();
};