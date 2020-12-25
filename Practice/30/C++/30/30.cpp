#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Coin {
    int count;
};

struct Rune {
    int level;
    enum class Element {FIRE, WATER, EARTH, AIR};
};

struct Weapon {
    int damage;
    int critical;
    int durability;
};
 
struct Armor {
    int guard;
    int durability;
};

//cобранная структура Item
struct Item {
    enum class ItemType {COIN, RUNE, WEAPON, ARMOR};
    union AllFeatures {struct Coin; struct Rune; struct Weapon; struct Armor;};
};

//вектор с элементами типа Item получает псевдоним lootBox
using LootBox = vector<Item>;

//возврат лутбокса с тремя случайными предметами
LootBox generateLootBox() {}
//возврат характеристик элементов------------еще не прописаны
Item CoinFeatures(int coin) {}

Item RuneFeatures(int level, Rune::Element) {} 
Item FireRune(int level){}
Item WaterRune(int level){}
Item EarthRune(int level){}
Item AirRune(int level){}

Item WeaponFeatures(int damage, int critical, int durability) {}

Item ArmorFeatures(int guard, int durability) {}

int main()
{
    std::cout << "Hello World!\n";
}
