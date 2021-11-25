#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
/*
if (f.is_open())
        {
            while (getline(f, b)) //read entire line
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1; //randomness
*/
/*TO DO
Change the fight romanian text file to include the 2nd line
finish the fight function
implement shop
*/
ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
ifstream questionsromanian("questionsromanian.txt"); //file containing questions romanian
ifstream questionsenglish("questionsenglish.txt"); //file containing questions english
ifstream fighthungarian("fighthungarian.txt"); //hungarian version for fights
ifstream fightromanian("fightromanian.txt"); //romanian version for fights
ifstream fightenglish("fightenglish.txt"); //english version for fights
ifstream hungarianstory("hungarian.txt"); //hungarian version of the story
ifstream romanianstory("romanian.txt"); //romanian version of the story
ifstream englishstory("english.txt"); //english version of the story
ofstream save1("save1.txt"); //save file one
ofstream save2("save2.txt"); //save file two
ofstream save3("save3.txt"); //save file three
string b, first_name, last_name, c, story[10000], questions[10000], d, ar, fight[1000];
int i, language, j, k, r, enemy_number, e, item_number, p, weapon_number, armor_number;
char a;
bool ok_name = false, ok_fight_first = true;
struct player //player
{
    string player_name = { " " }; //player name
    float ATK = { 0 }, DEF = { 0 }, THP = { 0 }, CHP = { 0 }; //player number stats
    int current_xp = { 0 }; //current xp
    int level = { 1 }; //current level
    int xp_to_next_level = {100};
};
struct weapon
{
    string name = { " " }; //name
    float ATK = { 0 }; //atk bonus
    string hand = { " " }; //main / off hand
};
struct enemy //enemies
{
    string enemy_name = { " " }; //enemy name
    float ATK = { 0 }, DEF = { 0 }, THP = { 0 }, CHP = { 0 }; //enemy number stats
    string drops = { " " }; //enemy dropped item
};
struct armor //armors
{
    string name = { " " }; //name
    float DEF = { 0 }; //def bonus
    string place = { " " }; //equip place
};
struct item //items
{
    string name = { " " }; //item name  //type of bonus from the item
    int price = { 0 }; //price of the item at a store
}; 
armor leatherh, leatherc, leatherp, leatherb, goldh, goldc, goldp, goldb, ironh, ironc, ironp, ironb, diamondh, diamondc, diamondp, diamondb, netheriteh, netheritec, netheritep, netheriteb; //armors
weapon wooden_sword, stone_sword, iron_sword, diamond_sword, netherite_sword, bow, crossbow, trident; //weapons
enemy iron_golem, zombie, skeleton, creeper, husk, current_enemy; //enemies
item iron_ingot, rotten_flesh, bone, gunpowder; //items
player pc; //player
void languagechoice(); //language choice
void read_language(char a, int& language); //read the story and the questions
void readfight(); //read all fight needed text
void readweapons(); //read all weapons
void readenemies(); //read all enemies
void readarmors(); //read all armors
void readitems(); //read all items
void playercurrentstate(player& x); //output current player state
void fight_action(enemy& current_enemy); //fight function
void fight_start(enemy& enemy); //summon enemy fight function
void ico(); //input one character then clear console
void enemy_stats(enemy& x); //output enemy_stats
void icm(); //input one word then clear console
void weapons(weapon& x); //read weapons from file
void enemies(enemy& x); //read enemy from file
void armors(armor& x); //read armor from file
void items(item& x); //read item from file
void name(); //get the name of the character
void tests(); //tests funciton
void languagechoice() //language choice
{
    cout << "Choose a language.\nAlege limba.\nChoose a language but hungarian.\n\n\n1)English/Engleza/\n2)Romana/Romanian/\n3)Magyar/Maghiara/Hungarian\n";
    ico(); //read language option
    if (a != '1' && a != '2' && a != '3')
    {
        cout << "Incorrect input please try again/Intrare incorecta te rog incearca din nou/Incorrect input please try again but hungarian" << endl; //incorrect input for the language choice
        languagechoice();
    }
}
void read_language(char a, int& language) //read the story and the questions
{
    if (a == '1')
    {
        if (englishstory.is_open()) //check if the file is open
        {
            while (getline(englishstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsenglish.is_open()) //check if the file is open
            while (getline(questionsenglish, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 1;
    }
    if (a == '2')
    {
        if (romanianstory.is_open()) //check if the file is open
        {
            while (getline(romanianstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsromanian.is_open()) //check if the file is open
            while (getline(questionsromanian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 2;
    }
    if (a == '3')
    {
        if (hungarianstory.is_open()) //check if the file is open
        {
            while (getline(hungarianstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionshungarian.is_open()) //check if the file is open
            while (getline(questionshungarian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 3;
    }
}
void readweapons()
{
    weapons(wooden_sword);
    weapons(stone_sword);
    weapons(iron_sword);
    weapons(diamond_sword);
    weapons(netherite_sword);
    weapons(bow);
    weapons(crossbow);
    weapons(trident);
}
void readenemies() //read all enemies
{
    enemies(iron_golem);
    enemies(zombie);
    enemies(skeleton);
    enemies(creeper);
    enemies(husk);
}
void readarmors()
{
    armors(leatherh);
    armors(leatherc);
    armors(leatherp);
    armors(leatherb);
    armors(goldh);
    armors(goldc);
    armors(goldp);
    armors(goldb);
    armors(ironh);
    armors(ironc);
    armors(ironp);
    armors(ironb);
    armors(diamondh);
    armors(diamondc);
    armors(diamondp);
    armors(diamondb);
    armors(netheriteh);
    armors(netheritec);
    armors(netheritep);
    armors(netheriteb);
}
void readitems() //read all items
{
    items(iron_ingot);
    items(rotten_flesh);
    items(bone);
    items(gunpowder);
}
void readfight()
{
    i = 1;
    if (language == 1)
        if (fightenglish.is_open()) //check if file is open
        {
            while (getline(fightenglish, b)) //read line and store in b
            {
                fight[i] = b; //add the line to the fight string
                i++; //increase the number for the line of the fight string
            }
        }
    if (language == 2)
        if (fightromanian.is_open()) //check if file is open
        {
            while (getline(fightromanian, b)) //read line and store in b
            {
                fight[i] = b; //add the line to the fight string
                i++; //increase the number for the line of the fight string
            }
        }
    if (language == 3)
        if (fighthungarian.is_open()) //check if file is open
        {
            while (getline(fighthungarian, b)) //read line and store in b
            {
                fight[i] = b; //add the line to the fight string
                i++; //increase the number for the line of the fight string
            }
        }
}
void fight_action(enemy& current_enemy)
{
    if (ok_fight_first == true)
        cout << fight[1] << " " << current_enemy.enemy_name; //you've been attacked by on the first run
    else cout << fight[2] << " " << current_enemy.enemy_name; //you're currently fighting on the subsequent ones
}
void fight_start(enemy& current_enemy)
{
    int r = (rand() % 100) + 1; //get random number
    if (r <= 32)
        current_enemy = zombie; //32% chance of zombie
    if (r > 32 && r <= 64)
        current_enemy = skeleton; //32% chance of zombie
    if (r > 64 && r <= 96)
        current_enemy = husk; //32% chance of husk
    if (r > 96 && r <= 98)
        current_enemy = creeper; //2% chance of creeper
    if (r > 98 && r <= 100)
        current_enemy = iron_golem; //2% chance of iron_golem
}
void playercurrentstate(player& x) //output current player state
{
    system("CLS");
    p = pc.player_name.length() - 1;
    if (language == 1)
    {
        if (pc.player_name[p] == 's') //if the language is english
            cout << pc.player_name << char(39) << " current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nExperience: "; //if the last letter is s
        else
            cout << pc.player_name << char(39) << "s current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nExperience: "; //if the last letter isn't s
    }
    if (language == 2)
        cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK << "\nAparare: " << pc.DEF << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nNivel: " << pc.level << "\nExperienta: "; //if the language is romanian
    if (language == 3)
        cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK << "\nAparare: " << pc.DEF << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nLevel: " << pc.level << "\nExperience" << "\nHungarian translation needed"; //if the language is hungarian
}
void enemy_stats(enemy& x) //output enemy_stats
{
    //system("CLS");
    if (language == 1)
        cout << "Name: " << x.enemy_name << endl << "Attack: " << x.ATK << endl << "Defense: " << x.DEF << endl << "Total Health Points: " << x.THP << endl << "Current Health Points: " << x.CHP << endl << "Drops: " << x.drops; // output enemy stats and drops
    if (language == 2)
        cout << "Nume: " << x.enemy_name << endl << "Atac: " << x.ATK << endl << "Aparare: " << x.DEF << endl << "Puncte Viata Totale: " << x.THP << endl << "Puncte Viata Curente: " << x.CHP << endl << "Drop-uri: " << x.drops; // output enemy stats and drops
    if (language == 3)
        cout << "Name but hungarian: " << x.enemy_name << endl << "Attack but hungarian: " << x.ATK << endl << "Defense but hungarian: " << x.DEF << endl << "Total Health Points but hungarian: " << x.THP << endl << "Current Health Points but hungarian: " << x.CHP << endl << "Drops but hungarian: " << x.drops; // output enemy stats and drops
    cout << endl << endl;
}
void weapons(weapon& x)
{
    ifstream weaponstxt("weapons.txt");
    for (e = 1; e <= weapon_number; e++)
        getline(weaponstxt, b); //skip unnecessary lines
    getline(weaponstxt, b); //getting line
    if (language == 1)
    {
        x.name = b;
        getline(weaponstxt, b);
        getline(weaponstxt, b);
    }
    if (language == 2)
    {
        getline(weaponstxt, b);
        x.name = b;
        getline(weaponstxt, b);
    }
    if (language == 3)
    {
        getline(weaponstxt, b);
        getline(weaponstxt, b);
        x.name = b;
    }
    getline(weaponstxt, b);
    x.hand = b;
    weaponstxt >> x.ATK;
    weapon_number += 5;
    weaponstxt.close();
}
void enemies(enemy& x) //read enemy from file
{
    ifstream h("enemies.txt"); //file containing enemy stats and names
    for (e = 1; e <= enemy_number; e++)
        getline(h, b); //skip unncessary lines
    getline(h, d); //getting line
    x.enemy_name = d; //enemy name 
    getline(h, d); //getting line
    if (language == 1)
    {
        x.drops = d; //enemy drops
        getline(h, d);
        getline(h, d);
    }
    if (language == 2)
    {
        getline(h, d);
        x.drops = d;
        getline(h, d);
    }
    if (language == 3)
    {
        getline(h, d);
        getline(h, d);
        x.drops = d;
    }
    h >> x.ATK >> x.DEF >> x.THP >> x.CHP; //reading the number stats from file
    enemy_number = enemy_number + 8;
    h.close();
}
void armors(armor& x)
{
    ifstream armortxt("armor.txt"); //file containg armor stats names and placement
    for (e = 1; e <= armor_number; e++)
        getline(armortxt, ar); //skip unnecessary lines
    getline(armortxt, ar);
    if (language == 1)
    {
        x.name = ar; //armor name
        getline(armortxt, ar);
        getline(armortxt, ar);
    }
    if (language == 2)
    {
        getline(armortxt, ar);
        x.name = ar; //armor name
        getline(armortxt, ar);
    }
    if (language == 3)
    {
        getline(armortxt, ar);
        getline(armortxt, ar);
        x.name = ar; //armor name
    }
    getline(armortxt, ar);
    x.place = ar;
    armortxt >> x.DEF;
    armor_number = armor_number + 5;
    
}
void items(item& x) //read item from file
{
    ifstream items("items.txt");
    for (e = 1; e <= item_number; e++)
        getline(items, b);
    getline(items, b);
    if (language == 1)
    {
        x.name = b;
        getline(items, b);
        getline(items, b);
    }
    if (language == 2)
    {
        getline(items, b);
        x.name = b;
        getline(items, b);
    }
    if (language == 3)
    {
        getline(items, b);
        getline(items, b);
        x.name = b;
    }
    items >> x.price;
    item_number += 4;
    items.close();
}
void name() //get the name of the character
{
    if (ok_name != true) //first time run test
        cout << story[1] << endl; //ask for name
    else //if the input was incorrect last time
    {
        cout << "Incorrect Input. Please try again" << endl;
        cout << story[1] << endl;
    }
    getline(cin, pc.player_name); //read name
    system("CLS");
    cout << questions[1] << " " << char(39) << pc.player_name << char(39) << " " << questions[2] << "\n\n" << questions[3] << "\n" << questions[4] << "\n"; //ask if the name is correct
    ico(); //read the answer
    if (a == '2') //check if the name is correct
    {
        ok_name = false; //reset ok for acknowledged incorrecst name
        name(); //redo name input if the name is incorrect
    }
    if (a != '2' && a != '1') //check if the input is correct
    {
        ok_name = true;
        name();
    }
    pc.ATK = 1;
    pc.DEF = 1;
    pc.THP = 20;
    pc.CHP = 20;
}
void ico() //input one character then clear console
{
    a = _getch(); //read one character user input
    system("CLS"); //clear console
}
void icm() //input one word then clear console
{
    cin >> c; //read multiple characters user input
    system("CLS"); //clear console
}
void tests()
{
    cout << "Items: " << endl;
    cout << iron_ingot.name << endl << iron_ingot.price << endl;
    cout << bone.name << endl << bone.price << endl;
    cout << rotten_flesh.name << endl << rotten_flesh.price << endl;
    cout << gunpowder.name << endl << gunpowder.price << endl;
    cout << endl << "Weapons: " << endl;
    cout << wooden_sword.name << endl << wooden_sword.ATK << endl << wooden_sword.hand << endl;
    cout << stone_sword.name << endl << stone_sword.ATK << endl << stone_sword.hand << endl;
    cout << iron_sword.name << endl << iron_sword.ATK << endl << iron_sword.hand << endl;
    cout << diamond_sword.name << endl << diamond_sword.ATK << endl << diamond_sword.hand << endl;
    cout << netherite_sword.name << endl << netherite_sword.ATK << endl << netherite_sword.hand << endl;
    cout << bow.name << endl << bow.ATK << endl << bow.hand << endl;
    cout << crossbow.name << endl << crossbow.ATK << endl << crossbow.hand << endl;
    cout << trident.name << endl << trident.ATK << endl << trident.hand << endl;
    cout << endl << "Armors: " << endl;
    cout << leatherh.name << endl << leatherh.DEF << endl << leatherh.place << endl;
    cout << leatherc.name << endl << leatherc.DEF << endl << leatherc.place << endl;
    cout << leatherp.name << endl << leatherp.DEF << endl << leatherp.place << endl;
    cout << leatherb.name << endl << leatherb.DEF << endl << leatherb.place << endl;
    cout << goldh.name << endl << goldh.DEF << endl << goldh.place << endl;
    cout << goldc.name << endl << goldc.DEF << endl << goldc.place << endl;
    cout << goldp.name << endl << goldp.DEF << endl << goldp.place << endl;
    cout << goldb.name << endl << goldb.DEF << endl << goldb.place << endl;
    cout << ironh.name << endl << ironh.DEF << endl << ironh.place << endl;
    cout << ironc.name << endl << ironc.DEF << endl << ironc.place << endl;
    cout << ironp.name << endl << ironp.DEF << endl << ironp.place << endl;
    cout << ironb.name << endl << ironb.DEF << endl << ironb.place << endl;
    cout << diamondh.name << endl << diamondh.DEF << endl << diamondh.place << endl;
    cout << diamondc.name << endl << diamondc.DEF << endl << diamondc.place << endl;
    cout << diamondp.name << endl << diamondp.DEF << endl << diamondp.place << endl;
    cout << diamondb.name << endl << diamondb.DEF << endl << diamondb.place << endl;
    cout << netheriteh.name << endl << netheriteh.DEF << endl << netheriteh.place << endl;
    cout << netheritec.name << endl << netheritec.DEF << endl << netheritec.place << endl;
    cout << netheritep.name << endl << netheritep.DEF << endl << netheritep.place << endl;
    cout << netheriteb.name << endl << netheriteb.DEF << endl << netheriteb.place << endl;
    cout << endl << "Enemies:" << endl;
    enemy_stats(skeleton);
    enemy_stats(husk);
    enemy_stats(zombie);
    enemy_stats(iron_golem);
    enemy_stats(creeper);
}
int main()
{
    SetConsoleTitleA("Recover your strength");
    srand((int)time(0)); //for randomness
    languagechoice(); //language choice 
    read_language(a, language); //read the story and the questions
    name(); //get the name of the character
    cout << "Loading...";
    readenemies(); //read all enemies
    readweapons(); //read all weapons
    readarmors(); //read all armors
    readitems(); //read all items
    system("CLS");
    tests(); //tests function
    //fight_start(current_enemy); //enemy fight starts
    
    return 0;
}
