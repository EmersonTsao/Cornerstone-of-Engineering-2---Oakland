#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd1(0x27, 20, 4); // I2C address 0x27, 20 column and 4 rows
LiquidCrystal_I2C lcd2(0x26, 20, 4); // I2C address 0x27, 20 column and 4 rows

int p1Score = 0;
int p2Score = 0;
int answeringPlayer = 0;
int roundNumber = 0;
const int resetPin = 12;


//Array Declare
//each array contains a question set, each row is a question with 4 answers and then the correcct answer
//to add a question set, add the array and add the relavent sections to the set up fuction
String SQ1[7][6] =
  { {"Which is one of the 5 senses","Balance", "Heat", "Love", "taste","taste"},
    {"One of the 4 cardinal directions is","Deusch", "West", "Up", "Down","West"},
    {"Fruits have more seeds on the ","Outside", "Stem", "Flower", "Inside","Inside"},
    {"Salt makes Ice melt ____","Slower", "Faster", "Worse", "More","Faster"},
    {"Dogs are most like __","Bears", "Hawks", "Wolves", "Deer","Wolves"},
    {"A __ is not a living thing","Tree", "Shrub", "Rock", "Mushroom","Rock"},
    {"Your Body has two _","Lungs", "Brains", "Stomach", "Hearts","Lungs"}
  };

String MQ1[7][6] = 
{
{"2x4=__", "8", "6", "24", "42","8"},
{"18-7=__", "10", "11", "25", "8", "11"},
  {"8+8+8", "11", "24", "21", "23", "24"},
  {"33+77=__","100", "1000", "110", "101", "110"},
  {"3x4 = ___", "7", "8", "10", "12", "12"}, 
  {"13x2=__", "15", "26", "21", "28", "26"},
  {"500+330", "830", "880", "800", "730", "830"}
};


//changes bassed off of which topic the user selects
String cQ[7][6] = 
{
  {"Error", "Error", "Error", "Error", "Error", "Error"},
  {"Error", "Error", "Error", "Error", "Error", "Error"},
  {"Error", "Error", "Error", "Error", "Error", "Error"},
  {"Error", "Error", "Error", "Error", "Error", "Error"},
  {"Error", "Error", "Error", "Error", "Error", "Error"}, 
  {"Error", "Error", "Error", "Error", "Error", "Error"},
  {"Error", "Error", "Error", "Error", "Error", "Error"}
};


//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________

//function generates a random number between the minimum and the maximum
int randomGenerator(int min, int max)
{
  randomSeed(analogRead(0));
  int randomNumber = random(min, max);
  return randomNumber;
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________

char takingInput() //this function takes a button input from the users
{
  int i=0;
  while(i==0){
    if (digitalRead(1)==LOW){
      return 'A';
    }
        if (digitalRead(2)==LOW){
      return 'B';
    }
        if (digitalRead(3)==LOW){
      return 'C';
    }
        if (digitalRead(4)==LOW){
      return 'D';
    }
        if (digitalRead(8)==LOW){
      return 'E';
    }
    if (digitalRead(9)==LOW){
      return 'F';
    }
    if (digitalRead(10)==LOW){
      return 'G';
    }
    if (digitalRead(11)==LOW){
      return 'H';
    } 
  }
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//function uses an input from the fucntion and simplifies it to one of the 4 letter answers
char simplifyInput(char givenInput) 
{
    switch (givenInput)
    {
        case 'A':
        case 'E':
            return 'A';
        case 'B':
        case 'F':
            return 'B';
        case 'C':
        case 'G':
            return 'C';
        case 'D':
        case 'H':
            return 'D';
    }
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//playerID function finds which user answered with the takingInput function. This information is uesd which we will use for scoring and dilaying correct messages on LCDs
int playerID(char givenInput)
{
    switch (givenInput)
    {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            return 1;
        case 'E':
        case 'F':
        case 'G':
        case 'H':
            return 2;
    }
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//this fucntion check is if the answer proided by a player matches the correct answer in the array
bool answerCheck(char givenInput, int r)
{
    int letterSelection = simplifyInput(givenInput);
    switch (letterSelection)
    {
        case 'A':
            if (cQ[r][1] == cQ[r][5])
            {
                return true;
            }
            else
            {
                return false;
            }
        case 'B':
            if (cQ[r][2] == cQ[r][5])
            {
                return true;
            }
            else
            {
                return false;
            }
        case 'C':
            if (cQ[r][3] == cQ[r][5])
            {
                return true;
            }
            else
            {
                return false;
            }
        case 'D':
            if (cQ[r][4] == cQ[r][5])
            {
                return true;
            }
            else
            {
                return false;
            }
    }
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________
int addPoints(int answeringPlayer) //this function adds points to the player who answered correctly
{
  if(answeringPlayer == 1)
  {
    p1Score++;
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Correct!");
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Better Luck Next Time");
    return 1;
  }
  if(answeringPlayer == 2)
  {
    p2Score++;
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Correct!");
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Better Luck Next Time");
    return 1;
  }
}

//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________


void setup() // runs on start, used to declare all of the pins then choose a topic and randomize questions
{
// first to stop a contiuous reset
digitalWrite(12, HIGH);

//pin declare
lcd1.init();
lcd1.backlight();
lcd2.init();
lcd2.backlight();
//buttons
pinMode(1, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
//allows us to code a arduino reset
pinMode(12, OUTPUT);


lcd1.clear();
lcd2.clear();
lcd1.setCursor(0,0);
lcd2.setCursor(0,0);
lcd1.print("Select a Topic");
lcd2.print("Select a Topic");
lcd1.setCursor(0,1);
lcd2.setCursor(0,1);
lcd1.print("A: Math   B:Science");
lcd2.print("A: Math   B:Science");
delay(2000);



//this works
char answer = takingInput();
answer = simplifyInput(answer);



switch (answer) // if not a or b ignore 
{
  
  case 'A':
    for (int r=0; r < 7; r++)
    {
      for (int c = 0; c < 6; c++)
        {
          cQ[r][c] = MQ1[r][c];
        }
    }
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Math selected");
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Math selected");
    delay(2000);
    break;
    
  case 'B':
    for (int r=0; r < 7; r++)
    {
      for (int c = 0; c < 6; c++)
        { 
          cQ[r][c] = SQ1[r][c];
        }
    }
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.print("Science selected.");
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Science selected.");
    delay(2000);
    break;

}



//Randimize Topic
// swap answers
for (int r = 0; r < 7; r++){
   for (int c = 1; c < 5; c++) {
    int j = randomGenerator(1, 4);
    // Swap the current element with the randomly selected one
     String tempString = cQ[r][c];
     cQ[r][c] = cQ[r][j];
     cQ[r][j] = tempString;
    }
}

for (int r = 0; r < 7; r++) //this is to swap order of questions
{
  int j = randomGenerator(1, 4);
  for (int c = 0; c < 6; c++)
  {
    String tempArray[1][6]; 
    tempArray[0][c] = cQ[r][c];
    cQ[r][c] = cQ[j][c];
    cQ[j][c] = tempArray[0][c];
  }
}
// starting countdown?

}
//___________________________________________________________________________________________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________________________________________________________________________________________

void loop() //this loop displays the questions and answer options for the kids
{
  if (roundNumber > 6) //if all seven rounds have been played find who won and display
  {
    if (p1Score > p2Score)
    {
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Player 1 wins");
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Player 1 wins");
      delay(2000);

    }
    else if (p2Score > p1Score)
    {
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Player 2 wins");
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Player 2 wins");
      delay(2000);
    }
    else if(p1Score == p2Score)
    {
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print("Both Players Tie");
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Both Players Tie");
      delay(2000);
    }
    //resets the arduino so the arrays are reset and voidSetup Runs again
    digitalWrite(12, LOW);
    delay(1000); // Optional delay to ensure the reset happens
    digitalWrite(12, HIGH);
  }
  else //if the game is still going... 
  {
    //prints the question and the answer options
      lcd1.clear();
      lcd1.setCursor(0,0);
      lcd1.print(cQ[roundNumber][0].substring(0,20));
      lcd1.setCursor(0,1);
      lcd1.print(cQ[roundNumber][0].substring(20,39)); // prints the question
      lcd1.setCursor(0,2);
      lcd1.print("A: " + cQ[roundNumber][1] + "  B:" + cQ[roundNumber][2]);
      lcd1.setCursor(0,3);
      lcd1.print("C: " + cQ[roundNumber][3] + "  D:" + cQ[roundNumber][4]);
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print(cQ[roundNumber][0].substring(0,20));
      lcd2.setCursor(0,1);
      lcd2.print(cQ[roundNumber][0].substring(20,39)); // prints the question
      lcd2.setCursor(0,2);
      lcd2.print("A: " + cQ[roundNumber][1] + "  B:" + cQ[roundNumber][2]);
      lcd2.setCursor(0,3);
      lcd2.print("C: " + cQ[roundNumber][3] + "  D:" + cQ[roundNumber][4]);
      delay(500);

      // takes the first answer and checks if its right
      char answer = takingInput();
      int playerIDA = playerID(answer);
      answer = simplifyInput(answer);
      bool isCorrect = answerCheck(answer, roundNumber);
      if(isCorrect) //if it is right, add points to the right player and display the relivant messages
      {
        int run = addPoints(playerIDA);
        if (playerIDA == 1)
        {
          
          lcd1.clear();
          lcd1.setCursor(0,0);
          lcd1.print("Correct");
          lcd2.clear();
          lcd2.setCursor(0,0);
          lcd2.print("Better Luck ");
          lcd2.setCursor(0,1);
          lcd2.print("Next Time");
          delay(1000);

        }
        else if (playerIDA == 2)
        {
          
          lcd2.clear();
          lcd2.setCursor(0,0);
          lcd2.print("Correct");
          lcd1.clear();
          lcd1.setCursor(0,0);
          lcd1.print("Better Luck ");
          lcd1.setCursor(0,1);
          lcd1.print("Next Time");
          delay(1000);
        }
      }
      else // first answer was wrong display that the answer is wrong
      {
        if (playerIDA == 1)
        {
          lcd1.clear();
          lcd1.setCursor(0,0);
          lcd1.print("Close!");
          lcd1.setCursor(0,1);
          lcd1.print("Wait for player 2 to answer");
        }
        else if (playerIDA == 2)
        {
          lcd2.clear();
          lcd2.setCursor(0,0);
          lcd2.print("Close!");
          lcd2.setCursor(0,1);
          lcd2.print("Wait for player 1 to answer");
        }
        //take an input only from the second user
        int playerIDB;
        do
        {
        answer = takingInput();
        playerIDB = playerID(answer);
        }
        while(playerIDB == playerIDA); //doesn't ignore the first player, just takes input from the second user
        answer = simplifyInput(answer);
        isCorrect = answerCheck(answer, roundNumber); 
      
        if(isCorrect) //if the second player is correct, add points and display the relivant messages
        {
          int run = addPoints(playerIDB);
          if (playerIDB == 1)
          {
            
            lcd1.clear();
            lcd1.setCursor(0,0);
            lcd1.print("Correct");
            delay(1000);

          }
          else if (playerIDB == 2)
          {
            
            lcd2.clear();
            lcd2.setCursor(0,0);
            lcd2.print("Correct");
            delay(1000);
          }
        }
        else // if both the first and second players are incorrect display the correct answers
        {
        lcd2.clear();
        lcd2.setCursor(0,0);
        lcd2.print("Neither Player Wins");
        lcd2.setCursor(0,1);
        lcd2.print("Correct answer:");
        lcd2.setCursor(0,2);
        lcd2.print(cQ[roundNumber][5]); //neither player wins, prints the correct answer
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("Neither Player Wins");
        lcd1.setCursor(0,1);
        lcd1.print("Correct answer:");
        lcd1.setCursor(0,2);
        lcd1.print(cQ[roundNumber][5]);
        delay(2000);
        }
      }
  }
  //display player score?
roundNumber++;
}

