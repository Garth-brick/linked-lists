#include <stdio.h>
#include <stdlib.h>


typedef struct record {
    int id;
    struct record *next;
} Record;
Record *tableStart = NULL; // address of where the linked list starts


void insert(int new_id, int flag);
void delete(int del_id);
int reverse(int flag);
void display();
void export_to_file();


int main() {
    int choice=0, flag=0; //choice is for the menu, flag is for whether the list is ascending or descending

    printf("\n\tThis is a program that uses a linked list to store as many integer values as entered.\n\
    \tEverything is always sorted and order can be reversed too.\n\
    \tIt also allows the user to get the sum, product or average of all the values and export them to a txt file.\n");

    while(choice!=6) {
        printf("\nEnter an integer:\n1) Insert\n2) Delete\n3) Reverse\n4) Display\n5) Export\n6) Exit\n> ");
        scanf("%d", &choice);
        if (choice==1) {
            int new_id;
            printf("\nEnter new ID: ");
            scanf("%d", &new_id);
            insert(new_id, flag);
        } else if (choice==2) {
            int del_id;
            printf("\nEnter ID to delete: ");
            scanf("%d", &del_id);
            delete(del_id);
        } else if (choice==3) {
            flag = reverse(flag);
        } else if (choice==4) {
            display();
        } else if (choice==5) {
            export_to_file();
        } else if (choice==6) {
            break;
        } else {
            printf("\n\t* invalid input *\n");
        }
    }

    printf("\n\t* exited successfully *\n");
    return 0;
}


void display() {
    if (tableStart==NULL) {
        printf("\n\t* empty list *\n");
        return;
    }

    printf("\nData: ");
    int num=0, sum=0, product=1, max=0, min=tableStart->id;
    for(Record *curr=tableStart; curr!=NULL; curr=curr->next) {
        printf("%d", curr->id);
        if (curr->next != NULL) printf(", ");
        num++;
        sum = sum + curr->id;
        product = product * curr->id;
        if (curr->id>max) max=curr->id;
        if (curr->id<min) min=curr->id;
    }
    float average=1;
    average = (float)sum / (float)num;
    printf("\nSize: %d\nSum: %d\nProduct: %d\nMaximum: %d\nMinimum: %d\nAverage: %.3f\n", num, sum, product, max, min, average);
    return;
}


// this function only works perfectly when it has to insert to a list that is already sorted
// flag=0 indicates sorting in ascending order
// flag=1 is descending order
// flag changes whenever list is reversed so the insertions are still sorted
void insert(int new_id, int flag) {
    Record *new_record;
    new_record = (Record *) malloc(sizeof(Record));
    new_record->id = new_id;
    new_record->next = NULL;

    Record *prev=NULL, *curr=tableStart;
    while(curr!=NULL && ((flag==0 && curr->id <= new_id) || (flag==1 && curr->id >= new_id))) {
        prev = curr;
        curr = curr->next;
    }

    if (prev==NULL) {
        tableStart = new_record;
        new_record->next = curr;
        printf("\n\t* successfully inserted first ID *\n");
    } else {
        prev->next = new_record;
        new_record->next = curr;
        printf("\n\t* successfully inserted *\n");
    }

    printf("\nData: ");
    if (tableStart==NULL) {
        printf("* empty *\n"); return;
    }
    for(Record *curr=tableStart; curr!=NULL; curr=curr->next) {
        printf("%d ", curr->id);
    }
    printf("\n");
    return;
}


void delete(int del_id) {
    Record *curr=tableStart, *prev=NULL;
    while(curr!=NULL && curr->id!=del_id) {
        prev=curr;
        curr=curr->next;
    }
    
    if (curr==NULL) {
        printf("\n\t* ID does not exist *\n");
        return;
    } else if (prev==NULL) {
        tableStart = curr->next;
        printf("\n\t* first ID deleted *\n");
    } else {
        prev->next = curr->next;
        printf("\n\t* ID deleted *\n");
    }

    printf("\nData: ");
    if (tableStart==NULL) {
        printf("* empty *\n"); return;
    }
    for(Record *curr=tableStart; curr!=NULL; curr=curr->next) {
        printf("%d ", curr->id);
    }
    printf("\n");
    return;
}


int reverse(int flag) {
    Record *curr=tableStart, *prev=NULL, *prev2=NULL;
    while(curr!=NULL) {
        prev2 = prev;
        prev = curr;
        curr = curr->next;
        prev->next = prev2;
    }
    tableStart = prev;
    printf("\n\t* successfully reversed list *\n");

    printf("\nData: ");
    if (tableStart==NULL) {
        printf("* empty *\n");
    }
    for(Record *curr=tableStart; curr!=NULL; curr=curr->next) {
        printf("%d ", curr->id);
    }
    printf("\n");
    if (flag==0) return 1;
    return 0;
}


void export_to_file() {
    FILE *fp = fopen("linked_list.txt", "w+");
    int num=0, sum=0, product=1;
    fprintf(fp, "Data: ");
    if (tableStart==NULL) {
        fprintf(fp, "* empty *");
    } else {
        for(Record *curr=tableStart; curr!=NULL; curr=curr->next) {
            fprintf(fp, "%d", curr->id);
            if(curr->next != NULL) fprintf(fp, ", ");
            num++;
            sum += curr->id;
            product *= curr->id;
        }
        float average = (float)sum / (float)num;
        fprintf(fp, "\nSize: %d\nSum: %d\nProduct: %d\nAverage: %.3f\n", num, sum, product, average);
    }
    printf("\n\t* successfully exported to \"linked_list.txt\" *\n");
    fclose(fp);
    return;
}