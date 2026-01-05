#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
//int argc, char* argv[]
int main(){

  glfwInit();
/*
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  */

  GLFWwindow* window = glfwCreateWindow(800, 800, "test", NULL, NULL);

  if (window == NULL) {
    printf("failed to create window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 800);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
