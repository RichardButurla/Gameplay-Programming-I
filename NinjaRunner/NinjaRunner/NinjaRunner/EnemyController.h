#pragma once
class EnemyController
{
public:
	EnemyController(float t_x, float t_y, float t_width, float t_height, int t_numberOfBlocks);
	EnemyController();
	~EnemyController();

	void update(double t_deltaTime);

	float getX() { return x; }
	float getY() { return y; }

	void setX(float t_x) { x = t_x; }
	void setY(float t_y) { y = t_y; }




private:
	float x = 300; //Offsccreen First
	float y = 20;
	float width = 0;
	float height = 0;
	float speed = 200;
};

