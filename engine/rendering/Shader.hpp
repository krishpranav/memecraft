//
// Created by Krisna Pranav on 21/12/25.
//

#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexSrc,
           const std::string& fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

private:
    unsigned int program = 0;

    unsigned int compile(unsigned int type, const std::string& src);
    void checkLinkErrors(unsigned int program);
};