#include "AppClass.h"
#include "../C04_ShaderCompiler/AppClass.h"

void Application::InitVariables(void)
{
	// VERY MESSY WILL FIX
	//If you don't need them jsut move it to InitRacetrack - Michael
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

	InitRacetrack();
	
}
void Application::InitRacetrack(void)
{
	//making hoops, I'm storing the inner and outer radius for collision detection
	fInnerRad = 2.75f;
	fOuterRad = 3.0f;

	
	for (int i = 0; i < 10; i++)
	{
		//just gonna make a giant line of them, we can put in better positions later
		v3HoopPositions[i] = vector3(0.0f, 0.0f, 20.0f * (i + 1));
		MyMesh* tempMesh = new MyMesh();
		if(i == 0)
			tempMesh->GenerateTube(fOuterRad, fInnerRad, 0.25f, 10, C_GREEN);
		else if(i == 9)
			tempMesh->GenerateTube(fOuterRad, fInnerRad, 0.25f, 10, C_RED);
		else
			tempMesh->GenerateTube(fOuterRad, fInnerRad, 0.25f, 10, C_BLUE);
		mHoops[i] = tempMesh;
	}

	//place hoops at correct locations
	for (int i = 0; i < 10; i++)
	{
		mHoops[i]->m_m4Model = glm::translate(mHoops[i]->m_m4Model, v3HoopPositions[i]);
	}
	
}
void Application::ProcessKeyboard(sf::Event a_event)
{

	if (a_event.key.code == sf::Keyboard::Key::Escape)//Event says I pressed the Escape key
		m_bRunning = false;

	float fAccel = 0.01f; //Added accel
	float fSpeed = 0.1f;
	float fMultiplier = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

	if (fMultiplier)
		fSpeed *= 5.0f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		boardMesh->boardVelocity.x += -fAccel;
		//boardMesh->boardPosition.x += -fSpeed;  // Don't do position here
		//boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, vector3(-fSpeed, 0.0f, 0.0f));  //Move this to the end
	}
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { boardMesh->boardVelocity.x += +fAccel; }
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { boardMesh->boardVelocity.z += -fAccel; }
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {	boardMesh->boardVelocity.z += +fAccel; }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {	boardMesh->boardVelocity.y += +fAccel; }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) { boardMesh->boardVelocity.y += -fAccel; }

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

	
	//if (!startedRace) { startedRace = true; }
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	//ArcBall();

	
	
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
	
	CheckRaceProgress();

	//Updating velocity here cause I don't want to mess with too much
	//TODO

	//adjust velocity vector to forward vector of Mat4
	//(not done)


	//apply velocity vector to model matrix and positon vector
	boardMesh->boardPosition += boardMesh->boardVelocity;
	boardMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, boardMesh->boardVelocity);


	//adjust camera
	vector3 newCamera = boardMesh->boardPosition - vector3(0, -2, 7);
	vector3 newPlayer = playerMesh->boardPosition + vector3(0, .5f, -1);
	playerMesh->m_m4Model = glm::translate(boardMesh->m_m4Model, newPlayer);
	m_pCameraMngr->SetPositionTargetAndUpward(newCamera, boardMesh->boardPosition, AXIS_Y);



}
void Application::CheckRaceProgress(void)
{
	/*
	Just doing a sphere trace between player position and the center of each hoop
	Its technically possible to cheat here, but I'm just trying to get it to work
	We're only going to check against the current target hoop to A: avoid people skipping ahead
	And B: Vastly reduce the number of calculation we need to do
	*/

	float disX = (boardMesh->boardPosition.x - v3HoopPositions[hoopNum].x) * (boardMesh->boardPosition.x - v3HoopPositions[hoopNum].x);
	float disY = (boardMesh->boardPosition.y - v3HoopPositions[hoopNum].y) * (boardMesh->boardPosition.y - v3HoopPositions[hoopNum].y);
	float disZ = (boardMesh->boardPosition.z - v3HoopPositions[hoopNum].z) * (boardMesh->boardPosition.z - v3HoopPositions[hoopNum].z);

	//squaring is being werid here, hense the layout
	float crntDist = glm::sqrt(disX + disY + disZ);

	if (crntDist < fInnerRad)
	{
		if (hoopNum == 0)
		{
			//start race in the first hoop
			startedRace = true;
		}
		if (hoopNum < 9)
		{
			//update for each one farther along
			hoopNum++;
		}
		else
		{
			completedRace = true;
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

	//Draw Hoops

	for (int i = 0; i < 10; i++)
	{
		mHoops[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), mHoops[i]->m_m4Model);
	}

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
	for (int i = 0; i < 10; i++)
	{
		if (mHoops[i] != nullptr)
		{
			delete mHoops[i];
			mHoops[i] = nullptr;
		}
			
	}
	SafeDelete(boardMesh);
	//release GUI
	ShutdownGUI();
}