#include <stdio.h>
#include <stdlib.h>


typedef struct record { // this will be a linked list that stores an integer
    int data;
    struct record *next;
} Record;


typedef struct list_start { // this will be a linked list of linked lists
    int list_id;
    Record *rec_start;
    struct list_start *next;
} List_start;
List_start *all_start = NULL;


void new_linked_list();
void insert();
void display();
void add_lists();
void multiply_lists();


int main() {
    int choice=0;
    while (choice!=5) {
        printf("\n1) Make new list\n2) Insert element in list \n3) Display all data\n4) Arithmetic\n5) Exit\n> ");
        scanf("%d", &choice);
        if (choice==1) {
            new_linked_list();
        } else if (choice==2) {
            insert();
        } else if (choice==3) {
            display();
        } else if (choice==4) {
            int choice2=0;
            printf("\n1) Add lists\n2) Multiply lists\n> ");
            scanf("%d", &choice2);
            if (choice2==1) {
                add_lists();
            } else if (choice2==2) {
                multiply_lists();
            } else {
                printf("\n* invalid input *\n");
            }
        } else if (choice==5) {
            break;
        } else {
            printf("\n* invalid input *\n");
        }
    }

    printf("\n* exited successfully *\n");
    return 0;
}


void display() {
    if (all_start==NULL) {
        printf("\n* no lists added yet *\n");
        return;
    }

    for (List_start *tempLL=all_start; tempLL!=NULL; tempLL=tempLL->next) {
        printf("\nList ID: %d\tData: ", tempLL->list_id);
        if(tempLL->rec_start==NULL) {
            printf("* empty list *");
            continue;
        }
        for(Record *tempR=tempLL->rec_start; tempR!=NULL; tempR=tempR->next) {
            printf("%d", tempR->data);
            if (tempR->next!=NULL) printf(" ");
        }
    }
    printf("\n");
    return;
}


void new_linked_list() {
    List_start *new_list;
    new_list = (List_start *) malloc(sizeof(List_start));
    new_list->rec_start = NULL;
    new_list->next = NULL;

    printf("\nNew list ID: ");
    scanf("%d", &(new_list->list_id));
    
    List_start *tempLL=all_start, *prev=NULL;
    while (tempLL!=NULL) {
        prev = tempLL;
        tempLL = tempLL->next;
        if (prev->list_id == new_list->list_id) {
            printf("\n* list ID already exists *\n");
            return;
        }
    }
    
    if (prev==NULL) {
        all_start = new_list;
        new_list->next = tempLL;
        printf("\n* first list created *\n");
    } else {
        prev->next = new_list;
        new_list->next = tempLL;
        printf("\n* list created *\n");
    }
    return;
}


void insert() {
    if (all_start==NULL) {
        printf("\n* no existing list to insert into *\n");
        return;
    }

    int list_id_input;
    printf("\nList ID to insert in: ");
    scanf("%d", &list_id_input);
    
    List_start *tempLL = all_start;
    while (tempLL!=NULL && tempLL->list_id!=list_id_input) {
        tempLL = tempLL->next;
    }
    printf("\nLoop over");
    if (tempLL==NULL) {
        printf("\n* list ID does not exist *\n");
        return;
    }

    int data_input;
    printf("\nElement to insert: ");
    scanf("%d", &data_input);

    Record *new_record;
    new_record = (Record *) malloc(sizeof(Record));
    new_record->data = data_input;
    new_record->next = NULL;

    Record *tempR=tempLL->rec_start, *prev=NULL;
    while (tempR!=NULL && tempR->data <= data_input) {
        prev = tempR;
        tempR = tempR->next;
    }

    if (prev==NULL) {
        tempLL->rec_start = new_record;
        new_record->next = tempR;
        printf("\n* successfully inserted first element *\n");
    } else {
        prev->next = new_record;
        new_record->next = tempR;
        printf("\n* successfully inserted *\n");
    }
}


void add_lists() {
    if (all_start==NULL) {
        printf("\n* no existing lists *\n");
    }

    int list_id1;
    printf("First list (store): ");
    scanf("%d", &list_id1);
    List_start *tempLL1=all_start;
    while (tempLL1!=NULL && tempLL1->list_id!=list_id1) tempLL1=tempLL1->next;
    if (tempLL1==NULL) { // if this becomes null then there was no time when the stored id was equal to the input id so list ID does not exist
        printf("\n* invalid list ID *\n");
        return;
    }
    int list_id2;
    printf("Second list: ");
    scanf("%d", &list_id2);
    List_start *tempLL2=all_start;
    while (tempLL2!=NULL && tempLL2->list_id!=list_id2) tempLL2=tempLL2->next;
    if (tempLL2==NULL) {
        printf("\n* invalid list ID *\n");
        return;
    }

    Record *tempR1=tempLL1->rec_start, *tempR2=tempLL2->rec_start;
    while (tempR1!=NULL && tempR2!=NULL) {
        tempR1->data = tempR1->data + tempR2->data;
        tempR1 = tempR1->next;
        tempR2 = tempR2->next;
    }

    printf("\n* data from list-%d added and stored in list-%d *\n", tempLL2->list_id, tempLL1->list_id);
    return;
}


void multiply_lists() {
    if (all_start==NULL) {
        printf("\n* no existing lists *\n");
    }

    int list_id1;
    printf("First list (store): ");
    scanf("%d", &list_id1);
    List_start *tempLL1=all_start;
    while (tempLL1!=NULL && tempLL1->list_id!=list_id1) tempLL1=tempLL1->next;
    if (tempLL1==NULL) { // if this becomes null then there was no time when the stored id was equal to the input id so list ID does not exist
        printf("\n* invalid list ID *\n");
        return;
    }
    int list_id2;
    printf("Second list: ");
    scanf("%d", &list_id2);
    List_start *tempLL2=all_start;
    while (tempLL2!=NULL && tempLL2->list_id!=list_id2) tempLL2=tempLL2->next;
    if (tempLL2==NULL) {
        printf("\n* invalid list ID *\n");
        return;
    }

    Record *tempR1=tempLL1->rec_start, *tempR2=tempLL2->rec_start;
    while (tempR1!=NULL && tempR2!=NULL) {
        tempR1->data = tempR1->data * tempR2->data;
        tempR1 = tempR1->next;
        tempR2 = tempR2->next;
    }

    printf("\n* data from list-%d multiplied and stored in list-%d *\n", tempLL2->list_id, tempLL1->list_id);
    return;
}