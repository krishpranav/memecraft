//
// Created by Krisna Pranav on 21/12/25.
//

#include "Shader.hpp"
#include "engine/core/Logger.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSrc,
               const std::string& fragmentSrc) {

    unsigned int vs = compile(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fs = compile(GL_FRAGMENT_SHADER, fragmentSrc);

    if (vs == 0 || fs == 0) {
        Logger::log(LogLevel::Error, "Shader compilation failed");
        return;
    }

    programHandle = glCreateProgram();
    glAttachShader(programHandle, vs);
    glAttachShader(programHandle, fs);
    glLinkProgram(programHandle);

    checkLinkErrors(programHandle);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    if (programHandle != 0) {
        glDeleteProgram(programHandle);
        programHandle = 0;
    }
}

void Shader::bind() const {
    glUseProgram(programHandle);
}

void Shader::unbind() const {
    glUseProgram(0);
}

unsigned int Shader::compile(unsigned int type, const std::string& src) {
    unsigned int shader = glCreateShader(type);
    const char* csrc = src.c_str();

    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);

        Logger::log(
            LogLevel::Error,
            std::string("Shader compile error: ") + log
        );

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void Shader::checkLinkErrors(unsigned int program) {
    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);

        Logger::log(
            LogLevel::Error,
            std::string("Shader link error: ") + log
        );
    }
}

void Shader::setMat4(const std::string& name,
                     const glm::mat4& value) const {
    int loc = glGetUniformLocation(programHandle, name.c_str());
    if (loc >= 0)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name,
                     const glm::vec3& value) const {
    int loc = glGetUniformLocation(programHandle, name.c_str());
    if (loc >= 0)
        glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Shader::setFloat(const std::string& name, float value) const {
    int loc = glGetUniformLocation(programHandle, name.c_str());
    if (loc >= 0)
        glUniform1f(loc, value);
}