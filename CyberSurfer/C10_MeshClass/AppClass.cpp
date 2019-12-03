#include "AppClass.h"
#include "../C04_ShaderCompiler/AppClass.h"

void Application::InitVariables(void)
{
	// VERY MESSY WILL FIX
	totemMesh = new MyMesh();
	totemMesh->GenerateTotem(2.0f, C_RED);
	totemMesh->m_m4Model = glm::translate(totemMesh->m_m4Model, vector3(-25.0f, 0.0f, 25.0f));

	totemMesh1 = new MyMesh();
	totemMesh1->GenerateTotem(2.0f, C_GREEN);
	totemMesh1->m_m4Model = glm::translate(totemMesh1->m_m4Model, vector3(25.0f, 0.0f, 25.0f));

	totemMesh2 = new MyMesh();
	totemMesh2->GenerateTotem(2.0f, C_BLUE);
	totemMesh2->m_m4Model = glm::translate(totemMesh2->m_m4Model, vector3(0.0f, 0.0f, 50.0f));

	totemMesh3 = new MyMesh();
	totemMesh3->GenerateTotem(2.0f, C_INDIGO);
	totemMesh3->m_m4Model = glm::translate(totemMesh3->m_m4Model, vector3(-25.0f, 0.0f, 75.0f));

	totemMesh4 = new MyMesh();
	totemMesh4->GenerateTotem(2.0f, C_ORANGE);
	totemMesh4->m_m4Model = glm::translate(totemMesh4->m_m4Model, vector3(25.0f, 0.0f, 75.0f));

	//Make MyMesh object
	boardMesh = new MyMesh();
	boardMesh->GenerateBoard(1.0f, C_WHITE);
	playerMesh = new MyMesh();
	playerMesh->GenerateCube(0.3f, C_RED);
	vector3 newPlayer = playerMesh->boardPosition + vector3(0, .5f, -1);
	playerMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, newPlayer);

}
void Application::ProcessKeyboard(sf::Event a_event)
{
	if (a_event.key.code == sf::Keyboard::Key::Escape)//Event says I pressed the Escape key
		m_bRunning = false;

	float fSpeed = 0.1f;
	float fMultiplier = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	if (fMultiplier)
		fSpeed *= 5.0f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		boardMesh->boardPosition.x += -fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(-fSpeed, 0.0f, 0.0f));
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		boardMesh->boardPosition.x += fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(fSpeed, 0.0f, 0.0f));
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		boardMesh->boardPosition.z += -fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(0.0f, 0.0f, -fSpeed));
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		boardMesh->boardPosition.z += fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(0.0f, 0.0f, fSpeed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		boardMesh->boardPosition.y += fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(0.0f, fSpeed, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
	{
		boardMesh->boardPosition.y += -fSpeed;
		boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(0.0f, -fSpeed, 0.0f));
	}

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		// pitch counterclockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(1.0f, 0.0f, 0.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		// pitch clockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(-1.0f, 0.0f, 0.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		// yaw counterclockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, 1.0f, 0.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		// yaw clockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, -1.0f, 0.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// roll counterclockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, 0.0f, 1.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		// roll clockwise
		quaternion q1;
		quaternion q2 = glm::angleAxis(glm::radians(359.9f), vector3(0.0f, 0.0f, -1.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		boardMesh->m_m4Model = glm::toMat4(qSLERP);
	}

	vector3 newCamera = boardMesh->boardPosition - vector3(0, 0, 5);
	vector3 newPlayer = playerMesh->boardPosition + vector3(0, .5f, -1);
	playerMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, newPlayer);
	m_pCameraMngr->SetPositionTargetAndUpward(newCamera, boardMesh->boardPosition, AXIS_Y);

	if (!startedRace)
	{
		startedRace = true;
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	//ArcBall();

	vector3 newCamera = boardMesh->boardPosition - vector3(0, -2, 7);
	m_pCameraMngr->SetPositionTargetAndUpward(newCamera, boardMesh->boardPosition, AXIS_Y);
	
	//Is the first person camera active?
	CameraRotation();
	
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			ProcessKeyboard(event);
		}
	}
	
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	totemMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), totemMesh->m_m4Model);
	totemMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), totemMesh1->m_m4Model);
	totemMesh2->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), totemMesh2->m_m4Model);
	totemMesh3->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), totemMesh3->m_m4Model);
	totemMesh4->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), totemMesh4->m_m4Model);

	//! Wanted Box Render
	boardMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), boardMesh->m_m4Model);
	playerMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), playerMesh->m_m4Model);
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (totemMesh != nullptr)
	{
		delete totemMesh;
		totemMesh = nullptr;
	}
	SafeDelete(boardMesh);
	//release GUI
	ShutdownGUI();
}