#include <iostream>
#include <string>
using namespace std;

//funkcja wyswietlajaca plansze
void wyswietlPlansze(char** plansza, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << " " << plansza[i][j] << " ";
            if (j < size - 1) cout << "|";
        }
        cout << endl;
        if (i < size - 1) {
            for (int j = 0; j < size; ++j) {
                cout << "---";
                if (j < size - 1) cout << "+";
            }
            cout << endl;
        }
    }
}
void znajdzZwyciezce(char** plansza, int size, char* zwyciezca){
    int licznik = 0;
    //sprawdzanie poziomo
    for(int i=0;i<size;i++){
        if(plansza[i][0] != ' ') {
        licznik = 1;
        for(int j = 1; j<size; j++){
            if(plansza[i][j] == plansza[i][j-1]) licznik++;
            else break;
        }
        }
        if(licznik == size) {
            *zwyciezca = plansza[i][0];
            return;
        }

    }

    //sprawdzanie pionowo
    for(int i=0;i<size;i++){
        if(plansza[0][i] != ' '){
            licznik = 1;
            for(int j = 1;j<size;j++){
                if(plansza[j][i]==plansza[j-1][i]) licznik++;
                else break;
            }
        }
        if(licznik == size) {
            *zwyciezca = plansza[0][i];
            return;
        }
    }

    //sprawdzanie po przekatnej
    //z lewej
    if(plansza[0][0] != ' '){
        licznik = 1;
        for(int i=1;i<size;i++){
                if(plansza[i][i]==plansza[i-1][i-1])licznik++;
                else break;
            if(licznik == size) {
                *zwyciezca = plansza[0][0];
                return;
            }
        }
    }


   //z prawej
    if(plansza[0][size-1] != ' '){
        licznik = 1;
        for(int i=1;i<size;i++){
                if(plansza[i][size-i-1] == plansza[i-1][size-i])licznik++;
                else break;
            if(licznik == size) {
                *zwyciezca = plansza[0][size-1];
                return;
            }
        }
    }



   //sprawdzenie warunku remisu
   int pusteMiejsca = 0;
   for(int i=0;i<size;i++){
       for(int j=0;j<size;j++){
           if(plansza[i][j] == ' ') pusteMiejsca++;
       }
   }
   if(pusteMiejsca == 0) *zwyciezca = '\0';
}

int main() {
    //deklaracja rozmiaru planszy przez uzytkownika
    int n = 0;
    cout<<"Podaj rozmiar planszy (np. 5 -> 5x5): ";
    while(n<3){
        cin>>n;
        if(n<3){
            cout<<"Rozmiar planszy musi być liczbą dodatnia większą od 2"<<endl;
        }
    }
    cout<<"Zadeklarowano plansze: "<<n<<"x"<<n<<endl;

    //zapelnianie planszy pustymi miejscami przed rozpoczeciem gry
    char** plansza=new char*[n];
    for (int i = 0; i<n; i++){
        plansza[i] = new char[n];
        for(int j=0;j<n;j++){
            plansza[i][j]=' ';
        }
    }

    //tworzenie graczy oraz zmiennej odpowiadajacej za pilnowanie tury
    const char graczX = 'X';
    const char graczO = 'O';
    char biezacyGracz = 'O';
    char* zwyciezca = new char(' ');

    //tworzenie zmiennych odpowiadajacych za kolmuny oraz wiersze
    int kolumna = -1;
    int wiersz = -1;

    bool straznik = true;
    for(int i = 0;i<n*n;i++){
        wyswietlPlansze(plansza,n);
        cout<<"Kolej gracza: gracz "<<biezacyGracz<<endl;
        //sprawdzanie poprawnosci danych wprowadzanych przez graczy
        straznik = true;
        while(straznik) {
            wiersz = -1;
            kolumna = -1;
            cout<<"Podaj wiersz oraz kolumne z zakresu: 1-"<<n<<": ";
            cin >> wiersz >> kolumna;
            wiersz--;
            kolumna--;
            if(wiersz<0 || wiersz>=n || kolumna<0 || kolumna>=n)
                cout<<"Nie ma takiej kolumny/wiersza!"<<endl;
            else if(plansza[wiersz][kolumna] != ' ')
                cout<<"Pole zapełnione, wybierz inne."<<endl;
            else
                straznik = false;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        plansza[wiersz][kolumna] = biezacyGracz;
        biezacyGracz = (biezacyGracz == graczO) ? graczX : graczO;
        znajdzZwyciezce(plansza,n,zwyciezca);
        if(*zwyciezca==graczO) {
            wyswietlPlansze(plansza,n);
            cout<<"Zwyciezyl gracz O! Gratulacje!";
            break;
        }
        else if (*zwyciezca==graczX){
            wyswietlPlansze(plansza,n);
            cout<<"Zwyciezyl gracz X! Gratulacje!";
            break;
        }
        else if (*zwyciezca == '\0'){
            wyswietlPlansze(plansza,n);
            cout<<"Remis! Brak zwyciezcy!";
            break;
        }

    }

    //zwolnienie pamieci
    for(int i=0;i<n;++i){
        delete[] plansza[i];
    }
    delete[] plansza;
    return 0;
}
