#ifndef UTILITY_H
#define UTILITY_H

#endif //UTILITY_H

#include <iostream>
#include <cstring>
#include <cmath>
#include <regex>
#include <string>
#include <algorithm>

using namespace std;

//function prototypes
void printMenu();
string listInput();
int rotateImageInput(string text);
string lightAdjustmentInput();
string shrinkImageInput();
int shuffleImageInput(string text);
string removeSpaces(string txt);




//_________________________________________
void printMenu()
{
    cout << endl
         << "Menu Options::" << endl
         << endl;
    cout << "1- Black and white Filter" << endl
         << "2- Invert Image Filter" << endl
         << "3- Merge Filter" << endl
         << "4- Flip Image Filter" << endl
         << "5- Rotate Image Filter" << endl
         << "6- Darken and Lighten Image Filter" << endl
         << "7- Detect Image Edges Filter" << endl
         << "8- Enlarge Image Filter" << endl
         << "9- Shrink Image Filter" << endl
         << "a- Mirror half RGBImage Filter" << endl
         << "b- Shuffle Image Filter" << endl
         << "c- Blur Image Filter" << endl
         << "s- Save the RGBImage to a file" << endl
         << endl;

    cout << "Please select a filter to apply: ";
}

//_________________________________________
string listInput()
{
    string userChoice;
    bool menuOptionValid = false;
    while (!menuOptionValid)
    {
        getline(cin, userChoice);
        regex check("[1-9]{1}|[a-c]{1}|[A-C]{1}|[s]{1}|[S]{1}");
        if (regex_match(userChoice, check) && userChoice.length() == 1)
        {
            menuOptionValid = true;
        }
        else
        {
            system("cls");
            cout << "Invalid input" << endl;
            printMenu();
        }
    }
    return userChoice;
}

//_________________________________________
int rotateImageInput(string text)
{
    regex check("[1-3]{1}");
    return regex_match(text, check);
}

//_________________________________________
string lightAdjustmentInput()
{
    string lightInput;
    bool menuOptionValid = false;
    while (!menuOptionValid)
    {
        cout << "1-Darken" << endl
             << "2-Lighten" << endl
             << endl
             << "Please select a filter to apply: ";
        getline(cin, lightInput);
        regex check("[1-2]{1}");
        if (regex_match(lightInput, check) && lightInput.length() == 1)
        {
            menuOptionValid = true;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
        }
    }
    return lightInput;
}

//_______________________________________________________________________________________
string shrinkImageInput()
{
    string shrinkInput;
    bool menuOptionValid = false;
    while (!menuOptionValid)
    {
        cout << "1-(1/2)" << endl
             << "2-(1/3)" << endl
             << "3-(1/4)" << endl
             << endl
             << "Please select a filter to apply: ";
        getline(cin, shrinkInput);
        regex check("[1-3]{1}");
        if (regex_match(shrinkInput, check) && shrinkInput.length() == 1)
        {
            menuOptionValid = true;
        }
        else
        {
            system("cls");
            cout << "Invalid Input" << endl
                 << endl;
        }
    }
    return shrinkInput;
}

//_________________________________________
int shuffleImageInput(string text)
{
    regex check("[1-4]{1} ?[1-4]{1} ?[1-4]{1} ?[1-4]{1}");
    return regex_match(text, check);
}
//_________________________________________
string removeSpaces(string txt)
{
    string newWord;
    for (char letter : txt)
    {
        if (isdigit(letter))
        {
            newWord.push_back(letter);
        }
    }
    return newWord;
}