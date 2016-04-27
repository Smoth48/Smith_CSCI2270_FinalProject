/*
Tyler Smith
CSCI 2270
Final Project
*/

#include <iostream>
#include <locale>
#include <sstream>

#include "Player.h"

using namespace std;

//Converts an integer key to the respective word
string KeyToWord(int key)
{
    switch (key)
    {
    case ROCK:
        return "Rock";
    case PAPER:
        return "Paper";
    case SCISSORS:
        return "Scissors";
    default:
        return "ERROR IN KeyToWord()";
    }
}

//Game Main Menu
int MainMenu(string n)
{
    cout << endl; //Just to make things look nice.
    cout << "Enter a number, " << n << ":" << endl;
    cout << "1. Begin the Battle" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Quit Game" << endl;
    string choice;
    getline(cin, choice);
    try
    {
        return stoi(choice);
    }
    catch (exception e)
    {
        return 0;
    }

}

//Displays game instructions
void Instructions()
{
    cout << "\nGoal:" << endl;
    cout << "Reduce the other player's health to 0." << endl;
    cout << endl;
    cout << "Rules:" << endl;
    cout << "-Each player has a deck of cards" << endl;
    cout << "-Your hand consists of 7 cards" << endl;
    cout << "-You draw 3 to start your turn" << endl;
    cout << "-You play 3 cards each turn" << endl;
    cout << "-Your 3 cards battle the opponents 3 cards" << endl;
    cout << endl;
    cout << "Rocks heal you, papers swap cards with" << endl;
    cout << "the opponent, and scissors deal damage." << endl;
    cout << endl;
    cout << "A winning card can do one of two things:" << endl;
    cout << "-Empower: Double the strength of your card" << endl;
    cout << "-Nullify: Stop the opponent's card from doing stuff" << endl;
    cout << "The above effects are per card, per turn." << endl;
    cout << endl;
    cout << "Just follow the on-screen prompts, and" << endl;
    cout << "good luck destroying your opponent!" << endl;
}

//Quits the game and deletes the things
void Quit(Player *p1, Player *p2)
{
    delete p1;
    delete p2;
    cout << "Thanks for playing, bye!" << endl;
}

//Displays player info for game
void DisplayInfo(Player *p1, Player *p2, string name)
{
    cout << "\n===" << name << "===" << endl;
    cout << "Health: " << p1->GetHealth() << endl;
    p1->ShowHand();
    for (unsigned int i = 0; i < name.length() + 6; i++)
    {
        cout << "=";
    }
    cout << endl;

    cout << "\n===Opponent===" << endl;
    cout << "Health: " << p2->GetHealth() << endl;
    p2->ShowHand();
    cout << "3 Unknowns" << endl;
    cout << "==============\n" << endl;
}

//Gets input to play cards
void PlayCards(Player *p1, Player *p2)
{
    //Player 1
    bool good;
    int rocks;
    int papers;
    int scissors;
    do
    {
        good = true;
        //get user input
        cout << "Play this many rock cards: ";
        string sRock;
        getline(cin, sRock);
        cout << "Play this many paper cards: ";
        string sPaper;
        getline(cin, sPaper);
        cout << "Play this many scissors cards: ";
        string sScissors;
        getline(cin, sScissors);
        //error checking... geez, that's a lot.
        try
        {
            rocks = stoi(sRock);
            papers = stoi(sPaper);
            scissors = stoi(sScissors);
        }
        catch (exception e)
        {
            good = false;
            cout << "Looks like you typed something wrong." << endl;
        }
        if (rocks + papers + scissors != 3)
        {
            good = false;
            cout << "You must play three cards." << endl;
        }
        if (rocks < 0 || papers < 0 || scissors < 0)
        {
            good = false;
            cout << "You can't play negative cards, silly!" << endl;
        }
        if (rocks > p1->NumCardInHand(ROCK))
        {
            good = false;
            cout << "You don't have that many rocks." << endl;
        }
        if (papers > p1->NumCardInHand(PAPER))
        {
            good = false;
            cout << "You don't have that many papers." << endl;
        }
        if (scissors > p1->NumCardInHand(SCISSORS))
        {
            good = false;
            cout << "You don't have that many scissors." << endl;
        }
        if (!good)
        {
            cout << "Try again, please." << endl;
        }
    }
    while (!good); //the user finally did it right

    p1->PlayCards(rocks, papers, scissors);

    //Player 2 (AI)
    int rNum;
    int pNum;
    int sNum;
    do
    {
        rNum = rand() % 4;
        pNum = rand() % 4;
        sNum = rand() % 4;
    }
    while (rNum + pNum + sNum != 3 ||
           rNum > p2->NumCardInHand(ROCK) ||
           pNum > p2->NumCardInHand(PAPER) ||
           sNum > p2->NumCardInHand(SCISSORS));
    p2->PlayCards(rNum, pNum, sNum);
}

//Determines which cards won
void SetWinners(Player *p1, Player *p2)
{
    Card *p1Play[3];
    Card *p2Play[3];
    p1->GetCardsInPlay(p1Play);
    p2->GetCardsInPlay(p2Play);
    cout << endl; //Just to make things look nice.
    cout << "You played: " << KeyToWord(p1Play[0]->cardType) << ", ";
    cout << KeyToWord(p1Play[1]->cardType) << ", and ";
    cout << KeyToWord(p1Play[2]->cardType) << "." << endl;
    cout << "They played: " << KeyToWord(p2Play[0]->cardType) << ", ";
    cout << KeyToWord(p2Play[1]->cardType) << ", and ";
    cout << KeyToWord(p2Play[2]->cardType) << "." << endl;

    for (int i = 0; i < 3; i++) //Reset variables to default
    {
        p1Play[i]->target = nullptr;
        p1Play[i]->gotBlipped = false;
        p2Play[i]->target = nullptr;
        p2Play[i]->gotBlipped = false;
    }

    for (int i = 0; i < 3; i++) //For each card you have
    {
        for (int j = 0; j < 3; j++) //For each of their cards
        {
            if (p1Play[i]->target == nullptr) //If your card hasnt won already
            {
                if (!(p2Play[j]->gotBlipped)) //If their card hasnt lost already
                {
                    switch (p1Play[i]->cardType)
                    {
                    case ROCK:
                        if (p2Play[j]->cardType == SCISSORS)
                        {
                            p1Play[i]->target = p2Play[j];
                            p2Play[j]->gotBlipped = true;
                        }
                        break;
                    case PAPER:
                        if (p2Play[j]->cardType == ROCK)
                        {
                            p1Play[i]->target = p2Play[j];
                            p2Play[j]->gotBlipped = true;
                        }
                        break;
                    case SCISSORS:
                        if (p2Play[j]->cardType == PAPER)
                        {
                            p1Play[i]->target = p2Play[j];
                            p2Play[j]->gotBlipped = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) //Player 2 towards 1
    {
        for (int j = 0; j < 3; j++)
        {
            if (p2Play[i]->target == nullptr)
            {
                if (!(p1Play[j]->gotBlipped))
                {
                    switch (p2Play[i]->cardType)
                    {
                    case ROCK:
                        if (p1Play[j]->cardType == SCISSORS)
                        {
                            p2Play[i]->target = p1Play[j];
                            p1Play[j]->gotBlipped = true;
                        }
                        break;
                    case PAPER:
                        if (p1Play[j]->cardType == ROCK)
                        {
                            p2Play[i]->target = p1Play[j];
                            p1Play[j]->gotBlipped = true;
                        }
                        break;
                    case SCISSORS:
                        if (p1Play[j]->cardType == PAPER)
                        {
                            p2Play[i]->target = p1Play[j];
                            p1Play[j]->gotBlipped = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

//See instructions for explaination
void EmpowerOrNullify(Player *p1, Player *p2)
{
    Card *p1Play[3];
    Card *p2Play[3];
    p1->GetCardsInPlay(p1Play);
    p2->GetCardsInPlay(p2Play);

    //RESET THINGS
    for (int i = 0; i < 3; i++)
    {
        p1Play[i]->empowered = false;
        p1Play[i]->nullified = false;
        p2Play[i]->empowered = false;
        p2Play[i]->nullified = false;
    }

    cout << endl; //Just to make things look nice.

    //Player 1
    for (int i = 0; i < 3; i++)
    {
        if (p1Play[i]->target != nullptr)
        {
            cout << "Your " << KeyToWord(p1Play[i]->cardType);
            cout << " beat their " << KeyToWord(p1Play[i]->target->cardType);
            cout << "\n1) Empower or 2) Nullify - ";
            string token;
            bool success = false;
            int num;
            while (!success)
            {
                getline(cin, token);
                try
                {
                    num = stoi(token);
                    if (num == 1 || num == 2)
                    {
                        success = true;
                    }
                    else
                    {
                        cout << "Please enter 1 or 2: ";
                    }
                }
                catch (exception e)
                {
                    cout << "Please enter 1 or 2: ";
                }
            }
            switch (num)
            {
            case 1: //empower
                p1Play[i]->empowered = true;
                break;
            case 2: //nullify
                p1Play[i]->target->nullified = true;
                break;
            default:
                cout << "If this is on your screen, you fucked up" << endl;
            }
        }
    }

    cout << endl; //Just to make things look nice.

    //Player 2 (AI)
    for (int i = 0; i < 3; i++)
    {
        if (p2Play[i]->target != nullptr)
        {
            int num = rand() % 2 + 1;
            switch (num)
            {
            case 1: //empower
                p2Play[i]->empowered = true;
                cout << "The opponent empowered their ";
                cout << KeyToWord(p2Play[i]->cardType) << endl;
                break;
            case 2: //nullify
                p2Play[i]->target->nullified = true;
                cout << "The opponent nullified your ";
                cout << KeyToWord(p2Play[i]->target->cardType) << endl;
                break;
            default:
                cout << "If this is on your screen, you fucked up" << endl;
            }
        }
    }
}

//Swaps cards from one player to the other
void Swap(Player *p1, Player *p2)
{
    bool good = false;
    string in1s;
    string in2s;
    int in1;
    int in2;
    cout << "\nSwapping via paper:\nRock=1\tPaper=2\tScissors=3" << endl;
    while (!good)
    {
        good = true;
        cout << "Give them: ";
        getline(cin, in1s);
        cout << "In exchange for: ";
        getline(cin, in2s);
        try
        {
            in1 = stoi(in1s);
            in2 = stoi(in2s);
        }
        catch (exception e)
        {
            cout << "Please enter 1, 2, or 3." << endl;
            good = false;
        }
        switch (in1)
        {
        case ROCK + 1:
            if (p1->NumCardInHand(ROCK) == 0)
            {
                cout << "You don't have a Rock." << endl;
                good = false;
            }
            break;
        case PAPER + 1:
            if (p1->NumCardInHand(PAPER) == 0)
            {
                cout << "You don't have a Paper." << endl;
                good = false;
            }
            break;
        case SCISSORS + 1:
            if (p1->NumCardInHand(SCISSORS) == 0)
            {
                cout << "You don't have Scissors." << endl;
                good = false;
            }
            break;
        default:
            cout << "Please enter 1, 2, or 3." << endl;
            good = false;
        }
        switch (in2)
        {
        case ROCK + 1:
            if (p2->NumCardInHand(ROCK) == 0)
            {
                cout << "They don't have a Rock." << endl;
                good = false;
            }
            break;
        case PAPER + 1:
            if (p2->NumCardInHand(PAPER) == 0)
            {
                cout << "They don't have a Paper." << endl;
                good = false;
            }
            break;
        case SCISSORS + 1:
            if (p2->NumCardInHand(SCISSORS) == 0)
            {
                cout << "They don't have Scissors." << endl;
                good = false;
            }
            break;
        default:
            cout << "Please enter 1, 2, or 3." << endl;
            good = false;
        }
    }
    Card *give = p1->GetFromHand(--in1);
    Card *take = p2->GetFromHand(--in2);

    p1->HandRemove(in1);
    p2->HandInsert(give);

    p2->HandRemove(in2);
    p1->HandInsert(take);
}

//Calculates damage / healing / swap / death
bool ResolveTurn(Player *p1, Player *p2)
{
    cout << "\nTurn Results:" << endl;

    Card *p1Play[3];
    Card *p2Play[3];
    p1->GetCardsInPlay(p1Play);
    p2->GetCardsInPlay(p2Play);

    //Damage
    for (int i = 0; i < 3; i++)
    {
        if (p1Play[i]->cardType == SCISSORS) //p1 deal dmg
        {
            if (!p1Play[i]->nullified)
            {
                if (p1Play[i]->empowered)
                {
                    p2->GetHurt(SCISSORS_DMG * 2);
                    cout << "You dealt " << SCISSORS_DMG*2 << " damage." << endl;
                }
                else
                {
                    p2->GetHurt(SCISSORS_DMG);
                    cout << "You dealt " << SCISSORS_DMG << " damage." << endl;
                }
            }
        }
        if (p2Play[i]->cardType == SCISSORS) //p2 deal dmg
        {
            if (!p2Play[i]->nullified)
            {
                if (p2Play[i]->empowered)
                {
                    p1->GetHurt(SCISSORS_DMG * 2);
                    cout << "You took " << SCISSORS_DMG*2 << " damage." << endl;
                }
                else
                {
                    p1->GetHurt(SCISSORS_DMG);
                    cout << "You took " << SCISSORS_DMG << " damage." << endl;
                }
            }
        }
    }
    //check for death
    int dc = 0;
    if (p1->GetHealth() <= 0) //p1 dead
    {
        dc += 1;
    }
    if (p2->GetHealth() <= 0) //p2 dead
    {
        dc += 2;
    }
    switch (dc)
    {
    case 1:
        p1->Lose();
        Quit(p1, p2);
        return true;
    case 2:
        p1->Win();
        Quit(p1, p2);
        return true;
    case 3:
        p1->Draw();
        Quit(p1, p2);
        return true;
    }

    //Healing
    for (int i = 0; i < 3; i++)
    {
        if (p1Play[i]->cardType == ROCK) //p1 heal
        {
            if (!p1Play[i]->nullified)
            {
                if (p1Play[i]->empowered)
                {
                    p1->GetHeal(ROCK_HEAL * 2);
                    cout << "You gained " << ROCK_HEAL*2 << " health." << endl;
                }
                else
                {
                    p1->GetHeal(ROCK_HEAL);
                    cout << "You gained " << ROCK_HEAL << " health." << endl;
                }
            }
        }
        if (p2Play[i]->cardType == ROCK) //p2 heal
        {
            if (!p2Play[i]->nullified)
            {
                if (p2Play[i]->empowered)
                {
                    p2->GetHeal(ROCK_HEAL * 2);
                    cout << "They gained " << ROCK_HEAL*2 << " health." << endl;
                }
                else
                {
                    p2->GetHeal(ROCK_HEAL);
                    cout << "They gained " << ROCK_HEAL << " health." << endl;
                }
            }
        }
    }

    //Swapping
    for (int i = 0; i < 3; i++)
    {
        if (p1Play[i]->cardType == PAPER) //p1 swapping
        {
            if (!p1Play[i]->nullified) //paper not nulled
            {
                cout << "\nYour hand:" << endl;
                p1->ShowHand();
                cout << "\nTheir hand:" << endl;
                p2->ShowHand();
                if (p1Play[i]->empowered) //paper emp
                {
                    Swap(p1, p2);
                    Swap(p1, p2);
                }
                else //not emp
                {
                    Swap(p1, p2);
                }
            }
        }
        if (p2Play[i]->cardType == PAPER) //p2 swapping (AI)
        {
            if (!p2Play[i]->nullified) //paper not nulled
            {
                int counter = 1;
                if (p2Play[i]->empowered) //emp
                {
                    counter++;
                }
                for (int j = 0; j < counter; j++)
                {
                    Card *give = nullptr;
                    Card *take = nullptr;
                    int in1;
                    int in2;
                    while (give == nullptr)
                    {
                        give = p2->GetFromHand(in1 = rand() % 3);
                    }
                    while (take == nullptr)
                    {
                        take = p2->GetFromHand(in2 = rand() % 3);
                    }
                    p2->HandRemove(in1);
                    p1->HandInsert(give);
                    p1->HandRemove(in2);
                    p2->HandInsert(take);
                    cout << "They gave a " << KeyToWord(in1);
                    cout << " and took a " << KeyToWord(in2) << endl;
                }
            }
        }
    }

    //Discard cards in play
    p1->PlayToDiscard();
    p2->PlayToDiscard();
    return false;
}

int main()
{
    Player *p1 = new Player();

    cout << "Welcome to RPS War!" << endl;
    cout << "What is your name: ";
    string playerName;
    getline(cin, playerName);

    Player *p2 = new Player();

    int choice;
    while ((choice = MainMenu(playerName)) != 1 && choice != 3)
    {
        switch (choice)
        {
        case 2:
            Instructions();
            break;
        default:
            cout << "Bad input, please try again." << endl;
        }
    }

    cout << endl; //Just to make things look nice.

    if (choice == 3)
    {
        Quit(p1, p2);
        return 0;
    }

    bool quit = false;
    for (int i = 0; i < 4; i++)
    {
        p1->DrawCard(true);
        p2->DrawCard(false);
    }
    while (!quit)
    {
        string tmp;
        for (int i = 0; i < 3; i++)
        {
            p1->DrawCard(true);
        }
        DisplayInfo(p1, p2, playerName);
        for (int i = 0; i < 3; i++)
        {
            p2->DrawCard(false);
        }
        PlayCards(p1, p2);
        SetWinners(p1, p2);
        EmpowerOrNullify(p1, p2);
        quit = ResolveTurn(p1, p2);
        if (!quit)
        {
            cout << "Press enter to go to the next turn!" << endl;
            getline(cin, tmp);
        }
    }

    return 0;
}













