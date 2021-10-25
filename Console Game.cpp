#define _CRT_SECURE_NO_WARNINGS
/*
if (f.is_open())
        {
            while (getline(f, b))
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1;
*/
#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
ifstream f("romana.txt"); //romanian version of the story
ifstream g("engleza.txt"); //english version of the story
ifstream h("enemies.txt"); //file containing enemy stats and names
ifstream questionsenglish("questionenglish.txt"); //file containing questions english
ifstream questionsromanian("questionromanian.txt"); //file containg questions romanian
ofstream save1("save1.txt"); //save file one
ofstream save2("save2.txt"); //save file two
ofstream save3("save3.txt"); //save file three
string b, first_name, last_name, c, story[10000], questions[10000];
int i, language, j, k, r;
char a;
struct item
{
    string item_name, bonus_type; //item name  //type of bonus from the item
    int bonus_number; //the bonus amount
    int price; //price of the item at a store
};
struct enemy
{
    string enemy_name, drops;
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK;
};
struct player 
{
    string player_name;
    float ATK, DEF, SPD, HLP, CHP, MPP, MDF, MAK;
};
struct inventory
{

};
void languagechoice();
void read(char);
void ico();
void icm();
void name();
void enemies(enemy &x);
void enemy_stats(enemy &x);
void items();
void playercurrentstate();
enemy iron_golem;
item iron;
void enemies(enemy &x)
{
    getline(h, b);
    x.enemy_name = b;
    h >> x.ATK >> x.DEF >> x.SPD >> x.HLP >> x.CHP >> x.MPP >> x.MDF >> x.MAK;
    getline(h, b);
    x.drops = b;
}
void enemy_stats(enemy &x)
{
    cout << x.enemy_name << " " << x.ATK << " " << x.DEF << " " << x.SPD << " " << x.HLP << " " << x.CHP << " " << x.MPP << " " << x.MDF << " " << x.MAK << endl << x.drops;
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
    cout << story[1] << endl; //ask for last name
    cin >> last_name; //read last name
    system("CLS");
    cout << story[2] << endl; //ask for first name
    cin >> first_name; //read first name
    system("CLS");
    cout << questions[1] << " " << char(39) << last_name << " " << first_name << char(39) << " " << questions[2] << "\n\n" << questions[3] << "\n" << questions[4] << "\n"; //ask if the name is correct
    ico(); //read the answer
    if (a == '2') //check if the name is correct
        name(); //redo name input if the name is incorrect
}
void items()
{
    iron.item_name = "iron";
    iron.price = 20;
}
void playercurrentstate()
{

}
int main()
{
    srand((int)time(0));
    languagechoice(); //choose langauge 
    read(a); //read the file containing the corresponding story
    name();
    enemies(iron_golem);
    enemy_stats(iron_golem);
    cout << iron_golem.drops;
    items();
}