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
            while (getline(f, b))
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1;
*/
ifstream f("romana.txt"); //romanian version of the story
ifstream g("engleza.txt"); //english version of the story
ifstream questionsenglish("questionenglish.txt"); //file containing questions english
ifstream questionsromanian("questionromanian.txt"); //file containg questions romanian
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
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK; //enemy number stats
    string drops; //enemy dropped item
};
struct player 
{
    string player_name; //player name
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK; //player number stats
};
enemy iron_golem, zombie, skeleton, creeper;
item iron, rotten_flesh, bone, gunpoweder;
player pc;
void languagechoice();
void read(char);
void ico();
void icm();
void name();
void enemies(enemy &x);
void enemy_stats(enemy &x);
void items();
void readenemies();
void playercurrentstate(player &x);
void enemies(enemy &x)
{
    ifstream h("enemies.txt"); //file containing enemy stats and names
    for (e = 1; e <= file_number; e++)
        getline(h, b); //skip unncessary lines
    getline(h, d); //getting line
    x.enemy_name = d; //enemy name 
    getline(h, d); //getting line
    x.drops = d; //enemy drops
    h >> x.ATK >> x.DEF >> x.SPD >> x.HLP >> x.CHP >> x.MPP >> x.MDF >> x.MAK; //reading the number stats from file
    file_number = file_number + 10;
    h.close();
}
void readenemies()
{
    enemies(iron_golem);
    enemies(zombie);
    enemies(skeleton);
    enemies(creeper);
}
void enemy_stats(enemy &x)
{
    system("CLS");
    cout << "Name: " << x.enemy_name << endl << "Attack: " << x.ATK << endl << "Defense: " << x.DEF << endl << "Speed: " << x.SPD << endl << "Health Points: " << x.HLP << endl << "Current Health Points: " << x.CHP << endl << "Magical Points: " << x.MPP << endl << "Magical Defense: " << x.MDF << endl << "Magical Attack: " << x.MAK << endl << "Drops: " << x.drops; // output enemy stats and drops
    cout << endl << endl;
}
void languagechoice()
{
    cout << "Choose a language.\nAlege limba.\n\n\n1)English/Engleza\n2)Romanian/Romana\n";
    ico(); //read language option
    if (a != '1' && a != '2')
    {
        cout << "Incorrect input please try again/Intrare incorecta te rog incearca din nou" << endl; //incorrect input for the language choice
        languagechoice();
    }
}
void read(char a) //read the story and the questions
{
    if (a == '1') //check if the answer is english
    {
        if (g.is_open()) //check if the file is open
        {
            while (getline(g, b)) //read line and store in b
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
    if (a == '2') //check if the answer is romanian
    {
        if (f.is_open()) //check if the file is open
        {
            while (getline(f, b)) //read line and store in b
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
    iron.item_name = "iron";
    iron.price = 20;
}
void playercurrentstate(player &x)
{

}
int main()
{
    srand((int)time(0)); //for randomness
    languagechoice(); //choose langauge 
    read(a); //read the file containing the corresponding story
    name(); //ask for the name of the character
    readenemies();
    items();
}