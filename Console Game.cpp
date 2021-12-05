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
/*
if (f.is_open())
        {
            while (getline(f, b)) //read entire line
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1; //randomness
*/
/*
TO DO:
finish fight_action function
finish implementing shop //text already made for all versions
implement the use for player stats
make the menu after game start (including but not limited to, text that says where you are and where you can go/do
make a check for levels (more exactly for when the game is done)
think of player progression when it comes to leveling up and stats increase from that
think of how enemies scale
save system
think of what's missing
*/
std::ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
std::ifstream questionsromanian("questionsromanian.txt"); //file containing questions romanian
std::ifstream questionsenglish("questionsenglish.txt"); //file containing questions english
std::ifstream fighthungarian("fighthungarian.txt"); //hungarian version for fights
std::ifstream fightromanian("fightromanian.txt"); //romanian version for fights
std::ifstream fightenglish("fightenglish.txt"); //english version for fights
std::ifstream hungarianstory("hungarian.txt"); //hungarian version of the story
std::ifstream romanianstory("romanian.txt"); //romanian version of the story
std::ifstream englishstory("english.txt"); //english version of the story
std::ifstream shophungarian("shophungarian.txt"); //hungarian version of the shop
std::ifstream shopromanian("shopromanian.txt"); //romanian version of the shop
std::ifstream shopenglish("shopenglish.txt"); //english version of the shop
std::ifstream menuenglish("menuenglish.txt"); //english version of the menu
std::ifstream menuromanian("menuromanian.txt"); //romanian version of the menu
std::ifstream menuhungarian("menuhungarian.txt"); //hungarian version of the menu
std::string b, first_name, last_name, c, story[100], questions[100], d, ar, fight[100],shop[100],menu[100];
int i, language, j, k, r, enemy_number, e, item_number, p, weapon_number, armor_number;
char a; //player input variable
bool ok_name = false, ok_fight_first = true, ok_access_shop = false;
struct player //player
{
    std::string player_name = { " " }; //player name
    float ATK = { 5 }, DEF = { 5 }, THP = { 20 }, CHP = { 20 }; //player number stats
    int current_xp = { 0 }; //current xp
    int level = { 1 }; //current level
    int xp_to_next_level = { 100 };
    int current_gold = { 0 };
};
struct weapon
{
    std::string name = { " " }; //name
    float ATK = { 0 }; //atk bonus
    std::string hand = { " " }; //main / off hand
};
struct enemy //enemies
{
    std::string enemy_name = { " " }; //enemy name
    float ATK = { 0 }, DEF = { 0 }, THP = { 0 }, CHP = { 0 }; //enemy number stats
    std::string drops = { " " }; //enemy dropped item
};
struct armor //armors
{
    std::string name = { " " }; //name
    float DEF = { 0 }; //def bonus
    std::string place = { " " }; //equip place
};
struct item //items
{
    std::string name = { " " }; //item name  //type of bonus from the item
    int price = { 0 }; //price of the item at a store
}; 
struct equipment
{
    std::string head = { "nothing" }; //head equipment name
    std::string chest = { "nothing" }; //chest equipment name
    std::string pants = { "nothing" }; //pants equipment name
    std::string boots = { "nothing" }; //boots equipment name
    int h_def = { 0 }; //head def
    int c_def = { 0 }; //chest def
    int p_def = { 0 }; //pants def
    int b_def = { 0 }; //boots def
};
armor leatherh, leatherc, leatherp, leatherb, goldh, goldc, goldp, goldb, ironh, ironc, ironp, ironb, diamondh, diamondc, diamondp, diamondb, netheriteh, netheritec, netheritep, netheriteb; //armors
weapon wooden_sword, stone_sword, iron_sword, diamond_sword, netherite_sword, bow, crossbow, trident; //weapons
enemy iron_golem, zombie, skeleton, creeper, husk, current_enemy; //enemies
item iron_ingot, rotten_flesh, bone, gunpowder, normal_hp, greater_hp, supreme_hp; //items
player pc; //player
equipment equip; //currently equipped stuff
void languagechoice(); //language choice
void read_language(char a, int& language); //read the story and the questions
void readfight(); //read all fight needed text
void readweapons(); //read all weapons
void readenemies(); //read all enemies
void readarmors(); //read all armors
void readitems(); //read all items
void playercurrentstate(player& x); //output current player state
void fight_action(enemy& current_enemy); //fight function
void fight_enemy_generate(enemy& enemy); //generate enemy function
void ico(); //input one character then clear console
void enemy_stats(enemy& x); //output enemy_stats
void weapons(weapon& x); //read weapons from file
void enemies(enemy& x); //read enemy from file
void armors(armor& x); //read armor from file
void items(item& x); //read item from file
void name(); //get the name of the character
void tests(); //tests funciton
void access_shop(); //access shop
void shop_buy(); //buying section of shop
void shop_sell(); //selling section of shop
void buy_armor(); //armor buying section of shop
void buy_weapon(); //weapon buying section of shop
void buy_health_potion(); //health potion buying section of shop
void buy_leather(); //leather armor buying section of shop
void buy_gold(); //gold armor buying section of shop
void buy_iron(); //iron armor buying section of shop
void buy_diamond(); //diamond armor buying section of shop
void buy_netherite(); //netherite armor buying section of shop
void buy_main_hand(); //main hand weapon buying section of shop
void buy_off_hand(); //off hand weapon buying section of shop
void main_menu(); //main menu
void readshop(); //shop reading function
void readfight(); //fight reading function
void readmenu(); //menu reading function
void languagechoice() //language choice
{
    std::cout << "Choose a language.\nAlege limba.\nValassz nyelvet.\n\n\n1)English/Engleza/Angol\n2)Romana/Romanian/Roman\n3)Magyar/Maghiara/Hungarian\n";
    ico(); //read language option
    if (a != '1' && a != '2' && a != '3')
    {
        std::cout << "Incorrect input, please try again:/Intrare incorecta, te rog incearca din nou:/Hiba, kerlek probald ujra:" << "\n"; //incorrect input for the language choice
        languagechoice();
    }
}
void read_language(char a, int& language) //read the story and the questions
{
    switch (a)
    {
    case '1': //if language is english
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
        break;
    case '2': //if language is romanian
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
        break;
    case '3': //if language is hungarian
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
        break;
    }
}
void readweapons()
{
    weapons(wooden_sword); //read wooden sword
    weapons(stone_sword); //read stone sword
    weapons(iron_sword); //read iron sword
    weapons(diamond_sword); //read diamond sword
    weapons(netherite_sword); //read netherite sword
    weapons(bow); //read bow
    weapons(crossbow); //read crossbow
    weapons(trident); //read trident
}
void readenemies() //read all enemies
{
    enemies(iron_golem); //read iron golem
    enemies(zombie); //read zombie
    enemies(skeleton); //read skeleton
    enemies(creeper); //read creeper
    enemies(husk); //read husk
}
void readarmors() //read all armors
{
    armors(leatherh); //read leather helmet
    armors(leatherc); //read leather chestplate
    armors(leatherp); //read leather pants
    armors(leatherb); //read leather boots
    armors(goldh); //read gold helmet
    armors(goldc); //read gold chestplate
    armors(goldp); //read gold pants
    armors(goldb); //read gold boots
    armors(ironh); //read iron helmet
    armors(ironc); //read iron chestplate
    armors(ironp); //read iron pants
    armors(ironb); //read iron boots
    armors(diamondh); //read diamond helmet
    armors(diamondc); //read diamond chestplate
    armors(diamondp); //read diamond pants
    armors(diamondb); //read diamond boots
    armors(netheriteh); //read netherite helmet
    armors(netheritec); //read netherite chestplate
    armors(netheritep); //read netherite pants
    armors(netheriteb); //read netherite boots
}
void readitems() //read all items
{
    items(iron_ingot); // read iron ingot
    items(rotten_flesh); //read rotten flesh
    items(bone); //read bone
    items(gunpowder); //read gunpowder
    items(normal_hp); //read normal health potion
    items(greater_hp); //read greater health potion
    items(supreme_hp); //read supreme health potion
}
void readfight()
{
    i = 1;
    switch (language) 
    {
    case 1: //if language is english
        if (fightenglish.is_open()) //check if file is open
            while (getline(fightenglish, b)) //read line and store in b
            {
                fight[i] = b; //add the line to the fight string
                i++; //increase the number for the line of the fight string
            }
        break;
    case 2: //if language is romanian
        while (getline(fightromanian, b)) //read line and store in b
        {
            fight[i] = b; //add the line to the fight string
            i++; //increase the number for the line of the fight string
        }
        break;
    case 3: //if language is hungarian
        while (getline(fighthungarian, b)) //read line and store in b
        {
            fight[i] = b; //add the line to the fight string
            i++; //increase the number for the line of the fight string
        }
        break;
    }
    fightromanian.close(); //close romanian version of file
    fightenglish.close(); //close english version of file
    fighthungarian.close(); //close hungarian version of file
}
void readshop()
{
    i = 1;
    if (language == 1) //if language is english
        if (shopenglish.is_open()) //check if file is open
        {
            while (getline(shopenglish, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    if (language == 2) //if language is romanian
        if (shopromanian.is_open()) //check if file is open
        {
            while (getline(shopromanian, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    if (language == 3) //if language is hungarian
        if (shophungarian.is_open()) //check if file is open
        {
            while (getline(shophungarian, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    shopenglish.close(); //close english version of file
    shophungarian.close(); //close hungarian version of file
    shopromanian.close(); //close romanian version of file
}
void readmenu()
{

}
//have to finish this ^
void access_shop()
{
    for (int shop_counter = 1; shop_counter <= 6; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read shop action
    switch (a)
    {
    case '1':
        shop_buy(); //if answer is buy
        break;
    case '2':
        shop_sell(); //if answer is sell
        break;
    case '0':
        main_menu();
        std::cout << "\n";
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        access_shop();
        break;
    }
}
void shop_buy()
{
    for (int shop_counter = 7; shop_counter <= 11; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read action
    switch (a)
    {
    case '1':
        buy_armor();
        break;
    case '2':
        buy_weapon();
        break;
    case '3':
        buy_health_potion();
        break;
    case '0':
        access_shop();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        shop_buy();
    }

}
void shop_sell()
{
    for (int shop_counter = 70; shop_counter <= 75; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //sell bones if they have any
        break;
    case '2':
        //sell rotten flesh if they have any
        break;
    case '3':
        //sell iron ingot if they have any
        break;
    case '4':
        //sell gunpowder if they have any
        break;
    case '0':
        access_shop();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        shop_sell();
        break;
    }
}
//have to finish this ^
void buy_armor()
{
    for (int shop_counter = 12; shop_counter <= 18; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        buy_leather();
        break;
    case '2':
        buy_gold();
        break;
    case '3':
        buy_iron();
        break;
    case '4':
        buy_diamond();
        break;
    case '5':
        buy_netherite();
        break;
    case '0':
        shop_buy();
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_armor();
    }
}
void buy_leather()
{
    for (int shop_counter = 19; shop_counter <= 24; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '2':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '3':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '4':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '0':
        buy_armor();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_leather();
        break;
    }
}
//have to finish this ^
void buy_gold()
{
    for (int shop_counter = 25; shop_counter <= 30; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '2':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '3':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '4':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '0':
        buy_armor();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_gold();
        break;
    }
}
//have to finish this ^
void buy_iron()
{
    for (int shop_counter = 31; shop_counter <= 36; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '2':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '3':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '4':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '0':
        buy_armor();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_iron();
        break;
    }
}
//have to finish this ^
void buy_diamond()
{
    for (int shop_counter = 37; shop_counter <= 42; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '2':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '3':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '4':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '0':
        buy_armor();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_diamond();
        break;
    }
}
//have to finish this ^
void buy_netherite()
{
    for (int shop_counter = 43; shop_counter <= 48; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '2':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '3':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '4':
        //check gold and if its better than currently equipped armor then change or give out message if its appropriate
        break;
    case '0':
        buy_armor();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_netherite();
        break;
    }
}
//have to finish this ^
void buy_weapon()
{
    for (int shop_counter = 49; shop_counter <= 52; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        buy_main_hand();
        break;
    case '2':
        buy_off_hand();
        break;
    case '0':
        shop_buy();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_weapon();
        break;
    }

}
//have to finish this ^
void buy_main_hand()
{
    for (int shop_counter = 53; shop_counter <= 59; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //buy wooden sword (if you have enough gold and its better than currently equipped one)
        break;
    case '2':
        //buy stone sword (if you have enough gold and its better than currently equipped one)
        break;
    case '3':
        //buy iron sword (if you have enough gold and its better than currently equipped one)
        break;
    case '4':
        //buy diamond sword (if you have enough gold and its better than currently equipped one)
        break;
    case '5':
        //buy netherite sword (if you have enough gold and its better than currently equipped one)
        break;
    case '0':
        buy_weapon();
        break;
    default:
        std::cout << shop[79] << "\n"; //if wrong input
        buy_main_hand();
        break;
    }
}
//have to finish this ^
void buy_off_hand()
{
    for (int shop_counter = 60; shop_counter <= 64; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read player's choice
    switch (a)
    {
    case '1':
        //buy bow (if you have enough gold and its better than currently equipped one)
        break;
    case '2':
        //buy crossbow (if you have enough gold and its better than currently equipped one)
        break;
    case '3':
        //buy trident (if you have enough gold and its better than currently equipped one)
        break;
    case '0': //go back
        buy_weapon();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_off_hand();
        break;
    }

}
//have to finish this ^
void buy_health_potion() //buy health potion
{
    for (int shop_counter = 65; shop_counter <= 69; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        //buy normal health potion if you have gold
        break;
    case '2':
        //buy greater health potion if you have gold
        break;
    case '3':
        //buy ultimate health potion if you have gold
    case '0':
        shop_buy(); //go back
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_health_potion();
        break;
    }
}
//have to finish this ^
void fight_action(enemy& current_enemy)
{
    if (ok_fight_first == true)
        std::cout << fight[1] << " " << current_enemy.enemy_name; //you've been attacked by on the first run
    else std::cout << fight[2] << " " << current_enemy.enemy_name; //you're currently fighting on the subsequent ones
}
//have to finish this ^
void fight_enemy_generate(enemy& current_enemy) //generate enemy
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
    //system("CLS");
    p = pc.player_name.length() - 1; //i dont really remember why this is here
    switch (language)
    {
    case 1: //if the language is english
        if (pc.player_name[p] == 's') //special case because english is a special language
            std::cout << pc.player_name << char(39) << " current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_to_next_level - pc.current_xp; //if the last letter is s
        else
            std::cout << pc.player_name << char(39) << "s current stats are:\nAttack: " << pc.ATK << "\nDefense: " << pc.DEF << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_to_next_level - pc.current_xp; //if the last letter isn't s
        break;
    case 2: //if the language is romanian
        std::cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK << "\nAparare: " << pc.DEF << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nNivel: " << pc.level << "\nAur: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Pana la Cresterea Nivelului: " << pc.xp_to_next_level - pc.current_xp;; //if the language is romanian
        break;
    case 3: //if the language is hungarian
        std::cout << "Jelenlegi statisztikak " << pc.player_name << ":\n" << "Tamadas : " << pc.ATK << "\nVedekezes: " << pc.DEF << "\nAz osszes eletero: " << pc.THP << "\nJelenlegi eletero: " << pc.CHP << "\nSzint: " << pc.level << "\nArany: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP szukseges a szint lepeshez: " << pc.xp_to_next_level - pc.current_xp; //if the language is hungarian
        break;
    }
}
void enemy_stats(enemy& x) //output enemy stats
{
    //system("CLS");
    switch (language)
    {
    case 1: //if the language is english
        std::cout << "Name: " << x.enemy_name << "\n" << "Attack: " << x.ATK << "\n" << "Defense: " << x.DEF << "\n" << "Total Health Points: " << x.THP << "\n" << "Current Health Points: " << x.CHP << "\n" << "Drops: " << x.drops; // output enemy stats and drops
        break;
    case 2: //if the language is romanian
        std::cout << "Nume: " << x.enemy_name << "\n" << "Atac: " << x.ATK << "\n" << "Aparare: " << x.DEF << "\n" << "Puncte Viata Totale: " << x.THP << "\n" << "Puncte Viata Curente: " << x.CHP << "\n" << "Drop-uri: " << x.drops; // output enemy stats and drops
        break;
    case 3: //if the language is hungarian
        std::cout << "Nev: " << x.enemy_name << "\n" << "Tamadas: " << x.ATK << "\n" << "Vedekezes: " << x.DEF << "\n" << "Az osszes eletero: " << x.THP << "\n" << "Jelenlegi eletero: " << x.CHP << "\n" << "Eszkozoket: " << x.drops; // output enemy stats and drops
        break;
    }
        std::cout << "\n" << "\n";
}
//have to add the clear console here and finish it after fight functions are done ^
void weapons(weapon& x) //read weapon from file
{
    std::ifstream weaponstxt("weapons.txt");
    for (e = 1; e <= weapon_number; e++)
        std::getline(weaponstxt, b); //skip unnecessary lines
    std::getline(weaponstxt, b); //getting line
    switch (language)
    {
    case 1: //if the language is english
        x.name = b; //weapon name
        std::getline(weaponstxt, b);
        std::getline(weaponstxt, b);
        break;
    case 2: //if the language is romanian
        std::getline(weaponstxt, b);
        x.name = b; //weapon name
        std::getline(weaponstxt, b);
        break;
    case 3: //if the language is hungarian
        getline(weaponstxt, b);
        getline(weaponstxt, b);
        x.name = b; //weapon name
        break;
    }
    getline(weaponstxt, b); //get the hand for the weapon
    x.hand = b; //save weapon hand
    weaponstxt >> x.ATK; //read weapon atk stat
    weapon_number += 5; //increase to get to next weapon
    weaponstxt.close(); //close weapon file
}
void enemies(enemy& x) //read enemy from file
{
    std::ifstream enemies("enemies.txt"); //file containing enemy stats and names
    for (e = 1; e <= enemy_number; e++)
        std::getline(enemies, b); //skip unncessary lines
    std::getline(enemies, d); //getting line
    x.enemy_name = d; //enemy name 
    std::getline(enemies, d); //getting line
    switch (language)
    {
    case 1: //if the language is english
        x.drops = d; //enemy drops
        std::getline(enemies, d);
        std::getline(enemies, d);
        break;
    case 2: //if the language is romanian
        std::getline(enemies, d);
        x.drops = d; //enemy drops
        std::getline(enemies, d);
        break;
    case 3: //if the language is hungarian
        std::getline(enemies, d);
        std::getline(enemies, d);
        x.drops = d; //enemy drops
        break;
    }
    enemies >> x.ATK >> x.DEF >> x.THP >> x.CHP; //reading the number stats from file
    enemy_number = enemy_number + 8; //increase to get to next enemy
    enemies.close(); //close enemy file
}
void armors(armor& x) //read armor from file
{
    std::ifstream armortxt("armor.txt"); //file containg armor stats names and placement
    for (e = 1; e <= armor_number; e++)
        std::getline(armortxt, ar); //skip unnecessary lines
    std::getline(armortxt, ar);
    switch (language)
    {
    case 1: //if the language is english
        x.name = ar; //armor name
        std::getline(armortxt, ar);
        std::getline(armortxt, ar);
        break;
    case 2: //if the language is romanian
        std::getline(armortxt, ar);
        x.name = ar; //armor name
        std::getline(armortxt, ar);
        break;
    case 3: //if the language is hungarian
        std::getline(armortxt, ar);
        std::getline(armortxt, ar);
        x.name = ar; //armor name
        break;
    }
    std::getline(armortxt, ar); //ger armor place
    x.place = ar; //save armor place
    armortxt >> x.DEF; //save armor def
    armor_number = armor_number + 5; //increase to get to next armor piece
    armortxt.close(); //close armor file
}
void items(item& x) //read item from file
{
    std::ifstream items("items.txt"); //items file
    for (e = 1; e <= item_number; e++)
        std::getline(items, b); //skip unneccessary lines
    std::getline(items, b); //get first important line
    switch (language)
    {
    case 1: //if language is english
        x.name = b; //item name
        std::getline(items, b);
        std::getline(items, b);
        break;
    case 2: //if language is romanian
        std::getline(items, b);
        x.name = b; //item name
        std::getline(items, b);
        break;
    case 3: //if language is hungarian
        std::getline(items, b);
        std::getline(items, b);
        x.name = b; //item name
        break;
    }
    items >> x.price; //get the price of item
    item_number += 4; //increase to get the next item
    items.close(); //close items file
}
void name() //get the name of the character
{
    if (ok_name != true) //first time run test
        std::cout << story[1] << "\n"; //ask for name
    else //if the input was incorrect last time
    {
        std::cout << "Incorrect Input. Please try again" << "\n";
        std::cout << story[1] << "\n";
    }
    std::getline(std::cin, pc.player_name); //read name
    system("CLS");
    std::cout << questions[1] << " " << char(39) << pc.player_name << char(39) << " " << questions[2] << "\n\n" << questions[3] << "\n" << questions[4] << "\n"; //ask if the name is correct
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
void ico() //input one character then clear console
{
    a = _getch(); //read one character user input
    system("CLS"); //clear console
}
void tests()
{
    std::cout << "Items: " << "\n";
    std::cout << iron_ingot.name << "\n" << iron_ingot.price << "\n";
    std::cout << bone.name << "\n" << bone.price << "\n";
    std::cout << rotten_flesh.name << "\n" << rotten_flesh.price << "\n";
    std::cout << gunpowder.name << "\n" << gunpowder.price << "\n";
    std::cout << normal_hp.name << "\n" << normal_hp.price << "\n";
    std::cout << greater_hp.name << "\n" << greater_hp.price << "\n";
    std::cout << supreme_hp.name << "\n" << supreme_hp.price << "\n";
    std::cout << "\n" << "Weapons: " << "\n";
    std::cout << wooden_sword.name << "\n" << wooden_sword.ATK << "\n" << wooden_sword.hand << "\n";
    std::cout << stone_sword.name << "\n" << stone_sword.ATK << "\n" << stone_sword.hand << "\n";
    std::cout << iron_sword.name << "\n" << iron_sword.ATK << "\n" << iron_sword.hand << "\n";
    std::cout << diamond_sword.name << "\n" << diamond_sword.ATK << "\n" << diamond_sword.hand << "\n";
    std::cout << netherite_sword.name << "\n" << netherite_sword.ATK << "\n" << netherite_sword.hand << "\n";
    std::cout << bow.name << "\n" << bow.ATK << "\n" << bow.hand << "\n";
    std::cout << crossbow.name << "\n" << crossbow.ATK << "\n" << crossbow.hand << "\n";
    std::cout << trident.name << "\n" << trident.ATK << "\n" << trident.hand << "\n";
    std::cout << "\n" << "Armors: " << "\n";
    std::cout << leatherh.name << "\n" << leatherh.DEF << "\n" << leatherh.place << "\n";
    std::cout << leatherc.name << "\n" << leatherc.DEF << "\n" << leatherc.place << "\n";
    std::cout << leatherp.name << "\n" << leatherp.DEF << "\n" << leatherp.place << "\n";
    std::cout << leatherb.name << "\n" << leatherb.DEF << "\n" << leatherb.place << "\n";
    std::cout << goldh.name << "\n" << goldh.DEF << "\n" << goldh.place << "\n";
    std::cout << goldc.name << "\n" << goldc.DEF << "\n" << goldc.place << "\n";
    std::cout << goldp.name << "\n" << goldp.DEF << "\n" << goldp.place << "\n";
    std::cout << goldb.name << "\n" << goldb.DEF << "\n" << goldb.place << "\n";
    std::cout << ironh.name << "\n" << ironh.DEF << "\n" << ironh.place << "\n";
    std::cout << ironc.name << "\n" << ironc.DEF << "\n" << ironc.place << "\n";
    std::cout << ironp.name << "\n" << ironp.DEF << "\n" << ironp.place << "\n";
    std::cout << ironb.name << "\n" << ironb.DEF << "\n" << ironb.place << "\n";
    std::cout << diamondh.name << "\n" << diamondh.DEF << "\n" << diamondh.place << "\n";
    std::cout << diamondc.name << "\n" << diamondc.DEF << "\n" << diamondc.place << "\n";
    std::cout << diamondp.name << "\n" << diamondp.DEF << "\n" << diamondp.place << "\n";
    std::cout << diamondb.name << "\n" << diamondb.DEF << "\n" << diamondb.place << "\n";
    std::cout << netheriteh.name << "\n" << netheriteh.DEF << "\n" << netheriteh.place << "\n";
    std::cout << netheritec.name << "\n" << netheritec.DEF << "\n" << netheritec.place << "\n";
    std::cout << netheritep.name << "\n" << netheritep.DEF << "\n" << netheritep.place << "\n";
    std::cout << netheriteb.name << "\n" << netheriteb.DEF << "\n" << netheriteb.place << "\n";
    std::cout << "\n" << "Enemies:" << "\n";
    enemy_stats(skeleton);
    enemy_stats(husk);
    enemy_stats(zombie);
    enemy_stats(iron_golem);
    enemy_stats(creeper);
    playercurrentstate(pc);
}
//only a test function have to delete before final iteration ^
void main_menu() 
{

}
//have to finish this ^
int main()
{
    SetConsoleTitleA("Recover your strength"); //set the title of the game
    srand((int)time(0)); //for randomness
    languagechoice(); //language choice 
    read_language(a, language); //read the story and the questions
    name(); //get the name of the character
    std::cout << "Loading..."; //loading screen 
    readenemies(); //read all enemies
    readweapons(); //read all weapons
    readarmors(); //read all armors
    readitems(); //read all items
    readshop(); //read the needed text for shop
    readfight(); //read all fight text
    system("CLS"); //clear console
    tests(); //tests function
    //fight_enemy_generate(current_enemy); //generate enemy to fight using randomness
    //access_shop();
    //playercurrentstate(pc);
    return 0;
}
