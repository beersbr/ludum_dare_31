#include "World.h"


World::World(Loader* loader)
{
	this->loaderKing = loader;
}


World::~World(void)
{

}


bool World::createTowerEntity(std::string entityName)
{
	//see if the loader has the props to create an entity
	std::stringstream ss;
	// How/what/where/when do we create bullets?
	// We should probably do it when the tower updates, but the tower needs a reference to the world?

	std::map<std::string, std::string>* towerProps = loaderKing->getTowerEntityProps(entityName);
	if(!towerProps)
	{
		ss << "[-] Failed to load tower entity: " << entityName << "\n";
		fprintf(stdout, ss.str().c_str());
		return false;
	}
	//Create the tower using these props
	entities.push_back(new TowerEntity(&this->entities, towerProps));

	return true;
}

bool World::createEnemyEntity(std::string entityName)
{
	//see if the loader has the props to create an entity
	std::stringstream ss;
	// How/what/where/when do we create bullets?
	// We should probably do it when the tower updates, but the tower needs a reference to the world?

	std::map<std::string, std::string>* enemyProps = loaderKing->getEnemyEntityProps(entityName);
	if(!enemyProps)
	{
		ss << "[-] Failed to load enemy entity: " << entityName << "\n";
		fprintf(stdout, ss.str().c_str());
		return false;
	}
	//Create the tower using these props
	entities.push_back(new TowerEntity(&this->entities, enemyProps));

	return true;
}


bool World::createTileAtPos(glm::vec2 const pos)
{
	// TOOD: this needs to be moved to a config


	return false;
}


bool World::createMap(/*std::vector<int> const tileDesc*/)
{
	int mapWidth = 1200;
	int mapHeight = 800;

	GLuint tid = SDL_SurfaceToTexture(IMG_Load("assets/test.bmp"));

	for(int i = 0; i < (1200/40)*(800/40); ++i)
	{
		glm::vec2 p = getPos(i);

		//create each tile
		TileEntity* tile = new TileEntity(glm::vec3(p.x*40, p.y*40, 1.0), glm::vec3(40.0, 40.0, 1.0));
		tile->mesh = Mesh();
		tile->mesh.textureID = tid;

		// verts
		tile->mesh.v.push_back(glm::vec3(-1.0,  1.0,  0.0));
		tile->mesh.v.push_back(glm::vec3(-1.0, -1.0,  0.0));
		tile->mesh.v.push_back(glm::vec3( 1.0,  1.0,  0.0));
		tile->mesh.v.push_back(glm::vec3( 1.0, -1.0,  0.0));

		// colors
		tile->mesh.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
		tile->mesh.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
		tile->mesh.c.push_back(glm::vec3( 0.0,  0.0,  0.0));
		tile->mesh.c.push_back(glm::vec3( 0.0,  0.0,  0.0));

		// normals
		tile->mesh.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
		tile->mesh.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
		tile->mesh.n.push_back(glm::vec3( 0.0,  0.0,  1.0));
		tile->mesh.n.push_back(glm::vec3( 0.0,  0.0,  1.0));

		// texture coords
		tile->mesh.t.push_back(glm::vec2( 0.0, 0.0));
		tile->mesh.t.push_back(glm::vec2( 1.0, 0.0));
		tile->mesh.t.push_back(glm::vec2( 0.0, 1.0));
		tile->mesh.t.push_back(glm::vec2( 1.0, 1.0));

		// elements
		tile->mesh.e.push_back(0);
		tile->mesh.e.push_back(1);
		tile->mesh.e.push_back(2);
		tile->mesh.e.push_back(2);
		tile->mesh.e.push_back(1);
		tile->mesh.e.push_back(3);

		tiles.push_back(tile);
	}

	return false;
}


glm::vec2 World::getPos(int index)
{
	glm::vec2 pos;
	pos.y = std::floor(index/(800/40));
	pos.x = index%(1200/40);

	return pos;
}

void World::RenderMap()
{
	glm::mat4 Projection = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, 500.0f, -500.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0, 0.0, 500.0),
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0)
		);

	//for(auto it = tiles.begin(); it != tiles.end(); ++it)
	//{
	//	//Mesh m = (*it)->mesh;
	//	//glm::vec3 pos = (*it)->pos;
	//	//m.transform = glm::translate(m.transform, glm::vec3(pos.x, pos.y, 1.0));
	//	//m.transform = glm::scale(m.transform, glm::vec3(40.0, 40.0, 1.0));
	//	//m.PrepareRender();
	//}

	/*for(int i = 0; i < tiles.size(); i++)
		Mesh m = tiles[i]->mesh*/;

	//Mesh::Render(Projection, View, ShaderProgram::shaders["main"]);
}