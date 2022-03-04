#include "LevelManager.h"
#include "Global.h"
#include "Mushroom.h"
#include "Goblin.h"
#include "FlyingEye.h"
void LevelManager::setLevel(int i)
{
	level = i;
}

void LevelManager::setCam(Vector<2> location)
{
	cam = location;
}

void LevelManager::setEnemSize(size_t i)
{
	enemSize = i;
}

void LevelManager::setItemSize(size_t i)
{
	itemSize = i;
}

Enemy* LevelManager::getEnemies()
{
    if (enemSize < level+2)
    {
        int x = rand() % (bkWidth * 2) - bkWidth;
        int y = rand() % (bkHeight * 2) - bkHeight;
        if (!((x > cam[0] - camWidth && x < cam[0] + camWidth) && (y > cam[1] - camHeight && y < cam[1] + camHeight)))
        {
            Vector<2> enemyLoc = Vector<2>(x, y);
            int a = rand() % 3;
            if (a == 0)
            {
                Mushroom* enemy = new Mushroom();
                enemy->Start();
                enemy->skin.Location = enemyLoc;
                return enemy;
            }
            else if (a == 1)
            {
                FlyingEye* enemy = new FlyingEye();
                enemy->Start();
                enemy->skin.Location = enemyLoc;
                return enemy;
            }
            else
            {
                Goblin* enemy = new Goblin();
                enemy->Start();
                enemy->skin.Location = enemyLoc;
                return enemy;
            }
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

Item* LevelManager::getItems()
{
    if (itemSize< 3)
    {
        int x = rand() % (bkWidth * 2) - bkWidth;
        int y = rand() % (bkHeight * 2) - bkHeight;
        if (!((x > cam[0] - camWidth && x < cam[0] + camWidth) && (y > cam[1] - camHeight && y < cam[1] + camHeight)))
        {
            Vector<2> itemLoc = Vector<2>(x, y);
            Item* item = new Item();
            item->skin.Location = itemLoc;
            item->Start();
            return item;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}
