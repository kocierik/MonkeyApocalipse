// #include <iostream>
// #include "menu.h"
// //#include <conio.h>
// using namespace std;


// void printMenu(){

//     int option = 0;
//     bool select =  false;

//     while(select == false){
        
//         system("cls");
//         if(option == 0){
            
//             cout << endl;

//             cout << "       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
//                     "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
//                     "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
//                     "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
//                     "                                                                                                                                        \n"
//                     "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
//                     "                                                                                                                                        \n";
            
//             cout << "\n\n\n\n";



//             cout << "                                                ==>  () START THE FIGHT! " << endl;
//             cout << "\n\n";
//             cout << "                                                     () HOW TO PLAY " << endl;
//             cout << "\n\n";
//             cout << "                                                     () CREDITS " << endl;
//             cout << "\n\n";
//             cout << "                                                     (q) QUIT " << endl;
//             cout << "\n\n\n\n\n";
//             cout << "                                           use \"W\" or \"S\" for navigate in the menu " << endl;
            
//         } else if (option == 1){
            
//             cout << endl;

//             cout << "       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
//                     "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
//                     "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
//                     "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
//                     "                                                                                                                                        \n"
//                     "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
//                     "                                                                                                                                        \n";
            
//             cout << "\n\n\n\n";



//             cout << "                                                     () START THE FIGHT! " << endl;
//             cout << "\n\n";
//             cout << "                                                ==>  () HOW TO PLAY " << endl;
//             cout << "\n\n";
//             cout << "                                                     () CREDITS " << endl;
//             cout << "\n\n";
//             cout << "                                                     (q) QUIT " << endl;
//             cout << "\n\n\n\n\n";
//             cout << "                                           use \"W\" or \"S\" for navigate in the menu " << endl;

//         }else if(option == 2){
            
//             cout << endl;

//             cout << "       8b    d8  dP*Yb  88b 88 88  dP 888888 Yb  dP        db    88**Yb  dP*Yb   dP**b8    db    88     Yb  dP 88**Yb .dP*Y8 888888     \n"
//                     "       88b  d88 dP   Yb 88Yb88 88odP  88__    YbdP        dPYb   88__dP dP   Yb dP   `*   dPYb   88      YbdP  88__dP `Ybo.* 88__       \n"
//                     "       88YbdP88 Yb   dP 88 Y88 88*Yb  88**     8P        dP__Yb  88***  Yb   dP Yb       dP__Yb  88  .o   8P   88***  o.`Y8b 88**       \n"
//                     "       88 YY 88  YbodP  88  Y8 88  Yb 888888  dP        dP****Yb 88      YbodP   YboodP dP****Yb 88ood8  dP    88     8bodP* 888888     \n"
//                     "                                                                                                                                        \n"
//                     "       LA VENDETTA DELLA SCIMMIA COGLIONA E' APPENA COMIMCIATA!                                                                         \n"
//                     "                                                                                                                                        \n";
            
//             cout << "\n\n\n\n";



//             cout << "                                                     () START THE FIGHT! " << endl;
//             cout << "\n\n";
//             cout << "                                                     () HOW TO PLAY " << endl;
//             cout << "\n\n";
//             cout << "                                                ==>  () CREDITS " << endl;
//             cout << "\n\n";
//             cout << "                                                     [q] QUIT " << endl;
//             cout << "\n\n\n\n\n";
//             cout << "                                           use \"W\" or \"S\" for navigate in the menu " << endl;
//         }

//         if(_kbhit()){
//             switch(getch()){

//                 case 's':
//                     option++;
//                     if(option>2){
//                         option = 0;
//                     }
//                     break;

//                 case 'w':
//                     option--;
//                     if(option<0){
//                         option = 2;
//                     }
//                     break;

//                 case 'q':
//                     select = true;
//                     break;

//                 case 13:
//                     select = true;
//                     if(option == 0){
//                         cout << "opzione 0" << endl;
//                     }else if(option == 1){
//                         system("cls");
//                         cout << "                    88  88  dP*Yb  Yb        dP     888888  dP*Yb      88**Yb 88        db    Yb  dP  \n"
//                                 "                    88  88 dP   Yb  Yb  db  dP        88   dP   Yb     88__dP 88       dPYb    YbdP   \n"
//                                 "                    888888 Yb   dP   YbdPYbdP         88   Yb   dP     88***  88  .o  dP__Yb    8P    \n"
//                                 "                    88  88  YbodP     YP  YP          88    YbodP      88     88ood8 dP****Yb  dP     \n";
//                         cout << "\n\n\n";
//                         cout << "              Non c'e' un cazzo da spiegare, andate a leccare i piedi a quella zoccolona di belle delphine. \n"
//                                 "  \n";
                        
//                     }else if(option == 2){
//                         cout << "opzione 2" << endl;
//                     }
//                     break;
//             }
//         }
        
//     }



// }