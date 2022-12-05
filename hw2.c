#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct serie {
    char serieName[20];
    int numSeasons;
    int rank;
    int* watchingDetails;
    int id;
}serie;

int showMenu();
int unifyDatabase(FILE*, FILE*);
serie** getUnifyDatabaseDetails();
void printSeriesList(serie**);
void getWatchingDetails(serie**, int*);
void printWatchingDetails();
void printSeriesByCode(serie**);
void printSeriesByRank(serie**, int);
void makeSeriesFileSortedByRank(serie**, int);
int getValues(FILE*, char*, int*, int*, char*);

int showMenu() {
    printf("%s", "***Main menu *****");
    printf("%s", "1. Unify Database");
    printf("%s", "2. Get Unify Database Details");
    printf("%s", "3. Print The Series List Sorted By Code");
    printf("%s", "4. Get Watching Details");
    printf("%s", "5. Show all Watching Details");
    printf("%s", "6. Print Series Sorted By Rank");
    printf("%s", "7. Make Series File Sorted By Rank");
    printf("%s", "8. Exit");
}

//void ret_line(FILE* f1, char* f1data) {
//    fgets(f1data, 50, f1);
//}

//void get_line_by_index(FILE* f1, char* f1data[4][20]) {
//    char data1[30];
//    ret_line(f1, data1);
//    int j = 0;
//    int count_loc = 0;
//    for (int i = 0; i < 20; i++) {
//        if (data1[count_loc] == 10) {
//            break;
//        }
//        if (data1[count_loc] != 44) {
//            f1data[j][i] = 0;
//            f1data[j][i] = data1[count_loc];
//            f1data[j][i] = (int)f1data[j][i];
//        }
//        else {
//            f1data[j][i] = '\0';
//            j++;
//            i = -1;
//        }
//        count_loc++;
//    }
//    count_loc = count_loc;
//}

int getValues(FILE* file, char* name_series, int* id, int* season_num, char* is_active) {
    int EOH = fscanf(file, "%20[^,] %*c %3d %*c %2d %*c %c %*[\n]", name_series, id, season_num, is_active);
    return EOH;
}

serie** getUnifyDatabaseDetails(int series_num) {
    FILE* file;
    file = fopen("series.txt", "r");
    serie** ptr;
    ptr = (serie**)malloc(series_num * sizeof(serie*));
    char serieName1[20];
    int numSeasons;
    int id;
    int i = 0;
    int* watchingDetails;
    int EOH = 0;
    serie* ptr_serie;
    ptr_serie = (serie*)malloc(series_num * sizeof(serie));
    while (EOH != -1) {
        EOH = fscanf(file, "%20[^,] %*c %3d %*c %2d %*[\n]", serieName1, &id, &numSeasons);
        if (EOH != -1) {
            (ptr_serie + i)->numSeasons = numSeasons;
            (ptr_serie + i)->id = id;
            watchingDetails = (int*)malloc(numSeasons * sizeof(int));
            (ptr_serie + i)->watchingDetails = watchingDetails;
            strcpy((ptr_serie + i)->serieName, serieName1);
            *(ptr + i) = ptr_serie + i;
            i++;
        }
    }
    fclose(file);
    return  ptr;
}

int unifyDatabase(FILE* file1, FILE* file2) {
    char name_series1[20], name_series2[20];
    int series_num = 0;
    int id1, id2;
    int season_num1, season_num2;
    char is_active1, is_active2;
    FILE* f_out;
    f_out = fopen("series.txt", "w");
    int EOH1;
    int EOH2;
    EOH1 = getValues(file1, name_series1, &id1, &season_num1, &is_active1);
    EOH2 = getValues(file2, name_series2, &id2, &season_num2, &is_active2);
    while (EOH1 != -1 || EOH2 != -1) {
        if (id1 > id2) {
            if (is_active2 == 'Y') {
                fprintf(f_out, "%s,%d,%d\n", name_series2, id2, season_num2);
                series_num++;
            }
            EOH2 = getValues(file2, name_series2, &id2, &season_num2, &is_active2);
            if (EOH2 == -1) id2 = 10000;

        }
        else if (id2 > id1) {
            if (is_active1 == 'Y') {
                fprintf(f_out, "%s,%d,%d\n", name_series1, id1, season_num1);
                series_num++;
            }
            EOH1 = getValues(file1, name_series1, &id1, &season_num1, &is_active1);
            if (EOH1 == -1) id1 = 10000;
        }
        else {
            if (is_active1 == 'Y' && is_active2 == 'Y') {
                int season_num;
                if (season_num1 > season_num2) season_num = season_num1;
                else season_num = season_num2;
                fprintf(f_out, "%s,%d,%d\n", name_series1, id1, season_num);
                series_num++;
            }
            else if (is_active1 == 'Y' || is_active2 == 'Y') {
                int season_num_f;
                if (is_active1 == 'Y') season_num_f = season_num1;
                else season_num_f = season_num2;
                fprintf(f_out, "%s,%d,%d\n", name_series1, id1, season_num_f);
                series_num++;
            }
            EOH1 = getValues(file1, name_series1, &id1, &season_num1, &is_active1);
            EOH2 = getValues(file2, name_series2, &id2, &season_num2, &is_active2);
            if (EOH2 == -1)id2 = 10000;
            if (EOH1 == -1)id1 = 10000;
        }
    }
    fclose(f_out);
    fclose(file1);
    fclose(file2);
    return series_num;
}

int main() {
    //printf("Hello, World!\n");
    FILE* f1;
    FILE* f2;
    serie** ptr;
    f1 = fopen("n.txt", "r");
    f2 = fopen("s.txt", "r");
    int series_num = unifyDatabase(f1, f2);
    ptr = getUnifyDatabaseDetails(series_num);
    return 0;
}