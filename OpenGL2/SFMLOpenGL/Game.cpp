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
			processEvents(event);
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
	
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
		   
	glBegin(GL_TRIANGLE_FAN); {
		// Set OpenGL Vertices
		for (int i = 0; i < 6; i++)
		{
			glVertex3f(m_pyramidPoints[i].x, m_pyramidPoints[i].y, m_pyramidPoints[i].z);
			glColor3f(m_pyramidColors[i].x, m_pyramidColors[i].y, m_pyramidColors[i].z);		
		}
	}
	glEnd();

	
	
	window.display();
}

void Game::processEvents(Event event)
{
	if (event.type == Event::Closed)
	{
		isRunning = false;
	}
	MyVector3 moveVector{ 0,0,0 };

	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:
		

		MyMatrix yRotation;
		MyMatrix scaleMatrix;
		
		switch (event.key.code)
		{
		case sf::Keyboard::Left:
			yRotation = MyMatrix::rotationAntiClockwiseZ(rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);

				m_pyramidPoints[i] = translateToOrigin * m_pyramidPoints[i];
				m_pyramidPoints[i] = yRotation * m_pyramidPoints[i] ;
				m_pyramidPoints[i] = translateBack * m_pyramidPoints[i];
			}
			
			break;
		case sf::Keyboard::Right:
			yRotation = MyMatrix::rotationAntiClockwiseZ(-rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);

				m_pyramidPoints[i] = translateToOrigin * m_pyramidPoints[i];
				m_pyramidPoints[i] = yRotation * m_pyramidPoints[i];
				m_pyramidPoints[i] = translateBack * m_pyramidPoints[i];
			}
			break;
		case sf::Keyboard::W:
			moveVector = { 0,0.1,0 };					
			break;

		case sf::Keyboard::A:
			moveVector = { -0.1,0,0 };
			break;

		case sf::Keyboard::S:
			moveVector = { 0,-0.1,0 };
			break;

		case sf::Keyboard::D:
			moveVector = { 0.1,0,0 };
			break;

		case sf::Keyboard::I:
			scaleMatrix = MyMatrix::scale(0.5);
			for (int i = 0; i < 6; i++)
			{
				m_pyramidPoints[i] = scaleMatrix * m_pyramidPoints[i];				
			}
			break;

		case sf::Keyboard::O:
			scaleMatrix = MyMatrix::scale(1.5);
			for (int i = 0; i < 6; i++)
				for (int i = 0; i < 6; i++)
				{
					m_pyramidPoints[i] = scaleMatrix * m_pyramidPoints[i];
				}
			break;

		default:
			break;
		}

		for (int i = 0; i < 6; i++)
		{
			m_pyramidPoints[i] += moveVector;
		}
	}
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

