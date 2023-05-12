/**------------------------------------------
    Program 2: Great 13
    Course: CS 141, Fall 2022.
    System: MacOSX 13.1
    Author: Aaryan Sharma
 ---------------------------------------------**/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

/* Everything below this comment is starter code, and you are not
allowed to modify */

using namespace std;

// Function that displays the instructions to the user

void display_instructions() {
  cout << "Class: CS 141" << endl
       << "Program 2: Great 13" << endl
       << endl
       << "Make a series of jumps until there is a single piece left" << endl
       << "anywhere on board. On each move you must jump an adjacent" << endl
       << "piece   into   an  empty  square,  jumping  horizontally," << endl
       << "vertically, or diagonally." << endl
       << endl
       << "Input of 'R' resets the board back to the beginning, and " << endl
       << "'X' exits the game." << endl;
}

// The internal representation of the board as an array. Do not modify directly.

char board[13]{};

/* These two functions are how you will get and set elements on the board. Only
use these two when changing, or reading the board. */

char get_element(char position) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to get element at position " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  return board[position - 'A'];
}

void set_element(char position, char value) {
  if ((position < 'A') || (position > 'M')) {
    cout << "Failed to set element at postion " << position << endl
         << "Make sure the given position is an uppercase letter " << endl
         << "between A-M." << endl;
    exit(1);
  }
  board[position - 'A'] = value;
}

// print out the board with the legend on the right

void display_board() {
  cout << endl;
  cout << setw(7) << "Board" << setw(12) << "Position" << endl;
  cout << setw(5) << board[0] << setw(11) << 'A' << endl
       << setw(3) << board[1] << ' ' << board[2] << ' ' << board[3] << setw(11)
       << "B C D" << endl
       << board[4] << ' ' << board[5] << ' ' << board[6] << ' ' << board[7]
       << ' ' << board[8] << ' ' << " E F G H I" << endl
       << setw(3) << board[9] << ' ' << board[10] << ' ' << board[11]
       << setw(11) << "J K L" << endl
       << setw(5) << board[12] << setw(11) << 'M' << endl;
  cout << endl;
}

/* This is the end of the starter code, and below is where you can
add your own code. Feel free to add helper functions or variables.
*/

/* forward declarations for the functions you will write later. This
is so the order of the function definitions, in this file,  does not
matter. */

void make_move(string str);
void initialize_board();
bool game_over();
void game_win();

int main() {
  string user_inp;
  bool over;
  display_instructions();
  initialize_board();

  do {                                                                                             // This is a do-while loop, which runs only if: 1. "X" or "x" is inputted, 2. User wins the game.
    display_board();
    cout << "Enter positions from, jump, and to (e.g. EFG): ";
    cin >> user_inp;
    for (int i = 0; i < user_inp.size(); i++) {
      /* The following for-loop is used to convert the input string to UPPERCASE */
      if (user_inp[i] >= 97 && user_inp[i] <= 122) {
        user_inp[i] = user_inp[i] - 32;
      }
    }

    if (user_inp == "X") {
      over = game_over();
    }

    else if(user_inp == "R"){
      cout << "Restarting game." << endl;
      initialize_board();
    }
      
    else {
      make_move(user_inp);
    }

    game_win();
  } while (over != true);

  return 0;
}

bool validity(string str) {
  /* This function is used to check the validity of the user's input, before a change is made to the board. */
  bool x = true;
  int prob = 0;
  
  string outcome[32] = {"ABE", "ACG", "ADI", "BFJ", "BCD", "BGL", "CGK", "DGJ",
                        "DHL", "DCB", "EFG", "EJM", "EBA", "FGH", "GKM", "GCA",
                        "GHI", "GFE", "HGF", "IDA", "IHG", "ILM", "JFB", "JKL",
                        "JGD", "KGC", "LHD", "LKJ", "LGB", "MLI", "MKG", "MJE"};

  if((str.length() != 3) && (str != "X") &&  (str != "R")){                                        // This if branch is used to output an error msg, when the input does not have 3 characters, and is not ’X’ or ’R’.
    x = false;
    prob = 1;
  }

  if(x){                                                                                           // This if branch is used to output an error msg, when the input has out of range positions.
    for (int i=0; i<str.length(); i++){
      if(str[i]<'A' || str[i]>'M'){
        x = false;
        prob = 2;
        break;
      }
    }
  }

  if(x){                                                                                           // This if branch is used to output an error msg, when any of the position status is unsatisfied.
    if(get_element(str[1]) == '.'){
      x = false;
      prob = 3;
    }

    if(x && (get_element(str[0]) == '.')){
      x = false;
      prob = 4;
    }

    if(x && (get_element(str[2]) == '#')){
      x = false;
      prob = 5;
    }
  }

  if(x){                                                                                           // This if branch is used to output an error msg, when the position sequence is invalid.
    for (int i=0; i<32; i++){
      if(outcome[i] == str){
        x = true;
        prob = 0;
        break;
      }
      else{
        prob = 6;
        x = false;
        continue;
      }
    }
  }
  
  switch (prob){                                                                                   // This switch case is used to output specific error msgs, using the variable "prob".
    
    case 1:
      cout << "*** Invalid sequence. Please retry." << endl;
      break;
    
    case 2:
      cout << "*** Given move has positions not on the board! Please retry." << endl;
      break;
    
    case 3:
      cout << "*** Must jump a piece. Please retry." << endl;
      break;
    
    case 4:
      cout << "*** Source needs a piece. Please retry." << endl;
      break;
    
    case 5:
      cout << "*** Destination must be empty. Please retry." << endl;
      break;
    
    case 6:
      cout << "*** Move is invalid. Please retry." << endl;
      break;
    
    default:
      break;
  }
    
  return x;
}

void make_move(string str) {
  /* This function takes the input string as a parameter and makes changes to the board if the input is valid. */
  if (validity(str)) {
    for (int i = 0; i < 3; i++) {
      switch (i) {                                                                                 // This switch case is used to make changes to the board, by employing the "set_element" function.
      case 0:
      case 1:
        set_element(str[i], '.');
        break;
      case 2:
        set_element(str[i], '#');
        break;
      }
    }
  }
}

bool game_over() {
  /* This function is used to print return a true value to the variable "over" in the main function, in order to exit the game. */
  cout << "Exiting." << endl;
  return true;
}

void initialize_board() {
  /* Function used to output the initial state of the board. */
  for (char i = 'A'; i < 'N'; i++) {
    if (i == 'G') {
      set_element('G', '.');
    } else {
      set_element(i, '#');
    }
  }
}

void game_win(){
  int count_peg = 0;
  for (int i='A'; i<'N'; i++){
    if(get_element(i) == '#'){
      count_peg += 1;
    }
  } 
  if (count_peg == 1){
    cout << "Congrats you win!" << endl;
    exit(1);
  }
}