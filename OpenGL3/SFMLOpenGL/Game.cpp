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
	std::cout << "One cube Point X: " << m_cubePoints[0][0].x << "Point Y: " << m_cubePoints[0][0].y << "One cube Point Z: " << m_cubePoints[0][0].z;
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
		   
	//glBegin(GL_TRIANGLE_FAN); {
	//	// Set OpenGL Vertices
	//	for (int i = 0; i < 6; i++)
	//	{
	//		glVertex3f(m_pyramidPoints[i].x, m_pyramidPoints[i].y, m_pyramidPoints[i].z);
	//		glColor3f(m_pyramidColors[i].x, m_pyramidColors[i].y, m_pyramidColors[i].z);		
	//	}
	//}
	//

	glBegin(GL_QUADS); {

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				glVertex3f(m_cubePoints[i][j].x, m_cubePoints[i][j].y, m_cubePoints[i][j].z);
				glColor3f(m_cubeColors[j].x, m_cubeColors[j].y, m_cubeColors[j].z);
			}
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
		

		MyMatrix xRotation;
		MyMatrix yRotation;
		MyMatrix zRotation;
		MyMatrix scaleMatrix;
		
		switch (event.key.code)
		{
		case sf::Keyboard::T:
			yRotation = MyMatrix::rotationAntiClockwiseY(rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);

				//m_pyramidPoints[i] = yRotation * m_pyramidPoints[i] ;

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = yRotation * m_cubePoints[i][j];
					}
				}

			}
			
			break;
		case sf::Keyboard::Y:
			yRotation = MyMatrix::rotationAntiClockwiseY(-rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);

				
				

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = yRotation * m_cubePoints[i][j];
					}
				}
				
			}
			break;

		case sf::Keyboard::G:
			xRotation = MyMatrix::rotationAntiClockwiseX(rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);


				/*m_pyramidPoints[i] = xRotation * m_pyramidPoints[i];*/

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = xRotation * m_cubePoints[i][j];
					}
				}

			}
			break;

		case sf::Keyboard::H:
			xRotation = MyMatrix::rotationAntiClockwiseX(-rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);


				//m_pyramidPoints[i] = xRotation * m_pyramidPoints[i];

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = xRotation * m_cubePoints[i][j];
					}
				}

			}
			break;
		case sf::Keyboard::V:
			zRotation = MyMatrix::rotationAntiClockwiseZ(rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);


				//m_pyramidPoints[i] = zRotation * m_pyramidPoints[i];

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = zRotation * m_cubePoints[i][j];
					}
				}

			}
			break;
		case sf::Keyboard::B:
			zRotation = MyMatrix::rotationAntiClockwiseZ(-rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);


				//m_pyramidPoints[i] = zRotation * m_pyramidPoints[i];

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = zRotation * m_cubePoints[i][j];
					}
				}

			}
			break;
		case sf::Keyboard::N:
			xRotation = MyMatrix::rotationAntiClockwiseX(-rotation);
			moveVector = { 0,-0.1,0 };
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						MyVector3 returningVector{ m_cubePoints[i][j] };
						MyMatrix toOrigin = MyMatrix::translationXY( MyVector3{ 0, 0, 0 } - m_cubePoints[i][j]);
						MyMatrix translateBack = MyMatrix::translationXY(returningVector);

						m_cubePoints[i][j] = toOrigin * m_cubePoints[i][j];
						//m_cubePoints[i][j] = xRotation * m_cubePoints[i][j];
						//m_cubePoints[i][j] = translateBack * m_cubePoints[i][j];
					}
				}
			break;

		case sf::Keyboard::M:
			zRotation = MyMatrix::rotationAntiClockwiseZ(-rotation);

			for (int i = 0; i < 6; i++)
			{
				MyVector3 originVector{ MyVector3{0,0,0} - m_pyramidPoints[i] };
				MyVector3 returningVector{ m_pyramidPoints[i] };

				MyMatrix translateToOrigin = MyMatrix::translationXY(originVector);
				MyMatrix translateBack = MyMatrix::translationXY(returningVector);


				//m_pyramidPoints[i] = zRotation * m_pyramidPoints[i];

				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						m_cubePoints[i][j] = zRotation * m_cubePoints[i][j];
					}
				}

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
				for (int j = 0; j < 4; j++)
				{
					m_cubePoints[i][j] = scaleMatrix * m_cubePoints[i][j];
				}
			}
			break;

		case sf::Keyboard::O:
			scaleMatrix = MyMatrix::scale(1.5);
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m_cubePoints[i][j] = scaleMatrix * m_cubePoints[i][j];
				}
			}
			break;

		default:
			break;
		}

		/*for (int i = 0; i < 6; i++)
		{
			m_pyramidPoints[i] += moveVector;
		}*/

		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_cubePoints[i][j] += moveVector;
			}
		}
	}
	
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

