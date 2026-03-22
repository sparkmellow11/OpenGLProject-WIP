//
// Created by schan on 26/12/2025.
//

#include "Utils.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

unsigned int TextureFromFile(const char *path, const std::string &directory)
{
        auto filename = std::string(path);
        filename = directory + "/" + filename;


        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrChannels;

        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
                GLenum format;
                switch (nrChannels)
                {
                case 1:
                        format = GL_RED;
                        break;
                case 3:
                        format = GL_RGB;
                        break;
                case 4:
                        format = GL_RGBA;
                        break;
                default:
                        format = GL_RGB;
                        break;
                }

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        } else
        {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                std::cout << "Failure reason: " << stbi_failure_reason << std::endl;
        }
        stbi_image_free(data);

        return textureID;
}

glm::vec3 GetSphericalDirection(const float colatitude, const float azimuth)
{
        return {glm::sin(colatitude)*glm::cos(azimuth), glm::cos(colatitude), -glm::sin(colatitude)*glm::sin(azimuth)};
}

glm::vec3 GetCameraLeftDirection(const float azimuth)
{
        return {-glm::sin(azimuth), 0.0f, -glm::cos(azimuth)};
}

float cosTimeDomain(const float min, const float max, const float frequency, const float time)
{
        const auto mean = (min + max) / 2.0f;
        const auto maxDiff = std::abs(max - mean);
        const auto angularFrequency = glm::two_pi<float>()*frequency;
        return maxDiff*glm::cos(angularFrequency*time)+mean;
}

void UpdateFallingPhysics(glm::vec3& position, glm::vec3& velocity, const float deltaTime)
{
        constexpr float gravAccel = -9.81f;
        velocity.y += gravAccel*deltaTime;
        position += velocity*deltaTime;
        if (position.y < 0.0f && velocity.y < 0.0f)
        {
                position.y = 0.0f;
                velocity.y = 0.0f;
        }
}