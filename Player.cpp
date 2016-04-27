#include "Player.h"

using namespace std;

Player::Player()
{
    srand(time(NULL));
    health = INIT_HEALTH;
    BuildDeck();
    ShuffleDeck();
}

Player::~Player()
{
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        delete hand[i];
    }
    for (unsigned int i = 0; i < inPlay.size(); i++)
    {
        delete inPlay[i];
    }
    for (unsigned int i = 0; i < deck.size(); i++)
    {
        delete deck.top();
        deck.pop();
    }
    for (unsigned int i = 0; i < discard.size(); i++)
    {
        delete discard.top();
        discard.pop();
    }
}

void Player::BuildDeck()
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        Card *c = new Card;
        c->cardType = i % 3;
        deck.push(c);
    }
}

void Player::ShuffleDeck()
{
    srand(time(NULL));
    int numCards = deck.size();
    Card *newDeck[numCards];
    for (int i = 0; i < numCards; i++)
    {
        newDeck[i] = nullptr;
    }
    while (deck.size() != 0)
    {
        Card *c = deck.top();
        deck.pop();
        int index = rand() % numCards;
        while (newDeck[index] != nullptr)
        {
            index = rand() % numCards;
        }
        newDeck[index] = c;
    }
    for (int i = 0; i < numCards; i++)
    {
        deck.push(newDeck[i]);
    }
}

void Player::Reshuffle()
{
    cout << "Reshuffling deck..." << endl;
    for (unsigned int i = 0; i < discard.size(); i++)
    {
        Card *c = discard.top();
        discard.pop();
        deck.push(c);
    }
    ShuffleDeck();
}

void Player::DrawCard(bool output)
{
    if (deck.empty())
    {
        Reshuffle();
    }
    Card *c = deck.top();
    deck.pop();
    HandInsert(c);
    string type;
    switch (c->cardType)
    {
    case ROCK:
        type = "Rock";
        break;
    case PAPER:
        type = "Paper";
        break;
    case SCISSORS:
        type = "Scissors";
        break;
    }
    if (output)
        cout << "You drew a " << type << " card." << endl;
}

void Player::Discard(Card *card)
{
    discard.push(card);
}

void Player::PlayCards(int rocks, int papers, int scissors)
{
    Card *c;
    int index;
    while (rocks != 0)
    {
        index = 0;
        c = hand[index];
        while (c->cardType != ROCK)
        {
            c = hand[++index];
        }
        HandRemove(c->cardType);
        inPlay.push_back(c);
        rocks--;
    }
    while (papers != 0)
    {
        index = 0;
        c = hand[index];
        while (c->cardType != PAPER)
        {
            c = hand[++index];
        }
        HandRemove(c->cardType);
        inPlay.push_back(c);
        papers--;
    }
    while (scissors != 0)
    {
        index = 0;
        c = hand[index];
        while (c->cardType != SCISSORS)
        {
            c = hand[++index];
        }
        HandRemove(c->cardType);
        inPlay.push_back(c);
        scissors--;
    }
}

void Player::PlayToDiscard()
{
    int num = inPlay.size();
    for (int i = 0; i < num; i++)
    {
        Card *c = inPlay[0];
        inPlay.erase(inPlay.begin());
        discard.push(c);
    }
}

void Player::GetHurt(int num)
{
    health -= num;
}

void Player::GetHeal(int num)
{
    health += num;
}

void Player::HandInsert(Card *card)
{
    hand.push_back(card);
}

void Player::HandRemove(int type)
{
    int index;
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        if (hand[i]->cardType == type)
        {
            index = i;
            break;
        }
    }
    for (unsigned int i = index; i < hand.size() - 1; i++)
    {
        hand[i] = hand[i + 1];
    }
    hand.pop_back();
}

int Player::GetHealth()
{
   return health;
}

void Player::ShowHand()
{
    cout << "Cards in Hand:" << endl;
    int rock = 0;
    int paper = 0;
    int scissors = 0;
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        switch ((hand[i])->cardType)
        {
        case ROCK:
            rock++;
            break;
        case PAPER:
            paper++;
            break;
        case SCISSORS:
            scissors++;
            break;
        }
    }
    cout << rock << " Rocks" << endl;
    cout << paper << " Papers" << endl;
    cout << scissors << " Scissors" << endl;
}

int Player::NumCardInHand(int type)
{
    int num = 0;
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        if (hand[i]->cardType == type)
        {
            num++;
        }
    }
    return num;
}

Card *Player::GetFromHand(int type)
{
    for (unsigned int i = 0; i < hand.size(); i++)
    {
        if (hand[i]->cardType == type)
        {
            return hand[i];
        }
    }
    return nullptr;
}

void Player::GetCardsInPlay(Card *arr[])
{
    for (int i = 0; i < 3; i++)
    {
        arr[i] = inPlay[i];
    }
}

bool Player::IsAlive()
{
    if (health > 0)
    {
        return true;
    }
    return false;
}

void Player::Win()
{
    cout << "\nCongratulations, you won the game!" << endl;
    cout << "But, I bet you just hit random buttons, didn't you?" << endl;
    cout << "Well, you played well, regardless :)" << endl;
}

void Player::Lose()
{
    cout << "\nI am sorry to say that you have been defeated." << endl;
    cout << "Those pesky computers sure can be tricky." << endl;
    cout << "You'll get it next time, champ!" << endl;
}

void Player::Draw()
{
    cout << "\nYour match has ended in a tie." << endl;
    cout << "You now reserve the right to say that you are" << endl;
    cout << "equally as smart as a crappy AI. Good job." << endl;
}
