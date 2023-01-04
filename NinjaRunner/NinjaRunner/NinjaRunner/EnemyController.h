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
	void setSpeed(float t_speed) { speed = t_speed; }

	bool isOffscreen();
	void trackPlayer(float t_x, float t_y);

	bool isTrackingPlayer() { return trackingPlayer; }
	bool isAttackingPlayer() { return attackingPlayer; }




private:
	float x = 0;
	float y = 00;
	float width = 0;
	float height = 0;
	float speed = 0;
	float chaseSpeed = 200;
	bool trackingPlayer{ false };
	bool attackingPlayer{ false };
};

