#include "MyEntityManager.h"
using namespace Simplex;
//  MyEntityManager
MyEntityManager* MyEntityManager::m_pInstance = nullptr;
void MyEntityManager::Init(void)
{
	// Instantiate GameState

	// Instantiate World Entities
	// UI as well

	// Instantiate AI Entities

	// Instantiate Player Entities
	for (MyEntity* m_entity_list : m_entityList)
	{
		// Create Entities
		m_uEntityCount++;
	}
	
	// Set First States
}
void MyEntityManager::Release(void)
{
	// Delete Entities
}
MyEntityManager* MyEntityManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MyEntityManager();
	}
	return m_pInstance;
}
void MyEntityManager::ReleaseInstance()
{
	// Delete this Object
}
int Simplex::MyEntityManager::GetEntityIndex(String a_sUniqueID)
{
	// return entity context
	
	return -1;
}
//Accessors
Model* Simplex::MyEntityManager::GetModel(uint a_uIndex)
{
	// Get the Model Object with uInt
	
	return nullptr;
}
Model* Simplex::MyEntityManager::GetModel(String a_sUniqueID)
{
	// Get model object with string
	
	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(uint a_uIndex)
{
	// Get rigidbody with uinteger
	
	return nullptr;
}
RigidBody* Simplex::MyEntityManager::GetRigidBody(String a_sUniqueID)
{
	// get rigidbody with string
	
	return nullptr;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(uint a_uIndex)
{
	// get model matrix from uint
	
	return IDENTITY_M4;
}
matrix4 Simplex::MyEntityManager::GetModelMatrix(String a_sUniqueID)
{
	return IDENTITY_M4;
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, String a_sUniqueID)
{
	// Set Model Matrix
	// Update the Matrix of the Object
}
void Simplex::MyEntityManager::SetModelMatrix(matrix4 a_m4ToWorld, uint a_uIndex)
{
	// Set Model Matrix
	// Update the Matrix of the Object
}
//The big 3
MyEntityManager::MyEntityManager(){Init();}
MyEntityManager::MyEntityManager(MyEntityManager const& other){ }
MyEntityManager& MyEntityManager::operator=(MyEntityManager const& other) { return *this; }
MyEntityManager::~MyEntityManager(){Release();};
// other methods
void Simplex::MyEntityManager::Update(void)
{
	// Check Game Loop

	// AABB, etc.
}
void Simplex::MyEntityManager::AddEntity(String a_sFileName, String a_sUniqueID)
{
	// Create a new enitiy, enlisting new information with it
}
void Simplex::MyEntityManager::RemoveEntity(uint a_uIndex)
{
	// remove entity with uint
}
void Simplex::MyEntityManager::RemoveEntity(String a_sUniqueID)
{
	// remove entity with string
}
String Simplex::MyEntityManager::GetUniqueID(uint a_uIndex)
{
	return "";
}
MyEntity* Simplex::MyEntityManager::GetEntity(uint a_uIndex)
{
	return nullptr;
}
void Simplex::MyEntityManager::AddEntityToRenderList(uint a_uIndex, bool a_bRigidBody)
{
	// add to renderlist
}
void Simplex::MyEntityManager::AddEntityToRenderList(String a_sUniqueID, bool a_bRigidBody)
{
	// Add to RenderList
}