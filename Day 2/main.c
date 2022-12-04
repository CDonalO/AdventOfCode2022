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

char fixedSign(char result,char sign){
    if(result == 'Y'){
        return sign;
    } else if (result == 'X'){
        if(sign == 'A'){
            return 'C';
        } else if (sign == 'B'){
            return 'A';
        } else if (sign == 'C'){
            return 'B';
        }
    } else if (result == 'Z'){
        if(sign == 'A'){
            return 'B';
        } else if (sign == 'B'){
            return 'C';
        } else if (sign == 'C'){
            return 'A';
        }
    }
    return ' ';
}

int main() {
    int points = 0;
    int oldPoints = 0;
    char buff[255];
    char oldSign;
    while (fgets(buff,255,stdin)!=NULL){
//        Part 1 stuff
        oldSign = decryptSign(buff[2]);
        oldPoints += psrScore(buff[0],oldSign);
//        Part 2 stuff
        points += psrScore(buff[0], fixedSign(buff[2],buff[0]));
    }
    printf("%d\n",oldPoints);
    printf("%d",points);
    return 0;
}
