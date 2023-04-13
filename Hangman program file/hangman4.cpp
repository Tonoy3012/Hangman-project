/**
Project Created by Team HASSASIN (Section 23A)
Members: Mustafa Haque
               Tonoy Sheikh
                Israt Jahan Archi
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include <conio.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;

void greet();
string takePasswdFromUser();
string generateBlanks(int n);
string convert_lowercase(string s);
void check_word(vector<string> v, string s);
void addWord(vector<string> v, string s);
int random_Number(int n);
string random_Word(vector<string> v);
void display_misses(int misses);
void display_status(vector<char> incorrect, string answer);
void end_game(string answer, string codeword, string p1, string p2);
void end_game(string answer, string codeword);

// global variable indicating a new word
bool newWord = false;

int main()
{
    greet();

    ifstream f_in("Wordlist.txt");
    vector<string> vec_words;
    string s_line;
    while (getline(f_in, s_line))
    {
        vec_words.push_back(s_line);
    }

    int choice;
    cout << "Please Enter your selection\n";
    cin >> choice;
    while (choice < 1 || choice > 3)
    {
        cout << "Invalid selection. Try again. \n";
        cin >> choice;
    }

    switch(choice)
    {
    case 1:
    {
        system("cls");
        cout << "Player vs Player mode has been chosen\n";
        string p1, p2;
        cout << "\nPlease Enter the name of Player 1: ";
        cin >> p1;
        cout << "\nPlease Enter the name of Player 2: ";
        cin >> p2;
        cout << endl;
        cout << p1 << " Will Enter a secret word\n";
        cout << p2 << " Will Guess the secret word\n";
        cout << endl;
        cout << p1 << ": Please enter a word you want your opponent to guess: \n";

        string codeword, codeword_mixed;
        codeword_mixed = takePasswdFromUser();
        codeword = convert_lowercase(codeword_mixed);

        check_word(vec_words, codeword);
        system("cls");

        int word_length = codeword.length();
        string answer;
        answer = generateBlanks(word_length);

        int misses = 0;
        vector<char> incorrect;
        bool guess = false;
        char letter;

        while(answer!=codeword && misses<7)
        {

            display_misses(misses);
            display_status(incorrect, answer);

            cout << "\n\nPlease Enter one letter as your guess: ";
            cin >> letter;
            system("cls");

            for(int i=0; i<codeword.length(); i++)
            {
                if(letter == codeword[i])
                {
                    answer[i] = letter;
                    guess = true;
                }
            }
            if(guess)
            {
                cout << "\nCorrect!\n\n";
            }
            else
            {
                cout << "\nIncorrect! Another portion of the person has been drawn\n\n";
                incorrect.push_back(letter);
                misses++;
            }
            guess = false;
        }

        end_game(answer, codeword, p1, p2);
    }
    break;
    case 2:
    {
        system("cls");
        cout << "Computer vs Player mode has been chosen\n";
        cout << "In this mode a random word will be chosen from the Word database\n";

        string codeword;
        codeword = random_Word(vec_words);
        system("cls");

        int word_length = codeword.length();
        string answer;
        answer = generateBlanks(word_length);

        int misses = 0;
        vector<char> incorrect;
        bool guess = false;
        char letter;

        while(answer!=codeword && misses<7)
        {

            display_misses(misses);
            display_status(incorrect, answer);

            cout << "\n\nPlease Enter one letter as your guess: ";
            cin >> letter;
            system("cls");

            for(int i=0; i<codeword.length(); i++)
            {
                if(letter == codeword[i])
                {
                    answer[i] = letter;
                    guess = true;
                }
            }
            if(guess)
            {
                cout << "\nCorrect!\n\n";
            }
            else
            {
                cout << "\nIncorrect! Another portion of the person has been drawn\n\n";
                incorrect.push_back(letter);
                misses++;
            }
            guess = false;
        }

        end_game(answer, codeword);

    }
    break;
    case 3:
        exit(0);
        break;
    default:
        cout << "Invalid choice" << endl;
    }

    return 0;
}

// Gives instruction about the game.
// Gives the list of different modes.
void greet()
{
    cout << "Created by Hasasins\n";
    cout << "Mustafa Haque, Tonoy Sheikh, Israt Jahan Archi\n\n";
    cout << "===================================================\n";
    cout << "Hangman: The Game\n";
    cout << "===================================================\n";
    cout << "Instructions: Save a man from being hanged by guessing the letters in the codeword.\n";
    cout << "Select the mode of game: \n";
    cout << "[1]. Player vs Player \n";
    cout << "[2]. Computer vs Player \n";
    cout << "[3]. Exit \n\n\n";
}

// Hangman pictorial representation
void display_misses(int misses)
{
    if(misses==0)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==1)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==2)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<"  |   | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==3)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<" /|   | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==4)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<" /|\\  | \n";
        cout<<"      | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==5)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<" /|\\  | \n";
        cout<<" /    | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
    else if(misses==6)
    {
        cout<<"  +---+ \n";
        cout<<"  |   | \n";
        cout<<"  O   | \n";
        cout<<" /|\\  | \n";
        cout<<" / \\  | \n";
        cout<<"      | \n";
        cout<<" ========= \n";
    }
}

// displays the guesses
void display_status(vector<char> incorrect, string answer)
{
    cout << "\nIncorrect Guesses: \n";

    for(int i=0; i<incorrect.size(); i++)
    {
        cout << incorrect[i] << " ";
    }

    cout << "\n\nCodeword: \n";
    for(int i=0; i<answer.length(); i++)
    {
        cout << answer[i] << " ";
    }
}

// End game prompt (player vs player)
void end_game(string answer, string codeword, string p1, string p2)
{
    if(answer == codeword)
    {
        cout << "The word is: " << codeword << endl << endl;
        if(newWord)
        {
            cout << "This word was NOT in the database.\n";
            cout << "This word has been added to the database.\n";
        }
        cout << "You saved the man from being hanged \n\n";
        cout << "Congratulations " << p2 << "!!\n";
    }
    else
    {
        cout << "\nOh no! The man is hanged! \n";
        cout << "The word was: " << codeword << endl;
        if(newWord)
        {
            cout << "This word was NOT in the database.\n";
            cout << "This word has been added to the database.\n";
        }
        cout << "\nGAME OVER \n";
        cout << "Congratulations " << p1 << "!!\n";

    }
}

// End game prompt (computer vs player)
void end_game(string answer, string codeword)
{
    if(answer == codeword)
    {
        cout << "The word is: " << codeword << endl << endl;
        if(newWord)
        {
            cout << "This word was NOT in the database.\n";
            cout << "This word has been added to the database.\n";
        }
        cout << "You saved the man from being hanged \n\n";
        cout << "Congratulations !!\n";
    }
    else
    {
        cout << "\nOh no! The man is hanged! \n";
        cout << "The word was: " << codeword << endl;
        if(newWord)
        {
            cout << "This word was NOT in the database.\n";
            cout << "This word has been added to the database.\n";
        }
        cout << "\nGAME OVER \n";
    }
}

// Takes password and masks it using '*'
string takePasswdFromUser()
{
    string in = "";
    char ch;
    while (true)
    {
        ch = _getch();
        _putch('*');

        // Check whether user enters
        // a special non-printable
        // character
        if (ch < 32)
        {
            cout << endl;
            return in;
        }
        in.push_back(ch);
    }
}

// Converts string to lower case
string convert_lowercase(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Check whether the word is in the Words database
void check_word(vector<string> v, string s)
{
    int flag = 0;
    for(int i=0; i<v.size(); i++)
    {
        if(s != v[i])
        {
            flag++;
        }
    }
    if(flag == v.size())
    {
        addWord(v, s);
    }
}

// Adds a word to the Words database
void addWord(vector<string> v, string s)
{
    ofstream f_out("Wordlist.txt");
    v.push_back(s);
    sort(v.begin(), v.end());   //Sorting the list
    for(int i=0; i<v.size(); i++)
    {
        f_out << v[i] << endl;
    }
    newWord = true;
}

// Generates blanks to represent each letter
string generateBlanks(int n)
{
    string a = "";
    string b = "_";
    for(int i=0; i<n; i++)
    {
        a = a.append(b);
    }
    return a;
}

// Generates random number
int random_Number(int n)
{
    srand((unsigned) time(NULL));
    // Retrieve a random number between 100 and 200
    // Offset = 0
    // Range = 100000000
    int random = (rand() % n);

    return random;
}

// Generates random word from the Words database
string random_Word(vector<string> v)
{
    int num = random_Number(v.size());
    return v[num];
}
