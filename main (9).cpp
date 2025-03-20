#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;

unsigned askForInititalStakeAmountFunc();
unsigned askForBetDonePlayingFunc(unsigned& stakeUns);
unsigned rollDemBonesFunc(unsigned& rollCountUns);
void evaluateRollFunc(unsigned diceRollResultsUns, unsigned& rollCountUns, unsigned& stakeUns, unsigned betUns);
bool pointRollDemBonesFunc(unsigned pointUns, unsigned& rollCountUns);

int main() {
  unsigned
    betUns,
    rollCountUns = 0,
    diceRollResultsUns,
    stakeUns = askForInititalStakeAmountFunc();

  do {
    betUns = askForBetDonePlayingFunc(stakeUns);
    if (betUns != 0) 
    {
      diceRollResultsUns = rollDemBonesFunc(rollCountUns);
      evaluateRollFunc(diceRollResultsUns, rollCountUns, stakeUns, betUns);
    //   cout << "Current Stake Amount : " << stakeUns << endl << endl;
    }
  } while ((betUns != 0) && (stakeUns != 0));

  cout << endl << endl;

  if (betUns == 0)
    cout << "Player ends Game" << endl;
  else
    cout << "Out of money, Game ends" << endl;

  cout << "Roll Count :         " << rollCountUns << endl;
  cout << "Final Stake Amount : " << stakeUns << endl << endl << endl;

  cout << "Press enter key once or twice to end ... ";
  cin.ignore(); cin.get();
  return 0;
}

/*
Name:              askForInitialStakeAmountFunc
Function Purpose : Retrieves the initial money from prompting the user
Function Design:   Checks if the input stake amount the player enters a proper amount:
                   stakeStartUns > 0
                   not a negative amount
Inputs:            None
Outputs:           By function name an unsigned integer that's the stake amount
*/

unsigned askForInititalStakeAmountFunc() {
  long int stakeStartUns;

  do {
    cout << "What is your stake amount ? ";  cin >> stakeStartUns; cout << endl;
    if (stakeStartUns > 0)
      break;
    else {
      cout << "You have to enter a > 0 or positive amount of money to bet with. Try again!" << endl << endl;
      continue;
    }

  } while (true);

  return stakeStartUns;
}

/*
Name: askForBetDonePlayingFunc
Function Purpose : Asks for what the player will bet and checks for validity
Function Design:   Checks for valid entry
                   if not valid entry, staes the reason why
                   retry entry if not valid
Inputs:            stakeUns - The total stake amount
Outputs:           By function name an unsigned integer that's the bet amount
*/

unsigned askForBetDonePlayingFunc(unsigned& stakeUns) 
{
  int inputUns;
  unsigned betUns = 0;
  
  cout << "Current Stake Amount : " << stakeUns << endl << endl;
  cout << "What will you bet ? ";
  cin >> betUns;
  cout << endl;
  
  if (stakeUns <= 0) 
  {
    cout << "Insufficient stake amount." << endl << endl;
    betUns = 0;
  }
  else if (betUns > stakeUns)
  {
    cout << "\nSorry, that is not a valid bet (end game)" << endl << endl;
    betUns = 0;
  }



  return betUns;
}

/*
Name:             rollDemBonesFunc
Function Purpose: generates an independent random number for each die
                  calculates the roll sum
                  increments rollCountUns
Function Design:  Prompts the user to throw the dice
                  Using rand() generates 2 random variables from 1 to 6 and adds to simulate dice throw
Inputs/Outpuut:   &rollCountUns - Reference of total rolls count in game
Outputs:          By function name an unsigned integer that's the sum of the two rolled dice
*/

unsigned rollDemBonesFunc(unsigned& rollCountUns) {
  unsigned die01Value,
    die02Value,
    diceSumUns = 0,
    lowerBound = 1,
    upperBound = 6;
    

  cout << "Press enter key once or twice to throw the dice ";
  cin.ignore(); cin.get();
  cout << endl;

  rollCountUns++;
  //seed the random number generator
  srand(clock());

  //execute the dice roll
  die01Value = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
  die02Value = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
  diceSumUns = die01Value + die02Value;
  
  cout << "Die 01 is " << die01Value << endl;
  cout << "Die 02 is " << die02Value << endl;
  cout << "The dice throw results : " << diceSumUns << " !" << endl << endl;
  

  return diceSumUns;
}

/*
Name: stakeCalc
Function Purpose: Calculate total stake amount
Function Design:  Check to see if win or lose. If win check too see if bet was all in or not.
                  If win and bet was all in, stake amount is doubled. 
                  If win and not all in, bet amount is doubled and added to stake amount.
                  If lose, bet amount is subtracted from the stake amount
Inputs:           &stakeUns - References total stake Units
                  betUns    - total bet Units
                  win       - bool flag to check if win or lose
Output:           &stakeUns
                  Returns nothing
*/

void stakeCalc(unsigned& stakeUns, unsigned betUns, bool win) 
{
   if (win) //Check for win
   {
        if (betUns == stakeUns) //Check for all in
        {
            stakeUns = stakeUns * 2;
        }
        else 
        {
            stakeUns = (stakeUns - betUns) + (betUns * 2);
        }
   }
   else //Check for lose
   {
       stakeUns -= betUns;
   }
    
}

/*
Name: evaluateRollFunc
Function Purpose: Check for a winning roll, a losing roll, or a point roll result
                  Adjust stakeUns using betUns for win or loss result
Function Design:  2, 3, 12      loses
                  7, 11         winner
                  anything else executes point rolls
Inputs:           diceRollResultsUns - The dice roll sum
                  betUns             - The placed bet
Input/Output:     &rollCountUns      - Reference to tally of total rolls
                  &stakeUns          - Reference to the total at stake
*/


void evaluateRollFunc(unsigned diceRollResultsUns, unsigned& rollCountUns, unsigned& stakeUns, unsigned betUns) 
{
    switch (diceRollResultsUns) 
    {
        //Case for instant win
        case 7:
        case 11: 
        {
          cout << "We've got ourselves a winner! " << endl << endl;
          stakeCalc(stakeUns, betUns, true);
          break;   
        }
        //Case for instant lose
        case 2:
        case 3:
        case 12: 
        {
            cout << "Sorry, you lose. " << endl << endl;
            stakeCalc(stakeUns, betUns, false);
            break;
        }
        //Handles "point" cases
        default: 
        {
            int pointUns = diceRollResultsUns;
            bool flag = pointRollDemBonesFunc(pointUns, rollCountUns);
            stakeCalc(stakeUns, betUns, flag);
        }
    }
}

/*
Name:             pointRollDemBonesFunc
Function Purpose: Executes the point rolls
Function Design:  Displays the point value.
                  Executes repeating rolls using rollDemBonesFunc until the point or 7 is the result
                  Each roll passes to rollDemBonesFunc() the rollCountUns and recives back the rollCountUns
Inputs:           pointUns      - The point set by the first roll
Inputs/Outputs    &rollCountUns - Reference to total roll count
Outputs:          After point rolls produces a return for a win (true) or a loss (false)
*/

bool pointRollDemBonesFunc(unsigned pointUns, unsigned& rollCountUns) {
  unsigned pointRollUns;
  
  //Executes until point  value  or 7 is rolled
    
    do 
    {
        pointRollUns = rollDemBonesFunc(rollCountUns);
        cout << "The point is " << pointUns << endl;
        if (pointRollUns == pointUns) 
        {
            cout << "We've got ourselves a winner! " << endl << endl;
            return (true);
        }
        else if (pointRollUns == 7) 
        {
            cout << "Sorry, you lose. " << endl << endl;
            return (false);
        }
        cout << "Throw em again and hope that luck is on your side!" << endl << endl;
    } while (pointRollUns != 7 || pointRollUns != pointUns);

  return(false);
}


