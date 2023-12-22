#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using std::cout, std::fstream, std::ios, std::endl, std::string, std::vector, std::strstr;

#define winningNumbersStart             (10)
#define scratchOffStart                 (42)

void getWinningNumbers(const string& card, vector<string>& winningNums){
    //could also hard code substrings but this is easier to look at I think
    for(int iter = 0; iter < 10; iter++){
        size_t currentNum = winningNumbersStart + (iter*3);         //finds current winning number by taking location of first winning number and adding 3*position
        winningNums.push_back(card.substr(currentNum, 2));          //winning numbers are 2 digits long
    }
}

int main(){
    //open file and check to see if file open
    fstream file;
    file.open("./puzzle.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return -1;
    }

    vector<string> listOfWinningNumbers;
    string line;

    int sumOfPoints = 0;
    while(getline(file, line)){

        //initialize card
        listOfWinningNumbers.clear();
        bool hasWinningNumbers = false;
        int cardPoints = 1;
        getWinningNumbers(line, listOfWinningNumbers);

        //at this point we have acquired the winning numbers for the card, now we must find if the card has winning numbers and how many point it gets.
        //easiest solution is strstr, and string is not big enough for complexity issues
        string scratchOffs = line.substr(scratchOffStart);

        for(string winningNumber : listOfWinningNumbers){
            if(scratchOffs.find(winningNumber) != string::npos){
                if(!hasWinningNumbers) hasWinningNumbers = true;
                else cardPoints *= 2;
            }
        }

        if(hasWinningNumbers) sumOfPoints += cardPoints;
    }

    cout << "Sum of points: " << sumOfPoints << endl;

    return 0;
}