#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <stack>
#include <vector>
#include <time.h>
#include <cstdlib>

#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define ROCK_HEAL 3
#define SCISSORS_DMG 3

#define INIT_HEALTH 20
#define DECK_SIZE 60

struct Card
{
    Card *target;
    int cardType;
    bool gotBlipped;
    bool empowered;
    bool nullified;
};

class Player
{
    public:
        Player();
        virtual ~Player();

        void BuildDeck();
        void ShuffleDeck();
        void Reshuffle();
        void DrawCard(bool output);
        void Discard(Card *card);

        void PlayCards(int rocks, int papers, int scissors);
        void PlayToDiscard();
        void GetHurt(int num);
        void GetHeal(int num);

        void HandInsert(Card *card);
        void HandRemove(int type);

        int GetHealth();
        void ShowHand();
        int NumCardInHand(int type);
        Card *GetFromHand(int type);
        void GetCardsInPlay(Card *arr[]);
        void SetWin(bool a, bool b, bool c);

        bool IsAlive();
        void Win();
        void Lose();
        void Draw();

    private:
        int health;
        std::stack<Card *> deck;
        std::stack<Card *> discard;
        std::vector<Card *> hand;
        std::vector<Card *> inPlay;
};

#endif // PLAYER_H
