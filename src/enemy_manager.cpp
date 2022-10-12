#include "enemy_manager.h"

int EnemyManager::LandedTroopers() const { return _landedTroopers; }
std::list<Helicopter*> EnemyManager::Helicopters() const { return _helicopters; }
std::list<Trooper*> EnemyManager::Troopers() const { return _troopers; }

void EnemyManager::Init()
{
	SetRandomSeed(time(NULL));
	helicopterSpawnTime = 3;
	timer = helicopterSpawnTime - 1;

	trooperTimer = 0;
	_landedTroopers = 0;
}

void EnemyManager::Update()
{
	// Helicopter spawn, move and destroy
	HelicopterRoutine();
	// Update && Destroy trooper
	if(!_troopers.empty())
		TrooperRoutine();
}

void EnemyManager::Draw()
{
	DrawHelicopters();
	DrawTroopers();
}

void EnemyManager::Reset()
{
	_landedTroopers = 0;
	for(Helicopter* helicopter : _helicopters)
	{
		helicopter->UnloadTextures();
		helicoptersPool.ReturnItem(helicopter);
	}
	_helicopters.clear();

	for(Trooper* trooper : _troopers)
	{
		trooper->UnloadTextures();
		troopersPool.ReturnItem(trooper);
	}
	_troopers.clear();
}

Helicopter* EnemyManager::SpawnHelicopter()
{
	Helicopter* helicopter = new Helicopter();
	helicopter->Init();
	return helicopter;
}

void EnemyManager::SpawnTrooper(Helicopter* helicopter)
{
	Trooper* trooper = troopersPool.GetItem();
	trooper->Init(helicopter->Position());
	_troopers.push_back(trooper);
	helicopter->DropTrooper();
}

void EnemyManager::HelicopterRoutine()
{
	timer += GetFrameTime();
	if (timer >= helicopterSpawnTime)
	{
		_helicopters.push_back(helicoptersPool.GetItem());
		helicopterSpawnTime = GetRandomValue(3, 5);
		timer = 0;
	}
	MoveHelicopters();
}

void EnemyManager::MoveHelicopters()
{
	for(Helicopter* helicopter : _helicopters)
	{
		if (helicopter->IsAlive() || helicopter->IsOutOfScreen())
		{
			if (helicopter->HasTrooper() && helicopter->TimeOut())
			{
				SpawnTrooper(helicopter);
			}
			helicopter->Move();
		}
		else
		{
			if (helicopter->ReloadTexture())
			{
				helicoptersPool.ReturnItem(helicopter);
				_helicopters.remove(helicopter);
			}
		}
	}
}

void EnemyManager::TrooperRoutine()
{
	for(Trooper* trooper : _troopers)
	{
		if(trooper->IsAlive())
		{
			trooper->Update();
			if(trooper->IsGrounded() && !trooper->previouslyGrounded)
			{
				_landedTroopers++;
				trooper->PreviouslyGrounded(true);
			}
		}
		else
		{
			if(trooper->ReloadTexture())
			{
				troopersPool.ReturnItem(trooper);
				_troopers.remove(trooper);
			}
		}
	}
}

void EnemyManager::DrawHelicopters()
{
	for(Helicopter* helicopter : _helicopters)
	{
		helicopter->Draw();
	}
}

void EnemyManager::DrawTroopers()
{
	for(Trooper* trooper : _troopers)
	{
		trooper->Draw();
	}
}