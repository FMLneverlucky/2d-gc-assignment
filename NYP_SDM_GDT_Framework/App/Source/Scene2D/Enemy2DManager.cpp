/**
 CEnemy2DManager
 By: Toh Da Jun
 Date: March 2023
 */
#include "Enemy2DManager.h"

#include <iostream>
using namespace std;

/**
 @brief Default Constructor
 */
CEnemy2DManager::CEnemy2DManager(void)
	: uiTotalElements(2)
	, uiIndexFirst(0)
	, uiIndexLast(0)
{
}

/**
 @brief Destructor
 */
CEnemy2DManager::~CEnemy2DManager(void)
{
	// Remove all CEnemy2D*
	for (unsigned int i = 0; i < vEnemy2D.size(); i++)
	{
		delete vEnemy2D[i];
		vEnemy2D[i] = NULL;
	}
	vEnemy2D.clear();
}

/**
 @brief Set a shader to this class instance
 @param _name The name of the Shader instance in the CShaderManager
 */
void CEnemy2DManager::SetShader(const std::string& _name)
{
	this->sShaderName = _name;
}

/**
 @brief Initialise this class instance
 @return A bool variable to indicate this method successfully completed its tasks
 */
bool CEnemy2DManager::Init(void)
{
	// Clear the vector
	vEnemy2D.clear();

	// Reserve the size of the vector
	vEnemy2D.reserve(uiTotalElements);

	// Create the instances of CEnemy2D* and store them in the vector
	for (unsigned int i = 0; i < uiTotalElements; i++)
	{
		CEntity2D* pointer_to_enemy;
		vEnemy2D.push_back(pointer_to_enemy);	//this remains same as framework because handling enemy types here is complicated 
	}
	return true;
}

/**
 @brief Activate a CEnemy2D* to this class instance
 @param vec3Position A const glm::vec3 variable containing the source position of the cEnemy2D
 @return A bool variable which is true if the CEnemy2D was activated successfully, otherwise false.
 */
bool CEnemy2DManager::Activate(glm::vec2 vec2Position, int& uiIndex, int enemy_type)
{
	//since all enemy is enemy2d class objects (push back in manager init), handle change of enemy class here?  (since going through class init [get texture] after this line)
	switch (enemy_type)
	{
	case 0: //enemy2d
		{
		
			vEnemy2D[uiIndexLast] = new CEnemy2D();
			//create new class object -> toss address of new object into placeholder?
			break;	
		}
	case 1:	//krab
		{
			vEnemy2D[uiIndexLast] = new CEnemyKrab(); //CEnemyKrab() <- linker error, have no idea why
			//i did scuffed fix referencing from the saviour website stackoverflow and included krab/shrimp files to be compiled in .vcxproj
			break;
		}
	case 2:	//shrimp
		{
			vEnemy2D[uiIndexLast] = new CEnemyShrimp(); //CEnemyShrimp() <- linking error LNK2019, have no idea why
			//eyeballing error output msg, guessing theres problem with this function being virtual and trying to access non virtual function [class::class()], even though enemy2d can run properly with same code O-|-<
			break;
		}
	default:
		{
			vEnemy2D[uiIndexLast] = new CEnemy2D();
			break;
		}
	}
	// Since a cEnemy2D has been added, we activate the next element in the vector
	vEnemy2D[uiIndexLast]->vec2Position = vec2Position;
	if (vEnemy2D[uiIndexLast]->Init() == false)	//if done properly, should go to respective class init (unlike whatever i was doing before it got deleted)
		return false;

	vEnemy2D[uiIndexLast]->SetShader(sShaderName);

	// Increase the uiIndexLast by 1 since a cEnemy2D is going to be added
	if (uiIndexLast + 1 == vEnemy2D.size())
		uiIndexLast = 0;
	else
		uiIndexLast++;

	uiIndex = uiIndexLast;	//passed in index value used to tie iteration of enemy to tile by address value (head empty, cant think of a better way to phrase at the moment yes)
	//replace address with current iteration of enemy address

	return true;
}

/**
 @brief Deactivate a CEnemy2D* from this class instance
 @param iIndex A const unsigned int variable containing the index of the cEnemy2D to deactivate
 @return A bool variable to indicate this method successfully completed its tasks
 */
bool CEnemy2DManager::Deactivate(const unsigned int iIndex)
{
	if (iIndex<vEnemy2D.size())
	{
		// Set the cEnemy2D to inactive
		vEnemy2D[iIndex]->SetStatus(false);
		// Return true
		return true;
	}

	// Return false if not found
	return false;
}

/**
 @brief Update this instance
 @param dElapsedTime A const double containing the elapsed time since the last frame
 */
void CEnemy2DManager::Update(const double dElapsedTime)
{
	uiIndexFirst = uiIndexLast + 1;
	if (uiIndexFirst >= vEnemy2D.size())
	{
		uiIndexFirst = 0;

		// CollisionCheck all projectiles against CSolidObject
		// Check the oldest index until the end of 
		for (unsigned int i = uiIndexFirst; i <= uiIndexLast; i++)
		{
			// If this cEnemy2D is not active, then skip it
			if (vEnemy2D[i]->GetStatus() == false)
				continue;

			// Update a cEnemy2D
			vEnemy2D[i]->Update(dElapsedTime);
		}
	}
	else
	{
		// CollisionCheck all projectiles against CSolidObject
		// Check the oldest index until the end of 
		for (unsigned int i = uiIndexFirst; i < vEnemy2D.size(); i++)
		{
			// If this cEnemy2D is not active, then skip it
			if (vEnemy2D[i]->GetStatus() == false)
				continue;

			// Update a cEnemy2D
			vEnemy2D[i]->Update(dElapsedTime);
		}

		// CollisionCheck all projectiles against CSolidObject
		for (unsigned int i = 0; i <= uiIndexLast; i++)
		{
			// If this cEnemy2D is not active, then skip it
			if (vEnemy2D[i]->GetStatus() == false)
				continue;

			// Update a cEnemy2D
			vEnemy2D[i]->Update(dElapsedTime);
		}
	}
}

/**
 @brief PreRender this class instance
 */
void CEnemy2DManager::PreRender(void)
{
}

/**
 @brief Render this class instance
 */
void CEnemy2DManager::Render(void)
{
	// Render all entities
	for (unsigned int i = 0; i < vEnemy2D.size(); i++)
	{
		// If this cEnemy2D is not active, then skip it
		if (vEnemy2D[i]->GetStatus() == false)
			continue;

		vEnemy2D[i]->PreRender();
		vEnemy2D[i]->Render();
		vEnemy2D[i]->PostRender();
	}
}

/**
 @brief PostRender this class instance
 */
void CEnemy2DManager::PostRender(void)
{
}

/**
 @brief PrintSelf
 */
void CEnemy2DManager::PrintSelf(void)
{
	cout << "===============================" << endl;
	cout << "CEnemy2DManager::PrintSelf()" << endl;
	cout << "-------------------------------" << endl;
	// Render all entities
	for (unsigned int i = 0; i < vEnemy2D.size(); i++)
	{
		cout << i << "\t: ";
		//vEnemy2D[i]->PrintSelf();
	}
	cout << "===============================" << endl;
}
