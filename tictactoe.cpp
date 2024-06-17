#include <iostream>
#include <string>
#include <climits>
using namespace std;

// Funkcja do wyświetlania planszy
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

// Funkcja do znajdowania zwycięzcy
void znajdzZwyciezce(char** plansza, int size, char* zwyciezca) {
    int licznik;

    // Sprawdzenie wierszy
    for (int i = 0; i < size; i++) {
        if (plansza[i][0] != ' ') {
            licznik = 1;
            for (int j = 1; j < size; j++) {
                if (plansza[i][j] == plansza[i][j - 1]) licznik++;
                else break;
            }
            if (licznik == size) {
                *zwyciezca = plansza[i][0];
                return;
            }
        }
    }

    // Sprawdzenie kolumn
    for (int i = 0; i < size; i++) {
        if (plansza[0][i] != ' ') {
            licznik = 1;
            for (int j = 1; j < size; j++) {
                if (plansza[j][i] == plansza[j - 1][i]) licznik++;
                else break;
            }
            if (licznik == size) {
                *zwyciezca = plansza[0][i];
                return;
            }
        }
    }

    // Sprawdzenie przekątnych
    // Od lewego górnego do prawego dolnego
    if (plansza[0][0] != ' ') {
        licznik = 1;
        for (int i = 1; i < size; i++) {
            if (plansza[i][i] == plansza[i - 1][i - 1]) licznik++;
            else break;
        }
        if (licznik == size) {
            *zwyciezca = plansza[0][0];
            return;
        }
    }

    // Od prawego górnego do lewego dolnego
    if (plansza[0][size - 1] != ' ') {
        licznik = 1;
        for (int i = 1; i < size; i++) {
            if (plansza[i][size - i - 1] == plansza[i - 1][size - i]) licznik++;
            else break;
        }
        if (licznik == size) {
            *zwyciezca = plansza[0][size - 1];
            return;
        }
    }

    // Sprawdzenie remisu
    int pusteMiejsca = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (plansza[i][j] == ' ') pusteMiejsca++;
        }
    }
    if (pusteMiejsca == 0) *zwyciezca = '\0';
}

class Engine {
public:
    void initialize(char** plansza, int size, int winCount) {
        this->plansza = plansza;
        this->field_count = size;
        this->winning_count = winCount;
    }

    int checkGameState() {
        int count1, count2;

        // Sprawdzenie wierszy i kolumn
        for (int i = 0; i < field_count; i++) {
            count1 = 1;
            count2 = 1;
            for (int j = 0; j < field_count - 1; j++) {
                if (plansza[i][j] != ' ') {
                    if (plansza[i][j] == plansza[i][j + 1]) count1++;
                    else count1 = 1;
                    if (count1 == winning_count) return plansza[i][j] == 'X' ? 1 : 2;
                }
                else count1 = 1;

                if (plansza[j][i] != ' ') {
                    if (plansza[j][i] == plansza[j + 1][i]) count2++;
                    else count2 = 1;
                    if (count2 == winning_count) return plansza[j][i] == 'X' ? 1 : 2;
                }
                else count2 = 1;
            }
        }

        // Sprawdzenie przekątnych
        for (int i = field_count - winning_count; i >= 0; i--) {
            count1 = 1;
            count2 = 1;
            for (int k = 0; k < field_count - i - 1; k++) {
                if (plansza[i + k][k] != ' ') {
                    if (plansza[i + k][k] == plansza[i + k + 1][k + 1]) count1++;
                    else count1 = 1;
                    if (count1 == winning_count) return plansza[i + k][k] == 'X' ? 1 : 2;
                }
                else count1 = 1;

                if (plansza[k][i + k] != ' ') {
                    if (plansza[k][i + k] == plansza[k + 1][i + k + 1]) count2++;
                    else count2 = 1;
                    if (count2 == winning_count) return plansza[k][i + k] == 'X' ? 1 : 2;
                }
                else count2 = 1;
            }
        }

        // Sprawdzenie remisu
        for (int i = 0; i < field_count; i++) {
            for (int j = 0; j < field_count; j++) {
                if (plansza[i][j] == ' ') return -1; // Gra trwa
            }
        }
        return 0; // Remis
    }

    int minMax(int depth, int alpha, int beta, bool isMaximizingPlayer) {
        int winner = checkGameState();

        if (winner == 1) return -10000 - depth;
        if (winner == 2) return 10000 + depth;
        if (winner == 0) return 0 - depth;

        if (depth == 0) return 0;  // Funkcja oceny usunięta dla prostoty

        if (isMaximizingPlayer) {
            int bestScore = INT_MIN;
            for (int i = 0; i < field_count; ++i) {
                for (int j = 0; j < field_count; ++j) {
                    if (plansza[i][j] == ' ') {
                        plansza[i][j] = 'O';
                        int score = minMax(depth - 1, alpha, beta, false);
                        plansza[i][j] = ' ';
                        bestScore = max(score, bestScore);
                        alpha = max(alpha, score);
                        if (beta <= alpha) break;
                    }
                }
            }
            return bestScore;
        }
        else {
            int bestScore = INT_MAX;
            for (int i = 0; i < field_count; ++i) {
                for (int j = 0; j < field_count; ++j) {
                    if (plansza[i][j] == ' ') {
                        plansza[i][j] = 'X';
                        int score = minMax(depth - 1, alpha, beta, true);
                        plansza[i][j] = ' ';
                        bestScore = min(score, bestScore);
                        beta = min(beta, score);
                        if (beta <= alpha) break;
                    }
                }
            }
            return bestScore;
        }
    }

    pair<int, int> best_move(int depth, bool isMaximizingPlayer) {
        int bestScore = INT_MIN;
        pair<int, int> bestMove = { -1, -1 };
        for (int i = 0; i < field_count; ++i) {
            for (int j = 0; j < field_count; ++j) {
                if (plansza[i][j] == ' ') {
                    plansza[i][j] = 'O';
                    int score = minMax(depth, INT_MIN, INT_MAX, false);
                    plansza[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = { i, j };
                    }
                }
            }
        }
        return bestMove;
    }

private:
    char** plansza;
    int field_count;
    int winning_count;
};

int main() {
    int size;
    cout << "Podaj rozmiar planszy: ";
    cin >> size;

    char** plansza = new char*[size];
    for(int i = 0; i < size; i++){
        plansza[i] = new char[size];
        for(int j = 0; j < size; j++){
            plansza[i][j] = ' ';
        }
    }

    int winning_count;
    cout << "Podaj liczbę znaków w rzędzie do wygrania: ";
    cin >> winning_count;

    Engine silnik;
    silnik.initialize(plansza, size, winning_count);
    char zwyciezca = ' ';
    bool czyGracz1 = true;

    while(zwyciezca == ' ') {
        wyswietlPlansze(plansza, size);
        if(czyGracz1){
            int x, y;
            cout << "Ruch gracza 1 (X): ";
            cin >> x >> y;
            if (x >= 0 && x < size && y >= 0 && y < size) {
                if (plansza[x][y] == ' ') {
                    plansza[x][y] = 'X';
                    czyGracz1 = false;
                }
                else {
                    cout << "Nieprawidłowy ruch! Spróbuj ponownie.\n";
                }
            }
            else {
                cout << "Nieprawidłowy ruch! Spróbuj ponownie.\n";
            }
        }
        else {
            cout << "Ruch gracza 2 (O): \n";
            pair<int, int> ruch = silnik.best_move(size * size, true);
            plansza[ruch.first][ruch.second] = 'O';
            czyGracz1 = true;
        }
        znajdzZwyciezce(plansza, size, &zwyciezca);
        if (zwyciezca == '\0') {
            cout << "Remis!\n";
            break;
        }
        else if (zwyciezca != ' ') {
            cout << "Zwyciezca: " << (zwyciezca == 'X' ? "Gracz 1" : "Gracz 2") << "!\n";
            break;
        }
    }

    for(int i=0;i<size;i++) delete[] plansza[i];
    delete[] plansza;
    return 0;
}

