#include "deck.h"
#include "player.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void init(){
    char suits[5] = {'H','C','D','S','\0'}; //defines an array of the four suits based on characters
    char ranks[14] = {'2','3','4','5','6','7','8','9','T','K','Q','J','A','\0'}; // defines the 13 ranks per suit. 10 is defined as T
    int i,j,k=0;
    deck_instance.top_card = 51;
    for(i=0;i<13;i++) {
        for (j = 0; j < 4; j++) {
            deck_instance.list[k].suit = suits[j];
            deck_instance.list[k].rank = ranks[i];
            k++;
        }
    }
}
int shuffle(){
    //might need to malloc the last one if reinitialization doesnt kill it from memory
    init();
    int ctr=0;
    int i;
    char temp;
    int random;
    srand(time(0));
    while(ctr<52){
        random = rand()%52;
        for(i=0;i<52;i++){
            temp = deck_instance.list[i].rank;
            deck_instance.list[i].rank = deck_instance.list[random].rank;
            deck_instance.list[random].rank = temp;

            temp = deck_instance.list[i].suit;
            deck_instance.list[i].suit = deck_instance.list[random].suit;
            deck_instance.list[random].suit = temp;
        }
        ctr++;
    }
    if(ctr > 51)
        return 0;
    else
        return 1;
}
void check(){
    int re = shuffle();
    int i,j,k=0;
    for(i=0;i<13;i++) {
        for (j = 0; j < 4; j++) {
            printf("%c%c,%d\n", deck_instance.list[k].suit ,deck_instance.list[k].rank, deck_instance.top_card);

            k++;
        }
    }

}
struct hand* initLinked(){
    struct hand* head = NULL;
    struct hand* temp = NULL;
    struct hand* nextp = NULL;

    int i = 0;
    for(i=0;i<7;i++){
        temp = (struct hand* )malloc(sizeof(struct hand));
        temp->top = deck_instance.list[deck_instance.top_card];
        temp->next=NULL;
        if(head == NULL){
            head = temp;
        }
        else{
            nextp = head;
            while(nextp->next != NULL){
                nextp = nextp->next;
            }
            nextp->next = temp;
        }
        deck_instance.top_card--;
    }

    return head;
}
void displayLinked(struct player target){
    struct hand* start = target.card_list;
    while(start->next != NULL){
        printf("%c,%c\n",start->top.suit,start->top.rank);
        start = start->next;
    }
    printf("%c,%c\n",start->top.suit,start->top.rank);

}
int deal_player_cards(struct player* target){
    target->card_list = initLinked();
    target->hand_size=7;
    int z;
    for(z=0;z<7;z++){
        target->book[z]='x';

    }
    target->book[7]='\0';
    return 0;
}
size_t deck_size(){
    return (deck_instance.top_card+1);

}






