//#include <stdio.h>
//#include <string.h>
//
//// Define states as constants
//#define S0 "S0"
//#define S1 "S1"
//#define S2 "S2"
//#define S3 "S3"
//#define S4 "S4"
//#define S5 "S5"
//#define S6 "S6"
//
//int main(void) {
//    char input[4];
//
//    while (1) {
//        printf("\nEntrada -> ");
//        scanf("%s", input);
//
//        if (strcmp(input, "r") == 0) {
//            printf("\n%s", S1);
//            printf("\nEntrada -> ");
//            scanf("%s", input);
//            if (strcmp(input, "1") == 0 || strcmp(input, "2") == 0) {
//                printf("\n%s", S2);
//                break;
//            } else if (strcmp(input, "3") == 0) {
//                printf("\n%s", S5);
//                break;
//            } else if (strspn(input, "0123456789") == strlen(input)) {
//                printf("\n%s", S4);
//                break;
//            }
//        } else if (strncmp(input, "r1", 2) == 0 || strncmp(input, "r2", 2) == 0) {
//            printf("\n%s", S2);
//            break;
//        } else if (strncmp(input, "r10", 3) == 0 || strncmp(input, "r", 2) == 0) {
//            printf("\n%s", S3);
//            break;
//        } else if (strcmp(input, "r3") == 0) {
//            printf("\n%s", S5);
//            break;
//        } else if (strncmp(input, "r30", 3) == 0 || strncmp(input, "r31", 3) == 0) {
//            printf("\n%s", S6);
//            break;
//        } else if (strspn(input, "0123456789") == strlen(input)) {
//            printf("\n%s", S4);
//            break;
//        } else {
//            printf("Valor invalido");
//            break;
//        }
//    }
//
//    return 0;
//}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum State {
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    INVALID
};

int main(void) {
    enum State currentState = S0;
    char input[4];

    while (1) {
        printf("\nEntrada -> ");
        scanf("%s", input);

        enum State nextState = INVALID;

        switch (currentState) {
            case S0:
                if (strcmp(input, "r") == 0) {
                    nextState = S1;
                }
                break;

            case S1:
                if (strcmp(input, "1") == 0 || strcmp(input, "2") == 0) {
                    nextState = S2;
                    break;
                } else if (strcmp(input, "3") == 0) {
                    nextState = S5;
                    
                }else if (strspn(input, "0456789") == strlen(input)) {
                    nextState = S4;
                }else if((strcmp(input, "10") == 0 || strcmp(input, "11") == 0 ||
                          strcmp(input, "12") == 0 || strcmp(input, "13") == 0 ||
                          strcmp(input, "14") == 0 || strcmp(input, "15") == 0 ||
                          strcmp(input, "16") == 0 || strcmp(input, "16") == 0 ||
                          strcmp(input, "17") == 0 || strcmp(input,"18") == 0 ||
                          strcmp(input, "19") == 0 || strcmp(input,"20") == 0 ||
                          strcmp(input, "21") == 0 || strcmp(input,"22") == 0 ||
                          strcmp(input, "23") == 0 ||strcmp(input, "24") == 0 ||
                          strcmp(input, "25") == 0 ||strcmp(input, "26") == 0 ||
                          strcmp(input, "26") == 0 ||strcmp(input, "27") == 0 ||
                          strcmp(input, "28") == 0 ||strcmp(input, "29") == 0)){
                    nextState = S3;
                }else if (strcmp(input, "30") == 0 || strcmp(input, "31") == 0){
                    nextState = S6;
                }
                break;

            case S2:
                
                break;

            case S3:
               
                break;

            case S4:
                
                break;

            case S5:
                
                break;

            case S6:
                
                break;

            case INVALID:
                
                break;
        }

        if (nextState == INVALID) {
            printf("Valor invalido\n");
            break;
        }

        currentState = nextState;
        printf("\nS%d\n", currentState);
        
        if(currentState == S2 || currentState == S3 || currentState == S4 || currentState == S5 || currentState == S6 ){
            exit(0);
        }
    }

    return 0;
}
