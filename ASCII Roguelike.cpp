#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

struct Player {
    int x, y;
    int score = 0;
};

struct Enemy {
    int x, y;
};

struct Item {
    int x, y;
    bool collected = false;
};

void draw(const Player& player, const Enemy& enemy, const vector<Item>& items) {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == player.y && j == player.x)
                cout << '@';
            else if (i == enemy.y && j == enemy.x)
                cout << 'E';
            else {
                bool printed = false;
                for (auto& item : items) {
                    if (!item.collected && item.x == j && item.y == i) {
                        cout << '*';
                        printed = true;
                        break;
                    }
                }
                if (!printed)
                    cout << '.';
            }
        }
        cout << '\n';
    }
    cout << "Score: " << player.score << "\n";
}

bool isGameOver(const Player& player, const Enemy& enemy) {
    return player.x == enemy.x && player.y == enemy.y;
}

int main() {
    srand(time(0));
    Player player{ WIDTH / 2, HEIGHT / 2 };
    Enemy enemy{ rand() % WIDTH, rand() % HEIGHT };

    vector<Item> items;
    for (int i = 0; i < 5; i++)
        items.push_back({ rand() % WIDTH, rand() % HEIGHT });

    while (true) {
        draw(player, enemy, items);
        if (isGameOver(player, enemy)) {
            cout << "Game Over! Last score: " << player.score << "\n";
            break;
        }

        char move = _getch();
        switch (move) {
        case 'w': if (player.y > 0) player.y--; break;
        case 's': if (player.y < HEIGHT - 1) player.y++; break;
        case 'a': if (player.x > 0) player.x--; break;
        case 'd': if (player.x < WIDTH - 1) player.x++; break;
        case 'q': return 0;
        }

        for (auto& item : items) {
            if (!item.collected && item.x == player.x && item.y == player.y) {
                item.collected = true;
                player.score += 5;
            }
        }

        if (enemy.x < player.x) enemy.x++;
        else if (enemy.x > player.x) enemy.x--;
        if (enemy.y < player.y) enemy.y++;
        else if (enemy.y > player.y) enemy.y--;

        player.score++;
    }

    return 0;
}
