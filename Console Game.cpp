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
ifstream questionsenglish("questionenglish.txt"); //file containing questions english
ifstream questionsromanian("questionromanian.txt"); //file containing questions romanian
ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
ofstream save1("save1.txt"); //save file one
ofstream save2("save2.txt"); //save file two
ofstream save3("save3.txt"); //save file three
string b, first_name, last_name, c, story[10000], questions[10000], d;
int i, language, j, k, r, file_number, e;
char a;
bool ok_name = false;
struct item
{
    string item_name, bonus_type; //item name  //type of bonus from the item
    int bonus_number; //the bonus amount
    int price; //price of the item at a store
};
struct enemy
{
    string enemy_name; //enemy name
    float ATK, DEF, SPD, THP, CHP, MPP, MDF, MAK; //enemy number stats
    string drops; //enemy dropped item
};
struct player 
{
    string player_name; //player name
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK; //player number stats
};
enemy iron_golem, zombie, skeleton, creeper, husk;
item iron, rotten_flesh, bone, gunpowder;
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
void playercurrentstate(player &x);
void enemies(enemy& x)
{
    ifstream h("enemies.txt"); //file containing enemy stats and names
    for (e = 1; e <= file_number; e++)
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
    file_number = file_number + 12;
    h.close();
}
void readenemies()
{
    enemies(iron_golem);
    enemies(zombie);
    enemies(skeleton);
    enemies(creeper);
    enemies(husk);
}
void enemy_stats(enemy &x)
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
void languagechoice()
{
    cout << "Choose a language.\nAlege limba.\nChoose a language but hungarian.\n\n\n1)English/Engleza\n2)Romanian/Romana\n3)Hungarian/Hungarian but hungarian\n";
    ico(); //read language option
    if (a != '1' && a != '2' && a!='3')
    {
        cout << "Incorrect input please try again/Intrare incorecta te rog incearca din nou/Incorrect input please try again but hungarian" << endl; //incorrect input for the language choice
        languagechoice();
    }
}
void read_language(char a, int &language) //read the story and the questions
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
    if(a=='3')
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
void items()
{
    switch (language)
    {
    case 1:
        iron.item_name = "Iron";
        rotten_flesh.item_name = "Rotten Flesh";
        bone.item_name = "Bone";
        gunpowder.item_name = "Gunpowder";
    case 2:
        iron.item_name = "Fier";
        rotten_flesh.item_name = "Carne Putrezita";
        bone.item_name = "Os";
        gunpowder.item_name = "Praf de pusca";
    case 3:
        iron.item_name = "Iron but hungarian";
        rotten_flesh.item_name = "Rotten Flesh but hungarian";
        bone.item_name = "Bone but hungarian";
        gunpowder.item_name = "Gunpowder but hungarian";
    }
    iron.price = 20;
    rotten_flesh.price = 10;
    bone.price = 5;
    gunpowder.price = 5;
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
    items();
}
