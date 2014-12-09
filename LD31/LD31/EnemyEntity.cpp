#include "EnemyEntity.h"

EnemyEntity::EnemyEntity() 
	: Entity()
{
	// THIS IS JUST FOR TESTING
	moveSpeed = 15;
	vel = glm::vec2(0,0);
	dir = glm::vec2(0,0);
	dest = glm::vec2(-1, -1);
}

EnemyEntity::EnemyEntity(std::map<std::string, std::string>* props) 
	: Entity()
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());

}

EnemyEntity::EnemyEntity(glm::vec2 pos, glm::vec2 size, std::map<std::string, std::string>* props)
	: Entity(pos, size)
{
	this->health = atoi((*props)["health"].c_str());
	this->moveSpeed = atoi((*props)["moveSpeed"].c_str());
	this->atkSpeed = atoi((*props)["atkSpeed"].c_str());

}

void EnemyEntity::Update(float time)
{
	// where do I need to go?
	glm::vec2 coord = world->getTileCoord(pos.x, pos.y);
	int index = world->GetIndexByCoord(coord);

	//get my target tile

	glm::vec2 _dir = glm::vec2(0.0, 0.0);
	if(dest.x == -1 && dest.y == -1)
	{
		// grab first item off the list
		dest = (world->safePath.front()).posPixel;
	}
	else
	{
		// check if we are close enough to that position
		// go to the next tiel if we are
		float dist = world->Dist(dest, pos);

		if(dist < 10.0f)
		{
			bool found = false;
			for(auto i = world->safePath.begin(); i != world->safePath.end(); ++i)
			{
				// the tile I am on is on the safePath
				// am I near the center enough to try and go to the next tile?
				int worldIndex =  world->GetIndexByCoord((*i).posIndex);
				if(index == worldIndex)
				{
					if((*i).isEndTile == true)
					{
						//fprintf(stdout, "DO SOMETHING HERE BECAUSE WE ARE AT THE END\n");
					}
					else
					{
						++i;
						found = true;
						dest = (*i).posPixel; 
						break;
					}
				}
			}

			if(!found)
			{
				glm::vec2 dist = glm::vec2(1200, 800);

				// find the node closest to me in the safePath
				float minDist = world->Dist(world->safePath.front().posPixel, pos);
				for(auto i = world->safePath.begin(); i != world->safePath.end(); ++i)
				{
					if(world->Dist((*i).posPixel, pos) < minDist)
					{
						dest = (*i).posIndex;
						minDist = world->Dist((*i).posPixel, pos);
					}
				}
			}

		}
	}
	

	dir = glm::vec2(dest.x-pos.x, dest.y-pos.y);
	float l = glm::length(dir);
	dir = glm::vec2(dir.x/l, dir.y/l);

	vel = glm::vec2(vel.x + (dir.x*moveSpeed*time), vel.y+(dir.y*moveSpeed*time));

	pos += vel;
	vel = glm::vec2(vel.x*0.89, vel.y*0.89);

	if((currentFrameLife += time) >= frameLife)
	{
		currentFrame = (currentFrame+1)%frames;
		frameRect.x = frameRect.w*currentFrame;
		currentFrameLife = 0.0f;
	}
}
