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
ifstream romanianstory("romana.txt"); //romanian version of the story
ifstream englishstory("engleza.txt"); //english version of the story
ifstream hungarianstory("hungarian.txt"); //hungarian version of the story
ifstream questionsenglish("questionsenglish.txt"); //file containing questions english
ifstream questionsromanian("questionsromanian.txt"); //file containing questions romanian
ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
ofstream save1("save1.txt"); //save file one
ofstream save2("save2.txt"); //save file two
ofstream save3("save3.txt"); //save file three
string b, first_name, last_name, c, story[10000], questions[10000], d;
int i, language, j, k, r, enemy_number, e, item_number;
char a;
bool ok_name = false;
struct item //items
{
    string name; //item name  //type of bonus from the item
    int price; //price of the item at a store
};
struct enemy //enemies
{
    string enemy_name; //enemy name
    float ATK, DEF, SPD, THP, CHP, MPP, MDF, MAK; //enemy number stats
    string drops; //enemy dropped item
};
struct player //player
{
    string player_name; //player name
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK; //player number stats
};
struct armor //amors
{
    string name; //name
    float DEF; //def bonus
    string place; //equip place
};
enemy iron_golem, zombie, skeleton, creeper, husk;
item iron_ingot, rotten_flesh, bone, gunpowder;
armor leatherh, leatherc, leatherp, leatherb, goldh, goldc, goldp, goldb, ironh, ironc, ironp, ironb, diamondh, diamondc, diamondp, diamondb, netheriteh, netheritec, netheritep, netheriteb;
player pc;
void languagechoice();
void read_language(char a, int &language);
void ico();
void icm();
void name();
void enemies(enemy &x);
void enemy_stats(enemy &x);
void items();
void readenemies();
void readitems();
void playercurrentstate(player &x);
void enemies(enemy& x)
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
void items(item& x)
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
}
void enemy_stats(enemy& x)
{
    //system("CLS");
    if (language == 1)
        cout << "Name: " << x.enemy_name << endl << "Attack: " << x.ATK << endl << "Defense: " << x.DEF << endl << "Speed: " << x.SPD << endl << "Health Points: " << x.THP << endl << "Current Health Points: " << x.CHP << endl << "Magical Points: " << x.MPP << endl << "Magical Defense: " << x.MDF << endl << "Magical Attack: " << x.MAK << endl << "Drops: " << x.drops; // output enemy stats and drops
    if (language == 2)
        cout << "Nume: " << x.enemy_name << endl << "Atac: " << x.ATK << endl << "Aparare: " << x.DEF << endl << "Viteza: " << x.SPD << endl << "Puncte Viata: " << x.THP << endl << "Puncte Viata Curente: " << x.CHP << endl << "Puncte Magie: " << x.MPP << endl << "Aparare Magica: " << x.MDF << endl << "Atac Magic: " << x.MAK << endl << "Drop-uri: " << x.drops; // output enemy stats and drops
    if (language == 3)
        cout << "Name but hungarian: " << x.enemy_name << endl << "Attack but hungarian: " << x.ATK << endl << "Defense but hungarian: " << x.DEF << endl << "Speed but hungarian: " << x.SPD << endl << "Current Health Points but hungarian: " << x.THP << endl << "Total Health Points but hungarian: " << x.CHP << endl << "Magic Points but hungarian: " << x.MPP << endl << "Magic Defense but hungarian: " << x.MDF << endl << "Magic Attack but hungarian: " << x.MAK << endl << "Drops but hungarian: " << x.drops; // output enemy stats and drops
    cout << endl << endl;
}
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
void readenemies()
{
    enemies(iron_golem);
    enemies(zombie);
    enemies(skeleton);
    enemies(creeper);
    enemies(husk);
}
void readitems()
{
    items(iron_ingot);
    items(rotten_flesh);
    items(bone);
    items(gunpowder);
}
void languagechoice()
{
    cout << "Choose a language.\nAlege limba.\nChoose a language but hungarian.\n\n\n1)English/Engleza/\n2)Romana/Romanian/\n3)Magyar/Maghiara/Hungarian\n";
    ico(); //read language option
    if (a != '1' && a != '2' && a!='3')
    {
        cout << "Incorrect input please try again/Intrare incorecta te rog incearca din nou/Incorrect input please try again but hungarian" << endl; //incorrect input for the language choice
        languagechoice();
    }
}
void ico() //input one character and clear console
{
    a = _getch(); //read one character user input
    system("CLS"); //clear console
}
void icm() //input more characters and clear console
{
    cin >> c; //read multiple characters user input
    system("CLS"); //clear console
}
void name()
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
}
void playercurrentstate(player &x)
{

}
int main()
{
    srand((int)time(0)); //for randomness
    languagechoice(); //choose langauge 
    read_language(a, language); //read the file containing the corresponding story
    name(); //ask for the name of the character
    readenemies();
    readitems();
}
