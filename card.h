#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

using namespace std;
struct Card
{
    int value;
    string suit;
    string face;
    
    int operator+(const Card &other)
    {
        return value + other.value;
    }
};

void face(Card& other)
{
    if (other.value ==1)
    {
        other.face = "Ace";
        other.value +=10;
    }
    else if (other.value == 11)
    {
        other.face = "Jack";
        other.value = 10;
    }
    else if (other.value ==12)
    {
        other.face = "Queen";
        other.value = 10;
    }
    else if (other.value == 13)
    {
        other.face = "King";
        other.value = 10;
    }
    else
    {
        other.face = to_string(other.value);
    }
    
}

/*
string displayCard(Card & other)
{
    return other.face + " of "+ other.suit;
}*/
/*
void displayHand(vector <Card> & vect, string name)
{
    
    cout<<name<<"'s Hand: ";
    for(Card i: vect)
    {
        cout<<i<<", ";
    }
    hand+="\b\b  ";
    //return hand;
}*/

//void printHand(vector <Card> & vect)

int handTotal(vector <Card> & vect, string name)
{
    int total;
    for (Card i: vect)
    {
        total += i.value;
    }
    return total;
}


ostream& operator <<(ostream & output, const Card & c)
{
    output<< c.face << " of "<<c.suit;
    return output;
}

bool operator >(const Card & uno, const Card & dos)
{
    vector <string> suits = {"Diamonds", "Hearts", "Clubs", "Spades"};
    bool result = false;
    
    if (uno.suit != dos.suit)
    {
        if (uno.suit == "Spades")
        {
            result = true;
        }
        else if(uno.suit == "Clubs" && dos.suit != "Spades")
        {
            result = true;
        }
        else if (uno.suit == "Hearts" && dos.suit == "Diamonds")
        {
            result = true;
        }
    }
    else
    {
        if(uno.face == "Ace")
        {
            result = false;
        }
        else if(uno.face == "King")
        {
            result = true;
        }
        else if(uno.face == "Queen" && dos.face == "King")
        {
            result = false;
        }
        else if (uno.face > dos.face)
        {
            result = true;
        }
        
    }
    return result;
}

bool operator ==(Card uno, Card dos)
{
    bool result;
    if(uno.face == dos.face && uno.suit == dos.suit)
    {
        result = true;
    }
    return result;
}

#endif
