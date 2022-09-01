#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GLFW/glfw3.h>

#include "shapes.h"
// #include "vector2.h"
#include "enemy.h"
#include "stats.h"
#include "text.h"

static void mouse_position_callback(GLFWwindow* window, double x, double y);
static void mouse_button_callback  (GLFWwindow* window, int button, int action, int mods);
static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Vector2 mouse;
Player player;

int width = 600,
    height = 400;

GLFWwindow* window;

bool gameLost = false, imagesEnabled = false, debug = false;;

Enemy EM_enemies[48];

const char* base_path = "";

double randf(){
    return rand() / (float) RAND_MAX;
}

int main(void){

    time_t t;
    srand((unsigned) time(&t));

    if (!glfwInit())
        return -1;
    puts("Game started!");
    window = glfwCreateWindow(width, height, "Asteroids C", NULL, NULL);
    glfwMakeContextCurrent(window);
    // #################################################################

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glOrtho(0, width, height, 0, 1.0, -1.0); // p5 proj mat thing yeap

    player = new_Player(new_Vector2(width / 2, height / 2));

    EM_init();
    Stats_init();

    // puts(someText.text);
    while (!glfwWindowShouldClose(window)){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSetCursorPosCallback(window, mouse_position_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        glfwSetKeyCallback(window, keyboard_callback);
        
        draw(&player);

        EM_trySpawn();
        EM_tick();

        if(FRAME_COUNT % 10 == 0){
            Stats_update();
            Stats_draw();
        }

        int tw, th;
        glfwGetWindowSize(window, &tw, &th);
        if(tw != width || th != height){
            width = tw; height = th;
            glViewport(0, 0, width, height);
            player.pos = _mul(new_Vector2(width, height), v(0.5));
            
            glLoadIdentity();
            glOrtho(0, width, height, 0, 1.0, -1.0); // p5 proj mat thing yeap
            glMatrixMode(GL_MODELVIEW);
        }

        FRAME_COUNT ++;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return (0);
}

static void mouse_position_callback(GLFWwindow* window, double x, double y) {
    mouse.x = x;
    mouse.y = y;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        shoot(&player);
}

static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F3 && action == GLFW_RELEASE)
        debug = !debug;
}