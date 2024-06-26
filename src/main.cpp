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
#include <thread>
#include "obstacle.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "random.hpp"
#include "bonus.hpp"
#include <algorithm>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 1000;
static const char WINDOW_TITLE[] = "The Light Corridor";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 60.;

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
	if ((key == GLFW_KEY_A || key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		flag_is_moving = 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		flag_is_moving = 0;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && choice == 1)
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

	Random::init();

	Ball ball = Ball();
	Ball life_ball = Ball();
	std::vector<Wall> walls = {
		Wall({-500.0, 10.0, 0.0}, {1000.0, 1.0, 12.0}, 90.0, {0.0, 0.0, 0.7}, Wall::WallType::RIGHT),
		Wall({-500.0, -10.0, 0.0}, {1000.0, 1.0, 12.0}, 90.0, {0.0, 0.0, 0.7}, Wall::WallType::LEFT),
		Wall({-500.0, 0.0, 6.0}, {1000.0, 20.0, 1.0}, 0.0, {0.0, 0.0, 0.5}, Wall::WallType::TOP),
		Wall({-500.0, 0.0, -6.0}, {1000.0, 20.0, 1.0}, 0.0, {0.0, 0.0, 0.5}, Wall::WallType::BOTTOM)};
	long level = 50;
	std::vector<Obstacle> obstacles;
	for (int i = 1; i < level; i++)
	{
		obstacles.push_back(Obstacle(-20 * i, i));
	}
	bool has_to_create = false;
	Racket racket = Racket();
	Player player = Player();
	std::vector<Bonus> bonus;
	for (int i = 1; i < 30; i++)
	{
		if (Random::get_int(1, 50) == 1)
			bonus.push_back(Bonus((i * -20) - 10, Random::get_int(-8, 8), Random::get_int(-4, 4), Random::get_int(1, 2)));
		else
		{
			bonus.push_back(Bonus((i * -20) - 10, 0, 0, 0));
		}
	}

	int width, height, nrChannels;
	int width2, height2, nrChannels2;
	int width3, height3, nrChannels3;
	int width4, height4, nrChannels4;
	int endw, endh, endc;
	auto ball_tex = stbi_load("../assets/steel.jpg", &width, &height, &nrChannels, 0);
	auto play_button = stbi_load("../assets/Play.jpg", &width2, &height2, &nrChannels2, 0);
	auto quit_button = stbi_load("../assets/Quit.jpg", &width3, &height3, &nrChannels3, 0);
	auto menu_tex = stbi_load("../assets/menu.jpg", &width4, &height4, &nrChannels4, 0);
	auto end_tex = stbi_load("../assets/end.jpg", &endw, &endh, &endc, 0);
	auto retry_button = stbi_load("../assets/Retry.jpg", &width2, &height2, &nrChannels2, 0);

	if (ball_tex == nullptr || play_button == nullptr || quit_button == nullptr || menu_tex == nullptr || end_tex == nullptr || retry_button == nullptr)
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}

	// digits loading
	int width5, height5, nrChannels5;
	int width6, height6, nrChannels6;
	int width7, height7, nrChannels7;
	int width8, height8, nrChannels8;
	int width9, height9, nrChannels9;
	int width10, height10, nrChannels10;
	int width11, height11, nrChannels11;
	int width12, height12, nrChannels12;
	int width13, height13, nrChannels13;
	int width14, height14, nrChannels14;
	auto tex_0 = stbi_load("../assets/digits/0.jpg", &width5, &height5, &nrChannels5, 0);
	auto tex_1 = stbi_load("../assets/digits/1.jpg", &width6, &height6, &nrChannels6, 0);
	auto tex_2 = stbi_load("../assets/digits/2.jpg", &width7, &height7, &nrChannels7, 0);
	auto tex_3 = stbi_load("../assets/digits/3.jpg", &width8, &height8, &nrChannels8, 0);
	auto tex_4 = stbi_load("../assets/digits/4.jpg", &width9, &height9, &nrChannels9, 0);
	auto tex_5 = stbi_load("../assets/digits/5.jpg", &width10, &height10, &nrChannels10, 0);
	auto tex_6 = stbi_load("../assets/digits/6.jpg", &width11, &height11, &nrChannels11, 0);
	auto tex_7 = stbi_load("../assets/digits/7.jpg", &width12, &height12, &nrChannels12, 0);
	auto tex_8 = stbi_load("../assets/digits/8.jpg", &width13, &height13, &nrChannels13, 0);
	auto tex_9 = stbi_load("../assets/digits/9.jpg", &width14, &height14, &nrChannels14, 0);

	if (tex_0 == nullptr || tex_1 == nullptr || tex_2 == nullptr || tex_3 == nullptr || tex_4 == nullptr || tex_5 == nullptr || tex_6 == nullptr || tex_7 == nullptr || tex_8 == nullptr || tex_9 == nullptr)
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}

	TextureObject texture_0 = TextureObject(tex_0, width5, height5);
	TextureObject texture_1 = TextureObject(tex_1, width6, height6);
	TextureObject texture_2 = TextureObject(tex_2, width7, height7);
	TextureObject texture_3 = TextureObject(tex_3, width8, height8);
	TextureObject texture_4 = TextureObject(tex_4, width9, height9);
	TextureObject texture_5 = TextureObject(tex_5, width10, height10);
	TextureObject texture_6 = TextureObject(tex_6, width11, height11);
	TextureObject texture_7 = TextureObject(tex_7, width12, height12);
	TextureObject texture_8 = TextureObject(tex_8, width13, height13);
	TextureObject texture_9 = TextureObject(tex_9, width14, height14);

	uint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Light
	GLfloat light_position[] = {20., 0., 0., 1.};
	GLfloat amb[] = {0.5, 0.5, 0.5, 0.5};
	GLfloat diff[] = {200 / 255., 200 / 255., 200 / 255.};
	GLfloat spec[] = {75 / 255., 75 / 255, 75 / 255};

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.);

	glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.);

	TextureObject texture_ball = TextureObject(ball_tex, width, height);
	TextureObject texture_play = TextureObject(play_button, width2, height2);
	TextureObject texture_quit = TextureObject(quit_button, width3, height3);
	TextureObject texture_menu = TextureObject(menu_tex, width4, height4);
	TextureObject texture_end = TextureObject(end_tex, endw, endh);
	TextureObject texture_retry = TextureObject(retry_button, width2, height2);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		setCamera();

		/* Scene rendering */

		if (choice == 0)
		{
			choice = draw_menu(texture_menu, texture_play, texture_quit, pos_x, pos_y, flag_is_moving);
		}
		else if (choice == 2)
		{
			break;
		}
		else if (choice == 3)
		{
			choice = drawEndMenu(player, texture_end, texture_quit, texture_retry, texture_0, texture_1, texture_2, texture_3, texture_4, texture_5, texture_6, texture_7, texture_8, texture_9, pos_x, pos_y, flag_is_moving);
			if (choice == 1)
			{
				level = 50;
				obstacles.clear();
				for (int i = 1; i < level; i++)
				{
					obstacles.push_back(Obstacle(-20 * i, i));
				}
				has_to_create = false;
				bonus.clear();
				for (int i = 1; i < 30; i++)
				{
					if (Random::get_int(1, 50) == 1)
						bonus.push_back(Bonus((i * -20) - 10, Random::get_int(-8, 8), Random::get_int(-4, 4), Random::get_int(1, 2)));
					else
					{
						bonus.push_back(Bonus((i * -20) - 10, 0, 0, 0));
					}
				}
			}
		}
		else if (choice == 1)
		{
			glPushMatrix();
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glColor3f(1., 1., 1.);
			glTranslatef(20., 0., 0.);
			glScalef(0.1, 0.1, 0.1);
			glRotatef(90, 0, 1, 0);
			drawSphere();
			glPopMatrix();
			ball.drawTex(texture_ball);

			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

			for (auto wall : walls)
			{
				wall.draw();
			}
			for (auto obstacle : obstacles)
			{
				obstacle.draw();
			}

			for (auto bonus_ : bonus)
			{
				bonus_.draw();
			}

			glDisable(GL_LIGHTING);
			racket.draw();
			// display life && score
			player.drawPlayer(texture_0, texture_1, texture_2, texture_3, texture_4, texture_5, texture_6, texture_7, texture_8, texture_9, life_ball, texture_ball);
			if (flag_is_grip && !ball.get_grip())
			{
				Bonus bonus_pickup = Bonus(0, 8., -8., 2);
				glPushMatrix();
				glColor3f(1., 1., 1.);
				bonus_pickup.draw();
				glPopMatrix();
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
			double remainingTime = FRAMERATE_IN_SECONDS - elapsedTime;
			if (remainingTime > 0)
			{
				std::this_thread::sleep_for(std::chrono::duration<double>(remainingTime));
			}
		}

		// Move
		if (choice == 1)
		{
			racket.move(pos_y, pos_x, 0.);
			if (ball.get_grip() && !flag_is_grip)
			{
				ball.set_speed(-1., 0., 0.);
				ball.set_grip(false);
			}
			if (ball.get_grip())
			{
				ball.move(-1., pos_x, -pos_y);
			}
			else
			{
				ball.update();
			}
			float limit = -2.0;
			if (ball.get_x() > -2.0)
			{
				limit = -4;
			}
			if (!ball.get_grip() && flag_is_moving && !Obstacle::do_any_collide(obstacles, racket, limit))
			{
				ball.move_with_delta(1.0);
				for (auto &obstacle : obstacles)
				{
					if (obstacle.move(1.0))
					{
						player.add_score(1);
						has_to_create = true;
					}
				}
				for (auto &bonus_ : bonus)
				{
					bonus_.move(1.0);
				}

				obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const Obstacle &obstacle)
											   { return obstacle.has_to_despawn(); }),
								obstacles.end());
				bonus.erase(std::remove_if(bonus.begin(), bonus.end(), [](const Bonus &bonus)
										   { return bonus.get_x() > 0; }),
							bonus.end());
			}

			if (has_to_create)
			{
				obstacles.push_back(Obstacle(obstacles.back().get_depth() - 20.0, level));
				level++;
				has_to_create = false;
			}

			if (bonus.size() < 29)
			{
				if (Random::get_int(1, 50) == 1)
					bonus.push_back(Bonus(bonus.back().get_x() - 20, Random::get_int(-8, 8), Random::get_int(-4, 4), Random::get_int(1, 2)));
				else
				{
					bonus.push_back(Bonus(bonus.back().get_x() - 20, 0, 0, 0));
				}
			}

			for (auto &obstacle : obstacles)
			{
				obstacle.evolve();
			}

			// Collision detection
			if (!ball.get_grip())
			{
				if (racket.collide(ball) && flag_is_grip && !ball.get_grip())
				{
					ball.set_grip(true);
				}
				for (auto &wall : walls)
				{
					wall.collide(ball);
				}
				for (auto &obstacle : obstacles)
				{
					obstacle.collide(ball);
				}
				for (auto &bonus_ : bonus)
				{
					int bonus_get = bonus_.collide(racket);
					if (bonus_get == 1 && player.get_life() < 5)
					{
						player.set_life(player.get_life() + 1);
					}
					else if (bonus_get == 2 && !flag_is_grip)
					{
						flag_is_grip = true;
					}
				}
			}
			for (auto &wall : walls)
			{
				for (auto &obstacle : obstacles)
				{
					obstacle.collide(wall);
				}
			}

			float ball_x, ball_y, ball_z;
			ball.get_position(ball_x, ball_y, ball_z);

			if (ball_x > 1.)
			{
				player.set_life(player.get_life() - 1);
				ball.set_grip(true);
				flag_is_grip = true;
				ball.move(-1., pos_x, -pos_y);
			}
			if (player.get_life() < 0)
			{
				choice = 3;
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &texture);
	stbi_image_free(ball_tex);
	stbi_image_free(play_button);
	stbi_image_free(quit_button);
	stbi_image_free(menu_tex);
	stbi_image_free(tex_0);
	stbi_image_free(tex_1);
	stbi_image_free(tex_2);
	stbi_image_free(tex_3);
	stbi_image_free(tex_4);
	stbi_image_free(tex_5);
	stbi_image_free(tex_6);
	stbi_image_free(tex_7);
	stbi_image_free(tex_8);
	stbi_image_free(tex_9);
	stbi_image_free(end_tex);
	stbi_image_free(retry_button);

	glfwTerminate();
	return 0;
}
