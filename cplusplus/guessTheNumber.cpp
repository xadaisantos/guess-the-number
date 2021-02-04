#include<iostream>
#include<cstdlib>
#include<exception> // library that contains try and catch error handling stuff
#include<ctime>
using namespace std;

// c++ teste.cpp -out teste.out
// ./teste.out

int main (){
    cout << "Welcome to the guessing game!" << endl;

    srand(time(0));
    // time(0) or time(NULL) number of seconds since 1970
    // srand() seed for random numbers

    const int SECRETNUMBER = rand() % 100;
    bool hasWon = false;
    double points = 1000.0;
    double lostPoints = 0;
    int attempts = 0;
    int numberOfAttempts = 0;

    bool isGreater;
    string difficulty;
    int guess;

    cout << "In which difficulty do you want to play? Easy (E), Normal (N) or Hard (H)?" << endl;
    cin >> difficulty;

    if(difficulty == "E"){
        cout << "You have chosen Easy!" << endl;
        numberOfAttempts = 15;
    }
    else if(difficulty == "H"){
        cout << "You have chosen Hard!" << endl;
        numberOfAttempts = 5;
    }
    else if(difficulty == "N"){
        cout << "You have chosen Normal!" << endl;
        numberOfAttempts = 10;
    }
    else{
        cout << "Since you didn't type \"E\", \"N\" or \"H\", I have chosen Normal for you." << endl;
        numberOfAttempts = 10;
    }

    for(attempts = 1; attempts <= numberOfAttempts; attempts++){

        cout << "Attempt number " << attempts << "! Guess a number! ";
        cin >> guess;        
        lostPoints = abs( (SECRETNUMBER - guess) ) / 2.0;
        points -= lostPoints;
        hasWon = (guess == SECRETNUMBER);
        isGreater = (guess > SECRETNUMBER);

        if(hasWon){
            cout << "Cheers! you've got it right in " << attempts << " attempt(s)!" << endl;
            break;
        }
        else if(isGreater){
            cout << "Guess a lower number!" << endl;
        }
        else{
            cout << "Guess a higher number!" << endl;
        }
    }

    if(hasWon){
        cout.precision(2);
        cout << fixed;
        cout << "You've scored " << points << " points! :D" << endl;
    }
    else{
        cout << "You've lost! Try Again!" << endl;
    }    
}