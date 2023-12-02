#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE         (64)

//assumes 0x30 <= value <= 0x39
int hexToInt(int value){
    value &= ~0x30;
    return value;
}

int main(){
    FILE* input_file;
    input_file = fopen("input.txt", "r");
    if(input_file == NULL){
        printf("error opening file");
        return -1;
    }

    int sum = 0;
    char line[BUFFER_SIZE];
    while(fgets(line, BUFFER_SIZE, input_file)){
        int tens = 0;
        int ones = 0;

        for(int i = 0; i < strlen(line); i++){
            if(line[i] >= 0x30 && line[i] <= 0x39){
                if(!tens) tens = hexToInt(line[i]);         //get first value
                ones = hexToInt(line[i]);                   //get second value, if only one value, both are that value
            }
        }

        sum += (tens*10) + ones;
    }
    printf("%d", sum);
    fclose(input_file);
    return 0;
}