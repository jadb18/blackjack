# Blackjack

The program simulates the card draw probabilities of blackjack with pseudorandom numbers and an array to keep track of the deck throughout the game (i.e., an array represents a 52-card deck, and more than four copies of a card cannot be generated). Therefore, it should still be possible to calculate probability bounds and make similar decisions/choices as in a setting with a physical deck of cards.

I initially wrote this as a simpler program to help teach programming, then later dived into the more fine-grained rules of blackjack such as converting aces and including more verbose output regarding the status of the player and dealer's cards.

## Instructions to run

Compile with (usually) clang++, c++, or g++ and run:

`% c++ blackjack.cpp -o blackjack`\
`% ./blackjack`

## Example game:

```
Welcome to Blackjack!
Controls: Type h to hit or s to stand.
Type q to quit at any time.
Type p to play!

p  

You start with a two and an ace.
The dealer's first card is a four.
You have 13 points.
Reminder: An ace will convert to one point if you break.
Hit or stand?

h

Hit: Eight
Player: 21 points
You have an ace that will convert to one point if you break.
Hit or stand?

s

Dealer draws 1 card.
Player: 21
Dealer: 18
You win!

Type p to play again or q to quit.

q

Thanks for playing!
```

By Jad Beydoun - <jadb@go.mail.umich.edu>

