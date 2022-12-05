#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>



void printMenu();
int checkString(char[]);
void printWords(char[][20], int);
void insertStrings(char[][20], int);
int getSize(int, int);
int asciiSum(char[]);
double asciiAvg(char[]);
void sortStringsLexicographic(char[][20], int);
void sortStringsByLength(char[][20], int);
void sortStringsByAsciiAvg(char[][20], int);
void sortStringsByAsciiSum(char[][20], int);
void sortEachString(char[][20], int);
void sortString(char[]);
void sortAllAsOne(char[][20], int);
int string_sort_help(char[]);
int getMenueVal();


void printMenu() {
    printf("The menu:\n");
    printf("=========\n");
    printf("0. Exit\n");
    printf("1. Insert words\n");
    printf("2. Print words\n");
    printf("3. Sort words lexicographic\n");
    printf("4. Sort words by length\n");
    printf("5. Sort words by ascii sum\n");
    printf("6. Sort words by ascii average\n");
    printf("7. Sort each word by ascii\n");
    printf("8. Sort all words as one\n");
}

int checkString(char arr_rec[]) {
    char arr_input[201] = { '\0' };
    fflush(stdin);
    fgets(arr_input, 201, stdin);
    int len = (int)strlen(arr_input);
    if (len != 1) arr_input[len - 1] = '\0';
    int fl = 1;
    int count = 0;
    int cor = 1;
    while (fl) {
        if (('a' <= arr_input[count] && arr_input[count] <= 'z') || ('A' <= arr_input[count] && arr_input[count] <= 'Z' || arr_input[count] == '\0')) {
            cor = 1;
            fl = 1;
        }
        else {
            cor = 0;
            fl = 0;

        }
        if (arr_input[count] == '\0') {
            fl = 0;
        }
        count++;
    }
    if (strlen(arr_input) > 19 || cor == 0) {
        return 0;
    }
    //change to strcpy
    for (int i = 0; i <= count; i++) {
        arr_rec[i] = arr_input[i];
    }
    return 1;
}

int asciiSum(char arr[]) {
    int count = 0;
    for (int i = 0; i < strlen(arr); ++i) {
        count = count + (int)arr[i];
    }
    return count;
}

double asciiAvg(char arr[]) {
    int sum = asciiSum(arr);
    double len = (double)strlen(arr);
    double ans = (double)sum / len;
    return ans;
}

void printWords(char arr[][20], int n) {
    printf("The words are:\n");
    printf("==============\n");
    for (int i = 0; i < n; i++) {
        printf("%02d:(ascii sum %4d, ascii avg %6.2f)%s\n", i + 1, asciiSum(arr[i]), asciiAvg(arr[i]), arr[i]);
    }
}

void insertStrings(char arr[][20], int n) {
    int count = 0;
    int index = -1;
    while (count < n) {
        if (index == count) {
            printf("Wrong input, try again:\n");
        }
        else {
            printf("Please enter word #%d:\n", count + 1);
        }
        int stat = checkString(arr[count]);
        if (stat == 1) {
            count = count + 1;
            index = -1;
        }
        else index = count;
    }
}

int getSize(int min, int max) {
    char num_input[201] = { '\0' };
    int fl = 0;

    while (!fl) {
        int index1 = 0;
        int index2 = 0;
        int res = 0;
        fl = 1;
        int num_index = -1;
        printf("Please enter a number between %d and %d:", min, max);
        fflush(stdin);
        fgets(num_input, 201, stdin);
        int len = (int)strlen(num_input);
        len = len - 1;

        for (int i = 0; (i < len) && fl; i++) {
            if (48 <= (int)num_input[i] && (int)num_input[i] <= 57) {
                if (num_index == -1) {
                    num_index = i;
                    index1 = i;
                }
                else if (i - num_index == 1) {
                    num_index = i;
                    index2 = i;
                }
                else fl = 0;
            }
            else if (!((int)num_input[i] == 32 || (int)num_input[i] == 9)) fl = 0;
        }
        if (fl) {
            for (int j = index1; j <= index2; j++) {
                if (j != index2)res = (((int)num_input[j] - 48) + res) * 10;
                else res = (((int)num_input[j] - 48) + res);
            };

            if (res >= min && res <= max) return res;
            else fl = 0;
        }
    };
    return 0;
}

void sortStringsLexicographic(char arr[][20], int n) {
    int res = 0;
    char temp[20];
    int fl = 1;
    while (fl) {
        fl = 0;
        for (int i = 0; i < n - 1; i++) {
            res = strcmp(arr[i], arr[i + 1]);
            if (res > 0) {
                fl = 1;
                strcpy(temp, arr[i + 1]);
                strcpy(arr[i + 1], arr[i]);
                strcpy(arr[i], temp);
            }
        }
    }

}

void sortStringsByLength(char arr[][20], int n) {
    int res = 0;
    char temp[20];
    int fl = 1;
    while (fl) {
        fl = 0;
        for (int i = 0; i < n - 1; i++) {
            res = (int)strlen(arr[i]) - (int)strlen(arr[i + 1]);
            if (res > 0) {
                fl = 1;
                strcpy(temp, arr[i + 1]);
                strcpy(arr[i + 1], arr[i]);
                strcpy(arr[i], temp);
            }
        }
    }

}

void sortStringsByAsciiAvg(char arr[][20], int n) {
    double res = 0;
    char temp[20];
    int fl = 1;
    while (fl) {
        fl = 0;
        for (int i = 0; i < n - 1; i++) {
            res = asciiAvg(arr[i]) - asciiAvg(arr[i + 1]);
            if (res > 0) {
                fl = 1;
                strcpy(temp, arr[i + 1]);
                strcpy(arr[i + 1], arr[i]);
                strcpy(arr[i], temp);
            }
        }
    }

}

void sortStringsByAsciiSum(char arr[][20], int n) {
    int res = 0;
    char temp[20];
    int fl = 1;
    while (fl) {
        fl = 0;
        for (int i = 0; i < n - 1; i++) {
            res = asciiSum(arr[i]) - asciiSum(arr[i + 1]);
            if (res > 0) {
                fl = 1;
                strcpy(temp, arr[i + 1]);
                strcpy(arr[i + 1], arr[i]);
                strcpy(arr[i], temp);
            }
        }
    }

}

void sortString(char arr[]) {
    int res = 0;
    char temp;
    int fl = 1;
    while (fl) {
        fl = 0;
        for (int i = 0; i < strlen(arr) - 1; i++) {
            res = (int)(arr[i]) - (int)(arr[i + 1]);
            if (res > 0) {
                fl = 1;
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

int string_sort_help(char arr[]) {
    int res = 0;
    char temp;
    int fl = 1;
    int ret_fl = 0;
    while (fl) {
        fl = 0;
        for (int i = 0; i < strlen(arr) - 1; i++) {
            res = (int)(arr[i]) - (int)(arr[i + 1]);
            if (res > 0) {
                fl = 1;
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                ret_fl = 1;
            }
        }
    }
    return ret_fl;
}

void sortEachString(char arr[][20], int n) {
    for (int i = 0; i < n; i++) {
        sortString(arr[i]);
    }
}

void sortAllAsOne(char arr[][20], int n) {
    int fl_sort = 1;
    int fl = 1;
    while (fl) {
        fl = 0;
        int res = 0;
        for (int i = 0; i < n; i++) {
            fl_sort = string_sort_help(arr[i]);
            if (fl != 1) {
                fl = fl_sort;
            }
            if (i != n - 1) {
                char temp;
                res = (int)(arr[i][(int)strlen(arr[i]) - 1]) - (int)(arr[i + 1][0]);
                if (res > 0) {
                    fl = 1;
                    temp = arr[i + 1][0];
                    arr[i + 1][0] = arr[i][(int)strlen(arr[i]) - 1];
                    arr[i][(int)strlen(arr[i]) - 1] = temp;
                }
            }

        }
    }

}

int getMenueVal() {
    printMenu();
    int num_choice = getSize(0, 99);
    if (num_choice <= 8) {
        return num_choice;
    }
    else {
        return -1;
    }
}


int main() {
    int fl = 1;
    int can_sort = 0;
    int counter = 0;
    int n = 0;
    char main_arr[10][20] = { '\0' };
    while (fl) {
        int val = getMenueVal();
        if (val == -1) {
            counter++;
            if (counter == 5) {
                fl = 0;
                printf("5 errors, bye bye.");
            }
            else printf("You made %d errors from 5, try again,\n", counter);

        }
        else {
            switch (val)
            {
            case 0:
                fl = 0;
                printf("You chose to end the program, bye!!!");
                break;
            case 1:
                printf("Enter new word count,\n");
                n = getSize(2, 10);
                insertStrings(main_arr, n);
                can_sort = 1;
                break;
            case 2:
                if (can_sort) printWords(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            case 3:
                if (can_sort) sortStringsLexicographic(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            case 4:
                if (can_sort) sortStringsByLength(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            case 5:
                if (can_sort) sortStringsByAsciiSum(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            case 6:
                if (can_sort) sortStringsByAsciiAvg(main_arr, n);
                else printf("There are no words, cannot operate.\n");

                break;
            case 7:
                if (can_sort) sortEachString(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            case 8:
                if (can_sort)  sortAllAsOne(main_arr, n);
                else printf("There are no words, cannot operate.\n");
                break;
            default:
                break;
            }

        }


    }

    return 0;
}
