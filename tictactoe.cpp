#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Engine {
public:
    void initialize(char** plansza, int field_count, int winning_count) {
        this->plansza = plansza;
        this->field_count = field_count;
        this->winning_count = winning_count;
    }

    int checkGameState() {
        for (int i = 0; i < field_count; i++) {
            for (int j = 0; j < field_count; j++) {
                if (plansza[i][j] == ' ') continue;

                // Sprawdzenie w poziomie
                if (j <= field_count - winning_count) {
                    bool win = true;
                    for (int k = 0; k < winning_count; k++) {
                        if (plansza[i][j] != plansza[i][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return plansza[i][j];
                }

                // Sprawdzenie w pionie
                if (i <= field_count - winning_count) {
                    bool win = true;
                    for (int k = 0; k < winning_count; k++) {
                        if (plansza[i][j] != plansza[i + k][j]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return plansza[i][j];
                }

                // Sprawdzenie przekątnej w dół
                if (i <= field_count - winning_count && j <= field_count - winning_count) {
                    bool win = true;
                    for (int k = 0; k < winning_count; k++) {
                        if (plansza[i][j] != plansza[i + k][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return plansza[i][j];
                }

                // Sprawdzenie przekątnej w górę
                if (i >= winning_count - 1 && j <= field_count - winning_count) {
                    bool win = true;
                    for (int k = 0; k < winning_count; k++) {
                        if (plansza[i][j] != plansza[i - k][j + k]) {
                            win = false;
                            break;
                        }
                    }
                    if (win) return plansza[i][j];
                }
            }
        }

        for (int i = 0; i < field_count; i++) {
            for (int j = 0; j < field_count; j++) {
                if (plansza[i][j] == ' ') return -1;
            }
        }
        return 0;
    }

    int estimate() {
        int score = 0;
        for (int i = 0; i < field_count; ++i) {
            for (int j = 0; j < field_count; ++j) {
                if (plansza[i][j] == 'O') {
                    if (j <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i][j + k] == 'O') {
                                count++;
                            }
                        }
                        if (count == winning_count) score += 10;
                        else if (count == winning_count - 1) score += 5;
                    }

                    if (i <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i + k][j] == 'O') {
                                count++;
                            }
                        }
                        if (count == winning_count) score += 10;
                        else if (count == winning_count - 1) score += 5;
                    }

                    if (i <= field_count - winning_count && j <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i + k][j + k] == 'O') {
                                count++;
                            }
                        }
                        if (count == winning_count) score += 10;
                        else if (count == winning_count - 1) score += 5;
                    }
                } else if (plansza[i][j] == 'X') {
                    if (j <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i][j + k] == 'X') {
                                count++;
                            }
                        }
                        if (count == winning_count) score -= 10;
                        else if (count == winning_count - 1) score -= 5;
                    }

                    if (i <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i + k][j] == 'X') {
                                count++;
                            }
                        }
                        if (count == winning_count) score -= 10;
                        else if (count == winning_count - 1) score -= 5;
                    }

                    if (i <= field_count - winning_count && j <= field_count - winning_count) {
                        int count = 0;
                        for (int k = 0; k < winning_count; ++k) {
                            if (plansza[i + k][j + k] == 'X') {
                                count++;
                            }
                        }
                        if (count == winning_count) score -= 10;
                        else if (count == winning_count - 1) score -= 5;
                    }
                }
            }
        }
        return score;
    }

    int minMax(int depth, int alpha, int beta, bool isMaximizingPlayer) {
        int winner = checkGameState();

        if (winner == 'X') return -10000 - depth;
        if (winner == 'O') return 10000 + depth;
        if (winner == 0) return 0 - depth;

        if (depth == 0) return estimate();

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
        } else {
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

    pair<int, int> bestMove(int depth, bool isMaximizingPlayer) {
        int bestScore = INT_MIN;
        pair<int, int> bestMove;

        for (int i = 0; i < field_count; ++i) {
            for (int j = 0; j < field_count; ++j) {
                if (plansza[i][j] == ' ') {
                    plansza[i][j] = 'O';
                    int score = minMax(depth - 1, INT_MIN, INT_MAX, false);
                    plansza[i][j] = ' ';
                    if (score > bestScore) {
                        bestScore = score;
                        bestMove = {i, j};
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

void wyswietlPlansze(char** plansza, int field_count) {
    for (int i = 0; i < field_count; ++i) {
        for (int j = 0; j < field_count; ++j) {
            cout << " " << plansza[i][j] << " ";
            if (j < field_count - 1) cout << "|";
        }
        cout << endl;
        if (i < field_count - 1) {
            for (int j = 0; j < field_count; ++j) {
                cout << "---";
                if (j < field_count - 1) cout << "+";
            }
            cout << endl;
        }
    }
}

void znajdzZwyciezce(char** plansza, int field_count, char* zwyciezca) {
    for (int i = 0; i < field_count; i++) {
        for (int j = 0; j < field_count; j++) {
            if (plansza[i][j] == ' ') continue;

            // Sprawdzenie w poziomie
            if (j <= field_count - 3) {
                if (plansza[i][j] == plansza[i][j + 1] && plansza[i][j] == plansza[i][j + 2]) {
                    *zwyciezca = plansza[i][j];
                    return;
                }
            }

            // Sprawdzenie w pionie
            if (i <= field_count - 3) {
                if (plansza[i][j] == plansza[i + 1][j] && plansza[i][j] == plansza[i + 2][j]) {
                    *zwyciezca = plansza[i][j];
                    return;
                }
            }

            // Sprawdzenie przekątnej w dół
            if (i <= field_count - 3 && j <= field_count - 3) {
                if (plansza[i][j] == plansza[i + 1][j + 1] && plansza[i][j] == plansza[i + 2][j + 2]) {
                    *zwyciezca = plansza[i][j];
                    return;
                }
            }

            // Sprawdzenie przekątnej w górę
            if (i >= 2 && j <= field_count - 3) {
                if (plansza[i][j] == plansza[i - 1][j + 1] && plansza[i][j] == plansza[i - 2][j + 2]) {
                    *zwyciezca = plansza[i][j];
                    return;
                }
            }
        }
    }
}

int main() {
    int field_count;
    cout << "Podaj rozmiar planszy: ";
    cin >> field_count;

    char** plansza = new char*[field_count];
    for (int i = 0; i < field_count; ++i) {
        plansza[i] = new char[field_count];
        for (int j = 0; j < field_count; ++j) {
            plansza[i][j] = ' ';
        }
    }

    Engine engine;
    engine.initialize(plansza, field_count, 3);

    wyswietlPlansze(plansza, field_count);

    char zwyciezca = ' ';
    bool isPlayerX = true;
    while (zwyciezca == ' ') {
        int x, y;
        if (isPlayerX) {
            cout << "Ruch gracza X: ";
            cin >> x >> y;
            if (x < 0 || x >= field_count || y < 0 || y >= field_count || plansza[x][y] != ' ') {
                cout << "Nieprawidlowy ruch. Sprobuj ponownie." << endl;
                continue;
            }
            plansza[x][y] = 'X';
        } else {
            cout << "Ruch komputera O: ";
            pair<int, int> bestMove = engine.bestMove(10, true);
            x = bestMove.first;
            y = bestMove.second;
            plansza[x][y] = 'O';
            cout << x << " " << y << endl;
        }

        wyswietlPlansze(plansza, field_count);
        znajdzZwyciezce(plansza, field_count, &zwyciezca);
        isPlayerX = !isPlayerX;
    }

    if (zwyciezca == 'X') cout << "Gracz X wygrywa!" << endl;
    else if (zwyciezca == 'O') cout << "Komputer O wygrywa!" << endl;
    else cout << "Remis!" << endl;

    for (int i = 0; i < field_count; ++i) {
        delete[] plansza[i];
    }
    delete[] plansza;

    return 0;
}
