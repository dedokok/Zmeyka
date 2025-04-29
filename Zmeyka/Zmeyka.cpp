#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <ctime>
using namespace std;


struct tochka_zmei{
    int stroka;
    int stolb;
};

void clear_console() {
	std::cout << "\033[2J\033[1;1H";
}




void printPole(char (&pole)[20][30]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30; j++) {
            cout << pole[i][j];
        }
        cout << endl;
    }

}


void dvij(char& naprav, char(&pole)[20][30],
    vector <tochka_zmei>& zmeya_1, bool& igra, int& tick,vector <tochka_zmei> &traectoriya_zmei,bool &sel_yabloko,char&naprav_do) {
    bool R = false, L = false, U = false, D = false;
    int*stroka_z_p = &zmeya_1[0].stroka;
    int stroka_z_int = *stroka_z_p;
    int* stolb_z_p = &zmeya_1[0].stolb;
    int stolb_z_int = *stolb_z_p;
    tochka_zmei tochka_4 = { stroka_z_int, stolb_z_int };
    traectoriya_zmei.push_back(tochka_4);
    if (traectoriya_zmei.size() > 600) {
        traectoriya_zmei.pop_back();
    }
    //naprav_do = naprav;

    if (naprav == 'R' and naprav_do != 'L') { R = true; }
    if (naprav == 'L' and naprav_do != 'R') { L = true; }
    if (naprav == 'R' and naprav_do == 'L') { L = true; }
    if (naprav == 'L' and naprav_do == 'R') { R = true; }
    if (naprav == 'U' and naprav_do != 'D' and naprav_do != 'U') { U = true; }
    if (naprav == 'D' and naprav_do != 'U' and naprav_do != 'D') { D = true; }
    if (naprav == 'U' and naprav_do == 'D' and naprav_do != 'U') { D = true; }
    if (naprav == 'D' and naprav_do == 'U' and naprav_do != 'D') { U = true; }


    if (R) {
        
        for (int i = zmeya_1.size() - 1; i > 0; i--) {
            pole[zmeya_1[i].stroka][zmeya_1[i].stolb] = ' ';
            zmeya_1[i] = zmeya_1[i - 1];

        }
        
        zmeya_1[0].stolb++;

    }
    if (L) {
        for (int i = zmeya_1.size() - 1; i > 0; i--) {
            pole[zmeya_1[i].stroka][zmeya_1[i].stolb] = ' ';
            zmeya_1[i] = zmeya_1[i - 1];

        }
        zmeya_1[0].stolb--;

    }
    if (D) {
        for (int i = zmeya_1.size() - 1; i > 0; i--) {
            pole[zmeya_1[i].stroka][zmeya_1[i].stolb] = ' ';
            zmeya_1[i] = zmeya_1[i - 1];

        }
        zmeya_1[0].stroka++;

    }
    if (U) {
        for (int i = zmeya_1.size()-1; i >0; i--) {
            pole[zmeya_1[i].stroka][zmeya_1[i].stolb] = ' ';

            zmeya_1[i] = zmeya_1[i - 1];


        }
        zmeya_1[0].stroka--;

    }
    for (int i = 1; i < zmeya_1.size(); i++)
    {

        if ((zmeya_1[0].stolb == zmeya_1[i].stolb and zmeya_1[0].stroka == zmeya_1[i].stroka and tick > 1) or zmeya_1[0].stroka == 0
            or zmeya_1[0].stolb == 0 or zmeya_1[0].stroka==19 or zmeya_1[0].stolb==29) {
            cout << "Proigral";
            igra = false;
            break;
        }
        


    }

    if (pole[zmeya_1[0].stroka][zmeya_1[0].stolb] == '*') {
        zmeya_1.push_back(traectoriya_zmei[traectoriya_zmei.size()-zmeya_1.size()]);
        sel_yabloko = true;
    }
    //cout << endl;
    //for (int i = 0; i < zmeya_1.size(); i++) {
    //    cout << zmeya_1[i].stroka << " " << zmeya_1[i].stolb << endl;
    //}
    for (int i = 0; i < zmeya_1.size(); i++) {
        pole[zmeya_1[i].stroka][zmeya_1[i].stolb] = '@';
        if (zmeya_1[0].stroka == zmeya_1[i].stroka and zmeya_1[0].stolb == zmeya_1[i].stolb and i != 0) {
            cout << "Proigral";
            igra = false;
            break;
        }
    }
    if (zmeya_1.size() == 502) {
        cout << "Pobedil" << endl;
        igra = false;
        
    }
    
}
    

void yabloko(char(&pole)[20][30], bool &sel_yabloko) {
    int yabloko_stroka = 1 + rand() % 18;
    int yabloko_stolb = 1 + rand() % 28;
    pole[yabloko_stroka][yabloko_stolb] = '*';
    sel_yabloko = false;
}


int main() {
    srand(time(NULL));
    //thread knopki_thread(knopki);
    int key_1 = 0;
    bool sel_yabloko = false;
    int tick = 0;
    char key_2 = 0;
    char naprav = 'R';
    char naprav_do = 'R';
    bool igra = true;
    char pole[20][30];
    vector <tochka_zmei> zmeya_1;
    tochka_zmei tochka_1 = { 10,15 };
    tochka_zmei tochka_2 = { 10,14 };
    zmeya_1.push_back(tochka_1);
    zmeya_1.push_back(tochka_2);
    
    vector <tochka_zmei> traectoriya_zmei;
    


    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 30; j++) {
            if (i == 0 or i == 19 or j == 0 or j == 29) {
                pole[i][j] = '#';
            }
            else {
                pole[i][j] = ' ';
            }
        }
    }
    yabloko(pole,sel_yabloko);
    printPole(pole);
    //if (naprav_do != naprav) {
    //    naprav_do = naprav;
    //}
    while (igra)
    {

        if (_kbhit()) // слушатель нажатия на клаву
        {
            char keyy = _getch();
            
            //key_1 = _getch();
            //cout << key_1 << endl;
            
            
            switch (keyy) //перед этим было switch(x)
            {
            case 119:
                
                //cout << "Up" << endl;
                if (naprav != keyy) {
                    naprav = 'U';
                }
                break;
            case 115:
               // cout << "Down" << endl;
                if (naprav != keyy) {
                    naprav = 'D';
                }
                break;
            case 97:
                //cout << "Left" << endl;
                if (naprav_do != naprav) {
                    naprav = 'L';
                }
                break;
            case 100:
                //cout << "Right" << endl;
                if (naprav_do != naprav) {
                    naprav = 'R';
                }
                break;

            case 72:
                //cout << "Up" << endl;
                if (naprav_do != naprav) {
                    naprav = 'U';
                }
                break;
            case 80:
                //cout << "Down" << endl;
                if (naprav_do != naprav) {
                    naprav = 'D';
                }
                break;
            case 75:
                //cout << "Left" << endl;
                if (naprav_do != naprav) {
                    naprav = 'L';
                }
                break;
            case 77:
                //cout << "Right" << endl;
                if (naprav_do != naprav) {
                    naprav = 'R';
                }
                break;
            }


        }
        
        dvij(naprav, pole, zmeya_1,igra,tick,traectoriya_zmei,sel_yabloko,naprav_do);
        //cout << zmeya_1[0].stroka << " " << zmeya_1[0].stolb << "|||" << zmeya_1[1].stroka << " " << zmeya_1[1].stolb << endl;
        clear_console();
        if (sel_yabloko == true) {
            yabloko(pole,sel_yabloko);
        }
        printPole(pole);
        cout << endl <<"Ochki: " << zmeya_1.size()-2<<"\\502" << endl;
        
        tick++;
        Sleep(100);
    }
	
}