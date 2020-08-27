#include "sceneManager.hpp"
#include "resourceManager.hpp"
#include "sceneGraph.hpp"
#include "mesh.h"
#include "shapes.h"
#include "terrain/terrain.hpp"
#include "rendering/glUtilities.h"
#include "rendering/texture.hpp"
#include "stb_image.h"

#include <vector>
#include <cstdlib>
#include <string>

SceneManager::SceneManager(ResourceManager* resourceManager)
{
	// NB: Legacy code for experimentation included
	mResourceManager = resourceManager;
	rootNode = createSceneNode();

	static SceneNode* groundNode;
	static SceneNode* boxNode;
	static SceneNode* box2Node;
	static SceneNode* box3Node;
	static SceneNode* terrainNode;

	groundNode = createSceneNode();
	boxNode = createSceneNode();
	box2Node = createSceneNode();
	box3Node = createSceneNode();
	terrainNode = createSceneNode();

	const glm::vec3 groundDimensions(30, 1, 90);
	const glm::vec3 boxDimensions(20, 20, 20);

	Mesh ground = cube(groundDimensions, glm::vec2(90), true, true);
	Mesh box = cube(boxDimensions, glm::vec2(1024), false, false);
	Mesh box2 = cube(glm::vec3(256, 2, 256), glm::vec2(20, 10), false, false);
	Mesh box3 = cube(glm::vec3(5, 30, 60), glm::vec2(20, 10), false, false);
	Terrain terrain(512);

	unsigned int groundVAO = generateVAO(ground);
	unsigned int boxVAO = generateVAO(box);
	unsigned int box2VAO = generateVAO(box2);
	unsigned int box3VAO = generateVAO(box3);
	unsigned int terrainVAO = generateVAO(*terrain.getHeightMap());

	// Using vectors instead. Fixing later...
	activePointLights = 1;
	activeDirectionalLights = 1;


	for (unsigned int light = 0; light < activeDirectionalLights; light++) {
		DirectionalLightSource directionalLight;
		directionalLight.lightNode = createSceneNode();
		directionalLight.lightNode->VAOID = light;
		directionalLight.lightNode->nodeType = DIRECTIONAL_LIGHT;
		directionalLight.color = glm::vec3(1.0);
		directionalLight.direction = glm::vec3(0.0, 1.0, 0.0);
		groundNode->children.push_back(directionalLight.lightNode);
		directionalLightSources.push_back(directionalLight);
	}
	
	rootNode->children.push_back(terrainNode);
	terrainNode->pos = glm::vec3(-float(terrain.getRows() / 2), -5.0, -float(terrain.getCols() / 2));
	terrainNode->VAOID = terrainVAO;
	terrainNode->VAOIndexCount = terrain.getHeightMap()->indices.size();

	int width, height, chans;

	unsigned char* imageData = stbi_load("../res/textures/grass1.png", &width, &height, &chans, 0);

	if (imageData == NULL)
	{
		printf("no image!!!!");
	}

	Texture* terrainTexture = new Texture();
	terrainTexture->generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, imageData);
	stbi_image_free(imageData);
	
	terrainNode->textureID = terrainTexture->getID();


	unsigned char* imageData3 = stbi_load("../res/textures/rock1.png", &width, &height, &chans, 0);

	if (imageData3 == NULL)
	{
		printf("no image3!!!!");
	}

	Texture* rockTexture = new Texture();
	rockTexture->generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, imageData3);
	stbi_image_free(imageData3);
	
	terrainNode->children.push_back(boxNode);
	boxNode->VAOID = boxVAO;
	boxNode->VAOIndexCount = box.indices.size();
	boxNode->pos = glm::vec3(256.0, 0.0, 170.0);
	boxNode->textureID = rockTexture->getID();

	unsigned char* imageData4 = stbi_load("../res/textures/road1.jpg", &width, &height, &chans, 0);

	if (imageData4 == NULL)
	{
		printf("no image4!!!!");
	}

	Texture* roadTexture = new Texture();
	roadTexture->generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, imageData4);
	stbi_image_free(imageData4);

	terrainNode->children.push_back(box2Node);
	box2Node->VAOID = box2VAO;
	box2Node->VAOIndexCount = box2.indices.size();
	box2Node->pos = glm::vec3(256.0, -4.0, 200.0);
	//box2Node->textureID = skyTexture->getID();

	unsigned char* imageData5 = stbi_load("../res/textures/brick1.png", &width, &height, &chans, 0);
	printf("here");
	if (imageData5 == NULL)
	{
		printf("no image5!!!!");
	}

	Texture* brickTexture = new Texture();
	brickTexture->generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, imageData5);
	stbi_image_free(imageData5);

	terrainNode->children.push_back(box3Node);
	box3Node->VAOID = box3VAO;
	box3Node->VAOIndexCount = box3.indices.size();
	box3Node->pos = glm::vec3(230.0, 0.0, 180.0);
	box3Node->textureID = brickTexture->getID();
	
	//std::vector<ImageData> skyBoxData = mResourceManager->loadSkyBoxImageData();
	const glm::vec3 skyBoxDimensions(512, 512, 512);
	Mesh skyBox = cube(skyBoxDimensions, glm::vec2(512), false, true);
	unsigned int skyBoxVAO = generateVAO(skyBox);

	static SceneNode* skyBoxNode;
	skyBoxNode = createSceneNode();
	skyBoxNode->nodeType = GEOMETRY;
	rootNode->children.push_back(skyBoxNode);
	skyBoxNode->VAOID = skyBoxVAO;
	skyBoxNode->VAOIndexCount = skyBox.indices.size();

	Texture* skyTexture = new Texture();
	unsigned char* imageData2 = stbi_load("../res/textures/sky4.jpg", &width, &height, &chans, 0);
	skyTexture->generate(height, width, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, true, imageData2);

	if (imageData2 == NULL)
	{
		printf("no image2!!!!");
	}
	stbi_image_free(imageData2);

	box2Node->textureID = skyTexture->getID();
	skyBoxNode->textureID = skyTexture->getID();

	// Create some light sources and place them in the scene
	for (unsigned int light = 0; light < activePointLights; light++) {
		PointLightSource pointLight;
		pointLight.lightNode = createSceneNode();
		pointLight.lightNode->VAOID = light;
		pointLight.lightNode->nodeType = POINT_LIGHT;
		pointLight.color = glm::vec3(1.0);
		pointLight.lightNode->pos = glm::vec3(256.0, 25.0, 180.0);
		terrainNode->children.push_back(pointLight.lightNode);
		pointLightSources.push_back(pointLight);
	}

	terrainNode->textureID = terrainTexture->getID();
	/*
	rootNode->children.push_back(groundNode);
	groundNode->children.push_back(boxNode);

	groundNode->vertexArrayObjectID = groundVAO;
	groundNode->VAOIndexCount = ground.indices.size();

	boxNode->vertexArrayObjectID = boxVAO;
	boxNode->VAOIndexCount = box.indices.size();
	*/
	printf("Created scene");
}

SceneManager::~SceneManager()
{

}

void SceneManager::createSkyBox(int height, int width, int depth)
{
	std::vector<ImageData> skyBoxData = mResourceManager->loadSkyBoxImageData();
	const glm::vec3 skyBoxDimensions(40, 40, 40);
	Mesh skyBox = cube(skyBoxDimensions, glm::vec2(40), true, true);
	unsigned int skyBoxVAO = generateVAO(skyBox);

}