//
// Created by montgomery anderson on 6/07/17.
//

#include "GameState.h"

#include <glm/gtc/matrix_transform.hpp>
#include <core/world/Chunk.h>

#include "core/rendering/TextRenderer.h"
#include "core/Constants.h"
#include "extensions/text/NumericToString.h"


GameState::GameState(Engine *engine) : State(engine) {
}


GameState::~GameState() {
    delete camera;
}


int GameState::initialise() {
    timer = Timer::Start();

    camera = new Camera();

    // Initialise the world
    // TODO generation phase
    world = new World(constants::WORLD_DEPTH, constants::WORLD_WIDTH);

    return EXIT_SUCCESS;
}


void GameState::cleanup() {}


void GameState::pause() {}


void GameState::resume() {}


void GameState::handleEvents() {}


void GameState::processInput() {
    if (glfwGetKey(engine->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        engine->stop();
}


void GameState::cursorMoved(GLFWwindow *window, double xPos, double yPos){
    camera->cursorMoved(xPos, yPos);
}


void GameState::update() {
    this->processInput();
    camera->processInput(engine->window);

    // Update the world w.r.t. the camera position
    world->update(camera->pos);

    this->runTime = timer.str();
    this->cameraInfo = "camera info: " +
        extensions::toString(camera->pos, 2) + ", " +
        extensions::toString(camera->viewDir, 2) + ", " +
        extensions::toString(camera->upDir, 2);
    this->meshInfo = "mesh info: " +
        extensions::toString(world->chunkVerticesCount(), 0) + " vertices";

}


void GameState::draw() {
    // update matrices
    glm::mat4 model = glm::mat4(1.0);
    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), engine->aspectRatio(), 0.1f, 1000.0f);

    engine->worldRenderer->modelMatrix = model;
    engine->worldRenderer->viewMatrix = view;
    engine->worldRenderer->projectionMatrix = projection;
    engine->worldRenderer->cameraPosition = glm::vec4(camera->pos, 1.0f);
    // render terrain
    for (int z = 0; z < world->getDepth(); z++) {
        for (int x = 0; x < world->getWidth(); x++) {
            Chunk* chunk = world->getChunk(x, z);
            if (chunk != NULL)
                engine->worldRenderer->renderTerrain(chunk->mesh);
        }
    }

    // render state info
    engine->textRenderer->render(this->name, Font::DEFAULT, 14, glm::vec2(20, 40));
    engine->textRenderer->render(this->runTime, Font::DEFAULT, 14, glm::vec2(20, 60));
    engine->textRenderer->render(this->meshInfo, Font::DEFAULT, 12, glm::vec2(20, 80));
    engine->textRenderer->render(this->cameraInfo, Font::DEFAULT, 12, glm::vec2(20, 100));
}
