#include <stdio.h>
#include "player.h"
#include "deck.h"
#include "card.h"
#include "time.h"
int add_card(struct player* target, struct card* new_card){
    struct hand* current_node = target->card_list;
    struct hand* new_node = (struct hand*)malloc(sizeof(struct hand));
    new_node->top = *new_card;
    new_node->next = NULL;
    while(current_node->next!= NULL){
        current_node = current_node->next;
    }
    current_node->next= new_node;
    current_node = current_node->next;
    target->hand_size++;
    return 0;
}

int remove_card(struct player* target, struct card* old_card){
    struct hand* current_node = target->card_list;
    struct hand* prev_node = current_node;
    struct hand* temp = current_node;
    int flag=0;
    while(current_node->next!=NULL){
        if(current_node->top.rank == old_card->rank){
            if(flag==0){
                temp = current_node;
                target->card_list = target->card_list->next;
                target->hand_size--;
                free(temp);
                flag=1;
            }
            else{
                temp=current_node;
                prev_node->next=current_node->next;
                target->hand_size--;
                free(temp);
            }
            return 1;
        }
        if(flag==1){
            prev_node = prev_node->next;
        }
        else if(prev_node == NULL){
            prev_node->top = target->card_list->top;
            prev_node->next = target->card_list->next;
        }
        flag=1;
        current_node = current_node->next;
    }
    if(current_node->top.rank == old_card->rank){
        temp=current_node;
        prev_node->next=current_node->next;
        free(temp);
        target->hand_size--;
        return 1;
    }
    return 0;
}
int search(struct player* target, char rank){
    struct hand* current_node = target->card_list;
    while(current_node->next!=NULL) {
        if (current_node->top.rank == rank) {
            return 1;
        }
        current_node = current_node->next;
    }
    if (current_node->top.rank == rank) {
        return 1;
    }
    return 0;
}
int transfer_cards(struct player* src, struct player* dest, char rank){
    int remove_response, add_response = 0;
    struct card hassle;
    struct card* c;
    c = &hassle;
    c->suit='C';
    c->rank=rank;
    int ret=0;
    while(1){
        int test=search(src,rank);
        if(test==0){
            break;
        }
        remove_response=remove_card(src,c);
        if(remove_response==1){
            add_response=add_card(dest,c);
            if(add_response!=0){
                return -1;
            }
        }
        else{
            return -1;
        }
        ret += 1;
    }
    return ret;
}
char check_add_book(struct player* target){
    struct hand* head = target->card_list;
    int ctr=0;
    char checking;
    char added;
    while(head!=NULL){
        struct hand* current_node = head;
        checking = current_node->top.rank;
        while(current_node!=NULL){
            if(current_node->top.rank==checking) {
                added=current_node->top.rank;
                ctr++;
            }
            current_node=current_node->next;
        }
        if(ctr==4){
            return added;
        }
        else{
            ctr=0;
        }
        head=head->next;
    }
    return '0';
}
int game_over(struct player* target){
    int i;
    int ctr=0;
    for(i=0;i<7;i++){
        if(target->book[i]=='x' )
            return 0;
    }
    return 1;
}
char computer_play(struct player* target){
    struct hand* temp = target->card_list;

    srand(time(0));
    int select = rand() % (target->hand_size);
    int i=1;
    while(i<select){
        temp = temp->next;
        i++;
    }
    return temp->top.rank;
}
char user_play(struct player* target){
    struct hand* temp = target->card_list;
    char userChoice;
    printf("enter the val\n");
    scanf("%c",&userChoice);
    while(temp->next!=NULL){
        if(temp->top.rank == userChoice){
            return userChoice;

        }
        temp=temp->next;
    }
    if(temp->top.rank == userChoice){
        return userChoice;
    }
    printf("Error - must have at least one card from rank to play\n");
    return '|';
}
int reset_player(struct player* target){
    struct hand* temp = target->card_list;
    int i;
    for(i=0;i<target->hand_size;i++){
        temp=target->card_list;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        free(temp);
    }

    return 0;
}

