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
		glBegin(GL_POINT); {
			glVertex3f(0.0, 0.0, -5.0);
			glVertex3f(2.0, 0.0, -5.0);
		}
		glEnd();
		break;
	case Shapes::Lines:
		glBegin(GL_LINES); {
			glVertex3f(0.0, 0.0, -5.0);
			glVertex3f(1.0, 0.0, -5.0);
			//
			glVertex3f(1.0, 0.0, -5.0);
			glVertex3f(1.0, 1.0, -5.0);
			//

			glVertex3f(1.0, 1.0, -5.0);
			glVertex3f(-1.0, 1.0, -5.0);
		}
		glEnd();
		break;
	case Shapes::LineStrip:
		glBegin(GL_LINE_STRIP); {
			glVertex3f(0.0, 0.0, -5.0);
			glVertex3f(1.0, 0.0, -5.0);
			glVertex3f(1.0, -1.0, -5.0);
			glVertex3f(0.0, -1.0, -5.0);
			glVertex3f(-2.0, -1.0, -5.0);
			glVertex3f(-2.0, 0.0, -5.0);
			
		}
		glEnd();
		break;
	case Shapes::LineLoop:
		glBegin(GL_LINE_LOOP); {
			glVertex3f(0.0, 0.0, -5.0);
			glVertex3f(2.0, 0.0, -5.0);
			glVertex3f(1.0, -1.0, -5.0);
			glVertex3f(-1.0, -1.0, -5.0);
		}
		glEnd();

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
		glBegin(GL_TRIANGLE_STRIP); {
			glVertex3f(0.0, 2.0, -5.0);
			glVertex3f(-2.0, -2.0, -8.0);
			glVertex3f(2.0, -2.0, -10.0);
			glVertex3f(2.0, 2.0, -13.0);
			glVertex3f(-2.0, 2.0, -15.0);

		}
		glEnd();
		break;
	case Shapes::TriangleFan:
		glBegin(GL_TRIANGLE_FAN); {
			glVertex3f(0.0, 2.0, -5.0);
			glVertex3f(-1.0, 0.0, -5.0);
			glVertex3f(1.0, 0.0, -5.0);
			glVertex3f(0, -1.0, -5.0);
			glVertex3f(-1, 1, -5.0);
			glVertex3f(1, 1, -5.0);
		}
		glEnd();
		break;
	case Shapes::Quads:
		glBegin(GL_QUADS); {
			glVertex3f(-1.0, 1.0, -5.0);
			glVertex3f(1.0, 1.0, -5.0);
			glVertex3f(1.0, -1.0, -5.0);
			glVertex3f(-1.0, -1.0, -5.0);
			
		}
		glEnd();
		break;
	case Shapes::QuadStrip:
		glBegin(GL_QUAD_STRIP); {
			glVertex3f(-2.0f, -2.0f, -10.0f);
			glVertex3f(-2.0f, 2.0f, -10.0f);
			glVertex3f(0.0f, -2.0f, -10.0f);
			glVertex3f(0.0f, 2.0f, -10.0f);
		}		 
		glEnd();
		break;
	case Shapes::Polygon:
		glBegin(GL_POLYGON); {
		glVertex3f(0.0, 2.0, -5.0);
		glVertex3f(1.0, 1.5, -5.0);
		glVertex3f(1.5, 1, -5.0);
		glVertex3f(2.0, 0, -5.0);
		//
		glVertex3f(1.5, -1, -5.0);
		glVertex3f(1.0, -1.5, -5.0);
		glVertex3f(0, -2, -5.0);
		//
		glVertex3f(-1.0, -1.5, -5.0);
		glVertex3f(-1.5, -1, -5.0);
		glVertex3f(-2.0, 0, -5.0);
		//
		glVertex3f(-1.5, 1, -5.0);
		glVertex3f(-1.0, 1.5, -5.0);
		glVertex3f(0, 2, -5.0);
		
		}
		glEnd();
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

