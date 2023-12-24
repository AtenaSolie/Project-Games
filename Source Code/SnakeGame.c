#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_SCORES 5

struct Score {
    char name[20];
    int score;
};

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

void setup();  // Function declaration
void displayLeaderboard();
void searchPlayerScore();
void draw();
void input();
void logic();
void updateLeaderboard();

void startMenu() {
    printf("==== Snake Game ====\n");
    printf("1. Start Game\n");
    printf("2. Display Leaderboard\n");
    printf("3. Search Player Score\n");
    printf("4. Exit\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            setup();
            while (!gameover) {
                draw();
                input();
                logic();
            }
            updateLeaderboard();
            break;
        case 2:
            displayLeaderboard();
            break;
        case 3:
            searchPlayerScore();
            break;
        case 4:
            gameover = 1;
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            gameover = 1;
    }
}

void searchPlayerScore() {
    char searchName[20];
    printf("Enter a name to search: ");
    scanf("%s", searchName);

    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        printf("No leaderboard entries yet.\n");
        return;
    }

    struct Score playerScore;
    int found = 0;

    while (fscanf(file, "%s %d", playerScore.name, &playerScore.score) != EOF) {
        if (strcmp(searchName, playerScore.name) == 0) {
            printf("Found: %s\t%d\n", playerScore.name, playerScore.score);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Name not found in the leaderboard.\n");
    }

    getch();
}

void setup() {
    gameover = 0;
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 20;
    if (fruity == 0)
        goto label2;
    score = 0;
}

void draw() {
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    printf("score = %d\n", score);
    printf("press X to quit the game\n");
}

void input() {
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    sleep(0.01);
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x >= height || y < 0 || y >= width)
        gameover = 1;

    if (x == fruitx && y == fruity) {
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;

    label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        score += 10;
    }
}

void updateLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        printf("Error opening the leaderboard file.\n");
        return;
    }

    struct Score newScore;
    printf("Enter your name: ");
    scanf("%s", newScore.name);
    newScore.score = score;

    fprintf(file, "%s %d\n", newScore.name, newScore.score);
    fclose(file);
}

void displayLeaderboard() {
    int i;
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        printf("No leaderboard entries yet.\n");
        return;
    }

    struct Score scores[MAX_SCORES];
    int count = 0;

    while (fscanf(file, "%s %d", scores[count].name, &scores[count].score) != EOF && count < MAX_SCORES) {
        count++;
    }

    fclose(file);

    printf("\nLeaderboard:\n");
    printf("Name\tScore\n");
    for (i = 0; i < count; i++) {
        printf("%s\t%d\n", scores[i].name, scores[i].score);
    }

    // Sorting the leaderboard entries based on scores (descending order)
    for (i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (scores[i].score < scores[j].score) {
                struct Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // Displaying the sorted leaderboard
    printf("\nSorted Leaderboard:\n");
    printf("Name\tScore\n");
    for (i = 0; i < count; i++) {
        printf("%s\t%d\n", scores[i].name, scores[i].score);
    }

    getch();
}

int main() {
    int m, n;

    startMenu();

    return 0;
}