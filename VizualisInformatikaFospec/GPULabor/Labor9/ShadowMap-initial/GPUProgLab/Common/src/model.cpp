#include "model.hpp"

Model::Model()
{
    position = { 0.0f, 0.0f, 0.0f };
    roll = 0.0f;
    yaw = 0.0f;
    pitch = 0.0f;
    scale = { 1.0f, 1.0f, 1.0f };

    modelMatrix = glm::mat4(1.0f);
}

Model::~Model()
{
}

void Model::init(const std::string& path, const std::string& textureFileName)
{
    image.initialize(100, 100);
    image.loadFromFile(textureFileName);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        assert(false);
    }

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
        {
            Vertex vertex;
            if (aiMesh->HasPositions())
            {
                vertex.position = glm::vec3(aiMesh->mVertices[i].x, aiMesh->mVertices[i].y, aiMesh->mVertices[i].z);
            }
            if (aiMesh->HasNormals())
            {
                vertex.normal = glm::vec3(aiMesh->mNormals[i].x, aiMesh->mNormals[i].y, aiMesh->mNormals[i].z);
            }
            if (aiMesh->mTextureCoords[0]) {
                vertex.texCoord = glm::vec2(aiMesh->mTextureCoords[0][i].x, aiMesh->mTextureCoords[0][i].y);
            }
            else {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
        {
            aiFace face = aiMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        meshes.push_back(Mesh(vertices, indices));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

void Model::render()
{
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].render();
    }
}

glm::mat4 Model::getModelMatrix()
{
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
    glm::mat4 rotationMat = glm::rotate(scaleMat, roll, glm::vec3(0.0f, 0.0f, 1.0f));
    rotationMat = glm::rotate(rotationMat, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMat = glm::rotate(rotationMat, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::translate(rotationMat, position);
    return modelMatrix;
}

void Model::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}
void Model::setRoll(GLfloat newRoll) {
    roll = newRoll;
}
void Model::setYaw(GLfloat newYaw) {
    yaw = newYaw;
}
void Model::setPitch(GLfloat newPitch) {
    pitch = newPitch;
}
void Model::setScale(glm::vec3 newScale) {
    scale = newScale;
}