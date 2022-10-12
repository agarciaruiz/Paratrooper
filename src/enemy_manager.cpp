#include "enemy_manager.h"

int EnemyManager::LandedTroopers() const { return _landedTroopers; }
std::vector<Helicopter*> EnemyManager::Helicopters() const { return _helicopters; }
std::vector<Trooper*> EnemyManager::Troopers() const { return _troopers; }

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
	for (int i = 0; i < _helicopters.size(); i++)
	{
		_helicopters[i]->UnloadTextures();
		delete(_helicopters[i]);
	}
	_helicopters.clear();

	for (int i = 0; i < _troopers.size(); i++)
	{
		_troopers[i]->UnloadTextures();
		delete(_troopers[i]);
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
	Trooper* trooper = new Trooper();
	trooper->Init(helicopter->Position());
	_troopers.push_back(trooper);
	helicopter->DropTrooper();
}

void EnemyManager::HelicopterRoutine()
{
	timer += GetFrameTime();
	if (timer >= helicopterSpawnTime)
	{
		_helicopters.push_back(SpawnHelicopter());
		helicopterSpawnTime = GetRandomValue(3, 5);
		timer = 0;
	}
	MoveHelicopters();
}

void EnemyManager::MoveHelicopters()
{
	for (int i = 0; i < _helicopters.size(); i++)
	{
		if (_helicopters[i]->IsAlive() || !_helicopters[i]->IsOutOfScreen())
		{
			if (_helicopters[i]->HasTrooper() && _helicopters[i]->TimeOut())
			{
				SpawnTrooper(_helicopters[i]);
			}
			_helicopters[i]->Move();
		}
		else
		{
			if (!_helicopters[i]->ReloadTexture())
			{
				delete(_helicopters[i]);
				_helicopters.erase(std::remove(_helicopters.begin(), _helicopters.end(), _helicopters[i]), _helicopters.end());
			}
		}
	}
}

void EnemyManager::TrooperRoutine()
{
	for (int i = 0; i < _troopers.size(); i++)
	{
		if (_troopers[i]->IsAlive())
		{
			_troopers[i]->Update();
			if (_troopers[i]->IsGrounded() && !_troopers[i]->previouslyGrounded)
			{
				_landedTroopers++;
				_troopers[i]->PreviouslyGrounded(true);
			}
		}
		else
		{
			if (_troopers[i]->ReloadTexture())
			{
				delete(_troopers[i]);
				_troopers.erase(std::remove(_troopers.begin(), _troopers.end(), _troopers[i]), _troopers.end());
			}
		}
	}
}

void EnemyManager::DrawHelicopters()
{
	for (int i = 0; i < _helicopters.size(); i++)
	{
		_helicopters[i]->Draw();
	}
}

void EnemyManager::DrawTroopers()
{
	for (int i = 0; i < _troopers.size(); i++)
	{
		_troopers[i]->Draw();
	}
}