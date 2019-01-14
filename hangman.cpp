#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

// Function declarations
void welcome();
void nextScreen();
void header();
int letterBoard(char x);
int hangman(int x);

// Stored words
string storedWords[] = {"abruptly", "absurd", "abyss", "affix", "askew", "avenue", "awkward", "axiom", "azure", "bagpipes", "bandwagon",
"banjo", "bayou", "beekeeper", "bikini", "blitz", "blizzard", "boggle", "bookworm", "boxcar", "boxful", "buckaroo", "buffalo", "buffoon",
"buxom", "buzzard", "buzzing", "buzzwords", "caliph", "cobweb", "cockiness", "croquet", "crypt", "curacao", "cycle", "daiquiri", "dirndl",
"disavow", "dizzying", "duplex", "dwarves", "embezzle", "equip", "espionage", "euouae", "exodus", "faking", "fishhook", "fixable", "fjord",
"flapjack", "flopping", "fluffiness", "flyby", "foxglove", "frazzled", "frizzled", "fuchsia", "funny", "gabby", "galaxy", "galvanize", "gazebo",
"giaour", "gizmo", "glowworm", "glyph", "gnarly", "gnostic", "gossip", "grogginess", "haiku", "haphazard", "hyphen", "iatrogenic", "icebox", "injury",
"ivory", "ivy", "jackpot", "jaundice", "jawbreaker", "jaywalk", "jazziest", "jazzy", "jelly", "jigsaw", "jinx", "jiujitsu", "jockey", "jogging", "joking",
"jovial", "joyful", "juicy", "jukebox", "jumbo", "kayak", "kazoo", "keyhole", "khaki", "kilobyte", "kiosk", "kitsch", "kiwifruit", "klutz", "knapsack", "larynx",
"lengths", "lucky", "luxury", "lymph", "marquis", "matrix", "megahertz", "microwave", "mnemonic", "mystify", "naphtha", "nightclub", "nowadays", "numbskull", "nymph",
"onyx", "ovary", "oxidize", "oxygen", "pajama", "peekaboo", "phlegm", "pixel", "pizazz", "pneumonia", "polka", "pshaw", "psyche", "puppy", "puzzling", "quartz", "queue",
"quips", "quixotic", "quiz", "quizzes", "quorum", "razzmatazz", "rhubarb", "rhythm", "rickshaw", "schnapps", "scratch", "shiv", "snazzy", "sphinx", "spritz", "squawk", "staff",
"strength", "strengths", "stretch", "stronghold", "stymied", "subway", "swivel", "syndrome", "thriftless", "thumbscrew", "topaz", "transcript", "transgress", "transplant", "triphthong",
"twelfth", "twelfths", "unknown", "unworthy", "unzip", "uptown", "vaporize", "vixen", "vodka", "voodoo", "vortex", "voyeurism", "walkway", "waltz", "wave", "wavy", "waxy", "wellspring",
"wheezy", "whiskey", "whizzing", "whomever", "wimpy", "witchcraft", "wizard", "woozy", "wristwatch", "wyvern", "xylophone", "yachtsman", "yippee", "yoked", "youthful", "yummy", "zephyr",
"zigzag", "zigzagging", "zilch", "zipper", "zodiac", "zombie"};

// Letters and blank spaces for letterboard
char letters1[14] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','\0'};
char letters2[14] = {'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
char lettersBlank1[14] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};
char lettersBlank2[14] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};

int main()
{
    // Variables
    bool start;
    char playExit;
    int rng;
    char word[40] = {0};
    char puzzle[40] = {0};
    bool win = false;
    int winCheck;
    int strikes = 0;
    int strikeCheck;
    int wordLength = 0;
    char guess;

    // Title screen
    welcome();

    // Check whether playing or exiting
    do
    {
    cout << "Play (Y) | Exit (N):  ";
    cin >> playExit;
    if (playExit != 'Y' && playExit != 'y' && playExit != 'N' && playExit != 'n')
        cout << "Invalid input! Try again." << endl;
    else
    {
        if (playExit == 'Y' || playExit == 'y')
            start = true;
        else
            start = false;
    }
    } while(playExit != 'Y' && playExit != 'y' && playExit != 'N' && playExit != 'n');


    // --------------- Main code if playing -----------------
    if (start == true)
    {
        // :::::: Set-up :::::::
        // RNG
        srand(time(NULL));
        rng = rand() % 213;
        // Copy random stored word to word array
        strcpy(word, storedWords[rng].c_str());
        // Make word uppercase, store letters as blanks into puzzle, and track word length for future use
        for(int i = 0; word[i] != '\0'; i++)
        {
            puzzle[i] = '_';
            word[i] = toupper(word[i]);
            wordLength++;
        }


        // ::::: Let's play! :::::
        while(win != true)
        {
            nextScreen();
            header();
            hangman(strikes);
            letterBoard(guess);
            for (int i = 0; i != (17 - wordLength); i++) { cout << " "; } // Indent blank puzzle based on size
            for (int i = 0; puzzle[i] != '\0'; i++) { cout << puzzle[i] << " "; } // Display blank puzzle

            if (strikes >= 6)           // 6 strikes = lose
            {
                win = false;
                break;
            }

            if (winCheck == wordLength) // All letters in word match puzzle = win
            {
                win = true;
                break;
            }

            //cout << word << endl;
            cout << "\n\nEnter guess:  ";   // User input
            cin >> guess;
            guess = toupper(guess);         // Convert user's guess to uppercase

            winCheck = 0;
            strikeCheck = 0;
            for (int i = 0; puzzle[i] != '\0'; i++)
            {
                if (word[i] == guess) { puzzle[i] = guess; }    // If guess matches word, replace letter in puzzle
                else { strikeCheck++; }

                if (word[i] == puzzle[i]) { winCheck++; }       // Check if puzzle is complete
            }

            if (strikeCheck == wordLength) { strikes++; }   // If no letters matched the guess then get a strike
        }

        if (win == false) { cout << "\n\n\n <<<<<<<<<<< YOU LOSE >>>>>>>>>>\n\nThe word is:  " << word << endl << endl; system("pause");}
        else { cout << "\n\n\n <<<<<<<<<<< YOU WIN >>>>>>>>>>>" << endl << endl; system("pause");}

        return 0;
    }

    // Code if exiting
    else
    {
        cout << "\nExiting..." << endl;
        system("pause");
        return 0;
    }
}

// Prints multiple empty lines to create a "blank" page
void nextScreen()
{
    for (char i = 75; i != 0; i--) { cout << endl; }
}


// Title screen
void welcome()
{
    cout << "=================================" << endl;
    cout << ":          PLAY HANGMAN         :" << endl;
    cout << "=================================" << endl;
    cout << ":          ___________          :" << endl;
    cout << ":               |               :" << endl;
    cout << ":               |               :" << endl;
    cout << ":               O               :" << endl;
    cout << ":              /|\\              :" << endl;
    cout << ":              / \\              :" << endl;
    cout << ":                               :" << endl;
    cout << "=================================" << endl << endl;
    cout << " -------------------------------" << endl;
    cout << "|   A B C D E F G H I J K L M   |" << endl;
    cout << "|   N O P Q R S T U V W X Y Z   |" << endl;
    cout << " -------------------------------" << endl << endl;
}

// Header when the game is started
void header()
{
    cout << "=================================" << endl;
    cout << ":            HANGMAN            :" << endl;
    cout << "=================================" << endl;
}

// Drawing hangman based on number of strikes
int hangman(int x)
{
    cout << ":          ___________          :" << endl;
    cout << ":               |               :" << endl;
    cout << ":               |               :" << endl;

    if (x == 1)
    {
    cout << ":               O               :" << endl;
    cout << ":                               :" << endl;
    cout << ":                               :" << endl;
    }

    else if (x == 2)
    {
    cout << ":               O               :" << endl;
    cout << ":               |               :" << endl;
    cout << ":                               :" << endl;
    }

    else if (x == 3)
    {
    cout << ":               O               :" << endl;
    cout << ":              /|               :" << endl;
    cout << ":                               :" << endl;
    }

    else if (x == 4)
    {
    cout << ":               O               :" << endl;
    cout << ":              /|\\              :" << endl;
    cout << ":                               :" << endl;
    }

    else if (x == 5)
    {
    cout << ":               O               :" << endl;
    cout << ":              /|\\              :" << endl;
    cout << ":              /                :" << endl;
    }

    else if (x == 6)
    {
    cout << ":               O               :" << endl;
    cout << ":              /|\\              :" << endl;
    cout << ":              / \\              :" << endl;
    }

    else
    {
    cout << ":                               :" << endl;
    cout << ":                               :" << endl;
    cout << ":                               :" << endl;
    }

    cout << ":                               :" << endl;
    cout << "=================================" << endl << endl;
}

// Displaying letters that have been guessed on the letterboard
int letterBoard(char x)
{
    for(int i = 0; i < 13; i++)
    {
        if (letters1[i] == x) { lettersBlank1[i] = letters1[i]; }
        if (letters2[i] == x) { lettersBlank2[i] = letters2[i]; }
    }

    cout << " -------------------------------" << endl;

    cout << "|    ";
    for (int i = 0; i < 13; i++) { cout << lettersBlank1[i] << " "; }
    cout << " |" << endl;

    cout << "|    ";
    for (int i = 0; i < 13; i++) { cout << lettersBlank2[i] << " "; }
    cout << " |" << endl;

    cout << " -------------------------------" << endl << endl; // 32 chars wide
}
