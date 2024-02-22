#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the StrList struct here
struct _StrList {
    char* _data;
    struct _StrList* _next;
    size_t _size;
};

#include "StrList.h"

// int find_string_len(char str[]){
//     int length = 0;

//     // Iterate through each character of the string until we reach the null terminator
//     while (str[length] != '\0' && str[length] != '\n') {
//         length++;
//     }
//     return length;
// }

// char* getRealString(const char str[]){
//     int length = find_string_len(str);
//     char* realString = (char*)malloc((length + 1) * sizeof(char));
//     if (realString == NULL) {
//         return NULL; // Handle memory allocation failure
//     }

//     // Copy the characters of the real string
//     strncpy(realString, str, length);
//     realString[length] = '\0'; // Null-terminate the string

//     return realString;
// }

int find_string_len(const char str[]);
char* getRealString(const char str[]);

int main(){
    int input = -1;
    StrList* List = StrList_alloc("", NULL);
    // scanf("%d", &input);
    while(scanf("%d", &input) != EOF){
        if (input == 0) {
        break; // Exit the loop if input is 0
        }
        switch (input)
        {
        case 0:{
            break;
        }
        //getting a sentence from the user and seperating it with whitespaces to strings. then, inserting the strings to a list.
        case 1:{
            int numOfWords = 0;
            scanf("%d", &numOfWords);
            getchar();

            char sentence[1000];
            // fgets(sentence, sizeof(sentence), stdin);
            scanf("%[^\n]", sentence);
            getchar();

            char* token = strtok(sentence, " ");
            int i = 0;
            while (token != NULL && i < numOfWords) {
                if (strcmp(List->_data, "") == 0) {
                    strcpy(List->_data, token);
                }
                else{
                    StrList_insertLast(List, strdup(token));
                }
                token = strtok(NULL, " ");
                i++;
            }
            break;
        }

        //entering a string in a certain index
        case 2:{
            int index = 0;
            scanf("%d", &index);
            char word[100];
            scanf(" %[^\n]", word);
            getchar();
            char* realWord = getRealString(word);
            StrList_insertAt(List, realWord, index);
            free(realWord);
            break;
        }
        //print the string
        case 3:{
            StrList_print(List);
            break;
        }

        case 4:{
            printf("%zu", List->_size);
            printf("\n");
            break;
        }

        case 5:{
            int index = 0;
            scanf("%d", &index);
            StrList_printAt(List, index);
            break;
        }

        case 6:{
            int len = StrList_printLen(List);
            printf("%d\n", len);
            break;
        }

        case 7:{
            char word[100];
            scanf("%[^\n]", word);
            getchar();
            char* realWord = getRealString(word);
            printf("%d\n", StrList_count(List, realWord));
            free(realWord);
            break;
        }

        case 8:{
            char word[100];
            scanf("%[^\n]", word);
            getchar();
            char* realWord = getRealString(word);
            StrList_remove(List, realWord);
            free(realWord);
            break;
        }

        case 9:{
            int index = 0;
            scanf("%d", &index);
            StrList_removeAt(List, index);
            break;
        }

        case 10:{
            StrList_reverse(List);
            break;
        }

        case 11:{
            StrList_free(List->_next);
            free(List->_data);
            List->_size = 0;
            break;
        }

        case 12:{
            StrList_sort(List);
            break;
        }

        case 13:{
            if(StrList_isSorted(List) != 0){
                printf("True\n");
            }
            else{
                printf("False\n");
            }
            break;
        }
                
        default:
            break;
        }
    }  
    StrList_free(List);
return 0;
}  