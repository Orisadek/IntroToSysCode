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
int managFirstOption();
int getValues(FILE*, char*, int*, int*, char*);
int unifyDatabase(FILE*, FILE*);
serie** getUnifyDatabaseDetails(int);
void sortById(serie**, int);
void printSeriesList(serie**, int);
int is_serie_exc(serie**, int, int);
serie* get_serie_by_id(serie**, int, int);
void getWatchingDetails(serie**, int);
int count_line(FILE*);
void printWatchingDetails(int);
void sortByRank(serie**, int);
int get_max_rank(serie**, int);
int is_var_exc(int*, int, int);
int arr_len(int*, int);
int* rank_arr(serie**, int, int);
void print_ser_ptr(serie*);
int* max_rank_arr(serie**, int, int);
void printSeriesByRank(serie**, int);
void makeSeriesFileSortedByRank(serie**, int);
void free_malloc(serie**, int);





int showMenu() {
    int input;

    printf("%s", "**********Main Menu **************\n");
    printf("%s", "1. Unify Database\n");
    printf("%s", "2. Get Unify Database Details\n");
    printf("%s", "3. Print The Series List Sorted By Code\n");
    printf("%s", "4. Get Watching Details\n");
    printf("%s", "5. Show all Watching Details\n");
    printf("%s", "6. Print Series Sorted By Rank\n");
    printf("%s", "7. Make Series File Sorted By Rank\n");
    printf("%s", "8. Exit\n");
    printf("%s", "Enter Your Selection:");
    fflush(stdin);
    scanf("%d", &input);
}

int getValues(FILE* file, char* name_series, int* id, int* season_num, char* is_active) {
    int EOH = fscanf(file, "%20[^,] %*c %3d %*c %2d %*c %c %*[\n]", name_series, id, season_num, is_active);
    return EOH;
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

    return series_num;
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
            for (int j = 0; j < (ptr_serie + i)->numSeasons; ++j) {
                (ptr_serie + i)->watchingDetails[j] = 0;
            }
            (ptr_serie + i)->rank = 0;
            strcpy((ptr_serie + i)->serieName, serieName1);
            *(ptr + i) = ptr_serie + i;
            i++;
        }
    }
    fclose(file);
    return  ptr;
}

void sortById(serie** ptr, int size) {
    int fl = 1;
    serie* ser_temp;
    while (fl) {
        fl = 0;
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (ptr[i]->id > ptr[j]->id) {
                    ser_temp = ptr[i];
                    ptr[i] = ptr[j];
                    ptr[j] = ser_temp;
                    fl = 1;
                }
            }
        }
    }
}

void printSeriesList(serie** ptr, int size) {
    sortById(ptr, size);
    printf("Series List\n");
    for (int i = 0; i < size; i++) {
        printf("%03d-%s(%d)\n", ptr[i]->id, ptr[i]->serieName, ptr[i]->numSeasons);
    }
}

int is_serie_exc(serie** ptr, int size, int id_ser) {
    for (int i = 0; i < size; i++) {
        if (ptr[i]->id == id_ser) {
            return 1;
        }
    }
    return 0;
}

serie* get_serie_by_id(serie** ptr, int size, int id) {
    serie* return_ptr = NULL;
    for (int i = 0; i < size; i++) {
        if (ptr[i]->id == id) {
            return_ptr = ptr[i];
        }
    }
    return return_ptr;
}

void getWatchingDetails(serie** ptr, int size) {
    FILE* f = fopen("watching.txt", "a");
    int ans, id_input, ses_input;
    int fl = 1;
    puts("Insert Serie Code:");
    do {
        fflush(stdin);
        ans = scanf("%d", &id_input);
        if (ans > 0) {
            if (is_serie_exc(ptr, size, id_input) == 1) {
                fl = 0;
            }
            else {
                puts("wrong serie code, try again!!");
            }
        }
        else {
            puts("wrong serie code, try again!!");
        }
    } while (fl);
    serie* ptr_by_id = get_serie_by_id(ptr, size, id_input);
    printf("Insert Season Number (1 - %d):\n", ptr_by_id->numSeasons);
    fl = 1;
    do {
        fflush(stdin);
        ans = scanf("%d", &ses_input);
        if (ans > 0) {
            if (ses_input >= 1 && ses_input <= ptr_by_id->numSeasons) {
                fl = 0;
            }
            else {
                puts("wrong season number, try again!!!");
            }
        }
        else {
            puts("wrong season number, try again!!!");
        }
    } while (fl);
    fprintf(f, "%d,%d\n", ptr_by_id->id, ptr_by_id->numSeasons);
    ptr_by_id->watchingDetails[ses_input - 1] = ptr_by_id->watchingDetails[ses_input - 1] + 1;
    ptr_by_id->rank = ptr_by_id->rank + 1;
    printf("series: %d, season: %d accepted!!\n", ptr_by_id->id, ptr_by_id->numSeasons);
    fclose(f);

}

void printWatchingDetails(int lines_num) {
    int lines;
    FILE* watch_file;
    watch_file = fopen("watching.txt", "r");
    lines = lines_num;
    int* ser_code = (int*)malloc(lines * sizeof(ser_code));
    int* ser_season = (int*)malloc(lines * sizeof(ser_season));
    printf("Watching Details\n");
    for (int i = 0; i < lines; i++) {
        fscanf(watch_file, "%d,%d", &ser_code[i], &ser_season[i]);
        printf("Series Code:%03d, Season Number:%d\n", ser_code[i], ser_season[i]);
    }
    free(ser_code);
    free(ser_season);
    fclose(watch_file);
}

void sortByRank(serie** ptr, int size) {
    int fl = 1;
    serie* ser_temp;
    while (fl) {
        fl = 0;
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (ptr[i]->rank < ptr[j]->rank) {
                    ser_temp = ptr[i];
                    ptr[i] = ptr[j];
                    ptr[j] = ser_temp;
                    fl = 1;
                }
            }
        }
    }
}

int get_max_rank(serie** ptr, int series_num) {
    int max_rank = 1;
    for (int i = 0; i < series_num; ++i) {
        if (max_rank < ptr[i]->rank) {
            max_rank = ptr[i]->rank;
        }
    }
    return max_rank;
}

int is_var_exc(int* ptr, int max_rank, int val) {
    int fl = 0;
    for (int i = 0; i < max_rank; i++) {
        if (ptr[0] == val) {
            fl = 1;
        }
    }
    return fl;
}

int arr_len(int* arr_val, int max_size) {
    int count = 0;
    for (int i = 0; i < max_size; i++) {
        if (arr_val[i] != 0) {
            count += 1;
        }
    }
    return count;
}

int* rank_arr(serie** ptr, int series_num, int max_rank) {
    int cor_rank = max_rank;
    int loc_index = 0;
    int* rank_arr = (int*)malloc(series_num * sizeof(int));
    for (int i = 0; i < series_num; i++) {
        rank_arr[i] = -1;
    }
    for (int i = 0; i < series_num; i++) {
        if (is_var_exc(rank_arr, max_rank, ptr[i]->rank) == 0) {
            rank_arr[loc_index] = ptr[i]->rank;
            loc_index = loc_index + 1;
        }
    }
    int fl = 1;
    int ser_temp;
    while (fl) {
        fl = 0;
        for (int i = 0; i < loc_index; i++) {
            for (int j = i; j < loc_index; j++) {
                if (rank_arr[i] < rank_arr[j]) {
                    ser_temp = rank_arr[i];
                    rank_arr[i] = rank_arr[j];
                    rank_arr[j] = ser_temp;
                    fl = 1;
                }
            }
        }
    }
    return rank_arr;
}

void print_ser_ptr(serie* ptr) {
    printf("%03d -%s\n", ptr->id, ptr->serieName);
    for (int i = 0; i < ptr->numSeasons; ++i) {
        printf("Season %d:%d\n", i + 1, ptr->watchingDetails[i]);
    }
}

int* max_rank_arr(serie** ptr, int series_num, int max_rank) {
    int* rank_arr = (int*)malloc(max_rank * sizeof(int));
    int loc = max_rank;
    for (int i = 0; i < loc; i++) {
        rank_arr[i] = max_rank;
        max_rank = max_rank - 1;
    }
    return rank_arr;
}

void printSeriesByRank(serie** ptr, int series_num) {
    int max_rank = get_max_rank(ptr, series_num);
    serie** series_rank_arr = (serie**)malloc(series_num * sizeof(serie*));
    serie* ptr_serie;
    int* rank_arr_val = max_rank_arr(ptr, series_num, max_rank);
    int rank_arr_size = arr_len(rank_arr_val, series_num);
    sortById(ptr, series_num);
    for (int i = 0; i < rank_arr_size; i++) {
        if (rank_arr_val[i] > -1 && rank_arr_val[i] <= max_rank) {
            printf("RANK %d\n", rank_arr_val[i]);
        }
        for (int j = 0; j < series_num; j++) {
            if (ptr[j]->rank == rank_arr_val[i]) {
                print_ser_ptr(ptr[j]);
            }
        }
    }
}

void makeSeriesFileSortedByRank(serie** ptr, int series_num) {

    FILE* f = fopen("seriesRank.txt", "w+");
    sortByRank(ptr, series_num);
    for (int i = 0; i < series_num; i++) {
        fprintf(f, "%03d(Rank:%d)-%s\n", ptr[i]->id, ptr[i]->rank, ptr[i]->serieName);
    }
    fclose(f);

}

void free_malloc(serie** ptr, int series_num) {
    serie* z;
    for (int i = 0; i < series_num; i++) {
        z = *(ptr + i);
        free(z->watchingDetails);
    }
    free(*ptr);
    free(ptr);
}

int managFirstOption() {
    int fl = 0;
    int series_num = 0;
    int fl1 = 0;
    char t1[20];
    char t2[20];
    FILE* f1;
    FILE* f2;
    FILE* watch_file;
    printf("Enter First File Name: \n");
    fflush(stdin);
    scanf("%s", t1);
    f1 = fopen(t1, "r");
    while (f1 == NULL) {
        printf("error in opening file %s !!!\n", t1);
        printf("Enter First File Name: \n");
        fflush(stdin);
        scanf("%s", t1);
        f1 = fopen(t1, "r");
    }

    printf("Enter Second File Name: \n");
    fflush(stdin);
    scanf("%s", t2);
    f2 = fopen(t2, "r");

    while (f2 == NULL) {
        printf("error in opening file %s !!!\n", t2);
        printf("Enter Second File Name: \n");
        fflush(stdin);
        scanf("%s", t2);
        f2 = fopen(t2, "r");
    }


    watch_file = fopen("watching.txt", "w");
    fclose(watch_file);
    series_num = unifyDatabase(f1, f2);
    fclose(f1);
    fclose(f2);
    printf("%s", "Unify Succeeded \n");
    return series_num;
}

int main() {
    serie** ptr = 0;
    int series_num;
    int input, fl, fl1, fl2;
    fl1 = 0;
    fl2 = 0;

    int lines_num = 0;
    int fl_8 = 1;
    while (fl_8) {
        input = showMenu();

        switch (input) {
        case  1:
            series_num = managFirstOption();
            fl1 = 1;
            break;
        case 2:
            if (fl1) {
                ptr = getUnifyDatabaseDetails(series_num);
                fl2 = 1;
                printf("Get Unify Database Details Succeeded\n");

            }
            else  printf("You must unify database before using this option!!!\n");
            break;
        case 3:
            if (fl1 && fl2)printSeriesList(ptr, series_num);
            else printf("You must Get Unify Database Details before using this option!!!\n");
            break;
        case 4:
            if (fl1 && fl2) {
                getWatchingDetails(ptr, series_num);
                lines_num++;
            }
            else printf("You must Get Unify Database Details before using this option!!!\n");
            break;
        case 5:
            if (fl1 && fl2)  printWatchingDetails(lines_num);
            else printf("You must Get Unify Database Details before using this option!!!\n");
            break;
        case 6:
            if (fl1 && fl2)  printSeriesByRank(ptr, series_num);
            else printf("You must Get Unify Database Details before using this option!!!\n");
            break;
        case 7:
            if (fl1 && fl2)  makeSeriesFileSortedByRank(ptr, series_num);
            else printf("You must Get Unify Database Details before using this option!!!\n");
            break;
        case 8:
            fl_8 = 0;
            break;
        default:
            printf("Wrong Option, Try Again !!!\n");
        }
    }
    if (fl2)free_malloc(ptr, series_num);

    printf("End Of The Program...\n");
    return 0;
}
