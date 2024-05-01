#include "Scene.hpp"

int Scene::screenWidth = 1280, Scene::screenHeight = 720;
ComponentManager* Scene::componentManager = nullptr;
EntityManager* Scene::entityManager = nullptr;
GLFWwindow* Scene::window = nullptr;