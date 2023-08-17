/**
 CEnemy2DManager
 By: Toh Da Jun
 Date: March 2023
 */
#pragma once

// Include SingletonTemplate
#include "DesignPatterns\SingletonTemplate.h"

// Include Enemy2D
#include "Enemy2D.h"

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include vector
#include <vector>

class CEnemy2DManager : public CSingletonTemplate<CEnemy2DManager>
{
	friend class CSingletonTemplate<CEnemy2DManager>;

public:
	// Set a shader to this class instance
	void SetShader(const std::string& _name);

	// Initialise this class instance
	bool Init(void);

	// Activate a CEnemy2D* to this class instance
	virtual bool Activate(glm::vec2 vec2Position, int& uiIndex, int enemy_type);
	// Deactivate a CEnemy2D* from this class instance
	virtual bool Deactivate(const unsigned int iIndex);

	// Update this class instance
	virtual void Update(const double dElapsedTime);

	// Render this class instance
	virtual void PreRender(void);

	// Render this class instance
	virtual void Render(void);

	// PostRender this class instance
	virtual void PostRender(void);

	// PrintSelf
	virtual void PrintSelf(void);

	// List of Enemies **IMPORTANT: DO NOT MAKE ANOTHER PLAYER (nothings going to happen but anyways)**
	std::vector<CEntity2D*> vEnemy2D;

protected:
	//making a enum so manager can handle diff enemy class cases
	enum TYPE
	{
		DEFAULT = 0,
		KRAB = 1,
		SHRIMP = 2,
		NUM_TYPE
	};
	// Name of Shader Program instance
	std::string sShaderName;

	// The total number of elements to reserve for the vector
	unsigned int uiTotalElements;
	// The index of the first active element in the vector to activate
	unsigned int uiIndexFirst;
	// The index of the last active element in the vector to activate
	unsigned int uiIndexLast;

	// Default Constructor
	CEnemy2DManager(void);
	// Destructor
	virtual ~CEnemy2DManager(void);
};
