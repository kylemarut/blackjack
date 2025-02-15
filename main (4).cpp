//Programmer: Kyle Marut
//Date: 10/4/24
//File: hw5.cpp
//Assignment: homework 5
//Purpose: this file contains the main function of the program to simulate a 
//game of blackjack to the user


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "card.h"

using namespace std;


//Function Prototypes
int generateRandomCard();
//int generateRandomCard(const int probability);

bool isBlackjack(vector<Card> vect);
void updatePlayerBalance(bool win, double & money, double bet);

void displayOutcome(bool win, bool blackjack, bool tie, double money, double bet, int & winsr, 
int & winsb, int & lossr, int & lossb, int &tiesr, int & tiesb);

void displayGameSummary(const int rounds, const int winsr, const int winsb, 
const int lossr, const int lossb, const int tiesr, const int tiesb, const double money, const double startingMoney);
int total(vector <Card> vect);

void hit(vector <Card> &master, vector <Card> &hand, const vector <string> & suits);

void printHand(vector <Card> & vect, string name);
template <typename T>
void sortElements(vector <T> &vect);
//void addCard(vector <Card> &hand, const vector<string>&suits);
bool beenDrawn(const Card c, const vector <Card> &hand);

int main()
{
    
    //setting rand value
    srand(time(0));
    
    //initializing various variables, vectors
    //Card temp;
    
    string name;
    double bet;
    //int luck;
    vector <string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};
    bool cont = true;
    vector <Card> player;//player's hand
    vector <Card> dealer;//dealer's hand
    vector <Card> master;//contains both player's and dealer's cards
    bool turn = true;
    int size;
    char choice;
    
    double money = (double)(rand()%698801)/100+12;
    double startingMoney = money;
    int rounds = 1;
    int winsr = 0;//regular wins
    int winsb = 0;//blackjack wins
    int lossr = 0;//regular losses
    int lossb = 0;//blackjack losses
    int tiesr = 0;//regular ties
    int tiesb = 0;//blackjack ties
    
    bool win;
    bool tie;
    bool blackjack;
    bool bust;
    
    
    
    //Introduction
    cout<<"Welcome to CodeJack: The Blackjack Simulator!"<<endl<<"Player, please enter your name: "<<endl;
    cin>>name;
    cout<<"Welcome "<<name<< ", I'm pleased to notify you that your starting balance is $"<<money<<endl;
    
    
    while (cont)//continues until player decides otherwise
    {
        player = {};
        dealer = {};
        master = {};
        
        bool win = false;
        bool tie = false;
        bool blackjack = false;
        bool bust = true;
        //luck = rand()%100;//luck value for overloaded generateRandomCard
        
        
        cout<<"Round "<<rounds<<endl<<"*******"<<endl;
        
        //sets bet amount and ensures it is a valid option
        cout<<"Player balance: $"<<money<<endl;
        cout<<"Please enter your wager:"<<endl;
        cin>>bet;
        while(bet > money || bet < 0)
        {
            cout<<"Invalid option\nPlease enter new wager:"<<endl;
            cin>>bet;
        }
        
        
        
        //gives player and dealer first two cards
        hit(master,player,suits);
        hit(master,player,suits);
        hit(master,dealer,suits);
        hit(master,dealer,suits);
        
        //prints player and and first dealer card
        printHand(player, "Player");
        cout<<"Dealer's Hand: "<<dealer[0]<<", [Hidden Card]"<<endl;
        
        //continues until player's turn is over
        while (turn)
        {
            cout<<"Player Total: "<<total(player);
            for(Card i: player)
            {
                if (i.value == 11 && total(player)!=21)
                {
                    cout<<" or "<<(total(player)-10);
                }
            }
            cout<<endl;
            //used when size of hand is important
            size = player.size();
            
            //ends the round if player or dealer have blackjack
            if (isBlackjack(player))
            {
                blackjack = true;
                bet*=1.5;
                win = true;
                if (isBlackjack(dealer))
                {
                    tie = true;
                }
                choice = 'S';
            }
            else if (isBlackjack(dealer))
            {
                cout<<"The dealer got blackjack.";
                blackjack = true;
                win = false;
                choice = 'S';
            }
            else
            {
                cout<<"Player, please choose your action: Hit(H), Stand(S)";
                //only lets player double down if they haven't hit yet and they have enough money
                if(size==2 && bet*2 < money)
                {
                    cout<<", Double Down(D):";
                }
                cout<<endl;
                cin>>choice;
            }
            
            //checks to make sure a valid option has been picked
            if (size==2 && bet * 2 < money)
            {
                while(choice != 'H' && choice != 'S' && choice != 'D')
                {
                    cout<<"Invalid, please choose one of the above options:"<<endl;
                    cin>>choice;
                }
            }
            else
            {
                while(choice != 'H' && choice != 'S')
                {
                    cout<<"Invalid, please choose one of the above options:"<<endl;
                    cin>>choice;
                }
            }
            
            if (choice == 'H')
            {
                hit(master,player,suits);
            }
            if (choice == 'D')
            {
                //increases bet and then hits if double down has been chosen
                bet*=2;
                hit(master,player, suits);
            }
            if(total(player) > 21)
            //changes value of ace to 1 if total is over 21
            {
                for (Card &i: player)
                {
                    if (i.face == "Ace" && total(player) > 21)
                    {
                        i.value = 1;
                    }
                }
            }
            
            
            //cout<<displayHand(player, "Player")<<endl;
            printHand(player, "Player");
            
            
            //if player has 21 or higher, or has chosen stay or double down, turn ends
            if (total(player) > 20 || choice != 'H')
            {
                turn = false;
                cout<<"Player Total: "<<total(player)<<endl;
            }
            
            //only loops back around if player has hit, hasn't busted, or hasn't hit 21
        }
        
        //reveals dealer hand and total
        printHand(dealer, "Dealer");
        cout<<"Dealer Total: "<<total(dealer)<<endl;
        
        
        //sets win/tie conditions for anything other than blackjacks
        if (!blackjack)
        {
            //bust
            if(total(player) > 21)
            {
                win = false;
                bust = true;
            }
            
            else
            {
                //hits for dealer if necessary
                while(total(dealer)<17 && total(dealer) < total(player))
                {
                    hit(master,dealer,suits);
                    cout<<"Dealer hits"<<endl;
                
                
                
                    //cout<<displayHand(dealer, "Dealer")<<endl;
                    printHand(dealer, "Dealer");
                    
                    
                    cout<<"Dealer Total: "<<total(dealer)<<endl;
                }
                //dealer bust check
                if (total(dealer) > 21)
                {
                    win = true;
                    bust = true;
                }
                //player wins
                else if(total(player)>total(dealer))
                {
                    win = true;
                }
                //dealer wins
                else if(total(player)<total(dealer))
                {
                    win = false;
                }
                //tie
                else
                {
                    tie = true;
                }
            }
        }
        
        //only updates player balance if they've won or lost
        if (!tie)
        {
            updatePlayerBalance(win, money, bet);
        }
        
        //displays outcome of game and increases tallies
        displayOutcome(win, blackjack,tie,money,bet,winsr,winsb,lossr,lossb,tiesr,tiesb);
        
        //sees if player wants to continue
        cout<<"Play another round? (y/n):"<<endl;
        cin>>choice;
        while (choice !='y' && choice != 'n')
        {
            cout<<"Invalid, please choose from options above:"<<endl;
            cin>>choice;
        }
        if (choice == 'n')
        {
            cont = false;
        }
        turn = true;
        
        rounds+=1;
    }
    //displays summary of game with all tallies after player quits
    displayGameSummary(rounds,winsr,winsb,lossr,lossb,tiesr,tiesb,money,startingMoney);
    

    return 0;
}
//generates a card value
int generateRandomCard()
{
    return rand()%13+1;
}


//checks for blackjack
bool isBlackjack(vector<Card> vect)
{
    bool result = false;
    if (vect[0]+vect[1]==21)
    {
        result = true;
    }
    return result;
}
//increases or decreases player money depending on win/loss
void updatePlayerBalance(bool win,double & money, double bet)
{
    if(win)
    {
        money += bet;
    }
    else
    {
        money -= bet;
    }
}


//gives player new card
//uses beenDrawn to ensure there are no duplicates
void hit(vector <Card> &master, vector <Card> &hand, const vector <string> & suits)//, double & money)
{
    bool cont = true;
    Card temp;
    while(cont)
    {
        temp = {generateRandomCard(), suits[rand()%4]};
        face(temp);
        if(!beenDrawn(temp,master))
        {
            hand.push_back(temp);
            master.push_back(temp);
            cont=false;
        }
    }
    
}
//finds the sum of all cards to assign total number
int total(vector <Card> vect)
{
    int sum = 0;
    for (Card i: vect)
    {
        sum += i.value;
    }
    return sum;
}

//checks win/lose conditions and displays result. Updates tallies
void displayOutcome(const bool win,const bool blackjack,const bool tie,const double money,const double bet, int & winsr,
int & winsb, int & lossr, int & lossb, int &tiesr, int & tiesb)
{
    if(tie)
    {
        if (blackjack)
        {
            cout<<"You and the dealer both got blackjack"<<endl;
            tiesb+=1;
        }
        else
        {
            tiesr+=1;
        }
        cout<<"The game ends in a tie"<<endl<<"No change in balance"<<endl;
    }
    else if (win)
    {
        if (blackjack)
        {
            cout<<"You got blackjack!"<<endl;
            winsb+=1;
        }
        else
        {
            winsr+=1;
        }
        cout<<"You win the game"<<endl<<"Balance update: +$"<<bet<<endl;
    }
    else
    {
        if (blackjack)
        {
            cout<<"The dealer got blackjack"<<endl;
            lossb+=1;
        }
        else
        {
            lossr+=1;
        }
        cout<<"You lose the game"<<endl<<"Balance update: -$"<<bet<<endl;
    }
    cout<<"Your balance is $"<<money<<endl;
}

//displays all tallies at end of game
void displayGameSummary(const int rounds, const int winsr, const int winsb, 
const int lossr, const int lossb, const int tiesr, const int tiesb, const double money, const double startingMoney)
{
    cout<<"=== Game Summary ==="<<endl
    <<"Total Rounds Played: "<<rounds<<endl
    <<"Total Wins (Regular): "<<winsr<<endl
    <<"Total Wins (Blackjack): "<<winsb<<endl
    <<"Total Losses (Regular): "<<lossr<<endl
    <<"Total Losses (Blackjack): "<<lossb<<endl
    <<"Total Ties (Regular): "<<tiesr<<endl
    <<"Total Ties (Blackjack): "<<tiesb<<endl
    <<"Final Balance: $"<<money<<endl
    <<"Net Gain/Loss: ";
    if (money <= startingMoney)
    {
        cout<<"-$"<<(startingMoney-money);
    }
    else
    {
        cout<<"+$"<<(money-startingMoney);
    }
    
    cout<<endl<<endl<<"Thank you for playing CodeJack: The Blackjack simulator!"<<endl
    <<"We hope to see you again soon."<<endl;
}

//prints out sorted hand
void printHand(vector <Card> & vect, string name)
{
    sortElements(vect);
    cout<<name<<"'s Hand: ";
    for(Card i: vect)
    {
        cout<<i<<", ";
    }
    cout<<"\b\b  "<<endl;
}

//sorts elements in vector 
//uses selection sort
template <typename T>
void sortElements(vector <T> &vect)
{
    int size = vect.size();
    for (int i = 0; i < size; i++)
    {
        for (int k = i+ 1; k < size; k++)
        {
            if (vect[i]>vect[k])
            {
                swap(vect[i],vect[k]);
            }
        }
    }
    
}

//checks to see if a card has already been drawn
//compares card with cards in master hand
bool beenDrawn(const Card c, const vector <Card> &hand)
{
    bool result = false;
    for (Card i: hand)
    {
        if (i == c)
        {
            result = true;
        }
    }
    return result;
}



