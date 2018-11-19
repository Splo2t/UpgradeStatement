#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _birth{
    int year;
    char month;
    char day;
} typedef birth;

struct _statement{
    char name[20];
    birth myBirth;
    char gender[7];
    char phoneNumber[14];
} typedef statement;
/*
늙은순
이름빠른순
 *
 */
struct _birth integerToBirth(int tempBirth);
struct _statement *inputStatement();
int birthToInteger(struct _birth birth1);
void printStatementArr(struct _statement **myStatement, int index);
void sortingStatement(struct _statement **arrStatement, int sortType, int sizeArrStatement);
int stringBirthToBirth(char *s);
void printStatement(struct _statement *statement);

int main() {
    int state;
    int n;

    statement **arrStatement;

    while (1){
        printf("수행 할 작업을 선택하세요(0 = 종료, 1 = 입력, 2 = 출력):");
        scanf("%d", &state);
        switch(state){
            case 0:
                return 0;
            case 1:
                printf("입력할 자료의 갯수를 입력하세요.");
                scanf("%d", &n);
                arrStatement = (statement**)malloc(sizeof(statement*)*n);
                for(int i = 0; i < n; i++){
                    printf("개별명세 입력%d(이름,생일,성별,번호 순):", i+1);
                    arrStatement[i] = inputStatement();
                }
                break;
            case 2:
                printStatementArr(arrStatement, n);
                break;
        }
    }
}

struct _statement* inputStatement(){
    statement *myStatement = malloc(sizeof(struct _statement)) ;
    char *tempBirth = malloc(sizeof(char)*20);
    while(1){
        scanf("%s", myStatement->name);
        scanf("%s", tempBirth);
        myStatement->myBirth = integerToBirth(stringBirthToBirth(tempBirth));
        scanf("%s",myStatement->gender);
        scanf("%s",myStatement->phoneNumber);
        free(tempBirth);
        return myStatement;
    }

}

void printStatementArr(struct _statement **myStatement, int index){
    printf("original_data\n");
    printf("\t\tname\t\t  birth\t\t   gender\tPhoneNumber\t\t\t\n");
    for(int i = 0; i < index; i++){
        printStatement(myStatement[i]);
    }

    sortingStatement(myStatement, 0, index);
    printf("\nname_sorting_data\n");
    printf("\t\tname\t\t  birth\t\t   gender\tPhoneNumber\t\t\t\n");
    for(int i = 0; i < index; i++){
        printStatement(myStatement[i]);
    }

    printf("\nage_sorting_data\n");
    sortingStatement(myStatement, 1, index);
    printf("\t\tname\t\t  birth\t\t   gender\tPhoneNumber\t\t\t\n");
    for(int i = 0; i < index; i++){
        printStatement(myStatement[i]);
    }
}

void printStatement(struct _statement *myStatement) {

        printf("%12s", myStatement->name);
        printf("\t\t%d.%d.%d",myStatement->myBirth.year,myStatement->myBirth.month,myStatement->myBirth.day);
        printf("\t\t%s",myStatement->gender);
        printf("\t%10s\n", myStatement->phoneNumber);

}

void sortingStatement(struct _statement **arrStatement, int sortType, int sizeArrStatement){
    statement *temp;
    switch(sortType){
        case 0: //이름순
            for(int i = 0; i < sizeArrStatement; i++){
                for(int j = 0; j <= i; j++){
                    if((strcmp(arrStatement[i]->name, arrStatement[j]->name)) > 0){
                        temp = arrStatement[i];
                        arrStatement[i] = arrStatement[j];
                        arrStatement[j] = temp;
                    }
                }
            }
             break;

        case 1: //나이순
            for(int i = 0; i < sizeArrStatement; i++){
                for(int j = 0; j <= i; j++){
                    if(birthToInteger(arrStatement[i]->myBirth) < birthToInteger(arrStatement[j]->myBirth)){
                        temp = arrStatement[i];
                        arrStatement[i] = arrStatement[j];
                        arrStatement[j] = temp;
                    }

                }
            }
            break;

        default : break;

    }
}

int birthToInteger(struct _birth birth1){
    return birth1.year*10000 + birth1.month*100 + birth1.day;
}

int stringBirthToBirth(char *s){
    char returnVal[12] = {0};
    int index = 0;
    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == '/')continue;
        returnVal[index++] = s[i];
    }
    returnVal[index] = '\0';
    return atoi(returnVal);
}
struct _birth integerToBirth(int tempBirth){
    birth returnBirth;

    returnBirth.year = tempBirth / 10000;
    returnBirth.month = (tempBirth % 10000 /100);
    returnBirth.day = tempBirth%100;

    return returnBirth;
}