//
// Created by montgomery anderson on 30/06/17.
//

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Camera.h"


Camera::Camera() {

}


Camera::Camera(glm::vec3 pos, glm::vec3 upDir, glm::vec3 viewDir)
        : pos(pos), upDir(upDir), viewDir(viewDir) {

}


glm::mat4 Camera::getViewMatrix() {
    viewPt = pos + viewDir;
    return glm::lookAt(pos, viewPt, upDir);
}


void Camera::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveForward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        strafeLeft();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveBackwards();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        strafeRight();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        moveUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        moveDown();
}


void Camera::moveForward() {
    pos += viewDir * DIRECTIONAL_SPEED;
}


void Camera::moveBackwards() {
    pos -= viewDir * DIRECTIONAL_SPEED;
}


void Camera::strafeLeft() {
    pos += glm::normalize(glm::cross(upDir, viewDir)) * LATERAL_SPEED;
}


void Camera::strafeRight() {
    pos -= glm::normalize(glm::cross(upDir, viewDir)) * LATERAL_SPEED;
}


void Camera::moveUp() {
    pos += upDir * VERTICAL_SPEED;
}


void Camera::moveDown() {
    pos -= upDir * VERTICAL_SPEED;
}
