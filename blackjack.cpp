//
// blackjack.cpp
// Blackjack
//
// By Jad Beydoun on 9/29/2019.
//

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <tuple>

int dealCards(int* cards, int &playerPoints, int &dealerPoints, int &playerAces, int &dealerAces);
int hitCard(int* cards, int &points, int &aces);
std::string lookupRank(int card);

int main() {
    // Used to generate better pseudorandom numbers
    srand((unsigned int) time(NULL));

    const int blackjack = 21;
    const int standLimit = 17;
    const int numRanks = 13;
    const int facePoints = 10;
    int playerPoints = 0;
    int playerAces = 0;
    int dealerPoints = 0;
    int dealerAces = 0;
    
    // Array to keep track of cards dealt (Only four of each rank)
    int cards[numRanks];

    const char play = 'p';
    const char hit = 'h';
    const char stand = 's';
    const char quit = 'q';
    char userInput = ' ';

    bool dealtCards = false;
    bool win = false;
    bool lose = false;
    bool push = false;

    std::cout << "Welcome to Blackjack!\n\n";
    std::cout << "Controls: Type h to hit or s to stand.\n";
    std::cout << "Type q to quit at any time.\nType p to play!\n\n";

    while (userInput != quit) {
    	std::cin >> userInput;

    	if (userInput == play) {
    		int dealerFirstCard = 0;

    		// Let the games begin!
    	    win = lose = push = false;
    	    playerPoints = playerAces = dealerPoints = dealerAces = 0;

    	    // Initializes cards array to be zero suits of each card drawn
    	    for (int i = 0; i < numRanks; ++i) {
    	        cards[i] = 0;
    	    }
    	    
			dealerFirstCard = dealCards(cards, playerPoints, dealerPoints, playerAces, dealerAces);
			dealtCards = true;
    	    
    	    // Checks for blackjack for either the player or both the player and the dealer
    	    if ((playerPoints == blackjack) && (playerAces == 1)) {
    	        if ((dealerPoints == blackjack) && (dealerAces == 1)) {
    	            std::cout << "\nYou and the dealer both have a blackjack! Push!\n";
    	            push = true;
    	        }
    	        else {
    	        	std::cout << "\nYou have a blackjack! You win!\n";
    	        	win = true;
    	        }   
    	    }
    	    else {
    	    	// Outputs starting information for the round
    	    	std::cout << "\nThe dealer's first card is " << lookupRank(dealerFirstCard) << ".\n";
    	        std::cout << "\nYou have " << playerPoints << " points.\n";

    	        if (playerAces == 1) {
                	std::cout << "\nReminder: An ace will convert to one point if you break.\n";
                }
    	        std::cout << "\nHit or stand?\n\n";
    	    }
    	}
        if ((userInput == hit) && (dealtCards)) {
        	int card = hitCard(cards, playerPoints, playerAces);

        	std::string cardStr = lookupRank(card);
        	cardStr = cardStr.substr(cardStr.find(' ') + 1);
        	cardStr[0] = (char) toupper(cardStr[0]);
        	std::cout << "\nHit: " << cardStr << '\n';

        	// Checks if the dealer has any aces to convert to 1 point
        	if ((playerPoints > blackjack) && (playerAces == 1)) {
        		playerPoints -= facePoints;
        		playerAces = 0;
        		std::cout << "An ace was converted.\n";
        	}

            std::cout << "Player: " << playerPoints << " points\n";

            // Checks if the player breaks or if the player breaks and the dealer has blackjack
            if (playerPoints > blackjack) {
            	std::cout << "Oh no! You broke :(\nBetter luck next time!\n";

            	if ((dealerPoints == blackjack) && (dealerAces == 1)) {
            		std::cout << "Dealer also had a Blackjack!\n";
            	}
            	else {
            		std::cout << "Dealer had " << dealerPoints << " points.\n";
            	}
            	lose = true;
            }
            else {
                if (playerAces == 1) {
                	std::cout << "You have an ace that will convert to one point if you break.\n";
                }
                std::cout << "Hit or stand?\n\n";
            }
        }
        else if ((userInput == stand) && dealtCards) {
        	int hitCount = 0; // Keeps track of how many cards the dealer drew this round
            std::cout << "\n";
        	// Checks if dealer had a blackjack the whole time
            if ((dealerPoints == blackjack) && (dealerAces == 1)) {
                std::cout << "Dealer has a Blackjack! Unfortunate!\n";
                lose = true;
            }
            while (dealerPoints < standLimit) {
                hitCard(cards, dealerPoints, dealerAces);
                ++hitCount;

                // Checks if the dealer has any aces to convert to 1 point
                if ((dealerPoints > blackjack) && (dealerAces == 1)) {
                	dealerPoints -= facePoints;
                	dealerAces = 0;
                }
            }

            if (hitCount == 1) {
            	std::cout << "Dealer draws " << hitCount << " card.\n";
            }
            else if (hitCount > 1) {
            	std::cout << "Dealer draws " << hitCount << " cards.\n";
            }

            if (dealerPoints > blackjack) {
            	std::cout << "The dealer broke at " << dealerPoints << ". You win!\n";
            	win = true;
            }
            else {
                std::cout << "Player: " << playerPoints << '\n';
                std::cout << "Dealer: " << dealerPoints << '\n';
                if (playerPoints > dealerPoints) {
                    std::cout << "You win!\n";
                    win = true;
                }
                else if (playerPoints < dealerPoints) {
                    std::cout << "Beter luck next time!\n";
                    lose = true;
                }
                else {
                	std::cout << "Push!\n";
                	push = true;
                }
            }
        }

        if ((win == true) || (lose == true) || (push == true) && !quit) {
            std::cout << "\nType p to play again or q to quit.\n" << std::endl;
            dealtCards = false;
        }
    }

    std::cout << "Thanks for playing!" << std::endl;

    return 0;
}

/**
 * Requires: Mothing
 *
 * Modifies: Nothing
 *
 * Effects: Calls the hitCard function to give the player and dealer two cards each.
 * Returns the dealer's first card.
 */
int dealCards(int* cards, int &playerPoints, int &dealerPoints, int &playerAces, int &dealerAces) {
	// Set up the player's hand
	int playerFirstCard = hitCard(cards, playerPoints, playerAces);
	int playerSecondCard = hitCard(cards, playerPoints, playerAces);

	// Set up the dealer's hand
	int dealerFirstCard = hitCard(cards, dealerPoints, dealerAces);
	hitCard(cards, dealerPoints, dealerAces);

	std::string firstCardStr = lookupRank(playerFirstCard);
	std::string secondCardStr = lookupRank(playerSecondCard);

	if (playerFirstCard == playerSecondCard) {
		std::string doubleCardStr = firstCardStr.substr(firstCardStr.find(' ') + 1) + 's';
		std::cout << "\nYou start with two " << doubleCardStr << ".\n";
		if (doubleCardStr.compare("ace") == 0) {
			std::cout << "Lucky!\n";
		}
	}
	else {
		std::cout << "\nYou start with " << firstCardStr << " and " << secondCardStr << ".\n";
	}

    return dealerFirstCard;
}

/**
 * Requires: Nothing
 *
 * Modifies: cards, points, and aces
 *
 * Effects: Generates a pseudorandom card and adds it to the player/dealer's points.
 * Increments number of aces accordingly.
 * Returns the value of the card that was generated.
 */
int hitCard(int* cards, int &points, int &aces) {
    int ace = 1;
    int king = 13;
    int numSuits = 4;
    int facePoints = 10; // Jacks, Queens, and Kings are all worth 10 points
    int acePoints = 11; // Aces count as 11 points until the user would break
    int cardIndex = 0; // Used to index into the cards array
    int randomNum = cardIndex = rand() % king + ace;

    if (randomNum == ace) {
        cardIndex = 1;
    }

    // Check if the card has been dealt 4 times and keep "rerolling" cards until valid
    while (cards[randomNum - 1] == numSuits) {
        randomNum = cardIndex = rand() % king + ace;
    }

    if (randomNum != ace) {
        if (randomNum > facePoints) { // Makes Jack, Queen, and King worth 10 points
            points += facePoints;
        }
        else {
            points += randomNum;
        }
    }
    else if (randomNum == ace) {
        points += acePoints;
        cardIndex = 1;
        ++aces;
    }
    ++cards[cardIndex - 1];

    // Changes aces from 22 points to 12 points for the player/dealer during dealing phase
	if (aces > 1) {
	    points -= facePoints;
	    --aces;
	}

    return randomNum;
}

/**
* Requires: Card rank must be positive.
*
* Modifies: Nothing
*
* Effects: Determines the rank of a card based on its random number value previously generated
* and return a string of the rank.
*/
std::string lookupRank(int card) {
	static const std::string ranks[] = { "ace", "two", "three", "four", "five", "six", "seven", 
											"eight", "nine", "ten", "jack", "queen", "king" };
	
	std::string cardString = "";

	if ((card == 1) || (card == 8)) {
		cardString = std::string("an ").append(ranks[card - 1]);
	}
	else {
		cardString = std::string("a ").append(ranks[card - 1]);
	}

	return cardString;
}
