/* =============================================================
   SECTION: HEADERS & CONSTANTS
   ============================================================= */
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_Q 30
#define TIME_LIMIT 60

/* =============================================================
   SECTION: DATA STRUCTURES
   ============================================================= */
typedef struct {
  char q[300], opts[4][100];
  int correct;
} Question;

// Function Prototypes
void startTest(char *topic, char *file);
int loadQuestions(char *file, Question list[]);
void hideCursor();

/* =============================================================
   SECTION: UTILITY FUNCTIONS (UI & SYSTEM)
   ============================================================= */
void hideCursor() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO info;
  info.dwSize = 100;
  info.bVisible = FALSE;
  SetConsoleCursorInfo(consoleHandle, &info);
}

/* =============================================================
   SECTION: MAIN ENTRY POINT (MENU LOGIC)
   ============================================================= */
int main() {
  int choice;
  hideCursor();       // Hide the blinking cursor
  system("color 3F"); // Aqua Text on White Background

  while (1) {
    system("cls"); // Clear screen
    printf("\n========================================\n");
    printf("      APTITUDE ASSESSMENT SYSTEM       \n");
    printf("========================================\n");
    printf(" 1. C Language\n 2. Python\n 3. Java\n 4. Web Tech\n 5. General "
           "Aptitude\n 0. Exit\n");
    printf("========================================\n");
    printf(" Enter Choice: ");
    scanf("%d", &choice);

    // Menu Routing
    if (choice == 0)
      exit(0);
    else if (choice == 1)
      startTest("C Language", "questions/c.txt");
    else if (choice == 2)
      startTest("Python", "questions/python.txt");
    else if (choice == 3)
      startTest("Java", "questions/java.txt");
    else if (choice == 4)
      startTest("Web Tech", "questions/web.txt");
    else if (choice == 5)
      startTest("Gen. Aptitude", "questions/aptitude.txt");
    else {
      printf("\n Invalid Choice!");
      Sleep(1000);
    }
  }
  return 0;
}

/* =============================================================
   SECTION: FILE ACCESS (LOADING DATA)
   ============================================================= */
int loadQuestions(char *file, Question list[]) {
  FILE *fp = fopen(file, "r");
  if (!fp)
    return 0; // Error opening file

  int n = 0;
  char buffer[300];

  // Read Loop
  while (n < MAX_Q && fgets(buffer, 300, fp)) {
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline
    strcpy(list[n].q, buffer);

    for (int i = 0; i < 4; i++) {
      fgets(list[n].opts[i], 100, fp);
      list[n].opts[i][strcspn(list[n].opts[i], "\n")] = 0;
    }

    fscanf(fp, "%d\n", &list[n].correct);
    fgets(buffer, 300, fp); // Skip separator block
    n++;
  }
  fclose(fp);
  return n;
}

/* =============================================================
   SECTION: TEST ENGINE (INPUT & OUTPUT LOGIC)
   ============================================================= */
void startTest(char *topic, char *file) {
  Question list[MAX_Q];
  // Step 1: Load Data
  int ans[MAX_Q] = {0}, n = loadQuestions(file, list);

  if (n == 0) {
    printf("\n No questions found!");
    Sleep(2000);
    return;
  }

  // Step 2: Game Loop
  for (int i = 0; i < n; i++) {
    system("cls");
    // --- OUTPUT: Display Question ---
    printf("=== %s (Q%d/%d) ===\n\n%s\n\n", topic, i + 1, n, list[i].q);
    for (int j = 0; j < 4; j++)
      printf(" %d. %s\n", j + 1, list[i].opts[j]);

    printf("\n Select Option (1-4) and Press ENTER\n");
    printf(" Your Selection: [ ]");

    int timeLeft = TIME_LIMIT * 10;
    int selection = 0;
    ans[i] = -1;

    // --- INPUT: Timer & Key Handler ---
    while (timeLeft > 0) {
      printf("\r Time Left: %02d sec | Your Selection: [%c]",
             (timeLeft + 9) / 10, selection ? selection + '0' : ' ');

      if (_kbhit()) {
        char ch = _getch();
        if (ch >= '1' && ch <= '4') {
          selection = ch - '0';  // Store Selection
        } else if (ch == '\r') { // ENTER Key
          if (selection != 0) {
            ans[i] = selection;
            break; // Confirm and Next
          }
        } else if (ch == '\b') { // BACKSPACE Key
          selection = 0;
        }
      }
      Sleep(100);
      timeLeft--;
    }

    if (ans[i] == -1 && timeLeft <= 0) {
      printf("\n Time's Up!");
      Sleep(1000);
    } else if (ans[i] == -1)
      return;
  }

  // --- OUTPUT: Results Calculation ---
  int score = 0;
  for (int i = 0; i < n; i++)
    if (ans[i] == list[i].correct)
      score++;

  system("cls");
  printf("\n================ RESULT ================\n");
  printf(" Score: %d / %d (%.1f%%)\n", score, n, (float)score * 100 / n);
  printf("========================================\n");

  printf("\n Press '1' to see wrong answers, or any key to Menu... \n");
  if (_getch() == '1') {
    for (int i = 0; i < n; i++) {
      if (ans[i] != list[i].correct) {
        printf("\n Q%d: %s\n Correct: %s\n", i + 1, list[i].q,
               list[i].opts[list[i].correct - 1]);
      }
    }
    printf("\n Press any key to Menu...");
    _getch();
  }
}
