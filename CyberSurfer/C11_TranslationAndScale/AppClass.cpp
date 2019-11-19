#include "AppClass.h"
#include "BoxConstruct.h"

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  D degrees of rotation */
#define DEF_D 5

void Application::InitVariables(void)
{
	//init the meshes
	totemMesh = new MyMesh();
	m_sMesh = new MyMesh();
	
	vector3 vec_WHITE = vector3(1.0f,1.0f,1.0f);
	vector3 vec_CUSTOMCOLOR = vector3(0.5f,0.2f,1.0f);
	//m_sMesh->GenerateCuboid(vec_WHITE, vec_CUSTOMCOLOR);
	//m_pMesh->GenerateSphere(1.2f, 5, C_WHITE);

	// Create New BoxConstruct
	BoxConstruct* boxConstruct = new BoxConstruct();
	boxConstruct->CreateRowConstructs();
	box = *boxConstruct;
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}

void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));
	static float xvalue = -25.0f;
	static float yvalue = -0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(xvalue, 2.0f, 3.0f));
	//value += 0.01f;
	//matrix4 m4Model = m4Translate * m4Scale;

	matrix4 m4Model = m4Scale;

	totemMesh->Render(m4Projection, m4View, m4Model);
	m_sMesh->Render(m4Projection, m4View, m4Model);

	// Render Coordinates for BoxConstruct
	std::array<int, 11>* rowSelected = nullptr;
	if (initRender == false) {
		for (size_t i = 0; i < 8; i++)
		{
			// Get Box Construct Row
			BoxRow* row = box.constructRows[i];

			// Get Current Row Information
			switch (i)
			{
			case 0:
				rowSelected = &box.row1;
				break;
			case 1:
				rowSelected = &box.row2;
				break;
			case 2:
				rowSelected = &box.row3;
				break;
			case 3:
				rowSelected = &box.row4;
				break;
			case 4:
				rowSelected = &box.row5;
				break;
			case 5:
				rowSelected = &box.row6;
				break;
			case 6:
				rowSelected = &box.row7;
				break;
			case 7:
				rowSelected = &box.row8;
				break;
			default:
				break;
			}
			
			// Render Each Selected RowElement
			for (size_t i = 0; i < 11; i++)
			{
				int x = xvalue;
				int y = yvalue;

				m4Scale = glm::scale(IDENTITY_M4, vector3(.5f, .5f, .5f));
				m4Translate = glm::translate(IDENTITY_M4, vector3(x, y, 3.0f));
				m4Model = m4Scale;

				// Get Wanted Active Meshes
				int retrieveMesh = 0;
				if (rowSelected->at(i) == 1)
				{
					row->rowMeshes[retrieveMesh]->Render(m4Projection, m4View, m4Model);
					retrieveMesh++;
				}
				//xvalue += 1.0f;
			}
			xvalue = -25.0f;
			yvalue += 1.0f;
		}
		initRender = true;
	}

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
	SafeDelete(totemMesh);
	SafeDelete(m_sMesh);
	//! safe delete vectore data
	for (size_t i = 0; i < 8; i++)
	{
		SafeDelete(box.constructRows[i]);
	}

	//release GUI
	ShutdownGUI();
}