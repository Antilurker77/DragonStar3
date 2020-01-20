// ================================================================
//
// camera.cpp
//
// ================================================================

#include "camera.hpp"

#include <iostream>
#include "settings.hpp"

Camera::Camera(sf::Vector2f size) {
	camera.setSize(size);
	camera.setCenter(sf::Vector2f(size.x / 2, size.y / 2));
	updatePos = camera.getCenter();
}

Camera::Camera(sf::Vector2f pos, sf::Vector2f size) {
	camera.setSize(size);
	camera.setCenter(pos);
	updatePos = pos;
}

sf::View Camera::GetCamera() {
	return camera;
}

void Camera::SetPosition(sf::Vector2f pos) {
	camera.setCenter(pos);
	currentPos = pos;
	updatePos = pos;
	velocity = { 0.f, 0.f };
	velocityPerUpdate = { 0.f, 0.f };
}

void Camera::SetSize(sf::Vector2f size) {
	camera.setSize(size);
}

void Camera::SetZoom(float cameraZoom) {
	camera.zoom(1.f / zoom);
	camera.zoom(cameraZoom);
	zoom = cameraZoom;
}

void Camera::GetInput(sf::Event event) {
	velocity = { 0.f, 0.f };
	velocityPerUpdate = { 0.f, 0.f };
	
	// Repeats while key is held down.
	if (sf::Keyboard::isKeyPressed(settings.CameraKeybinds.CameraUp)) {
		velocity.y -= sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(settings.CameraKeybinds.CameraRight)) {
		velocity.x += sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(settings.CameraKeybinds.CameraDown)) {
		velocity.y += sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(settings.CameraKeybinds.CameraLeft)) {
		velocity.x -= sensitivty * zoom;
	}
	if (sf::Keyboard::isKeyPressed(settings.CameraKeybinds.ResetZoom)) {
		camera.zoom(1.f / zoom);
		zoom = 1.f;
	}

	if (event.type == sf::Event::MouseWheelScrolled) {
		//std::cout << "mouse wheel scroll: " << event.mouseWheelScroll.delta << "\n"; // this line stops the camera from infinitely zooming and I have no idea why SFML plz
		// up -- zoom in
		//if (event.mouseWheelScroll.delta == 1) {
		//	if (zoom == 0.5f) {
		//		camera.zoom(1.f / zoom);
		//		camera.zoom(1.f / 3.f);
		//		zoom = 1.f / 3.f;
		//	}
		//	else if (zoom == 1.f) {
		//		camera.zoom(0.5f);
		//		zoom = 0.5f;
		//	}
		//}
		//// down -- zoom out
		//if (event.mouseWheelScroll.delta == -1) {
		//	if (zoom == 1.f / 3.f) {
		//		camera.zoom(1.f / zoom);
		//		camera.zoom(0.5f);
		//		zoom = 0.5f;
		//	}
		//	else if (zoom == 0.5f) {
		//		camera.zoom(1.f / zoom);
		//		zoom = 1.f;
		//	}
		//}
	}
}

void Camera::Update(float secondsPerUpdate) {
	camera.setCenter(updatePos);
	
	velocityPerUpdate = { std::roundf(velocity.x * secondsPerUpdate), std::roundf(velocity.y * secondsPerUpdate) };
	//velocityPerUpdate = { velocity.x * secondsPerUpdate, velocity.y * secondsPerUpdate };
	
	updatePos.x += velocityPerUpdate.x;
	updatePos.y += velocityPerUpdate.y;

	currentPos = camera.getCenter();
}

void Camera::Interpolate(float intlop) {
	//camera.setCenter(sf::Vector2f(std::roundf(currentPos.x + velocityPerUpdate.x * intlop), std::roundf(currentPos.y + velocityPerUpdate.y * intlop)));
	camera.setCenter(sf::Vector2f(currentPos.x + velocityPerUpdate.x * intlop, currentPos.y + velocityPerUpdate.y * intlop));
}