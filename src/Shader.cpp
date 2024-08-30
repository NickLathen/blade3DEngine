#include <iostream>

#include "Shader.hpp"
#include "utils.hpp"
#include <glm/ext.hpp>
#include <glm/glm.hpp>

Shader::Shader(const char *vertexPath, const char *fragPath) {
  const std::string vertexSource = loadFileIntoString(vertexPath);
  const std::string fragSource = loadFileIntoString(fragPath);
  const char *vertCStr = vertexSource.c_str();
  const char *fragCStr = fragSource.c_str();

  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // compile shaders
  const uint LOG_BUFFER_SIZE = 512;
  int success;
  char infoLog[LOG_BUFFER_SIZE]{};
  glShaderSource(vertexShader, 1, &vertCStr, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, LOG_BUFFER_SIZE, NULL, infoLog);
    throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" +
                             std::string{infoLog});
  }
  glShaderSource(fragmentShader, 1, &fragCStr, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, LOG_BUFFER_SIZE, NULL, infoLog);
    glDeleteShader(vertexShader);
    throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" +
                             std::string{infoLog});
  }

  // link program
  _program = glCreateProgram();
  glAttachShader(_program, vertexShader);
  glAttachShader(_program, fragmentShader);
  glLinkProgram(_program);
  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_program, LOG_BUFFER_SIZE, NULL, infoLog);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    throw std::runtime_error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" +
                             std::string{infoLog});
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  std::cout << "Loaded shaders:" << vertexPath << ", " << fragPath << std::endl;
};
Shader::~Shader() {
  if (_program != 0) {
    glDeleteProgram(_program);
  }
};

void Shader::useProgram() const { glUseProgram(_program); };

GLuint Shader::getAttribLocation(const std::string &attribName) const {
  return glGetAttribLocation(_program, attribName.c_str());
}

GLuint Shader::getUniformLocation(const std::string &uniformName) const {
  return glGetUniformLocation(_program, uniformName.c_str());
};

GLuint Shader::getUniformBlockIndex(const std::string &blockName) const {
  return glGetUniformBlockIndex(_program, blockName.c_str());
};

void Shader::setUniformBlockBinding(const std::string &blockName,
                                    GLuint uniformBlockBinding) const {
  GLuint uniformBlockIndex = getUniformBlockIndex(blockName);
  return glUniformBlockBinding(_program, uniformBlockIndex,
                               uniformBlockBinding);
};

void Shader::uniform3fv(const std::string &uniformName,
                        const glm::vec3 &value) const {
  glUniform3fv(getUniformLocation(uniformName), 1, glm::value_ptr(value));
};
void Shader::uniform4fv(const std::string &uniformName,
                        const glm::vec4 &value) const {
  glUniform4fv(getUniformLocation(uniformName), 1, glm::value_ptr(value));
};
void Shader::uniformMatrix4fv(const std::string &uniformName,
                              GLboolean transpose,
                              const glm::mat4 &value) const {
  glUniformMatrix4fv(getUniformLocation(uniformName), 1, transpose,
                     glm::value_ptr(value));
};
void Shader::uniform1f(const std::string &uniformName, float value) const {
  glUniform1f(getUniformLocation(uniformName), value);
};

void Shader::uniform1i(const std::string &uniformName, GLint value) const {
  glUniform1i(getUniformLocation(uniformName), value);
};
void Shader::uniform1ui(const std::string &uniformName, GLuint value) const {
  glUniform1ui(getUniformLocation(uniformName), value);
};