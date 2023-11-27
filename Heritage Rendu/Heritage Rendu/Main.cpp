#include<iostream>
using namespace std;
#include <vector>

class DealDamage
{
public:
	virtual int SubstractDamage(int value, int valueRemove)
	{
		value -= valueRemove;
		return value;
	}
};
class EnemySkeleton : public DealDamage
{
public: int health;
public: int damage;
public: string name;

public:
	void SetStatistic(int h, int d, string n)
	{
		health = h;
		damage = d;
		name = n;
	}

	int SubstractDamage(int value, int valueRemove)
	{
		health = DealDamage::SubstractDamage(value, valueRemove);
		InfoOnHit();
		return health;
	}

	virtual std::ostream& Announcement()
	{
		return std::cout << "The ennemy is a " << name << ": " << health << " HP/" << damage << " Attack.";
	}
	virtual std::ostream& InfoOnHit()
	{
		return std::cout << name << " have " << health << " HP " << endl << endl;
	}
	virtual std::ostream& Attack()
	{
		return cout << "Clac, clac, clac...";
	}
};

class SkeletonWarrior : public EnemySkeleton
{

};

class SkeletonKnight : public EnemySkeleton
{

};

static std::vector<EnemySkeleton> enemySkeletons;

class Player : public DealDamage
{
public: int health;
public: int damage;
public: string name;

public:
	void SetStatistic(int h, int d, string n)
	{
		health = h;
		damage = d;
		name = n;
	}
	int SubstractDamage(int value, int valueRemove)
	{
		return DealDamage::SubstractDamage(value, valueRemove);
	}
	virtual std::ostream& Announcement()
	{
		return std::cout << "You're a " << name << ": " << health << " HP/" << damage << " Attack." << std::endl << std::endl;
	}
	virtual std::ostream& InfoOnHit()
	{
		return std::cout << "You have " << health << " HP " << endl << endl;
	}
	virtual void AttackPrincipal(int value)
	{
	}
	virtual void AttackSecondary(int value)
	{
	}
};

static Player* staticPlayer;
static int action;

void SelectedEnemyArray(int selected, int damage)
{
	cout << "The enemy " << selected << " : ";
	enemySkeletons[selected].SubstractDamage(enemySkeletons[selected].health, damage);
}

void Slash(int damage)
{
	int selected = 0;
	cout << "Choose the skeleton to hit: 0 First/ 1 Second/ 2 Third." << endl;
	cin >> selected;
	SelectedEnemyArray(selected, damage);
}

void Reinforcement(int value)
{
	staticPlayer->health += value;
	cout << "You have " << staticPlayer->health << " HP" << endl;
}

void MultipleSlash(int value)
{
	for (EnemySkeleton& skeleton : enemySkeletons)
	{
		skeleton.SubstractDamage(skeleton.health, value);
	}
}

class Legionary : public Player
{
	void AttackPrincipal(int dmg) override
	{
		Slash(dmg);
	}

	void AttackSecondary(int value) override
	{
		Reinforcement(value);
	}
	int SubstractDamage(int value, int valueRemove) override
	{
		health = DealDamage::SubstractDamage(value, valueRemove);
		InfoOnHit();
		return health;
	}
};

class Auxiliary : public Player
{
	void AttackPrincipal(int dmg) override
	{
		Slash(dmg);
	}

	void AttackSecondary(int value) override
	{
		MultipleSlash(value);
	}
	int SubstractDamage(int value, int valueRemove) override
	{
		health = DealDamage::SubstractDamage(value, valueRemove);
		InfoOnHit();
		return health;
	}
};


void SetEnemyArray(int number) {
	std::cout << "You fight against " << number << " Skeleton(s)" << std::endl << std::endl;

	SkeletonWarrior skeletonWarrior;
	SkeletonKnight skeletonKnight;

	enemySkeletons.clear();

	for (int i = 0; i < number; i++)
	{
		if (i == 0) {
			enemySkeletons.push_back(skeletonWarrior);
			enemySkeletons[i].SetStatistic(10, 2, "Skeleton Warrior");
		}
		else if (i == 1) {
			enemySkeletons.push_back(skeletonWarrior);
			enemySkeletons[i].SetStatistic(10, 2, "Skeleton Warrior");
		}
		else if (i == 2) {
			enemySkeletons.push_back(skeletonKnight);
			enemySkeletons[i].SetStatistic(15, 3, "Skeleton Knight");
		}

		enemySkeletons[i].Announcement();
		std::cout << " : enemy " << i << std::endl << std::endl;
	}
}

void SelectAction(int selected, Player* player)
{
	int attack = 0;
	switch (selected)
	{
	case 1:
		cout << "Select your Action: 1 = Slash (deal 4 damage) / 2 = Reinforcement (gain 5 HP)" << endl;
		cin >> attack;

		if (attack == 2)
		{
			player->AttackSecondary(player->damage + 1);
		}

		else
		{
			player->AttackPrincipal(player->damage);
		}
		break;

	case 2:
		cout << "Select your Action: 1 = Slash (deal 4 damage)/ 2 = Multiple Slash (deal 3 damage on every enemy)" << endl;
		cin >> attack;
		if (attack == 2)
		{
			player->AttackSecondary(player->damage - 3);
		}
		else
		{
			player->AttackPrincipal(player->damage);
		}
		break;

	default:
		break;
	}
}
void SelectClasses()
{
	int selected = 0;

	Legionary legionary;
	Auxiliary auxiliary;

	Player* p1 = &legionary;
	p1->SetStatistic(30, 4, "Legionary");
	Player* p2 = &auxiliary;
	p2->SetStatistic(20, 6, "Auxiliary");

	cout << "Select your Classe: 1 = Legionnary / 2 = Auxiliary" << endl;
	cin >> selected;
	action = selected;
	switch (selected)
	{
	case 1:
		staticPlayer = p1;
		staticPlayer->Announcement(); 
			break;
	case 2:
		staticPlayer = p2;
		staticPlayer->Announcement();
		break;
	default:
		break;
	}
	SelectAction(selected, staticPlayer);
}

void SelectDifficulty()
{
	int selected = 0;
	int numberEnemy = 0;

	cout << "Select your difficulty: 1 = Easy / 2 = Normal / 3 = Hard" << endl;
	cin >> selected;

	numberEnemy = selected;
	switch (selected)
	{
	case 1:
		cout << "Your difficulty is Easy" << endl << endl;
		SetEnemyArray(numberEnemy);
		break;
	case 2:
		cout << "Your difficulty is Normal" << endl << endl;
		SetEnemyArray(numberEnemy);
		break;
	case 3:
		cout << "Your difficulty is Hard" << endl << endl;
		SetEnemyArray(numberEnemy);
		break;
	default:
		break;
	}
}

void PlayTurn(Player *player)
{
	cout << "Enemies' turn:" << endl;
	for (EnemySkeleton& skeleton : enemySkeletons)
	{
		if (skeleton.health > 0 && player->health > 0)
		{		
			player->SubstractDamage(player->health, skeleton.damage);		
		}


		if (skeleton.health <= 0)
		{
			cout << "The enemy " << skeleton.name << " has been defeated." << endl;
		}


		if (player->health <= 0)
		{
			cout << "You have been defeated. Game over!" << endl;
			return;
		}
	}


	bool allEnemiesDefeated = true;
	for (const EnemySkeleton& skeleton : enemySkeletons)
	{
		if (skeleton.health > 0)
		{
			allEnemiesDefeated = false;
			break;
		}
	}

	if (allEnemiesDefeated)
	{
		cout << "Congratulations! You defeated all enemies. You win!" << endl;
		return;
	}


	cout << "It's your turn!" << endl;
	player->Player::Announcement();
	SelectAction(action, player);


	allEnemiesDefeated = true;
	for (const EnemySkeleton& skeleton : enemySkeletons)
	{
		if (skeleton.health > 0)
		{
			allEnemiesDefeated = false;
			break;
		}
	}
}

void main()
{
	SelectDifficulty();
	SelectClasses();

	while (true)
	{
		PlayTurn(staticPlayer);

		bool allEnemiesDefeated = true;
		for (EnemySkeleton& skeleton : enemySkeletons)
		{
			if (skeleton.health > 0)
			{
				allEnemiesDefeated = false;
				break;
			}
		}

		if (allEnemiesDefeated)
		{
			cout << "Congratulations! You defeated all enemies. You win!" << endl;
			break;
		}

		if (staticPlayer->health <= 0)
		{
			break;
		}
	}

	cout << "Game over." << endl;
}