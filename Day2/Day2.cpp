#include <iostream>
#include <fstream>
#include <string>
using std::cout, std::fstream, std::ios, std::endl, std::string;

#define REDMAX          (12)
#define GREENMAX        (13)
#define BLUEMAX         (14)

enum{red = 0, green = 1, blue = 2};

int main(){
    fstream file;
    file.open("./puzzle.txt", ios::in);
    if(!file.is_open()){
        cout << "error opening file" << endl;
        return -1;
    }

    string line;
    unsigned int game = 0;
    unsigned int gameSum = 0;
    unsigned int powerSum = 0;
    while(getline(file, line)){
        game++;
        bool gamePossible = true;                           //assume game is possible
        unsigned int gamePower = 0;
        unsigned int minRed = 0;
        unsigned int minGreen = 0;
        unsigned int minBlue = 0;
        for(unsigned int i = 7; i < line.length(); i++){
            if(isdigit(line.at(i))){
                unsigned int temp = 0;                      //holds temp value for comparison
                unsigned int jump = 2;                      //how far to jump to color
                temp += (line.at(i) - 0x30);
                if(isdigit(line.at(i + 1))){
                    temp *= 10;
                    temp += (line.at(i + 1) - 0x30);
                    jump = 3;
                }
                //check to see what color it is and if that value is less than the maximum value
                if(line.at(i + jump) == 'r'){
                    if(temp > REDMAX) gamePossible = false;
                    if(temp > minRed) minRed = temp;
                }
                else if(line.at(i+jump) == 'g'){
                    if(temp > GREENMAX) gamePossible = false;
                    if(temp > minGreen) minGreen = temp;
                }
                else if(line.at(i+jump) == 'b'){
                    if(temp > BLUEMAX) gamePossible = false;
                    if(temp > minBlue) minBlue = temp;
                }
            }
        }
        if(gamePossible) gameSum += game;           //if the game was possible with these values, add the game to the sum
        gamePower = minRed * minBlue * minGreen;    //find game power
        powerSum += gamePower;                      //add game power to power sum
    }
    cout << "Sum of Games: " << gameSum << endl;
    cout << "Sum of Game Powers: " << powerSum << endl;


    file.close();
    return 0;
}