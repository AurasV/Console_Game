#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
/*
if (f.is_open())
        {
            while (getline(f, b)) //read entire line
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1; //randomness
*/
ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
ifstream questionsromanian("questionsromanian.txt"); //file containing questions romanian
ifstream questionsenglish("questionsenglish.txt"); //file containing questions english
ifstream hungarianstory("hungarian.txt"); //hungarian version of the story
ifstream romanianstory("romana.txt"); //romanian version of the story
ifstream englishstory("engleza.txt"); //english version of the story
ofstream save1("save1.txt"); //save file one
ofstream save2("save2.txt"); //save file two
ofstream save3("save3.txt"); //save file three
string b, first_name, last_name, c, story[10000], questions[10000], d;
int i, language, j, k, r, enemy_number, e, item_number, p, weapon_number;
char a;
bool ok_name = false;
struct player //player
{
    string player_name; //player name
    float ATK, DEF, SPD, THP, CHP, MPP, MDF, MAK; //player number stats
};
struct weapon
{
    string name; //name
    float ATK; //atk bonus
    int hand; //1 for primary 2 for secondary
};
struct enemy //enemies
{
    string enemy_name; //enemy name
    float ATK, DEF, SPD, THP, CHP, MPP, MDF, MAK; //enemy number stats
    string drops; //enemy dropped item
};
struct armor //armors
{
    string name; //name
    float DEF; //def bonus
    string place; //equip place
};
struct item //items
{
    string name; //item name  //type of bonus from the item
    int price; //price of the item at a store
}; 
armor leatherh, leatherc, leatherp, leatherb, goldh, goldc, goldp, goldb, ironh, ironc, ironp, ironb, diamondh, diamondc, diamondp, diamondb, netheriteh, netheritec, netheritep, netheriteb; //armors
weapon wooden_sword, stone_sword, iron_sword, diamond_sword, netherite_sword, bow, crossbow, trident; //weapons
enemy iron_golem, zombie, skeleton, creeper, husk; //enemies
item iron_ingot, rotten_flesh, bone, gunpowder; //items
player pc; //player
void read_language(char a, int& language); //read the story and the questions
void playercurrentstate(player& x); //output current player state
void ico(); //input one character then clear console
void weapons(weapon& x); //read weapons from file
void enemy_stats(enemy& x); //output enemy_stats
void icm(); //input one word then clear console
void enemies(enemy& x); //read enemy from file
void name(); //get the name of the character
void items(item& x); //read item from file
void languagechoice(); //language choice
void readweapons(); //read all weapons
void readenemies(); //read all enemies
void readitems(); //read all items
void read_language(char a, int& language) //read the story and the questions
{
    if (a == '1')
    {
        if (englishstory.is_open()) //check if the file is open
        {
            while (getline(englishstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsenglish.is_open()) //check if the file is open
            while (getline(questionsenglish, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions
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
                i++; //increase the number for the line of the story
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsromanian.is_open()) //check if the file is open
            while (getline(questionsromanian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions
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
                i++; //increase the number for the line of the story
                story[i] = b; //add the line to the story string
            }
        }
        if (questionshungarian.is_open()) //check if the file is open
            while (getline(questionshungarian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions
                questions[j] = b; //add the line to the questions string
            }
        language = 3;
    }
}
void playercurrentstate(player& x) //output current player state
{
    system("CLS");
    p = pc.player_name.length() - 1;
    if (language == 1)
    {
        if (pc.player_name[p] == 's') //if the language is english
            cout << pc.player_name << char(39) << " current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP; //if the last letter is s
        else
            cout << pc.player_name << char(39) << "s current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP; //if the last letter isn't s
    }
    if (language == 2)
        cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK << "\nAparare: " << pc.DEF << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP; //if the language is romanian
    if (language == 3)
        cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK << "\nAparare: " << pc.DEF << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nHungarian translation needed"; //if the language is hungarian
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
    weaponstxt >> x.ATK >> x.hand;
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
    h >> x.ATK >> x.DEF >> x.SPD >> x.THP >> x.CHP >> x.MPP >> x.MDF >> x.MAK; //reading the number stats from file
    enemy_number = enemy_number + 12;
    h.close();
}
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
void readitems() //read all items
{
    items(iron_ingot);
    items(rotten_flesh);
    items(bone);
    items(gunpowder);
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
int main()
{
    srand((int)time(0)); //for randomness
    languagechoice(); //language choice 
    read_language(a, language); //read the story and the questions
    name(); //get the name of the character
    readenemies(); //read all enemies
    readitems(); //read all items
    readweapons();
    return 0;
}
