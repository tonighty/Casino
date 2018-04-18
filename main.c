#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define STARTMONEY 500
#define SCREENROWS 29
#define SCREENCOLUMS 73

typedef enum consolecolor
{
    ConsoleColor_Black,
    ConsoleColor_DarkBlue,
    ConsoleColor_DarkGreen,
    ConsoleColor_DarkCyan,
    ConsoleColor_DarkRed,
    ConsoleColor_DarkMagenta,
    ConsoleColor_DarkYellow,
    ConsoleColor_Gray,
    ConsoleColor_DarkGray,
    ConsoleColor_Blue,
    ConsoleColor_Green,
    ConsoleColor_Cyan,
    ConsoleColor_Red,
    ConsoleColor_Magenta,
    ConsoleColor_Yellow,
    ConsoleColor_White
} ConsoleColor;

typedef struct consolesymboldata
{
    char symbol;
    ConsoleColor symbolColor;
    ConsoleColor backgroundColor;
} ConsoleSymbolData;

ConsoleSymbolData backBuffer[SCREENROWS][SCREENCOLUMS];
ConsoleSymbolData screenBuffer[SCREENROWS][SCREENCOLUMS];

char userName[21];
int money = 500;
char strMoney[21];
HANDLE hConsole;

int numbers[] = {0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13, 36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14, 31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26};

void ShowMainMenu();

void CreateAccount();

int LogIn();

void ShowListOfUsers();

void SlotMachine();

void DrawBetChooseByState(int state);

void Roullete();

void ShowGameMenu();

void CasinoEpta();

void CleanDisplay();

void SetConsoleCursor(int x, int y);

void RenderSystemFlush();

void RenderSystemInitialize();

void RenderSystemClear();

void RenderSystemDrawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);

void RenderSystemDrawText(int r, int c, const char *text, ConsoleColor symbolColor, ConsoleColor backgroundColor);

void DrawRoulleteWheel(int key);

void DrawMainMenuByState(int state);

void DrawGameManuByState(int state);

int Input(char* msg, int x, int y);

ConsoleColor GetColor(int k);

int IsCorrectAnswer(char c)
{
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5') return 1;
    return 0;
}

int main()
{
    FILE *tmp = fopen("users.txt", "a+");
    fclose(tmp);

    system("title CASINO EPT");
    system("mode con:cols=74 lines=30");
    RenderSystemInitialize();
    RenderSystemClear();

    while (1)
        ShowMainMenu();
    return 0;
}

void ShowMainMenu()
{
    int state = 0;

    int row = 0;

    RenderSystemDrawText(row++, 0, ".-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                            CASINO EPTA 777                            |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                            HELLO EPTA                                 |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "!                                                                       !",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ":                             LOG IN                                    :",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ":                             SIGN UP                                   :",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ".                             LIST OF USERS                             .",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ":                             EXIT                                      :",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ":                                                                       :",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "!                                                                       !",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, ".                                                                       .",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "|                                                                       |",
                         ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(row++, 0, "`-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Majorov-'",
                         ConsoleColor_White, ConsoleColor_Black);

    DrawMainMenuByState(0);

    RenderSystemFlush();

    char answer = '0';
    //    while(!IsCorrectAnswer(answer = getch()));
    //
    //    if (answer == '1')
    //    {
    //        if(LogIn())
    //            ShowGameMenu();
    //    }
    //    else if (answer == '2') CreateAccount();
    //    else if (answer == '3') ShowListOfUsers();
    //    else if (answer == '4') exit(0);
    //    else if (answer == '5') CleanDisplay();
    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 4;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 3 : state - 1;
        }
        DrawMainMenuByState(state);
    }
    if (state == 0)
    {
        if (LogIn())
            ShowGameMenu();
    }
    else if (state == 1) CreateAccount();
    else if (state == 2) ShowListOfUsers();
    else if (state == 3) exit(0);
}
//прет солнышко

void DrawMainMenuByState(int state)
{
    RenderSystemDrawText(7,  30, "LOG IN",        ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(8,  30, "SIGN UP",       ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9,  30, "LIST OF USERS", ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(10, 30, "EXIT",          ConsoleColor_White, state == 3 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

//Список игроков
void ShowListOfUsers()
{
    FILE *users = fopen("users.txt", "r");

    CleanDisplay();

    RenderSystemDrawText(3, 27, "LIST OF USERS:", ConsoleColor_Blue, ConsoleColor_Black);

    int raw = 5;
    while (!feof(users) && (raw < 25))
    {
        char money[21];

        fscanf(users, "%s %s", userName, money);

        if (userName[0] == '\n') break;

        RenderSystemDrawText(raw, 23, userName, 9 + (raw % 4), ConsoleColor_Black);
        RenderSystemDrawText(raw, 42, "$", ConsoleColor_Yellow, ConsoleColor_Black);
        RenderSystemDrawText(raw, 43, money, 9 + (raw % 4), ConsoleColor_Black);

        raw++;
    }

    RenderSystemDrawText(27, 22, "PRESS ANY KEY TO MAIN MENU", ConsoleColor_Cyan, ConsoleColor_Black);

    RenderSystemFlush();

    getch();
}

void CreateAccount()
{
    FILE *users = fopen("users.txt", "a+");

    CleanDisplay();

    RenderSystemDrawText(6, 29, "CREATING ACCOUNT", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(9, 27, "ENTER YOUR USERNAME", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(10, 29, "MAX - 20 LETTERS", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(11, 29, "MIN -  5 LETTERS", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(13, 20, "USERNAME:", ConsoleColor_White, ConsoleColor_Black);

    RenderSystemFlush();

    do
    {
        SetConsoleCursor(13, 30);

        scanf("%s", userName);

        RenderSystemDrawText(13, 30, userName, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();

        if (strlen(userName) < 5)
        {
            RenderSystemDrawText(13, 30, "                   ", ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawText(16, 27, "TUPOI SHTOLE?", ConsoleColor_White, ConsoleColor_Black);

            RenderSystemFlush();
        }
    }
    while (strlen(userName) < 5);

    RenderSystemFlush();

    fprintf(users, "%s %d\n", userName, STARTMONEY);
    fclose(users);
}

int LogIn()
{
    CleanDisplay();
    SetConsoleCursor(29, 6);

    RenderSystemDrawText(6, 29, "LOGING IN", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(8, 24, "ENTER YOUR USERNAME", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(10, 26, "MAX - 20 LETTERS", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(11, 26, "MIN -  5 LETTERS", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(11, 26, "MIN -  5 LETTERS", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(13, 17, "USERNAME:", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(27, 20, "TYPE EXIT TO MAINMENU", ConsoleColor_White, ConsoleColor_Black);

    RenderSystemFlush();

    while (1)
    {
        SetConsoleCursor(13, 27);

        FILE *users = fopen("users.txt", "r");
        char userNameFromFile[21];

        scanf("%s", userName);

        RenderSystemDrawText(13, 27, userName, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();

        if (!strcmp(userName, "EXIT") || !strcmp(userName, "exit")) return 0;

        while (!(feof(users)))
        {
            fscanf(users, "%s %d", userNameFromFile, &money);

            if (userNameFromFile[0] == '\n') return 0;

            if (!strcmp(userName, userNameFromFile))
            {
                fscanf(users, "%d", &money);
                return 1;
            }
        }

        RenderSystemDrawText(13, 27, "                   ", ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(16, 27, "NO SUCH USER, EPTA", ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();
    }
}

void ShowGameMenu()
{
    while (1)
    {
        int state = 0;

        CleanDisplay();

        RenderSystemDrawText(6, 29, "WELCOME BLYA", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(8, 27, "USER:", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(8, 33, userName, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(9, 27, "BALANCE:", ConsoleColor_White, ConsoleColor_Black);
        SetConsoleCursor(29, 6);
        sprintf(strMoney, "%d", money);
        RenderSystemDrawText(9, 36, strMoney, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(11, 27, "CHOOSE THE GAME:", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(13, 27, "ROULETTE", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(14, 27, "SLOT MACHINE", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(15, 27, "CHO TO", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(16, 27, "GO V BAR BUHAT'? GO!", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(17, 27, "EXIT AND SAVE", ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();

        DrawGameManuByState(0);

        char answer;

        while ((answer = getch()) != 13)
        {
            if (answer == 80)
            {
                state = (state + 1) % 5;
            }
            else if (answer == 72)
            {
                state = state == 0 ? 4 : state - 1;
            }
            DrawGameManuByState(state);
        }

        if      (state == 0) Roullete();
        else if (state == 1) SlotMachine();
        else if (state == 2);
        else if (state == 3);
        else if (state == 4)
        {
            FILE *users = fopen("users.txt", "r+");

            char userNameFromFile[21];

            while (!(feof(users)))
            {
                fscanf(users, "%s", userNameFromFile);
                if (userNameFromFile[0] == '\n') return;
                if (!strcmp(userName, userNameFromFile))
                {
                    fprintf(users, " %d ", money);
                    return;
                }
                while (fgetc(users) != '\n');
            }
        }
    }
}

void DrawGameManuByState(int state)
{

    RenderSystemDrawText(13, 27, "ROULETTE",             ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(14, 27, "SLOT MACHINE",         ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(15, 27, "CHO TO",               ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(16, 27, "GO V BAR BUHAT'? GO!", ConsoleColor_White, state == 3 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(17, 27, "EXIT AND SAVE",        ConsoleColor_White, state == 4 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);


    RenderSystemFlush();
}

void SlotMachine()
{
    int bet = 50;

    char panel1 = 'X';
    char panel2 = 'X';
    char panel3 = 'X';

    int youWon = 0;

    srand(time(0));

    CleanDisplay();

    while (1)
    {
        RenderSystemDrawText(3, 4, "USER:", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(3, 10, userName, ConsoleColor_White, ConsoleColor_Black);

        char strMoney[21];
        sprintf(strMoney, "%d", money);

        RenderSystemDrawText(4, 4, "BALANCE: $", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(4, 14, "                    ", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(4, 14, strMoney, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(7, 23,        ".-------.",            ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(8, 20,     "oO{-JACKPOT-}Oo",         ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(9, 20,     ".=============. __",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(10, 20,    "| |X| |X| |X| |(  )",     ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(11, 20,    "| [X] [X] [X] | ||",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(12, 20,    "| |X| |X| |X| | ||",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(13, 20,    "|             |_||",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(14, 20,    "| #$# ::x2::  |--'",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(15, 20,    "| &#& ::x2::  |    ",     ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(16, 20,    "| $$$ ::x3::  |    ",     ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(17, 20,    "|             |    ",     ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(18, 20,    "|      __ === |    ",     ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(19, 20,    "|_____/__\\____|",        ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(20, 19,   "/###############\\",       ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(21, 18,  "/#################\\",      ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(22, 17, "|###################|",      ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(27, 20, "ENTER YOUR BET OR TYPE 0 TO LEAVE", ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(14, 44, "BET: $           ", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(16, 44, "YOU WON: $", ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawChar(10, 23, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(10, 27, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(10, 31, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawChar(11, 23, panel1, ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(11, 27, panel2, ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(11, 31, panel3, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawChar(12, 23, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(12, 27, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawChar(12, 31, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();

        SetConsoleCursor(14, 50);

        scanf("%d", &bet);

        char strBet[21];

        sprintf(strBet, "%d", bet);
        RenderSystemDrawText(14, 50, strBet, ConsoleColor_White, ConsoleColor_Blue);


        if (bet == 0) return;

        int doubleBonus = bet * 2;
        int tripleBonus = bet * 3;

        int i = 0;
        while (i++ < 5)
        {
            RenderSystemDrawText(7, 23,        ".-------.",            ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(8, 20,     "oO{-JACKPOT-}Oo",         ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(9, 20,     ".=============.   ",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(10, 20,    "| |X| |X| |X| |    ",     ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(11, 20,    "| [X] [X] [X] |   ",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(12, 20,    "| |X| |X| |X| |   ",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(13, 20,    "|             |__ ",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(14, 20,    "| #$# ::x2::  |_ |",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(15, 20,    "| &#& ::x2::  | ||",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(16, 20,    "| $$$ ::x3::  | ||",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(17, 20,    "|             |(__)",     ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(18, 20,    "|      __ === |",         ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(19, 20,    "|_____/__\\____|",        ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(20, 19,   "/###############\\",       ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(21, 18,  "/#################\\",      ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawText(22, 17, "|###################|",      ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawChar(10, 23, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(10, 27, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(10, 31, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawChar(11, 23, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(11, 27, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(11, 31, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawChar(12, 23, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(12, 27, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);
            RenderSystemDrawChar(12, 31, 35 + (rand() % 4), ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawText(3, 55, "LOH",      ConsoleColor_White, ConsoleColor_Black);

            RenderSystemDrawText(16, 44, "YOU WON: $          ", ConsoleColor_White, ConsoleColor_Black);

            RenderSystemFlush();

            Sleep(200);
        }

        RenderSystemDrawText(3, 55, "   ",      ConsoleColor_White, ConsoleColor_Black);

        money -= bet;

        panel1 = 35 + (rand() % 4);
        panel2 = 35 + (rand() % 4);
        panel3 = 35 + (rand() % 4);

        if ((panel1 == panel2) && (panel1 == panel3))
        {
            money += tripleBonus;
            youWon = tripleBonus;
        }
        else if ((panel1 == panel2) || (panel1 == panel3) || (panel2 == panel3))
        {
            money += doubleBonus;
            youWon = doubleBonus;
        }
        else youWon = 0;

        char strYouWon[50];

        sprintf(strYouWon, "%d", youWon);
        RenderSystemDrawText(16, 54, strYouWon, ConsoleColor_White, ConsoleColor_Black);
    }
}

void CleanBetChooseMenu()
{
    for (int i = 6; i < 20; i++)
    {
        RenderSystemDrawText(i, 50, "                   ", ConsoleColor_White, ConsoleColor_Black);
    }
    RenderSystemFlush();
}

void GoToStaightUp(int *chislo, int *bet)
{
    CleanBetChooseMenu();

    while ((*chislo = Input("VVEDI CHISLO:", 6, 50)) > 36);

    *bet = Input("VVEDI BET:", 10, 50);
}
// <3 <3 <3

void DrawSmallBigMenuByState(int state)
{

    RenderSystemDrawText(8, 50, "1-18",  ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9, 50, "19-36", ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

void GoToSmallBig(int *isSmall, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawSmallBigMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 2;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 1 : state - 1;
        }
        DrawSmallBigMenuByState(state);
    }

    if (state == 0) *isSmall = 1;
    else *isSmall = 0;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawEvenOddMenuByState(int state)
{

    RenderSystemDrawText(8, 50, "EVEN", ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9, 50, "ODD",  ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}
// :***

void GoToEvenOdd(int *isEven, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawEvenOddMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 2;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 1 : state - 1;
        }
        DrawEvenOddMenuByState(state);
    }

    if (state == 0) *isEven = 1;
    else *isEven = 0;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawRedBlackMenuByState(int state)
{

    RenderSystemDrawText(8, 50, "RED",   ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9, 50, "BLACK", ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

void GoToRedBlack(int *isRed, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawRedBlackMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 2;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 1 : state - 1;
        }
        DrawRedBlackMenuByState(state);
    }

    if (state == 0) *isRed = 1;
    else *isRed = 0;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawColumnsMenuByState(int state)
{
    RenderSystemDrawText(8,  50, "FIRST",  ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);
    RenderSystemDrawText(9,  50, "SECOND", ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);
    RenderSystemDrawText(10, 50, "THIRD",  ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);

    RenderSystemFlush();
}

void GoToColumns(int *column, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawColumnsMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 3;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 2 : state - 1;
        }
        DrawColumnsMenuByState(state);
    }

    if (state == 0) *column = 1;
    else if (state == 1) *column = 2;
    else *column = 3;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawDozensMenuByState(int state)
{
    RenderSystemDrawText(8,  50, "FIRST 12",  ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);
    RenderSystemDrawText(9,  50, "SECOND 12", ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);
    RenderSystemDrawText(10, 50, "THIRD 12",  ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta :  ConsoleColor_Black);

    RenderSystemFlush();
}
// даж хз че написать
// помолчим....
// помолимся???

void GoToDozens(int *dozen, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawDozensMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 3;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 2 : state - 1;
        }
        DrawDozensMenuByState(state);
    }

    if (state == 0) *dozen = 1;
    else if (state == 1) *dozen = 2;
    else *dozen = 3;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawSixlineMenuByState(int state)
{
    RenderSystemDrawText(8,  50, "1 - 6",   ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9,  50, "4 - 9",   ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(10, 50, "7 - 12",  ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(11, 50, "10 - 15", ConsoleColor_White, state == 3 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(12, 50, "13 - 18", ConsoleColor_White, state == 4 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(13, 50, "16 - 21", ConsoleColor_White, state == 5 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(14, 50, "19 - 24", ConsoleColor_White, state == 6 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(15, 50, "22 - 27", ConsoleColor_White, state == 7 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(16, 50, "25 - 30", ConsoleColor_White, state == 8 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(17, 50, "28 - 33", ConsoleColor_White, state == 9 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(18, 50, "31 - 36", ConsoleColor_White, state == 10 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

void GoToSixline(int *line, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawSixlineMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 11;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 10 : state - 1;
        }
        DrawSixlineMenuByState(state);
    }

    *line = state + 1;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

void DrawStreetMenuByState(int state)
{
    RenderSystemDrawText(8,  50, "1 - 3",   ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9,  50, "4 - 6",   ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(10, 50, "7 - 9",   ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(11, 50, "10 - 12", ConsoleColor_White, state == 3 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(12, 50, "13 - 15", ConsoleColor_White, state == 4 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(13, 50, "16 - 18", ConsoleColor_White, state == 5 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(14, 50, "19 - 21", ConsoleColor_White, state == 6 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(15, 50, "22 - 24", ConsoleColor_White, state == 7 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(16, 50, "25 - 27", ConsoleColor_White, state == 8 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(17, 50, "28 - 30", ConsoleColor_White, state == 9 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(18, 50, "31 - 33", ConsoleColor_White, state == 10 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(19, 50, "34 - 36", ConsoleColor_White, state == 11 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

void GoToStreet(int *line, int *bet)
{
    CleanBetChooseMenu();

    char answer;
    int state = 0;

    DrawStreetMenuByState(0);

    while ((answer = getch()) != 13)
    {
        if (answer == 80)
        {
            state = (state + 1) % 12;
        }
        else if (answer == 72)
        {
            state = state == 0 ? 11 : state - 1;
        }
        DrawStreetMenuByState(state);
    }

    *line = state + 1;

    CleanBetChooseMenu();

    *bet = Input("VVEDI BET:", 8, 50);
}

int Input(char* msg, int x, int y)
{
    RenderSystemDrawText(x, y, "              ", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(x + 1, y, "              ", ConsoleColor_White, ConsoleColor_Black);
    RenderSystemDrawText(x, y, msg, ConsoleColor_White, ConsoleColor_Black);

    RenderSystemFlush();

    SetConsoleCursor(x + 1, y);

    int result;

    scanf("%d", &result);

    char strResult[21];

    sprintf(strResult, "%d", result);
    RenderSystemDrawText(x + 1, y, strResult, ConsoleColor_White, ConsoleColor_Blue);

    RenderSystemFlush();

    return result;
}

void Roullete()
{
    CleanDisplay();

    while (1)
    {
        RenderSystemDrawText(3, 50, "USER:", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(3, 57, userName, ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(4, 50, "BALANCE:", ConsoleColor_White, ConsoleColor_Black);

        sprintf(strMoney, "%d", money);

        RenderSystemDrawText(4, 60, strMoney, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemDrawText(6, 50, "CHOOSE TYPE OF BET", ConsoleColor_White, ConsoleColor_Black);
        RenderSystemDrawText(7, 50, "                  ", ConsoleColor_White, ConsoleColor_Black);

        DrawBetChooseByState(0);

        for (int i = 3; i < 25; i++)
            RenderSystemDrawText(i, 5, "                                       ", ConsoleColor_DarkMagenta, ConsoleColor_DarkMagenta);

        DrawRoulleteWheel(0);

        char answer;
        int state = 0;

        while ((answer = getch()) != 13)
        {
            if (answer == 27) return;

            if (answer == 80)
            {
                state = (state + 1) % 10;
            }
            else if (answer == 72)
            {
                state = state == 0 ? 9 : state - 1;
            }
            DrawBetChooseByState(state);
        }

        int chislo, bet, isSmall, isEven, isRed, column, dozen, line;

        switch(state)
        {
            case 0:
                GoToStaightUp(&chislo, &bet);
                break;
            case 2:
                GoToStreet(&line, &bet);
                break;
            case 4:
                GoToSixline(&line, &bet);
                break;
            case 5:
                GoToColumns(&column, &bet);
                break;
            case 6:
                GoToDozens(&dozen, &bet);
                break;
            case 7:
                GoToSmallBig(&isSmall, &bet);
                break;
            case 8:
                GoToEvenOdd(&isEven, &bet);
                break;
            case 9:
                GoToRedBlack(&isRed, &bet);
                break;
        }

        srand(time(0));

        int k = rand() % 37 + 50;

        int OCHKO = numbers[(k - 1) % 37];

        for (int i = 1; i < k; i++)
        {
            DrawRoulleteWheel(i);
            Sleep(i * 2);
        }

        switch(state)
        {
            case 0:
                if (OCHKO == chislo) money += bet;
                else money -= bet;
                break;
            case 2:
                if (OCHKO == 0) money -= bet;
                else
                    switch (line)
                    {
                        case 1:
                            if (OCHKO >= 1 && OCHKO <= 3) money += bet;
                            else money -= bet;
                            break;
                        case 2:
                            if (OCHKO >= 4 && OCHKO <= 6) money += bet;
                            else money -= bet;
                            break;
                        case 3:
                            if (OCHKO >= 7 && OCHKO <= 9) money += bet;
                            else money -= bet;
                            break;
                        case 4:
                            if (OCHKO >= 10 && OCHKO <= 12) money += bet;
                            else money -= bet;
                            break;
                        case 5:
                            if (OCHKO >= 13 && OCHKO <= 15) money += bet;
                            else money -= bet;
                            break;
                        case 6:
                            if (OCHKO >= 16 && OCHKO <= 18) money += bet;
                            else money -= bet;
                            break;
                        case 7:
                            if (OCHKO >= 19 && OCHKO <= 21) money += bet;
                            else money -= bet;
                            break;
                        case 8:
                            if (OCHKO >= 22 && OCHKO <= 24) money += bet;
                            else money -= bet;
                            break;
                        case 9:
                            if (OCHKO >= 25 && OCHKO <= 27) money += bet;
                            else money -= bet;
                            break;
                        case 10:
                            if (OCHKO >= 28 && OCHKO <= 30) money += bet;
                            else money -= bet;
                            break;
                        case 11:
                            if (OCHKO >= 31 && OCHKO <= 33) money += bet;
                            else money -= bet;
                            break;
                        case 12:
                            if (OCHKO >= 31 && OCHKO <= 36) money += bet;
                            else money -= bet;
                            break;
                    }
            case 4:
                if (OCHKO == 0) money -= bet;
                else
                    switch (line)
                    {
                        case 1:
                            if (OCHKO >= 1 && OCHKO <= 6) money += bet;
                            else money -= bet;
                            break;
                        case 2:
                            if (OCHKO >= 4 && OCHKO <= 9) money += bet;
                            else money -= bet;
                            break;
                        case 3:
                            if (OCHKO >= 7 && OCHKO <= 12) money += bet;
                            else money -= bet;
                            break;
                        case 4:
                            if (OCHKO >= 10 && OCHKO <= 15) money += bet;
                            else money -= bet;
                            break;
                        case 5:
                            if (OCHKO >= 13 && OCHKO <= 18) money += bet;
                            else money -= bet;
                            break;
                        case 6:
                            if (OCHKO >= 16 && OCHKO <= 21) money += bet;
                            else money -= bet;
                            break;
                        case 7:
                            if (OCHKO >= 19 && OCHKO <= 24) money += bet;
                            else money -= bet;
                            break;
                        case 8:
                            if (OCHKO >= 22 && OCHKO <= 27) money += bet;
                            else money -= bet;
                            break;
                        case 9:
                            if (OCHKO >= 25 && OCHKO <= 30) money += bet;
                            else money -= bet;
                            break;
                        case 10:
                            if (OCHKO >= 28 && OCHKO <= 33) money += bet;
                            else money -= bet;
                            break;
                        case 11:
                            if (OCHKO >= 31 && OCHKO <= 36) money += bet;
                            else money -= bet;
                            break;
                    }
                break;
            case 5:
                if (OCHKO == 0) money -= bet;
                else if (column == 1 && OCHKO % 3 == 1) money += bet;
                else if (column == 2 && OCHKO % 3 == 2) money += bet;
                else if (column == 3 && OCHKO % 3 == 0) money += bet;
                else money -= bet;
                break;
            case 6:
                if (OCHKO == 0) money -= bet;
                else if (dozen == 1 && OCHKO <= 12) money += bet;
                else if (dozen == 2 && OCHKO > 12 && OCHKO <= 24) money += bet;
                else if (dozen == 3 && OCHKO > 24) money += bet;
                else money -= bet;
                break;
            case 7:
                if (isSmall && (OCHKO >= 1 && OCHKO <= 18)) money += bet;
                else if (!isSmall && (OCHKO >= 19 && OCHKO <= 36)) money += bet;
                else money -= bet;
                break;
            case 8:
                if (OCHKO == 0) money -= bet;
                else if (isEven && OCHKO % 2 == 0) money += bet;
                else if (!isEven && OCHKO % 2 == 1) money += bet;
                else money -= bet;
                break;
            case 9:
                if (OCHKO == 0) money -= bet;
                else if (isRed && GetColor((k - 2) % 36) == ConsoleColor_Red) money += bet;
                else if (!isRed && GetColor((k - 2) % 36) == ConsoleColor_Black) money += bet;
                else money -= bet;
                break;
        }

        sprintf(strMoney, "%d", money);

        RenderSystemDrawText(4, 60, strMoney, ConsoleColor_White, ConsoleColor_Black);

        RenderSystemFlush();

        getch();
    }
}

void DrawBetChooseByState(int state)
{
    RenderSystemDrawText(8,  50, "STRAIGHT UP",    ConsoleColor_White, state == 0 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(9,  50, "SPLIT",          ConsoleColor_White, state == 1 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(10, 50, "STREET",         ConsoleColor_White, state == 2 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(11, 50, "CORNER",         ConsoleColor_White, state == 3 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(12, 50, "SIXLINE",        ConsoleColor_White, state == 4 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(13, 50, "COLUMNS",        ConsoleColor_White, state == 5 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(14, 50, "DOZENS",         ConsoleColor_White, state == 6 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(15, 50, "(1-18)/(19-36)", ConsoleColor_White, state == 7 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(16, 50, "EVEN/ODD",       ConsoleColor_White, state == 8 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);
    RenderSystemDrawText(17, 50, "RED/BLACK",      ConsoleColor_White, state == 9 ? ConsoleColor_DarkMagenta : ConsoleColor_Black);

    RenderSystemFlush();
}

void CasinoEpta()
{
    printf("|                            ");

    SetConsoleTextAttribute(hConsole, (WORD) ((8 << 4) | 14));

    printf("CASINO EPTA 777");

    SetConsoleTextAttribute(hConsole, (WORD) ((0 << 4) | 15));

    printf("                            |\n");
}

void SetConsoleCursor(int r, int c)
{
    COORD cursorCoord;
    cursorCoord.X = c;
    cursorCoord.Y = r;
    SetConsoleCursorPosition(hConsole, cursorCoord);
}

void SetConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    unsigned char consoleColor = symbolColor | (backgroundColor << 4);
    SetConsoleTextAttribute(hConsole, consoleColor);
}

void CleanDisplay()
{
    for (int i = 2; i <= 27; i++)
    {
        RenderSystemDrawText(i, 1, "                                                                       ",
                             ConsoleColor_White, ConsoleColor_Black);
    }

    RenderSystemFlush();
}

void RenderSystemInitialize()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    for (int r = 0; r < SCREENROWS; r++)
    {
        for (int c = 0; c < SCREENCOLUMS; c++)
        {
            backBuffer[r][c].symbol = 0;
            backBuffer[r][c].symbolColor = ConsoleColor_Gray;
            backBuffer[r][c].backgroundColor = ConsoleColor_Black;

            screenBuffer[r][c] = backBuffer[r][c];
        }
    }
}

void RenderSystemClear()
{
    for (int r = 0; r < SCREENROWS; r++)
    {
        for (int c = 0; c < SCREENCOLUMS; c++)
        {
            backBuffer[r][c].symbol = 0;
            backBuffer[r][c].backgroundColor = ConsoleColor_Black;
        }
    }
}

void RenderSystemDrawChar(int r, int c, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    backBuffer[r][c].symbol = symbol;
    backBuffer[r][c].symbolColor = symbolColor;
    backBuffer[r][c].backgroundColor = backgroundColor;
}

void RenderSystemDrawText(int r, int c, const char *text, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    int column = c;
    char symbol = *text;

    while (symbol != 0)
    {
        RenderSystemDrawChar(r, column, symbol, symbolColor, backgroundColor);

        column++;
        symbol = *(++text);
    }
}

void RenderSystemFlush()
{
    int screenBufferModified = 0;

    for (int r = 0; r < SCREENROWS; r++)
    {
        for (int c = 0; c < SCREENCOLUMS; c++)
        {
            if ((backBuffer[r][c].symbolColor                != screenBuffer[r][c].symbolColor)
                    ||   (backBuffer[r][c].symbol           != screenBuffer[r][c].symbol)
                    ||   (backBuffer[r][c].backgroundColor  != screenBuffer[r][c].backgroundColor))
            {
                screenBuffer[r][c] = backBuffer[r][c];

                SetConsoleCursor(r, c);
                SetConsoleColor(screenBuffer[r][c].symbolColor, screenBuffer[r][c].backgroundColor);
                printf("%c", screenBuffer[r][c].symbol);

                screenBufferModified = 1;
            }
        }
    }

    if (screenBufferModified)
        SetConsoleCursor(0, 0);
}

ConsoleColor GetColor(int k)
{
    ConsoleColor color = k == 0 ? ConsoleColor_Green : k % 2 == 0 ? ConsoleColor_Black : ConsoleColor_Red;
    return color;
}

void DrawRoulleteWheel(int key)
{
    int i;
    char c[3];

    for (int i = 4; i < 24; i++)
        RenderSystemDrawText(i, 5, "                                       ", ConsoleColor_DarkMagenta, ConsoleColor_DarkMagenta);

    RenderSystemDrawText(4, 26, "<- OCHKO", ConsoleColor_Green, ConsoleColor_DarkMagenta);

    sprintf(c, "%d", numbers[key % 37]);
    RenderSystemDrawText(4, 24, c, ConsoleColor_White, GetColor(key % 37));
    sprintf(c, "%d", numbers[(key + 1) % 37]);
    RenderSystemDrawText(6, 25, c, ConsoleColor_White, GetColor((key + 1) % 37));
    sprintf(c, "%d", numbers[(key + 18) % 37]);
    RenderSystemDrawText(23, 25, c, ConsoleColor_White, GetColor((key + 18) % 37));
    sprintf(c, "%d", numbers[(key + 36) % 37]);
    RenderSystemDrawText(6, 22, c, ConsoleColor_White, GetColor((key + 36) % 37));
    sprintf(c, "%d", numbers[(key + 19) % 37]);
    RenderSystemDrawText(23, 22, c, ConsoleColor_White, GetColor((key + 19) % 37));

    for (i = 2; i < 18; i++)
    {
        int k = (i + key) % 37;

        sprintf(c, "%d", numbers[k]);
        RenderSystemDrawText(5 + i, 19 + sqrt(72.25 - (i - 9.5) * (i - 9.5)) * 2.4, c, ConsoleColor_White, GetColor(k));

        sprintf(c, "%d", numbers[(37 - i + key) % 37]);
        RenderSystemDrawText(5 + i, 29 - sqrt(72.25 - (i - 9.5) * (i - 9.5)) * 2.4, c, ConsoleColor_White, GetColor((37 - i + key) % 37));
    }

    RenderSystemFlush();
}
