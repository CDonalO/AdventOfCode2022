#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {fileSystemSize = 70000000,updateSizeRequired=30000000};

typedef struct KeyValue {
    char * key;
    unsigned long size;
    struct KeyValue** children;
    int childCount;
    struct KeyValue* parent;
}kv;

kv* root;
kv* currentDir;

kv * getDirectory(char * dir){
    if (strcmp(dir,root->key) == 0){
        return root;
    } else {
        for (int i = 0; i < currentDir->childCount; i++) {
            if(strcmp(dir,currentDir->children[i]->key)==0){
                return currentDir->children[i];
            }
        }
    }
    return NULL;
}

void executeCommand(char* command){
    command+=2;
    char *cmd = strtok(command," ");
    char *argument = strtok(NULL," ");
    if(argument != NULL){
        argument[strlen(argument)-1] = '\000';
    } else{
        cmd[strlen(cmd)-1] = '\000';
    }
    if(strcmp("cd",cmd)==0){
        if(strcmp("/",argument)==0){
            root = malloc(sizeof(kv));
            root->size = 0;
            root->key = "/";
            root->childCount = 0;
            root->children = NULL;
            root->parent = NULL;
            currentDir = root;
        } else if (strcmp("..",argument)==0){
            currentDir = currentDir->parent;
        } else {
            kv * index =getDirectory(argument);
            currentDir = index;
        }

    }
//    else if(strcmp("ls",cmd)==0){
//        printf("a");
//    }
}

void addToParent(kv * parent,kv* target){
    if(parent->children == NULL){
        parent->children = malloc(sizeof(kv*)*100);
    }
    parent->children[parent->childCount] = target;
    parent->childCount+=1;
}

void createDir(char * dir){
    dir+=4;
    dir[strlen(dir)-1] = '\000';
    kv * index = getDirectory(dir);
    if(index == NULL){
        kv * directory = malloc(sizeof(kv));
        directory->parent= currentDir;
        directory->key = malloc(sizeof(char)*50);
        strcpy(directory->key,dir);
        directory->children = NULL;
        directory->childCount = 0;
        directory->size = 0;
        addToParent(directory->parent,directory);
    } else{
        printf("uh oh");
    }
}

void calculateTrueSize(kv* currDir){
    if(currDir == NULL){
        return;
    }
    for(int i = 0;i<currDir->childCount;i++){
        calculateTrueSize(currDir->children[i]);
    }
    if(currDir != root) {
        currDir->parent->size += currDir->size;
    }
}

void calculateSumOfDir(unsigned long*sum,kv * currDir){
    for (int i = 0; i < currDir->childCount; i++) {
        calculateSumOfDir(sum,currDir->children[i]);
    }
    if(currDir->size <= 100000){
        *sum+= currDir->size;
    }

}

void printTree(kv*currDir,int depth){
    for (int i = 0; i < depth; ++i) {
        printf(" ");
    }
    printf("- ");
    printf("%s (%lli)\n",currDir->key,currDir->size);
    for (int i = 0; i < currDir->childCount; i++) {
        printTree(currDir->children[i],depth+1);
    }
}

void findMinSizeToUpdate(kv * currDir,unsigned long* currSmallest,unsigned long sizeNeeded){
    for (int i = 0; i < currDir->childCount; i++) {
        findMinSizeToUpdate(currDir->children[i],currSmallest,sizeNeeded);
    }
    if(currDir->size >= sizeNeeded && currDir->size < *currSmallest){
        *currSmallest = currDir->size;
    }
}

int main() {
    char buff[100];
    unsigned long sum = 0;
    while ((fgets(buff,100,stdin))!= NULL){
        if(buff[0] == '$'){
            executeCommand(buff);
        } else if(buff[0] == 'd'){
            createDir(buff);
        } else {
            int size = strtol(buff,NULL,10);
            currentDir->size+=size;
        }
    }
    calculateTrueSize(root);
    calculateSumOfDir(&sum,root);
    unsigned long sizeNeeded = updateSizeRequired-(fileSystemSize-root->size);
    unsigned long smallestSize = root->size;
    findMinSizeToUpdate(root,&smallestSize,sizeNeeded);
//    printTree(root,0);
    printf("%lli\n",sum);
    printf("%lli",smallestSize);
    return 0;
}
