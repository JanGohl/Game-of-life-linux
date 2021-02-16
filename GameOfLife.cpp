#include <bits/stdc++.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cstring>

using namespace std;

int now[110][110];
bool tab[110][110];

int show(int x, int y, int f){
    int a=0;
    system("clear");
    for(int i=1; i<=x; i++){
        cout<< "\n    ";
        for(int j=1; j<=y; j++){
            if(tab[i][j]) a++;
            cout<< tab[i][j]<< " ";
        }
    }
    if(f==0) cout<< "\n\n    Cells alive: " << a<< "\n";
    return a;
}

void neighbors(int x, int y){
    for(int i=1; i<=x; i++) for(int j=1; j<=y; j++) now[i][j]=0;
    for(int i=1; i<=x; i++){
        for(int j=1; j<=y; j++){
            if(tab[i-1][j]) now[i][j]++;
            if(tab[i][j-1]) now[i][j]++;
            if(tab[i-1][j-1]) now[i][j]++;
            if(tab[i+1][j-1]) now[i][j]++;
            if(tab[i][j]){
                now[i-1][j]++;
                now[i][j-1]++;
                now[i-1][j-1]++;
                now[i+1][j-1]++;
            }
        }
    }  
}

void alive(int x, int y){
    for(int i=1; i<=x; i++){
        for(int j=1; j<=y; j++){
            if(now[i][j]==3) tab[i][j]=1;
            else if(now[i][j]!=2) tab[i][j]=0;
        }
    }
}

int stoint(string s){
    int n=0;
    for(int i=0; i<s.size() and i<9; i++) n=n*10+int(s[i])-'0';
    return n;
}

void print(string name){
    system("clear");
    ifstream text(name);
    string line;
    while(getline(text, line)) cout<< line<< "\n";
    text.close ();
}

void hello(){ 
    print("Hello.txt");
    this_thread::sleep_for(2500ms); 
    system("clear");
}

string menu(){
    print("Menu.txt");
    string ch;
    cout<< "    ";
    cin>> ch;
    ch[0]=toupper(ch[0]);
    while(ch!="E" && ch!="G" && ch!="C" && ch!="I"){
        print("Menu.txt");
        cout<< "    There is no such option, try again: ";
        cin>> ch;
        ch[0]=toupper(ch[0]);
    }
    return ch;
}

string lost(){
    print("Lost.txt");
    cout<< "    ";
    string i;
    cin>> i;
    i[0]=toupper(i[0]);
    while(i!="A" and i!="E"){
        print("Lost.txt");
        cout<< "    ";
        cout<< "There is no such option, try again: ";
        cin>> i;
        i[0]=toupper(i[0]);
    }
    return i;
}

bool is_number(string n){
    for(int i=0; i<n.size(); i++) if(!isdigit(n[i])) return 0;
    return 1;
}

void adding_cells_is_number(int x, int y, string xc, string yc, int nr){
    while(!is_number(xc) or !is_number(yc)){
        show(x, y, 1);
        cout<< "\n\n    You still have to select "<< nr<< " cells that will live \n    ";
        cout<< "At least one of your inputs isn't a number, try again: ";
        cin>> xc>> yc;
    }

}

void adding_cells(int x, int y, int nr){
    while(nr!=0){
        show(x, y, 1);
        cout<< "\n\n    You still have to select "<< nr<< " cells that will live \n    ";
        string xc, yc;
        int XC, YC;
        cin>> xc>> yc;
        adding_cells_is_number(x, y, xc, yc, nr);
        XC=stoint(xc);
        YC=stoint(yc);
        while(XC<1 or XC>x or YC<1 or YC>y or tab[XC][YC]){
            show(x, y, 1);
            cout<< "\n\n    You still have to select "<< nr<< " cells that will live \n    ";
            cout<< "You selected a incorrect cell, try again: ";
            cin>> xc>> yc;
            adding_cells_is_number(x, y, xc, yc, nr);
            XC=stoint(xc);
            YC=stoint(yc);
        }
        tab[XC][YC]=1;
        nr--;
    }
}

void instructions(){
    print("Instructions.txt");
    cout<< "    ";
    string i;
    cin>> i;
    i[0]=toupper(i[0]);
    while(i!="C"){
        print("Instructions.txt");
        cout<< "    ";
        cout<< "There is no such option, try again: ";
        cin>> i;
        i[0]=toupper(i[0]);
    }
}

string pasue_game(int x, int y, int g){
    system("clear");
    show(x, y, 0);
    cout<< "    Generation: "<< g<< "\n\n    What do you want to do? Select and press enter\n    R - resume    I - instructions    E - exit to menu\n    ";
    string i;
    cin>> i;
    i[0]=toupper(i[0]);
    while(i!="R" and i!="I" and i!="E"){
        show(x, y, 0);
        cout<< "    Generation: "<< g<< "\n\n    What do you want to do? Select and press enter\n    R - resume    I - instructions    E - exit to menu\n    "; 
        cout<< "There is no such option, try again: ";
        cin>> i;
        i[0]=toupper(i[0]);
    }
    if(i=="I"){
        instructions();
        pasue_game(x, y, g);
    }
    return i;
}

void number_of_cells_is_number(int x, int y, string nr, int a){
    while(!is_number(nr)){
        show(x, y, 1);
        cout<< "\n\n    How many cells do you want to add? (0 - "<< x*y-a<< "): \n    ";
        cout<< "Not a number, try again: ";
        cin>> nr;
    }
}

int number_of_cells(int x, int y, int a){
    show(x, y, 1);
    cout<< "\n\n    How many cells do you want to add? (0 - "<< x*y-a<< "): ";
    string nr;
    int NR;
    cin>> nr;
    number_of_cells_is_number(x, y, nr, a);
    NR=stoint(nr);
    while(NR>x*y-a or NR<0){
        show(x, y, 1);
        cout<< "\n\n    How many cells do you want to add? (0 - "<< x*y-a<< "): ";
        cout<< "\n    The number is incorrect, try again: ";
        cin>> nr;
        number_of_cells_is_number(x, y, nr, a);
        NR=stoint(nr);
    }
    return NR;
}

int gameplay(int x, int y, int G){
    int a=0, g=G;
    a=show(x, y, 0);
    while (a!=0){
        show(x, y, 0);
        cout<< "    Generation: "<< g<<"\n\n    What do you want to do? Select and press enter:\n    C - contiune    P - pause    A - add living cells\n    ";
        string i;
        cin>> i;
        i[0]=toupper(i[0]);
        while(i!="C" and i!="P" and i!="A"){
            a=show(x, y, 0);
            cout<< "    Generation: "<< g<<"\n\n    What do you want to do? Select and press enter:\n    C - continue    P - pause    A - add living cells\n    ";
            cout<< "There is no such option, try again: ";
            getline(cin, i);
            i[0]=toupper(i[0]);
        }
        if(i=="P") if(pasue_game(x, y, g)=="E") return 0;
        if(i=="A"){
            int nr=number_of_cells(x, y, a);
            adding_cells(x, y, nr);
        }
        if(i=="C"){
            neighbors(x, y);
            alive(x, y);
            a=show(x, y, 0);
            g++;
        }
    } 
    if(a==0){
        this_thread::sleep_for(2000ms); 
        if(lose()=="A"){
            int nr=number_of_cells(x, y, a);
            adding_cells(x, y, nr);
            gameplay(x, y, g);
        }
    }

    return 0;
}

void game_is_number(string x, string y){
    while(!is_number(x) or !is_number(y)){
        system("clear");
        cout<< "\n    How big should be the game area? (2 <= x, y <= 100): \n    ";
        cout<< "At least one of your inputs isn't a number, try again: ";
        cin>> x>> y;
    }
}

void game(){    
    system("clear");
    cout<< "\n    How big should be the game area? (2 <= x, y <= 100): ";
    string x, y;
    int X, Y;
    cin>> x>> y;
    game_is_number(x, y);
    X=stoint(x);
    Y=stoint(y);
    while((X<2 or X>100) or (Y<2 or Y>100)){
        system("clear");
        cout<< "\n    How big should be the game area? (2 <= x, y <= 100): ";
        cout<< "\n    At least one of your numbers is incorrect, try again: ";
        cin>> x>> y;
        game_is_number(x, y);
        X=stoint(x);
        Y=stoint(y);
    }
    for(int i=0; i<=X+5; i++) for(int j=0; j<=Y+5; j++) tab[i][j]=0;
    int nr=number_of_cells(X, Y, 0);
    adding_cells(Y, X, nr);
    gameplay(X, Y, 1);
}

void cool_animation(){
    system("./RayTracing_GameOfLife");
}

void program(){
    hello();
    while(1){
        string ch=menu();
        if(ch=="G") game();
        else if(ch=="C") cool_animation();
        else if(ch=="I") instructions();
        else if(ch=="E")break;
    }
    print("Goodbye.txt");
    this_thread::sleep_for(2500ms); 
    system("clear");
}

int main(){
    program();
    return 0;
}

//g++ GameOfLife.cpp -o GameOfLife
