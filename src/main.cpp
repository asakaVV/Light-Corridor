#define GLFW_INCLUDE_NONE
#define _USE_MATH_DEFINES

#include "../third_party/glfw/include/GLFW/glfw3.h"
#include "../third_party/glad/include/glad/glad.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "3D_tools.hpp"
#include "menu.hpp"
#include "ball.hpp"
#include "wall.hpp"
#include "racket.hpp"
#include <vector>
#include "obstacle.hpp"

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

/* IHM flag */
static int flag_filaire = 0;
static int flag_animate_rot_scale = 0;
static int flag_animate_rot_arm = 0;

/* Gameplay flags */
static int flag_is_moving = 0;
static bool flag_is_grip = true;

static int choice = 0;

static float pos_x = 0.0;
static float pos_y = 0.0;

/* Error handling function */
void onError(int error, const char *description)
{
	std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow * /* window */, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setPerspective(60.0, aspectRatio, Z_NEAR, Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void onKey(GLFWwindow *window, int key, int /* scancode */, int action, int /* mods */)
{
	int is_pressed = (action == GLFW_PRESS);
	switch (key)
	{
	case GLFW_KEY_A:
	case GLFW_KEY_ESCAPE:
		if (is_pressed)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_F:
		if (is_pressed)
		{
			flag_filaire = !flag_filaire;
			std::cout << "Mode filaire : " << ((flag_filaire) ? "ON" : "OFF") << std::endl;
		}
		break;
	case GLFW_KEY_R:
		if (is_pressed)
			flag_animate_rot_arm = 1 - flag_animate_rot_arm;
		break;
	case GLFW_KEY_T:
		if (is_pressed)
			flag_animate_rot_scale = 1 - flag_animate_rot_scale;
		break;
	case GLFW_KEY_J:
		if (dist_zoom < 60.0f)
			dist_zoom *= 1.1;
		std::cout << "Zoom is " << dist_zoom << std::endl;
		break;
	case GLFW_KEY_I:
		if (dist_zoom > 1.0f)
			dist_zoom *= 0.9;
		std::cout << "Zoom is " << dist_zoom << std::endl;
		break;
	case GLFW_KEY_UP:
		if (phy > 2)
			phy -= 2;
		std::cout << "Phy : " << phy << std::endl;
		break;
	case GLFW_KEY_DOWN:
		if (phy <= 88.)
			phy += 2;
		std::cout << "Phy : " << phy << std::endl;
		break;
	case GLFW_KEY_LEFT:
		theta -= 5;
		break;
	case GLFW_KEY_RIGHT:
		theta += 5;
		break;
	case GLFW_KEY_O:
		if (is_pressed)
			choice = abs(choice - 2);
		break;
	case GLFW_KEY_K:
		if (is_pressed)
			choice = abs(choice - 1);
		break;
	case GLFW_KEY_L:
		if (is_pressed)
			choice = abs(choice - 2);
		break;
	case GLFW_KEY_M:
		if (is_pressed)
			choice = abs(choice - 1);
		break;
	default:
		std::cout << "Touche non gérée" << std::endl;
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "MOVE" << std::endl;
		flag_is_moving = 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		std::cout << "STOP" << std::endl;
		flag_is_moving = 0;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		flag_is_grip = false;
	}
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	double normalized_xpos = (2.0 * xpos / width - 1.0) * aspectRatio;
	double normalized_ypos = 1.0 - 2.0 * ypos / height;

	pos_x = std::max(std::min(10.0 * normalized_xpos, 8.), -8.0);
	pos_y = std::max(std::min(-10.0 * normalized_ypos, 4.0), -4.0);
}

int main(int /* argc */, char ** /* argv */)
{
	/* GLFW initialisation */
	GLFWwindow *window;
	if (!glfwInit())
		return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	glPointSize(5.0);
	glEnable(GL_DEPTH_TEST);

	Ball ball = Ball();
	std::vector<Wall> walls = {
		Wall({-500.0, 10.0, 0.0}, {1000.0, 1.0, 12.0}, 90.0, {0.0, 0.0, 0.7}, Wall::WallType::RIGHT),
		Wall({-500.0, -10.0, 0.0}, {1000.0, 1.0, 12.0}, 90.0, {0.0, 0.0, 0.7}, Wall::WallType::LEFT),
		Wall({-500.0, 0.0, 6.0}, {1000.0, 20.0, 1.0}, 0.0, {0.0, 0.0, 0.5}, Wall::WallType::TOP),
		Wall({-500.0, 0.0, -6.0}, {1000.0, 20.0, 1.0}, 0.0, {0.0, 0.0, 0.5}, Wall::WallType::BOTTOM)};
	std::vector<Obstacle> obstacles = {
		Obstacle(-0.0),
		Obstacle(-20.0),
		Obstacle(-40.0),
		Obstacle(-60.0),
		Obstacle(-80.0)};
	Racket racket = Racket();

	int width, height, nrChannels;
	auto image = stbi_load("../assets/wave.jpg", &width, &height, &nrChannels, 0);

	if (image == nullptr)
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Image loaded with width: " << width << " and height: " << height << std::endl;
	}

	uint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (flag_filaire)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Initial scenery setup */
		glPushMatrix();
		glTranslatef(0.0, 0.0, -0.01);
		glScalef(10.0, 10.0, 1.0);
		glColor3f(0.0, 0.0, 0.1);
		// drawSquare();
		glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glEnd();
		glPopMatrix();

		/* Scene rendering */
		draw_scene();
		if (choice == 0)
		{
			glPushMatrix();
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glPushMatrix();
			glTranslatef(-2.5, 0., 0.);
			if (pos_x > -4.5 && pos_x < -0.5 && pos_y > -1. && pos_y < 1.)
			{
				draw_hover_button();
			}
			else
			{
				draw_button();
			}
			glPopMatrix();
			glPushMatrix();
			glTranslatef(2.5, 0., 0.);
			if (pos_x > 0.5 && pos_x < 4.5 && pos_y > -1. && pos_y < 1.)
			{
				draw_hover_button();
			}
			else
			{
				draw_button();
			}
			glPopMatrix();
			glPopMatrix();
		}
		else
		{
			racket.draw();
			glEnable(GL_TEXTURE_2D);
			ball.draw();
			glDisable(GL_TEXTURE_2D);
			for (auto wall : walls)
			{
				wall.draw();
			}
			for (auto obstacle : obstacles)
			{
				obstacle.draw();
			}
		}

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
		}

		// Move
		racket.move(pos_y, pos_x, 0.);
		if (ball.get_grip() && !flag_is_grip)
		{
			ball.set_grip(false);
		}
		if (ball.get_grip())
		{
			ball.move(0., pos_x, -pos_y);
		}
		else
		{
			ball.update();
		}
		if (flag_is_moving)
		{
			ball.move_with_delta(0.3);
			for (auto &obstacle : obstacles)
			{
				obstacle.move(0.3);
			}

			obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle &obstacle)
										   { return obstacle.has_to_despawn(); }),
							obstacles.end());
		}

		// Collision detection
		for (auto &wall : walls)
		{
			wall.collide(ball);
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture);
	stbi_image_free(image);

	glfwTerminate();
	return 0;
}
