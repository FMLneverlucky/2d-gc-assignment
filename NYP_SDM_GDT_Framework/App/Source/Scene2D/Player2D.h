/**
 CPlayer2D
 @brief A class representing the player object
 By: Toh Da Jun
 Date: Mar 2020
 */
#pragma once

// Include Singleton template
#include "DesignPatterns\SingletonTemplate.h"

// Include GLEW
#ifndef GLEW_STATIC
#include <GL/glew.h>
#define GLEW_STATIC
#endif

// Include GLM
#include <includes/glm.hpp>
#include <includes/gtc/matrix_transform.hpp>
#include <includes/gtc/type_ptr.hpp>

// Include CEntity2D
#include "Primitives/Entity2D.h"

// Include the Map2D as we will use it to check the player's movements and actions
class CMap2D;

// Include Keyboard controller
#include "Inputs\KeyboardController.h"

// Include Physics2D
#include "Physics2D.h"

//Include Enemy2D

// Include AnimatedSprites
#include "Primitives/SpriteAnimation.h"

// Include InventoryManager
#include "InventoryManager.h"

// Include SoundController
#include "..\SoundController\SoundController.h"

class CPlayer2D : public CSingletonTemplate<CPlayer2D>, public CEntity2D
{
	friend CSingletonTemplate<CPlayer2D>;
public:

	// Init
	bool Init(void);

	// Reset
	bool Reset(void);

	// Update
	bool Update(const double dElapsedTime);

	// PreRender
	void PreRender(void);

	// Render
	void Render(void);

	// PostRender
	void PostRender(void);


	// Physics
	CPhysics2D cPhysics2D;


protected:
	const glm::vec2 vec2JumpSpeed = glm::vec2(0.0f, 250.0f);
	const glm::vec2 vec2WalkSpeed = glm::vec2(100.0f, 100.0f);
	const glm::vec2 vec2RunSpeed = glm::vec2(200.0f, 100.0f);
	const float knockback_speed = 150.f;

	const glm::vec2 vec2HalfSize = glm::vec2(12.5f, 12.5f);
	glm::vec2 vec2MovementVelocity;

	//glm::vec2 vec2OldIndex;

	// Handler to the CMap2D instance
	CMap2D* cMap2D;

	// Keyboard Controller singleton instance
	CKeyboardController* cKeyboardController;


	//CS: Animated Sprite
	CSpriteAnimation* animatedSprites;

	// Current colour
	glm::vec4 vec4ColourTint;

	// InventoryManager
	CInventoryManager* cInventoryManager;
	// InventoryItem
	CInventoryItem* cInventoryItem;

	// Handler to the CSoundController
	CSoundController* cSoundController;

	// Constructor
	CPlayer2D(void);

	// Destructor
	virtual ~CPlayer2D(void);
	
	// Check if the player is in mid-air
	//bool IsMidAir(void);

	//// Update Jump or Fall
	//void UpdateJumpFall(const double dElapsedTime = 0.0166666666666667);

	//player knockback destination
	glm::vec2 knockback_destination;

	bool fullyCharged;

	// Let player interact with the map
	void InteractWithMap(void);

	void LightToWedge(void);

	void Recharge();

	void InteractWithEnemy(void);

	bool InteractKey(void);

	// Update the health and lives
	void UpdateHealthLives(void);

	//check player wings status
	bool fullcharge_status(void);

	bool get_charge_status(void);

	void meterToWedge(void);
};

