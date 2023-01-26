#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

using namespace std;
using namespace sf;

enum class Shapes
{
	Point,
	Lines,
	LineStrip,
	LineLoop,
	Triangle,
	TriangleStrip,
	TriangleFan,
	Quads,
	QuadStrip,
	Polygon,
	Cube
};

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
	void unload();

	Shapes m_currentShape = Shapes::Cube;
	 // Uncomment for Part 2
	 // ********************
	 const int primatives;

	GLuint index;
	Clock clock;
	Time elapsed;

	bool flip{ false };
	int current = 1;

	float rotationAngle = 0.0f;
	 // ********************
};