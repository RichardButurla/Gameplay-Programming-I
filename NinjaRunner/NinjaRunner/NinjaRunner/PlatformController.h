#pragma once
class PlatformController
{
public:
	PlatformController(float t_x, float t_y, float t_width, float t_height, int t_numberOfBlocks);
	PlatformController();
	~PlatformController();

	void update(double t_deltaTime);
	float getX() { return x; }
	float getY() { return y; }
	float getWidth() { return width; }
	float getHeight() { return height; }

	void checkBounds();



private:
	float x = -1500; //Offsccreen First
	float y = 0;
	float width = 0;
	float height = 0;
	float speed = 200;
	int numberOfBlocks = 0;
};

