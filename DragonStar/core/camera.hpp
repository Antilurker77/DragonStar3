// ================================================================
//
// camera.hpp
// 
// Manages camera view, camera movement, and camera input.
//
// ================================================================

#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Camera {
public:
	
	// Default location is left corner at 0, 0.
	Camera(sf::Vector2f size);

	// Sets size and center.
	Camera(sf::Vector2f pos, sf::Vector2f size);

	// Returns the view.
	sf::View GetCamera();

	// Moves the camera to the designated positon.
	void SetPosition(sf::Vector2f pos);

	// Resizes the camera.
	void SetSize(sf::Vector2f size);

	// Sets the camera's zoom.
	void SetZoom(float cameraZoom);

	// Checks for input from player.
	void Interpolate(float intlop);

	// Adjusts camera speed based on how long it takes inbetween frames.
	void GetInput(sf::Event event);

	// Makes camera movement smooth.
	void Update(float secondsPerUpdate);

private:
	sf::View camera;
	float sensitivty = 400.f;
	float zoom = 1.f;
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f velocityPerUpdate = { 0.f, 0.f };

	sf::Vector2f currentPos;
	sf::Vector2f updatePos;



};
