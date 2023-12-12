#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout, std::fstream, std::ios, std::endl, std::string, std::vector;

bool hasNeighboringSymbol(const vector<string>& map, unsigned int row, unsigned int column){
    unsigned int maxRows = map.size();
    unsigned int maxColumns = map.at(row).size();

    //check area around given position to find symbol
    for(int neighborRow = row-1; neighborRow < row+2; neighborRow++){
        for(int neighborColumn = column-1; neighborColumn < column+2; neighborColumn++){
            //check bounds
            if(neighborRow >= 0 && neighborRow < maxRows && neighborColumn >= 0 && neighborColumn < maxColumns){
                char neighbor = map.at(neighborRow).at(neighborColumn);
                if(neighbor != '.' && !isdigit(neighbor)){
                    return true;    //if the neighboring character is not '.' or is not a digit, then there is a part number at map[row][column]
                }
            }
        }
    }
    return false;                   //no special symbol found, so no part detected
}

int main(){
    //open file and check to see if file open
    fstream file;
    file.open("./puzzle.txt", ios::in);
    if(!file.is_open()){
        cout << "Error opening file" << endl;
        return -1;
    }

    vector<string> puzzleMap;           //operational map of puzzle
    string line;                        //line to copy from input

    //copy input to puzzleMap vector
    while(getline(file, line)){
        puzzleMap.push_back(line);
    }
    file.close();                       //close file, no longer needed
    line.clear();                       //line no longer needed

    string partNumString;               //for converting string to int
    bool isAPart = false;               //checks to see if part is valid, assume false
    unsigned int sumOfParts = 0;        //final sum

    for(int row = 0; row < puzzleMap.size(); row++){
        for(unsigned int column = 0; column < puzzleMap.at(row).size(); column++){
            char character = puzzleMap.at(row).at(column);
            if(isdigit(character)){                                                             //find digit
                partNumString += character;                                                     //add number to numstring
                if(!isAPart && hasNeighboringSymbol(puzzleMap, row, column)) isAPart = true;    //if not yet a valid part, check to see if valid part, add if true.
            }
            else{
                if(isAPart) sumOfParts += stoi(partNumString);      //convert and add to sum
                isAPart = false;                                    //reset for next part
                partNumString = "";                                 //reset for next part
            }
        }
    }
    //currently 1,507,443 (too high)
    cout << "Sum of parts: " << sumOfParts << endl;

    return 1;
}