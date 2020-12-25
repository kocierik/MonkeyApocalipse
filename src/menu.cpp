#include <iostream>
#include "menu.h"
#include <curses.h>
using namespace std;


void printMenu(){

    int option = 0;
    bool select =  false;

    while(select == false){
        

        if(option == 0){
            


            printf("       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
                    "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
                    "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
                    "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
                    "                                                                                                                                        \n"
                    "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
                    "                                                                                                                                        \n");
            
            printf("\n\n\n\n");



            printf("                                                ==>  () START THE FIGHT! " );
            printf("\n\n");
            printf("                                                     () HOW TO PLAY " );
            printf("\n\n");
            printf("                                                     () CREDITS " );
            printf("\n\n");
            printf("                                                     (q) QUIT " );
            printf("\n\n\n\n\n");
            printf("                                           use \"W\" or \"S\" for navigate in the menu " );
            
        } else if (option == 1){

            printf("       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
                    "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
                    "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
                    "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
                    "                                                                                                                                        \n"
                    "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
                    "                                                                                                                                        \n");
            
            printf("\n\n\n\n");



            printf("                                                     () START THE FIGHT! " );
            printf("\n\n");
            printf("                                                ==>  () HOW TO PLAY " );
            printf("\n\n");
            printf("                                                     () CREDITS " );
            printf("\n\n");
            printf("                                                     (q) QUIT " );
            printf("\n\n\n\n\n");
            printf("                                           use \"W\" or \"S\" for navigate in the menu " );

        }else if(option == 2){
            


            printf("       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
                    "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
                    "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
                    "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
                    "                                                                                                                                        \n"
                    "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
                    "                                                                                                                                        \n");
            
            printf("\n\n\n\n");



            printf("                                                     () START THE FIGHT! " );
            printf("\n\n");
            printf("                                                     () HOW TO PLAY " );
            printf("\n\n");
            printf("                                                ==>  () CREDITS " );
            printf("\n\n");
            printf("                                                     [q] QUIT " );
            printf("\n\n\n\n\n");
            printf("                                           use \"W\" or \"S\" for navigate in the menu " );
        }


            // switch((select = getch()) != 27){

            //     case 's':
            //         option++;
            //         if(option>2){
            //             option = 0;
            //         }
            //         break;

            //     case 'w':
            //         option--;
            //         if(option<0){
            //             option = 2;
            //         }
            //         break;

            //     case 'q':
            //         select = true;
            //         break;

            //     case 13:
            //         select = true;
            //         if(option == 0){
            //             printf("opzione 0" );
            //         }else if(option == 1){
            //             system("cls");
            //             printf("                    88  88  dP*Yb  Yb        dP     888888  dP*Yb      88**Yb 88        db    Yb  dP  \n"
            //                     "                    88  88 dP   Yb  Yb  db  dP        88   dP   Yb     88__dP 88       dPYb    YbdP   \n"
            //                     "                    888888 Yb   dP   YbdPYbdP         88   Yb   dP     88***  88  .o  dP__Yb    8P    \n"
            //                     "                    88  88  YbodP     YP  YP          88    YbodP      88     88ood8 dP****Yb  dP     \n");
            //             printf("\n\n\n");
            //             printf("              Non c'e' un cazzo da spiegare, andate a leccare i piedi a quella zoccolona di belle delphine. \n"
            //                     "  \n");
                        
            //         }else if(option == 2){
            //             printf("opzione 2" );
            //         }
            //         break;
            // }
    }



}