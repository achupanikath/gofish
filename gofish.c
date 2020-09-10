#include <stdio.h>
#include "deck.h"
#include "card.h"
#include "player.h"
int main(int args, char* argv[]){
    MAINMETHOD:
    printf("%s","Welcome to GoFish!\n Shuffling Deck\n");
    int checkShuffle = shuffle();
    int ctruser=0, ctrcomp=0;
    if(checkShuffle!=0){
        printf("%s", "Error Shuffling. Please call Tech Support!\n");
        exit(1);
    }
    struct player* userp;
    userp = &user;
    int checkDeal = deal_player_cards(userp);
    printf("***Here is your hand!***\n");
    displayLinked(user);
    if(checkDeal!=0){
        exit(1);
    }
    struct player* computerp;
    computerp = &computer;
    int checkDeal1 = deal_player_cards(computerp);
    printf("Number of decks computer won:%d\n",ctrcomp);

    if(checkDeal1!=0){
        exit(1);
    }
    int drawcard;
    int gameuser = game_over(userp);
    int gamecomp = game_over(computerp);
    while(gameuser!=1 && gamecomp!=1){
        char userPlay = user_play(userp);
        while(userPlay=='|'){
            userPlay=user_play(userp);
        }
        int transfer_request = transfer_cards(computerp,userp,userPlay);
        if(transfer_request>=1){
            printf("Number of cards transferred from opponents hand to yours = %d\n ",transfer_request);
        }
        else if(transfer_request == 0){
            printf("GO FISH! No cards found in the opponent's hand! \n");
            printf("Drawing a card from the deck to your hand...\n");
            struct card* drawcarp;
            drawcarp = &deck_instance.list[deck_instance.top_card];
            drawcard = add_card(userp,drawcarp);
            deck_instance.top_card--;
            if(drawcard!=0){
                printf("Error drawing card from deck! Game ends!");
                exit(0);
            }
        }
        else{
            printf("Error, Please re-run the program");
        }
        printf("Here is your hand!\n Number of books you have won:%d\n",ctruser);
        displayLinked(user);
        printf(" Number of books computer won:%d\n",ctrcomp);
        char addBookCheck = check_add_book(userp);
        if(addBookCheck!='0'){
            userp->book[ctruser]=addBookCheck;
            ctruser++;
            printf("%c",addBookCheck);
            int g;
            for(g=0;g<4;g++){
                struct card bookc;
                struct card* bookcp;
                bookcp = &bookc;
                bookcp->rank=addBookCheck;
                bookcp->suit='C';
                remove_card(userp,bookcp);
            }

        }

        if(ctruser==7){
            printf("Game Over! You WON! Do you want to play again? Enter Y/y to play again!");
            char ch;
            scanf("%c",&ch);
            if(ch=='Y'||ch=='y'){
                int x=reset_player(userp);
                x=reset_player(computerp);
                goto MAINMETHOD;
            }
            else{
                exit(0);
            }
        }
        char computerPlay = computer_play(computerp);
        transfer_request = transfer_cards(userp,computerp,computerPlay);
        if(transfer_request>=1){
            printf("Compuetr plays \nnumber of cards transferred = %d",transfer_request);
        }
        else if(transfer_request == 0){
            printf("GO FISH! No cards found in your hand!");
            printf("Drawing a card from the deck to computers hand...");
            struct card* drawcarp;
            drawcarp = &deck_instance.list[deck_instance.top_card];
            drawcard = add_card(computerp,drawcarp);
            deck_instance.top_card--;
            if(drawcard!=0){
                printf("Error drawing card from deck! Game ends!");
                exit(0);
            }
        }
        else{
            printf("Error! Rerun the program");
            exit(0);
        }
        printf("Here is your hand!\n Number of books you have won:%d\n",ctruser);
        displayLinked(user);
        printf(" Number of books computer won:%d\n",ctrcomp);
        addBookCheck = check_add_book(computerp);
        if(addBookCheck!='0'){
            userp->book[ctrcomp]=addBookCheck;
            ctrcomp++;
            printf("%c",addBookCheck);
            int g;
            for(g=0;g<4;g++){
                struct card bookc;
                struct card* bookcp;
                bookcp = &bookc;
                bookcp->rank=addBookCheck;
                bookcp->suit='C';
                remove_card(computerp,bookcp);
            }

        }

        if(ctrcomp==7){
            printf("Game Over! Tough Luck! You lost! Do you want to play again? Enter Y/y to play again!");
            char ch;
            scanf("%c",&ch);
            if(ch=='Y'||ch=='y'){
                int x=reset_player(userp);
                x=reset_player(computerp);
                goto MAINMETHOD;
            }
            else{
                exit(0);
            }
        }
    }
//    printf("%s","shuffling deck...\n");
//    check();
//    printf("%s","this is your hand \n");
//
//    struct player* userp;
//    userp = &user;
//    int a = deal_player_cards(userp);
//    struct player* computerp;
//    computerp = &computer;
//    int b = deal_player_cards(computerp);
//    printf("%s","comp hand before ask\n");
//    displayLinked(user);
//    printf("----------------------");
//    displayLinked(computer);
//    printf("----------------------");
//    int kukkkuk = transfer_cards(userp,computerp,'5');
//    printf("%d\n%s",kukkkuk, "user hand after ask\n");
//    displayLinked(user);
//    printf("%s","comp hand after ask\n");
//    displayLinked(computer);


    return 0;
}
