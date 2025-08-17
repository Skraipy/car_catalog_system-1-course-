#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxlen 128
/* Structure ------------------------------------------------------------------- */
struct Record;  /* Define structure of Record */
struct Record_head; /* Define structure of Record List Head*/
struct model;  /* Define structure of model */
struct model_head; /* Define structure of model List Head */
typedef struct Record MOV; /* Define Structured Type of Record */
typedef struct Record_head MHD; /* Define Structured Type of Record List Head*/
typedef struct model DIR; /* Define Structured Type of model */
typedef struct model_head DHD; /* Define Structured Type of model List Head*/
/* Node and List --------------------------------------------------------------- */
MHD *make_Record_head(); /* Record Head Initialization */
DHD *make_model_head(); /* model Head Initialization */
DIR *find_model(DHD *dph, int id); /* Get pointer to Node in model List by ID */
MOV *create_Record(int id_mov, char *Record_brand, int id, int Record_year, int Record_price, float Record_enginePower, float Record_mileage, int watch_seats[3], DHD *dph); /* Record Node Initialization */
DIR *create_model(int id, char *Record_model); /* model  Node Initialization */
void add_Record(MHD *ph, MOV *new_node, MOV *current_node); /* Add new Record Node to List */
void add_model(DHD *dph, DIR *new_node, DIR *current_node); /* Add new model Node to List */
void delete_Record(MHD *mph, MOV *current_Record); /* Delete selected Record Node */
void delete_model(DHD *dph, MHD *mph, DIR *current_model); /* Delete selected model Node */
void save_database_changes(char *Record_filename, char *model_filename, MHD *mph, DHD *dph, char sep);
/* Interface --------------------------------------------------------------------*/
void menu(); /* Output main menu */
void print_head(int n); /* Output title of sheet (0 - for Record LIST, 1 - for model LIST) */
void output_Record(MHD *mph, int n, int reverse); /* Output list with MOV structure (n for PRINT HEAD) */
void output_model(DHD *dph, int n, int reverse); /* Output list with DIR structure (n for PRINT HEAD) */
void clear_screen(); /* Clear the console */
void search_menu(MHD *mph, DHD *dph);
/* Sort, Form and other Stuff */
void split_string(char *inputString, char **words, int *wordCount, char delimiter); /* Split string by separator */
void add_Record_to_list(char *filebrand, MHD *mph, char sep, DHD *dph); /* Adding the Record data of file to list */
void add_model_to_list(char *filebrand, DHD *dph, char sep); /* Adding the model data of file to list */
void add_Record_to_file(char *filebrand, MHD *mph, char sep, DHD *dph);/*write to file*/
int add_Model_to_file(char *filemodel, DHD *dph);/*add a new model to the list or select an existing one*/
void delete_Record_by_ID(MHD *mph, int id);/*removal from database by ID*/
void search_by_model(MHD *mph, DHD *dph);/** Search records by model name */
void search_by_brand(MHD *mph, DHD *dph);/** Search records by brand name */
void Sort_menu(MHD *mph, DHD *dph);/** Display sorting menu and perform sorting based on user selection */
void sort_by_year(MHD *mph);/** Sort records by year */
void sort_by_brand(MHD *mph);/** Sort records by brand name */
void sort_by_model(MHD *mph);/** Sort records by model name */
void edit_menu(MHD *mph, DHD *dph);
void edit_Record(MHD *mph, DHD *dph);
void edit_model(DHD *dph);
void print_unique_brands(MHD *mph);
void add_new_model_to_list(DHD *dph);
void delete_model_by_ID(DHD *dph, MHD *mph, int id);

/* Main Program */
/**/
int main() {/*block complete*/
    char save_choice;
    char sep=';';
    int option;
    int id_to_delete,model_id_to_delete;
    DHD *dph;
    MHD *mph;
    dph=make_model_head();
    mph=make_Record_head();
    add_model_to_list("struct-data2-win.txt",dph,sep);
    add_Record_to_list("struct-data-win.txt",mph,sep,dph);
    do{
        menu();
        scanf("%i", &option);
        switch(option){
        case 0:{
            puts("\nYour selection is EXIT");
            printf("Do you want to save the changes to the database before exiting? (Y/N): ");
            scanf(" %c", &save_choice);
            if (toupper(save_choice) == 'Y') {
                save_database_changes("struct-data-win.txt", "struct-data2-win.txt", mph, dph, sep);
                printf("Changes saved successfully.\n");
            } else {
            printf("Changes were not saved.\n");
            }
            exit(0);
        }
        case 1:{
            puts("\nYour selection is SHOW THE Record DATA\n");
            getchar();
            output_Record(mph,0,0);
            break;
        }
        case 2:{
            puts("\nYour selection is SHOW THE model DATA\n");
            getchar();
            output_model(dph,1,0);
            break;
        }
        case 3: {
            puts("\nYour selection is ADD DATA TO FILE\n");
            getchar();
            add_Record_to_file("struct-data-win.txt", mph, sep, dph);
            break;
        }
        case 4:{
            puts("\nYour selection is DELETE RECORD BY ID\n");
            output_Record(mph,0,0);
            printf("Enter the ID of the record you want to delete:");
            scanf("%d", &id_to_delete);
            delete_Record_by_ID(mph, id_to_delete);
            printf("\nUpdated database:\n");
            output_Record(mph,0,0);
            getchar();
            break;
        }
        case 5: {
            puts("\nYour selection is SEARCH MENU\n");
            search_menu(mph, dph);
            getchar();
            break;
        }
        case 6: {
            puts("\nYour selection is SORT MENU\n");
            Sort_menu(mph, dph);
            break;
        }
        case 7: {
            puts("\nYour selection is EDIT DATA\n");
            getchar();
            edit_menu(mph, dph);
            break;
        }
        case 8:{
            puts("\nYour selection is SHOW THE DIRECTORY\n");
            getchar();
            puts("This program is a file cabinet. Performs the functions presented in the menu.\nAuto have been selected as the subject area.\nDesignations: brand- the name of the auto,\nmodel - the model of the car, year - the year of the care,\nprice - the price of the car, enginePower - enginePower of the car,\nmileage - mileage of the car,\nseats - the seats of the car.");
            break;
        }
        case 9: {
            puts("\nYour selection is ADD NEW MODEL TO LIST\n");
            getchar();
            add_new_model_to_list(dph);
            break;
        }
        case 10: {
            puts("\nYour selection is REMOVE MODEL FROM LIST\n");
            output_model(dph, 1, 0);
            printf("Enter the ID of the model you want to delete: ");
            scanf("%d", &model_id_to_delete);
            delete_model_by_ID(dph, mph, model_id_to_delete);
            break;
        }
        default:{
            puts("\nIncorrect key");
            getchar();

        }
    }
    puts("\nPress ENTER to continue");
    getchar();
    clear_screen();
    } while (option!=0);
    return 0;
}
/* Functions and their description ---------------------------------------------- */
struct Record{
    int id;
    char *brand;
    DIR *model;
    int year;
    int price;
    float enginePower;
    float mileage;
    int seats[3];
    struct Record *prev;
    struct Record *next;
};
struct Record_head{
    struct Record *first;
    struct Record *last;
};
struct model{
    int id; /* ID of the model */
    char *brand; /* model brand */
    struct model *next; /* Link to previous node */
    struct model *prev; /* Link to next node */
};
struct model_head{
    struct model *first;
    struct model *last;
};
typedef struct {
    int id;
    char brand[100];
} UniqueBrand;
MHD *make_Record_head(){/*block complete*/
    MHD *ph=NULL; /* Define and init Head */
    ph=(MHD*)malloc(sizeof(MHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}
DHD *make_model_head(){/*block complete*/
    DHD *ph=NULL; /* Define and init Head */
    ph=(DHD*)malloc(sizeof(DHD));
    ph->first=NULL;
    ph->last=NULL;
    return ph;
}
DIR *find_model(DHD *dph, int id){/*block complete*/
    DIR *current = NULL;
    int flag=0;
    current = dph->first;

    while(current!=NULL && flag==0){
        if(current->id==id){
            flag=1;
        } else current=current->next;
    }
    return current;
}
MOV *create_Record(int id_mov, char *Record_brand, int id, int Record_year, int Record_price, float Record_enginePower, float Record_mileage, int watch_seats[3], DHD *dph){/*block complete*/
    MOV *new_Record = NULL; /* Pointer to new node */
    DIR *Record_model = NULL; /* Pointer to model of Record */
    char *brand = NULL;
    new_Record = (MOV*)malloc(sizeof(MOV));
    brand = (char*)malloc((strlen(Record_brand) + 1) * sizeof(char));
    Record_model = (DIR *)malloc(sizeof(DIR));
    Record_model=find_model(dph, id);
    if (new_Record && brand) { /* Data is not empty */
        new_Record->id = id_mov;
        new_Record->brand = brand;
        new_Record->model = Record_model;
        new_Record->year = Record_year;
        new_Record->price = Record_price;
        new_Record->enginePower = Record_enginePower;
        new_Record->mileage = Record_mileage;
        memcpy(brand, Record_brand, strlen(Record_brand) + 1);
        memcpy(new_Record->seats, watch_seats, sizeof(new_Record->seats));
        new_Record->next = NULL;
        new_Record->prev = NULL;
    }

    return new_Record; /* Return adress of node */
}
DIR *create_model(int id, char *Record_model){/*block complete*/
    DIR *new_model = NULL; /* Pointer to new node */
    char *model = NULL;
    new_model = (DIR*)malloc(sizeof(DIR));
    model = (char*)malloc((strlen(Record_model) + 1) * sizeof(char));
    if (new_model && model){ /* Data is not empty */
        new_model->id = id;
        new_model->brand = model;
        memcpy(model, Record_model, strlen(Record_model) + 1);
        new_model->prev = NULL;
        new_model->next = NULL;
        model[strlen(Record_model)] = '\0';
    }
    return new_model; /* return adress of node */
}
void add_Record(MHD *ph, MOV *new_node, MOV *current_node){/*block complete*/
    if (ph && new_node) {
        if (current_node == NULL) { /* Add first node of list */
            ph->first = new_node;
            ph->last = new_node;
            new_node->prev = NULL;
            new_node->next = NULL;
        } else {
            current_node->next = new_node;
            new_node->prev = current_node;
            new_node->next = NULL;
            ph->last = new_node;
        }
    }
}
void add_model(DHD *dph, DIR *new_node, DIR *current_node){/*block complete*/
    if (dph && new_node) {
        if (current_node == NULL) { /* Add first node of list */
            dph->first = new_node;
            dph->last = new_node;
            new_node->prev = NULL;
            new_node->next = NULL;
        } else {
            current_node->next = new_node;
            new_node->prev = current_node;
            new_node->next = NULL;
            dph->last = new_node;
        }
    }
}
void delete_Record(MHD *mph, MOV *current_Record) {/*block complete*/
    if (current_Record == mph->first) { /* If deleted node is the first in the list */
        mph->first = current_Record->next;
        if (mph->first) {
            mph->first->prev = NULL;
        } else { /* If deleted node is alone in the list */
            mph->last = NULL;
        }
    } else if (current_Record == mph->last) { /* If deleted node is the last in the list */
        mph->last = current_Record->prev;
        if (mph->last) {
            mph->last->next = NULL;
        } else { /* If deleted node is alone in the list */
            mph->first = NULL;
        }
    } else { /* If deleted node not first or last of the list */
        current_Record->prev->next = current_Record->next;
        current_Record->next->prev = current_Record->prev;
    }
    current_Record->next = NULL;
    current_Record->prev = NULL;
    free(current_Record);
}
void delete_model(DHD *dph, MHD *mph, DIR *current_model) {/*block complete*/
    MOV *current_Record = mph->first;
    MOV *next_Record = NULL;
    while (current_Record != NULL) {
        next_Record = current_Record->next;
        if (current_Record->model == current_model) {
            delete_Record(mph, current_Record);
        }
        current_Record = next_Record;
    }
    if (current_model == dph->first) {
        dph->first = current_model->next;
        if (dph->first) {
            dph->first->prev = NULL;
        } else {
            dph->last = NULL;
        }
    } else if (current_model== dph->last) {
        dph->last = current_model->prev;
        if (dph->last) {
            dph->last->next = NULL;
        } else {
            dph->first = NULL;
        }
    } else {
        current_model->prev->next = current_model->next;
        current_model->next->prev = current_model->prev;
    }
    current_model->next = NULL;
    current_model->prev = NULL;
    free(current_model);
}
void menu(){
    puts("Choose the option");
    puts("0 - for EXIT program");
    puts("1 - for show the Record data");
    puts("2 - for show the model data");
    puts("3 - add data to database");
    puts("4 - delete data from the database");
    puts("5 - search menu");
    puts("6 - sort menu");
    puts("7 - edit data menu");
    puts("8 - SHOW directory");
    puts("9 - add new model to list");
    puts("10 - remove model from list");
    printf("Enter the option: ");
}
void print_head(int n){
    if(n==0){
        printf("| %2s | %25s | %25s | %4s | %7s | %4s | %5s | %7s |\n","ID","brand","model","Year","Price","enginePower","mileage","Seats");
        printf("+----+---------------------------+---------------------------+------+---------+-------------+---------+---------+\n");
    } else {
        printf("| %2s | %25s |\n","ID","model");
        printf("+----+---------------------------+\n");
    }
}
void output_Record(MHD *mph, int n, int reverse) {/*block complete*/
    MOV *current;
    if (reverse)
        current = mph->last;
    else
        current = mph->first;
    print_head(n);
    while (current != NULL) {
        if (current->model != NULL) {
            printf("| %2d | %25s | %25s | %4d | %7d | %11.1f | %7.1f | %2d %2d %d |\n", current->id, current->brand, current->model->brand, current->year, current->price, current->enginePower, current->mileage, current->seats[0], current->seats[1], current->seats[2]);
        }
        if (reverse)
            current = current->prev;
        else
            current = current->next;
    }
}
void output_model(DHD *dph, int n, int reverse) {/*block complete*/
    DIR *current;
    if (reverse)
        current = dph->last;
    else
        current = dph->first;
    print_head(n);
    while (current != NULL) {
        printf("| %2d | %25s |\n", current->id, current->brand);
        if (reverse)
            current = current->prev;
        else
            current = current->next;
    }
}
void clear_screen(){
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}
void split_string(char *inputString, char **words, int *wordCount, char delimiter) {/*block complete*/
    int wordIndex = 0, wordStart=0, wordLength=0, inWord=0, i;
    for (i = 0; i <= strlen(inputString); i++) {
        if ((inputString[i] == delimiter || inputString[i] == '\0')&&(inWord==1)) {
            words[wordIndex] = (char *)malloc(wordLength + 1);
            strncpy(words[wordIndex], inputString + wordStart, wordLength);
            words[wordIndex][wordLength] = '\0';
            wordIndex++;
            inWord = 0;
        } else {
            if (inWord==0) {
                wordStart = i;
                wordLength = 1;
                inWord = 1;
            } else {
                wordLength++;
            }
        }
    }
    *wordCount = wordIndex;
    for (i = 0; i < *wordCount; i++) {
        int len = strlen(words[i]);
        if (words[i][len - 1] == '\r') {
            words[i][len - 1] = '\0';
        }
    }
}
void add_Record_to_list(char *filebrand, MHD *mph, char sep, DHD *dph){/*block complete*/
    char line[maxlen], *words[10];
    int wordCount, seats[3], i;
    MOV *new_Record;
    FILE *file = fopen(filebrand, "r");
    if (file == NULL) printf("Error opening file.\n");
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);
        if (wordCount == 10){
            int id_mov = atoi(words[0]);
            char *brand = words[1];
            int id = atoi(words[2]);
            int year = atoi(words[3]);
            int price = atoi(words[4]);
            float enginePower = atof(words[5]);
            float mileage = atof(words[6]);
            seats[0] = atoi(words[7]);
            seats[1] = atoi(words[8]);
            seats[2] = atoi(words[9]);
            new_Record = create_Record(id_mov, brand, id, year, price, enginePower, mileage, seats, dph);
            add_Record(mph, new_Record, mph->last);
        }
        else printf("Invalid number of attributes in line: %s\n", line);
        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}
void add_model_to_list(char *filebrand, DHD *dph, char sep){/*block complete*/
    char line[maxlen], *words[2];
    int wordCount, i;
    DIR *new_model;
    FILE *file = fopen(filebrand, "r");
    if (file == NULL) printf("Error opening file.\n");
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        split_string(line, words, &wordCount, sep);
        if (wordCount == 2){
            int id = atoi(words[0]);
            char *brand = words[1];
            new_model = create_model(id, brand);
            add_model(dph, new_model, dph->last);
        }
        else printf("Invalid number of attributes in line: %s\n", line);

        for (i = 0; i < wordCount; i++){
            free(words[i]);
        }
    }
    fclose(file);
}
void add_Record_to_file(char *filebrand, MHD *mph, char sep, DHD *dph){/*block complete*/
    int id_mov=1, id, year, price, seats[3];
    float enginePower, mileage;
    char brand[100];
    FILE *file = fopen(filebrand, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
    }
    if (mph->last != NULL) {
        id_mov = mph->last->id + 1;
    }
    printf("Enter brand: ");
    scanf("%s", brand);
    /*add a new model to the list or select an existing one*/
    printf("Model ID which are in the database:\n");
    output_model(dph,1,0);
    printf("Enter 10 to add a new model or select existing model ID: ");
    scanf("%d", &id);
    if(id==10){
        id = add_Model_to_file("struct-data2-win.txt", dph);
    }
    /*------------------------------------------------------------------*/
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter price: ");
    scanf("%d", &price);
    printf("Enter engine power: ");
    scanf("%f", &enginePower);
    printf("Enter mileage: ");
    scanf("%f", &mileage);
    printf("Enter seats (3 integers separated by spaces): ");
    scanf("%d %d %d", &seats[0], &seats[1], &seats[2]);
    /*write to file*/
    fprintf(file, "%d;%s;%d;%d;%d;%.3f;%.3f;%d;%d;%d\n", id_mov,  brand,  id,  year,  price,  enginePower,  mileage, seats[0], seats[1], seats[2]);
    fclose(file);
    printf("Data added successfully.\n");
}
int add_Model_to_file(char *filemodel, DHD *dph) {/*block complete*/
    int id;
    char model[100];
    FILE *file = fopen(filemodel, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
    }
    printf("Enter model name: ");
    scanf("%s", model);
    if (dph->last != NULL) {
        id = dph->last->id + 1;
    } else {
        id = 1;
    }
    fprintf(file, "%d;%s\n", id, model);
    fclose(file);
    printf("Model added successfully.\n");
    return id;
}
void delete_model_by_ID(DHD *dph, MHD *mph, int id) {/*block complete*/
    DIR *current_model = dph->first;
    while (current_model != NULL) {
        if (current_model->id == id) {
            delete_model(dph, mph, current_model);
            printf("Model with ID '%d' deleted successfully.\n", id);
        }
        current_model = current_model->next;
    }
    printf("Model with ID '%d' not found in the list.\n", id);
}
void delete_Record_by_ID(MHD *mph, int id) {/*block complete*/
    MOV *current_Record = mph->first;
    if (mph->first == NULL) {
        printf("Database is empty. No records to delete.\n");
    } else {
        while (current_Record != NULL) {
            if (current_Record->id == id) {
                MOV *next_Record = current_Record->next;
                delete_Record(mph, current_Record);
                current_Record = next_Record;
            } else {
                current_Record = current_Record->next;
            }
        }
    }
}
void search_menu(MHD *mph, DHD *dph) {
    int search_option;
    puts("Select an option to search:");
    puts("1 - Search by model");
    puts("2 - Search by brand");
    printf("Enter option: ");
    scanf("%i", &search_option);
    getchar();
    switch(search_option) {
        case 1:
            puts("\nYour selection is SEARCH DATA BY MODEL\n");
            output_model(dph, 1, 0);
            search_by_model(mph, dph);
            break;
        case 2:
            puts("\nYour selection is SEARCH DATA BY BRAND\n");
            print_unique_brands(mph);
            search_by_brand(mph, dph);
            break;
        default:
            puts("Invalid option");
    }
}
void search_by_model(MHD *mph, DHD *dph) {/*block complete*/
    int found = 0;
    MOV *current_Record = mph->first;
    int model_id;
    printf("Enter the model ID to search: ");
    scanf("%d", &model_id);
    getchar();
    while (current_Record != NULL) {
        if (current_Record->model->id == model_id) {
            if (!found) {
                printf("\nRecords with model ID '%d':\n", model_id);
                print_head(0);
            }
            found = 1;
            printf("| %2d | %25s | %25s | %4d | %7d | %11.1f | %7.1f | %2d %2d %d |\n", current_Record->id, current_Record->brand, current_Record->model->brand, current_Record->year, current_Record->price, current_Record->enginePower, current_Record->mileage, current_Record->seats[0], current_Record->seats[1], current_Record->seats[2]);
        }
        current_Record = current_Record->next;
    }
    if (!found) {
        printf("No records found with model ID '%d'.\n", model_id);
    }
}
void search_by_brand(MHD *mph, DHD *dph) {/*block complete*/
    int brand_id=0;
    DIR *brand = find_model(dph, brand_id);
    MOV *current_Record = mph->first;
    int found = 0;
    char brand_name[100];
    printf("Enter the brand ID to search: ");
    scanf("%d", &brand_id);
    if (brand == NULL) {
        printf("Brand with ID '%d' not found.\n", brand_id);
    }
    strcpy(brand_name, brand->brand);
    while (current_Record != NULL) {
        if (current_Record->model->id == brand_id) {
            if (!found) {
                printf("\nRecords with brand '%s':\n", brand_name);
                print_head(0);
            }
            found = 1;
            printf("| %2d | %25s | %25s | %4d | %7d | %11.1f | %7.1f | %2d %2d %d |\n", current_Record->id, current_Record->brand, current_Record->model->brand, current_Record->year, current_Record->price, current_Record->enginePower, current_Record->mileage, current_Record->seats[0], current_Record->seats[1], current_Record->seats[2]);
        }
        current_Record = current_Record->next;
    }
    if (!found) {
        printf("No records found with brand '%s' (ID: %d).\n", brand_name, brand_id);
    }
}
void Sort_menu(MHD *mph, DHD *dph) {
    int search_option;
    puts("Select an option to search:");
    puts("1 - Sort by model");
    puts("2 - Sort by brand");
    puts("3 - Sort by year");
    printf("enter option: ");
    scanf("%i", &search_option);
    getchar();
    switch(search_option) {
        case 1:
            puts("\nYour selection is SORT DATA BY MODEL\n");
            sort_by_model(mph);
            break;
        case 2:
            puts("\nYour selection is SORT DATA BY BRAND\n");
            sort_by_brand(mph);
            break;
        case 3:
            puts("\nYour selection is SORT DATA BY YEAR\n");
            sort_by_year(mph);
            output_Record(mph,0,0);
            break;
        default:
            puts("Invalid option");
    }
}
void sort_by_year(MHD *mph) {/*block complete*/
    MOV *current, *temp;
        int swapped = 0;
    if (mph != NULL && mph->first != NULL) {
        do {
            swapped = 0;
            current = mph->first;
            while (current->next != NULL) {
                if (current->year > current->next->year) {
                    temp = current->next;
                    current->next = temp->next;
                    temp->next = current;
                    if (current == mph->first) {
                        mph->first = temp;
                    } else {
                        current->prev->next = temp;
                    }
                    temp->prev = current->prev;
                    current->prev = temp;
                    if (current->next != NULL) {
                        current->next->prev = current;
                    }
                    swapped = 1;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }
}
void sort_by_brand(MHD *mph) {/*block complete*/
    MOV *current, *temp;
        int swapped = 0;
    if (mph != NULL && mph->first != NULL) {
        do {
            swapped = 0;
            current = mph->first;
            while (current->next != NULL) {
                if (strcmp(current->brand, current->next->brand) > 0) {
                    temp = current->next;
                    current->next = temp->next;
                    temp->next = current;
                    if (current == mph->first) {
                        mph->first = temp;
                    } else {
                        current->prev->next = temp;
                    }
                    temp->prev = current->prev;
                    current->prev = temp;
                    if (current->next != NULL) {
                        current->next->prev = current;
                    }
                    swapped = 1;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }
}
void sort_by_model(MHD *mph) {/*block complete*/
    MOV *current, *temp;
        int swapped;
    if (mph != NULL && mph->first != NULL) {
        do {
            swapped = 0;
            current = mph->first;
            while (current->next != NULL) {
                if (strcmp(current->model->brand, current->next->model->brand) > 0) {
                    temp = current->next;
                    current->next = temp->next;
                    temp->next = current;
                    if (current == mph->first) {
                        mph->first = temp;
                    } else {
                        current->prev->next = temp;
                    }
                    temp->prev = current->prev;
                    current->prev = temp;
                    if (current->next != NULL) {
                        current->next->prev = current;
                    }
                    swapped = 1;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }
}
void edit_menu(MHD *mph, DHD *dph) {
    int edit_option,model_id_to_delete;
    puts("Select an option to edit:");
    puts("1 - Edit Record");
    puts("2 - Edit model");

    printf("Enter option: ");
    scanf("%i", &edit_option);
    getchar();
    switch (edit_option) {
        case 1:
            edit_Record(mph, dph);
            break;
        case 2:
            edit_model(dph);
            break;
        default:
            puts("Invalid option");
    }
}
void add_new_model_to_list(DHD *dph) {/*block complete*/
    char model[100];
    DIR *new_model;
    int id;
    printf("Enter model name: ");
    scanf("%s", model);
    if (dph->last != NULL) {
        id = dph->last->id + 1;
    } else {
        id = 1;
    }
    new_model = create_model(id, model);
    add_model(dph, new_model, dph->last);
    output_model(dph,1,0);
    printf("the addition was successful");
    getchar();
}
void edit_Record(MHD *mph, DHD *dph) {/*block complete*/
    char new_brand[100];
    int new_model_id, id_to_edit, edit_line_option,record_found = 0;
    MOV *current_Record = mph->first;
    output_Record(mph, 0, 0);
    printf("Enter the ID of the record you want to edit: ");
    scanf("%d", &id_to_edit);
    getchar();
    while (current_Record != NULL) {
        if (current_Record->id == id_to_edit) {
            record_found = 1;
            puts("Select an option to edit line:");
            puts("1 - Edit brand");
            puts("2 - Edit model");
            puts("3 - Edit year");
            puts("4 - Edit price");
            puts("5 - Edit engine power");
            puts("6 - Edit mileage");
            puts("7 - Edit seats");
            puts("8 - Edit all line");
            printf("Enter option: ");
            scanf("%i", &edit_line_option);
            getchar();

            switch (edit_line_option) {
                case 1:
                    printf("Enter new brand: ");
                    fgets(new_brand, 100, stdin);
                    new_brand[strcspn(new_brand, "\n")] = 0;
                    strcpy(current_Record->brand, new_brand);
                    break;
                case 2:
                    output_model(dph, 1, 0);
                    printf("Enter new model ID: ");
                    scanf("%d", &new_model_id);
                    getchar();
                    current_Record->model = find_model(dph, new_model_id);
                    break;
                case 3:
                    printf("Enter new year: ");
                    scanf("%d", &(current_Record->year));
                    getchar();
                    break;
                case 4:
                    printf("Enter new price: ");
                    scanf("%d", &(current_Record->price));
                    getchar();
                    break;
                case 5:
                    printf("Enter new engine power: ");
                    scanf("%f", &(current_Record->enginePower));
                    getchar();
                    break;
                case 6:
                    printf("Enter new mileage: ");
                    scanf("%f", &(current_Record->mileage));
                    getchar();
                    break;
                case 7:
                    printf("Enter new seats (3 integers separated by spaces): ");
                    scanf("%d %d %d", &(current_Record->seats[0]), &(current_Record->seats[1]), &(current_Record->seats[2]));
                    getchar();
                    break;
                case 8:
                    printf("Enter new brand: ");
                    fgets(new_brand, 100, stdin);
                    new_brand[strcspn(new_brand, "\n")] = 0;
                    strcpy(current_Record->brand, new_brand);
                    output_model(dph, 1, 0);
                    printf("Enter new model ID: ");
                    scanf("%d", &new_model_id);
                    getchar();
                    current_Record->model = find_model(dph, new_model_id);
                    printf("Enter new year: ");
                    scanf("%d", &(current_Record->year));
                    getchar();
                    printf("Enter new price: ");
                    scanf("%d", &(current_Record->price));
                    getchar();
                    printf("Enter new engine power: ");
                    scanf("%f", &(current_Record->enginePower));
                    getchar();
                    printf("Enter new mileage: ");
                    scanf("%f", &(current_Record->mileage));
                    getchar();
                    printf("Enter new seats (3 integers separated by spaces): ");
                    scanf("%d %d %d", &(current_Record->seats[0]), &(current_Record->seats[1]), &(current_Record->seats[2]));
                    getchar();
                    break;
                default:
                    puts("Invalid option");
            }
            printf("Record updated successfully.\n");
        }
        current_Record = current_Record->next;
    }
    if (!record_found) {
        printf("Record with ID %d not found.\n", id_to_edit);
    }
}
void edit_model(DHD *dph) {/*block complete*/

    DIR *current_model = dph->first;
    int id_to_edit, model_found = 0;
    output_model(dph,1,0);
    printf("Enter the ID of the model you want to edit: ");
    scanf("%d", &id_to_edit);
    getchar();
    while (current_model != NULL) {
        if (current_model->id == id_to_edit) {
            model_found = 1;
            printf("Enter new model name: ");
            fgets(current_model->brand, 100, stdin);
            current_model->brand[strcspn(current_model->brand, "\n")] = 0;

            printf("Model updated successfully.\n");
        }
        current_model = current_model->next;
    }
    if (!model_found) {
        printf("Model with ID %d not found.\n", id_to_edit);
    }
}
void save_database_changes(char *Record_filename, char *model_filename, MHD *mph, DHD *dph, char sep) {/*block complete*/
    FILE *Record_file = fopen(Record_filename, "w");
    FILE *model_file = fopen(model_filename, "w");
    MOV *current_Record = mph->first;
    DIR *current_model = dph->first;
    if (Record_file == NULL || model_file == NULL) {
        printf("Error opening files for writing.\n");
    }
    while (current_Record != NULL) {
        fprintf(Record_file, "%d;%s;%d;%d;%d;%.3f;%.3f;%d;%d;%d\n",
            current_Record->id,  current_Record->brand,  current_Record->model->id,
            current_Record->year,  current_Record->price,  current_Record->enginePower,
             current_Record->mileage,  current_Record->seats[0],  current_Record->seats[1],
             current_Record->seats[2]);
        current_Record = current_Record->next;
    }
    while (current_model != NULL) {
        fprintf(model_file, "%d%c%s\n", current_model->id, sep, current_model->brand);
        current_model = current_model->next;
    }
    fclose(Record_file);
    fclose(model_file);
    printf("Changes saved successfully.\n");
}
void print_unique_brands(MHD *mph) {/*block complete*/
    MOV *current_Record = mph->first;
    char unique_brands[maxlen][100];
    int unique_ids[maxlen];
    int unique_count = 0, i,found;
    while (current_Record != NULL) {
        found = 0;
        for (i = 0; i < unique_count; ++i) {
            if (strcmp(current_Record->brand, unique_brands[i]) == 0) {
                found = 1;
            }
        }
        if (!found) {
            strcpy(unique_brands[unique_count], current_Record->brand);
            unique_ids[unique_count] = current_Record->model->id;
            ++unique_count;
        }
        current_Record = current_Record->next;
    }
    printf("+----+-----------+\n");
    printf("| ID |   Brand   |\n");
    printf("+----+-----------+\n");
    for (i = 0; i < unique_count; ++i) {
        printf("|%3d |%11s|\n", unique_ids[i], unique_brands[i]);
    }
    printf("+----+-----------+\n");
}
