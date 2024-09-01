#pragma once

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <string>

#define NEVER_COPY(T)                                                          \
  T(const T &) = delete;                                                       \
  T &operator=(const T &) = delete;

std::string loadFileIntoString(const std::string &filePath);
void printMaterial(const aiMaterial *material);
void printVertices(const aiMesh *mesh);
void printNormals(const aiMesh *mesh);
void printTexCoords(const aiMesh *mesh);
void printFaces(const aiMesh *mesh);
void printNode(aiNode *node, const aiScene *scene);
void printMatrix(const glm::mat4 &m);
glm::vec3 getCameraPos(const glm::mat4 &viewMatrix);
void zoomCamera(glm::mat4 &viewMatrix, glm::vec3 &target, float zoomAmount);
void orbitYaw(glm::mat4 &viewMatrix, glm::vec3 &target, float amount);
void orbitPitch(glm::mat4 &viewMatrix, glm::vec3 &target, float amount);
void rotateYaw(glm::mat4 &viewMatrix, float amount);
void rotatePitch(glm::mat4 &viewMatrix, float amount);
void slideView(glm::mat4 &viewMatrix, glm::vec3 &target, float xAmount,
               float yAmount);
void moveAlongCameraAxes(glm::mat4 &viewMatrix, glm::vec3 translation);