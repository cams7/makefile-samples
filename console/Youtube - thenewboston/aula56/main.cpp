#include "Enemy.h"
#include "Ninja.h"
#include "Monster.h"

#include <iostream>
using namespace std;

void enemyAttack(Enemy&);

int main()
{
    Ninja ninja;
    ninja.attack();

    Monster monster;
    monster.attack();

    cout << "Enemies attack together" << endl;
    enemyAttack(ninja);
    enemyAttack(monster);

    return 0;
}

void enemyAttack(Enemy& enemy){
    enemy.attack();
}
