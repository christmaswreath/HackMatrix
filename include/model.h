#pragma once
#include "components/BoundingSphere.h"
#include "mesh.h"
#include "SQLPersisterImpl.h"
#include "shader.h"
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include "entity.h"

unsigned int TextureFromFile(const char *path, const string &directory,
                             bool gamma = false);

class Light {
  unsigned int depthMapFBO;
  unsigned int depthMap;
  const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
public:
  Light(glm::vec3 color);
  void renderDepthMap(function<void()>);
  glm::vec3 color;
};

class LightPersister: public SQLPersisterImpl {
public:
  LightPersister(std::shared_ptr<EntityRegistry> registry)
    : SQLPersisterImpl("Light", registry){};
  void createTablesIfNeeded() override;
  void saveAll() override;
  void save(entt::entity) override;
  void loadAll() override;
  void load(entt::entity) override;
  void depersistIfGone(entt::entity) override;
};

struct Positionable {
  Positionable(glm::vec3 pos, glm::vec3 origin, glm::vec3 rotate, float scale);
  glm::vec3 pos;
  glm::vec3 origin;
  glm::vec3 rotate;
  float scale;
  void update();
  glm::mat4 modelMatrix;
  glm::mat3 normalMatrix;
  bool damaged = false;
  void damage();
};

class PositionablePersister : public SQLPersisterImpl {
public:
  PositionablePersister(std::shared_ptr<EntityRegistry> registry)
    : SQLPersisterImpl("Positionable", registry){};
  void createTablesIfNeeded() override;
  void saveAll() override;
  void save(entt::entity) override;
  void loadAll() override;
  void load(entt::entity) override;
  void depersistIfGone(entt::entity) override;
};

class Model {
public:
  string path;
  Model(string path);
  void Draw(Shader &shader);

  BoundingSphere getBoundingSphere(float scale);

private:
  // model data
  vector<Mesh> meshes;
  vector<MeshTexture> textures_loaded;
  string directory;

  vector<Vertex> getAllVertices();
  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  vector<MeshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                       string typeName);
};

class ModelPersister : public SQLPersisterImpl {
public:
  ModelPersister(std::shared_ptr<EntityRegistry> registry):
    SQLPersisterImpl("Model", registry){};
  void createTablesIfNeeded() override;
  void saveAll() override;
  void save(entt::entity) override;
  void loadAll() override;
  void load(entt::entity) override;
  void depersistIfGone(entt::entity) override;
};
