#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

enum class ItemType { COIN, RUNE, WEAPON, ARMOR };
enum class Element { FIRE, WATER, EARTH, AIR };

struct Coin {
    int count;
    Coin(int count) : count(count){}
};

struct Rune {
    int level;
    Element element;
    Rune(int level, Element element) : level(level), element(element) {}
};

struct Weapon {
    int damage;
    int critical;
    int durability;
    Weapon(int damage, int critical, int durability) : damage(damage), critical(critical), durability(durability) {}
};
 
struct Armor {
    int guard;
    int durability;
    Armor(int guard, int durability) : guard(guard), durability(durability) {}
};

union AllFeatures { 
    Coin coin; 
    Rune rune; 
    Weapon weapon; 
    Armor armor; 
    AllFeatures() {};
};
//cобранная структура Item
struct Item {
    ItemType type;
    AllFeatures union_type;
};
//вектор с элементами типа Item получает псевдоним lootBox
using LootBox = vector<Item>;
//возможные элементы, их характеристики и шансы выпадения; возврат готового лутбокса
LootBox get_lootbox() {
    LootBox all(16);
    vector<double> chances{ 50.0, 6.0, 13.0, 7.0, 14.0, 0.6, 1.3, 0,7, 1.4, 0.06, 0.13, 0.07, 0.14, 1.4, 1.4, 2.8 };

    all[0].type = ItemType::COIN;
    all[0].union_type.coin = Coin(1000);

    all[1].type = ItemType::RUNE;
    all[1].union_type.rune = Rune(1, Element::FIRE);

    all[2].type = ItemType::RUNE;
    all[2].union_type.rune = Rune(1, Element::WATER);

    all[3].type = ItemType::RUNE;
    all[3].union_type.rune = Rune(1, Element::EARTH);

    all[4].type = ItemType::RUNE;
    all[4].union_type.rune = Rune(1, Element::AIR);

    all[5].type = ItemType::RUNE;
    all[5].union_type.rune = Rune(5, Element::FIRE);

    all[6].type = ItemType::RUNE;
    all[6].union_type.rune = Rune(5, Element::WATER);

    all[7].type = ItemType::RUNE;
    all[7].union_type.rune = Rune(5, Element::EARTH);

    all[8].type = ItemType::RUNE;
    all[8].union_type.rune = Rune(5, Element::AIR);

    all[9].type = ItemType::RUNE;
    all[9].union_type.rune = Rune(10, Element::FIRE);

    all[10].type = ItemType::RUNE;
    all[10].union_type.rune = Rune(10, Element::WATER);

    all[11].type = ItemType::RUNE;
    all[11].union_type.rune = Rune(10, Element::EARTH);

    all[12].type = ItemType::RUNE;
    all[12].union_type.rune = Rune(10, Element::AIR);

    all[13].type = ItemType::WEAPON;
    all[13].union_type.weapon = Weapon(100, 0, 100);

    all[14].type = ItemType::WEAPON;
    all[14].union_type.weapon = Weapon(75, 50, 100);

    all[15].type = ItemType::ARMOR;
    all[15].union_type.armor = Armor(50, 100);

    srand(time(0));
    for (int i = 0; i < 3; ++i)
    {
        double random = (rand() % 10000) / 100;
        double sum = 0;
        short num = 0;

        for (auto chance : chances)
        {
            ++num;
            if (sum <= random and random < sum + chance)
            {
                Item item = all[num];
                all.push_back(item);
                break;
            }
            sum += chance;
        }
    }
    return all;
}

//перегрузка оператора << для типов LootBox и Item 
LootBox& operator << (LootBox Box, Item item) {
    Box.push_back(item);
    return Box;
}

//перегрузка оператора << для типов std::ostream и Item
ostream& operator << (ostream& out, Item item) {
    string name;
    switch (item.type) {
    case ItemType::COIN:
        name = "1000 gold coins";
        break;

    case ItemType::RUNE:
        if (item.union_type.rune.level == 1) {
            name = "Common";
        }
        else if (item.union_type.rune.level == 50) {
            name = "Angelic";
        }
        else if (item.union_type.rune.level == 100) {
            name = "Divine";
        }
        name += " rune of ";
        switch (item.union_type.rune.element)
        {
        case Element::FIRE:
            name += "fire";
            break;
        case Element::EARTH:
            name += "earth";
            break;
        case Element::WATER:
            name += "water";
            break;
        case Element::AIR:
            name += "air";
            break;
        }
        name += " (" + to_string(item.union_type.rune.level) + " lvl)";
        break;

    case ItemType::WEAPON:
        if (item.union_type.weapon.critical == 0) {
            name = "Divine blade";
        }
        else if (item.union_type.weapon.critical == 50) {
            name = "Lucifer's blade";
        }
        break;

    case ItemType::ARMOR:
        name = "Witcher west";
        break;
    }
    out << name;
    return out;
}

//перегрузка оператора << для типов std::ostream и LootBox
ostream& operator << (ostream& out, LootBox all) {
    for (int i = 0; i < 3; i++) {
        out << all[i] << endl;
    }
    return out;
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "russian");

    while (true) {
        string answer;
        cout << "Открыть лутбокс? Yes/No\n";
        cin >> answer;

        if (answer == "Y" or answer == "Yes" or answer == "y" or answer == "yes") {
            LootBox box = get_lootbox();
            cout << box;
            box.clear();
        }
        else if (answer == "N" or answer == "No" or answer == "n" or answer == "no") break;
        else continue;
    }
}
