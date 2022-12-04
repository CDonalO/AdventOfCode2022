#include <stdio.h>
#include <string.h>

char decryptSign(char a){
    if(strcmp(&a,"Z")==0){
        return 'C';
    } else if(strcmp(&a,"X")==0){
        return 'A';
    } else if(strcmp(&a,"Y")==0){
        return 'B';
    }
    return ' ';
}

int psrScore(char a,char b){
    b = decryptSign(b);
    int score = 0;
    if (b == 'A'){
        score += 1;
    } else if (b == 'B'){
        score += 2;
    } else if (b == 'C'){
        score += 3;
    }
    if(a == b){
        score += 3;
    } else if ((b == 'B' && a == 'A') || (b == 'C' && a == 'B') || (b == 'A' && a == 'C')){
        score += 6;
    }

    return score;
}

int main() {
    int points = 0;
    char buff[255];
    while (fgets(buff,255,stdin)!=NULL){
        points += psrScore(buff[0],buff[2]);
    }

    printf("%d",points);
    return 0;
}
