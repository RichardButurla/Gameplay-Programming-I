#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyVector3.h"
#include "Matrix.h"

using namespace std;
using namespace sf;



class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void processEvents(Event event);
	void unload();

	float rotation = 0.5f;

	MyVector3 m_cubePoints[6][4]
	{
		{//left
			{0,0,-5},
			{1,0,-5},
			{1,0,-6},
			{0,0,-6}
		},
		{//front
			{1,0,-5},
			{1,1,-5},
			{1,1,-6},
			{1,0,-6}
		},
		{//right
			{1,1,-5},
			{0,1,-5},
			{0,1,-6},
			{1,1,-6}
		},
		{//back
			{0,1,-5},
			{0,0,-5},
			{0,0,-6},
			{0,1,-6}
		},
		{//top
			{1,0,-6},
			{1,1,-6},
			{0,1,-6},
			{0,0,-6}
		},
		{//bottom
			{1,0,-5},
			{1,1,-5},
			{0,1,-5},
			{0,0,-5}
		},
	};

	MyVector3 m_cubeColors[4]
	{
		{1.0f, 0.0f, 0.0f},//V0(red)
		{0.0f, 1.0f, 0.0f}, //V1(green)
		{0.0f, 0.0f, 1.0f}, //V2(blue)
		{0.0f, 1.0f, 0.0f}, //V3(green)
	};

	MyVector3 m_pyramidPoints[6]
	{
		{0.0f, 1.0f, -15.0f},
		{-1.0f, -1.0f, -14.0f},
		{1.0f, -1.0f, -14.0f},
		{1.0f, -1.0f, -16.0f},
		{-1.0f, -1.0f, -16.0f},
		{-1.0f, -1.0f, -14.0f}
	};

	MyVector3 m_pyramidColors[6]
	{
		{1.0f, 0.0f, 0.0f},//V0(red)
		{0.0f, 1.0f, 0.0f}, //V1(green)
		{0.0f, 0.0f, 1.0f}, //V2(blue)
		{0.0f, 1.0f, 0.0f}, //V3(green)
		{0.0f, 0.0f, 1.0f}, //V4(blue)
		{0.0f, 1.0f, 0.0f} //V5(green)
	};

	//midpoint of pyramid which is the base point
	MyVector3 baseOfPyramid;
	MyVector3 centroidOfPyramid;

	float rotationAngle = 0.05f;
	 // ********************
};