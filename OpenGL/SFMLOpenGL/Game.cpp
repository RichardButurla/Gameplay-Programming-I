#include <Game.h>

Game::Game() : window(VideoMode(800, 600), "OpenGL")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x /
		window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	

	cout << "Update up" << endl;
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	switch (m_currentShape)
	{
	case Shapes::Point:
		break;
	case Shapes::Lines:
		break;
	case Shapes::LineStrip:
		break;
	case Shapes::LineLoop:
		break;
	case Shapes::Triangle:
		glBegin(GL_TRIANGLES); {
			glVertex3f(0.0, 2.0, -5.0);
			glVertex3f(-2.0, -2.0, -15.0);
			glVertex3f(2.0, -2.0, -10.0);
		}
		glEnd();
		break;
	case Shapes::TriangleStrip:
		break;
	case Shapes::TriangleFan:
		break;
	case Shapes::Quads:
		break;
	case Shapes::QuadStrip:
		break;
	case Shapes::Polygon:
		break;
	default:
		break;
	}

	
	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}
