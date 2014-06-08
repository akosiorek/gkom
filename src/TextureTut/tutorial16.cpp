/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Tutorial 16 - Basic Texture Mapping
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ogldev_util.h"
#include "pipeline.h"
#include "camera.h"
//#include "ogldev_texture.h"
#include "Texture.h"
#include "RendererOGL.h"
#include "PerspectiveCamera.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include "Trajectory.h"
#include "Utils.h"
#include "NormalGenerator.h"

struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;

    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
        m_pos = pos;
        m_tex = tex;
    }
};

int main(int argc, char** argv) {

    CameraPtr camera = std::make_shared<PerspectiveCamera>();
    camera->setClipping(0.5f, 500.f);
    // camera->setFOV(90);
    camera->translate(0, 0, -5);
    auto cameraTrajectory = std::make_shared<Trajectory>();
    cameraTrajectory->addMove(20, 0, MoveType::RotY);
    camera->addTrajectory(cameraTrajectory);

    GLuint TBO, IBO, VBO;
    GLuint gWVPLocation;
    GLuint gSampler;
    Texture* pTexture = NULL;

//  Renderer setup
    RendererPtr renderer(new RendererOGL(1920, 1080));
    renderer->init();
    renderer->setCamera(camera);


    std::vector<float> geom = {
        0.0f, -1.0f, -1.15475f,
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.5773f,
        1.0f, -1.0f, 0.5773f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, -1.f,
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.5773f,
        -1.0f, -1.0f, 0.5773f,
        1.0f, -1.0f, 0.5773f,
        0.0f, -1.0f, -1.15475f,
        -1.0f, -1.0f, 0.5773f
    };

    std::vector<float> normal = NormalGenerator::gen(geom);

    std::vector<float> texCoords = {
        0.5f, 0.0f,
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 1.0f,
        0.5f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.5f, 0.0f,
        0.0f, 0.0f
    };

    std::vector<uint> indices;
    for(int i = 0; i < geom.size(); ++i) {
        indices.push_back(i);
    };
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, geom.size() * sizeof(float), geom.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &TBO);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), indices.data(), GL_STATIC_DRAW);


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


    GLuint ShaderProgram = Utils::createProgram({
        Utils::loadShader(GL_VERTEX_SHADER, "texture.vs"),
        Utils::loadShader(GL_FRAGMENT_SHADER, "texture.fs")
    });
    glUseProgram(ShaderProgram);
    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
    gSampler = glGetUniformLocation(ShaderProgram, "gSampler");
    glUniform1i(gSampler, 0);

    pTexture = new Texture(GL_TEXTURE_2D, "../textures/spaceship.jpg");
    pTexture->load();   

    NodePtr rootNode = std::make_shared<Node>();
    while(!renderer->shouldClose()) {
        renderer->clearScreen();
        camera->update(0.05);

        glUniformMatrix4fv(gWVPLocation, 1, GL_FALSE, glm::value_ptr(camera->getTransform()));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
      
        glBindVertexArray (vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        pTexture->bind(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 12);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        renderer->render(rootNode, 0);

    }

    return 0;
}