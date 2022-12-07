#include <stdio.h>
#include <string.h>

int typeToPoints(char c){
    if(c >= 'A' && c <= 'Z'){
        return c-'A'+1+26;
    } else {
        return c-'a'+1;
    }
}

void splitString(char* source,char* left,char* right,size_t size){
    char *startOfString = source;
    memcpy(left,startOfString,size/2);
    left[size/2] = '\000';
    startOfString += size/2;
    memcpy(right,startOfString,size/2);
    right[size/2] = '\000';
}

char * findObjectInCommon(char group[3][255]){
    char common[50];
    int count = 0;
    for(int x=0;x< strlen(group[1]);x++){
        char *matchUp = strchr(group[0],group[1][x]);
        char *matchDown = strchr(group[2],group[1][x]);

        if(matchUp != NULL && matchDown != NULL && matchDown[0] != '\n' && matchDown[0] != '\000'){
            return matchDown;
        }
    }
    return group[0];
}

int main() {
    int prioritySum = 0;
    int groupPrioritySum = 0;
    char buff[255];

    char left[255];
    char right[255];

    char group[3][255];

    size_t len = 0;
    int count = 0;

    while (fgets(buff,255,stdin)!=NULL){
        len = strlen(buff)-1;
        strcpy(group[count],buff);
        count++;
        if (count > 2){
            char *commonTypeP = findObjectInCommon(group);
            char commonType;
            memcpy(&commonType,commonTypeP,1);
            groupPrioritySum += typeToPoints(commonType);
            count = 0;
            memset(group[0],'\000',sizeof(group[0]));
            memset(group[1],'\000',sizeof(group[1]));
            memset(group[2],'\000',sizeof(group[2]));

        }
        splitString(buff,left,right,len);
        for(int i =0;i<len/2;i++){
            char *contains = strchr(right,left[i]);
            if(contains != NULL){
                prioritySum += typeToPoints(*contains);
                break;
            }
        }
    }
    printf("%d\n",prioritySum);
    printf("%d",groupPrioritySum);
    return 0;
}
