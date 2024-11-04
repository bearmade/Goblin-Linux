// Goblin.cpp : Defines the entry point for the application.
//
#include <iostream>
#include "Goblin.h"
#include <fstream>


using namespace std;
void saveGame();
void loadGame();
void processSaveLoad();
void saveLoadScreen();
char getch();
void pauseGame();
void printDisplay();
void displayTitle();
string generateName();
void processTerrain();
void processShop();
void processSkillShop();
void processMerchant();
void processInventory();
void processBattle(string TYPE, string enemyType);
void generatePlayer(string object, string TILE);
void processInput();
void processMovement(int dx, int dy);
void generateWorldMap();
void generateDungeon();
int getRandom(int low, int high);
void printBoard();
void initBoard();
void cellularAutomataMaze(int iterations);
void cellularAutomata(int iterations);
void cellularAuto(int iterations);
int countNeighbors(int row, int column, string TYPE);
void randGen();
void cellularAutomataMiniMaze(int iterations);
void villageSpawn(int iterations);
void cellularAutomataBorder(int iterations);
void randomWalk(int iterations, string TYPE);
void runRuleTile(string TYPE, string vertTYPE, string horTYPE);
void destroyIslands(string TYPE);
void crossRiver(int iterations, string TYPE, string changeTYPE, string clearTYPE);
void changeTiles(string TYPE, string changeTYPE);


//gloabal colors
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string bgWHITE = "\033[47m";
const string bgRED = "\033[41m";
const string bgGREEN = "\033[42m";
const string bgYELLOW = "\033[43m";
const string bgBLUE = "\033[44m";
const string MAGENTA = "\033[35m";
const string bgMAGENTA = "\033[45m";
const string CYAN = "\033[36m";
const string bgCYAN = "\033[46m";
const string BLINK = "\033[5m";
const string REVERSED = "\033[7m";
//string GROUND = bgWHITE + BLUE + "/\\" +RESET;
//string gGROUND = bgGREEN + BLACK + ", " + RESET;
//string WATER = bgBLUE+ "  " +RESET;
//string GROUNDrand = bgWHITE + BLUE + "^ " + RESET;
//string gGROUNDrand = bgGREEN+ YELLOW+"~."+RESET;
//string WATERrand = bgBLUE + "~ " + RESET;


string GROUND = "/\\" + RESET;
string EXIT = "()" + RESET;
string BLOCKER = "##" + RESET;
string gGROUND = YELLOW + "^ " + RESET;
string WATER = YELLOW + "  " + RESET;
string GROUNDrand = GREEN + ". " + RESET;
string gGROUNDrand = MAGENTA + ", " + RESET;
string WATERrand = "  " + RESET;
string CASTLE = RED + "[]" + RESET;
string CASTLEwall = YELLOW + "==" + RESET;
string CASTLEwallUP = YELLOW + "||" + RESET;
string VILLA = "  ";
string SHORE = GREEN + ";:" + RESET;
string WALKER = BLUE + "~ " + RESET;
string crossWATER = bgCYAN + "~ " + RESET;

string tempTileA = "  ";
string tempTileB = "  ";
string tempTileC = "  ";
string currentTerrain = "  ";
string terrainMessage = " ";
string terrainMessageTemp = " ";

//global vars
int SIZE = 35;
int gridWidth = SIZE;
int gridHeight = SIZE;
int row = 0;
int column = 0;

vector<vector<string>> board(gridWidth, vector<string>(gridHeight, ""));
vector<vector<string>> boardTemp(gridWidth, vector<string>(gridHeight, ""));

//Player variables
string PLAYER = BLINK + "db" + RESET;
int playerX = 0;
int playerY = 0;
int playerPOS[2] = { playerX,playerY };

int tempPlayerX = 0;
int tempPlayerY = 0;
int tempPlayerPOS[2] = { tempPlayerX,tempPlayerY };

int pHealth = 30;
int pAttack = 1;
int pDefense = 5;
int pExp = 0;
int pLevel = 0;
int money = 0;
int steps = 0;
int goblinsKilled = 0;
//inventory variables
string itemNames[3] = { "skulls","bones","meat" };
int itemAmount[3] = { 0, 0, 0 };
int itemBasePrice[3] = { 4, 2, 1 };

//string GOBLINname = " ";
string playerAttackMessage[5] = { "You attack ","You swing at ","You strike in the general area of ","You throw a rock at ","You trip into " };


//function to process save/load screen
void processSaveLoad(){
    // display the save/load screen
    cout << "Save/Load Screen" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. New Game" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        saveGame();
        break;
    case 2:
        loadGame();
        break;
    case 3:
        break;
    default:
        cout << "Invalid choice" << endl;
        break;


    }
}

//function to save the game to a file
void saveGame() {
    // open the file for writing
    ofstream file("savegame.txt");
    if (!file.is_open()) {
       cout << "Error: could not open save game file" << endl;
        return;
    }
    // write the game state to the file
    file << playerX << " " << playerY << " " << pHealth << " " << pAttack << " " << pDefense << " " << pExp << " " << pLevel << " " << money << " " << steps << " " << goblinsKilled;
    // write the inventory to the file
    for (int i = 0; i < 3; i++) {
        file << " " << itemAmount[i];
    }
    // close the file
    file.close();
    cout << "Game saved successfully!" << endl;
    pauseGame();
}

// function to load the game from a file
void loadGame(){


    // open the file for reading
    ifstream file("savegame.txt");
    if (!file.is_open()) {
        cout << "Error: could not open save game file" << endl;
        return;
    }
    // read the game state from the file
    file >> playerX >> playerY >> pHealth >> pAttack >> pDefense >> pExp >> pLevel >> money >> steps >> goblinsKilled;
    // read the inventory from the file
    for (int i = 0; i < 3; i++) {
        file >> itemAmount[i];
    }
    // close the file
    file.close();
    // update the game state
    playerPOS[0] = playerX;
    playerPOS[1] = playerY;
    // update the inventory
    for (int i = 0; i < 3; i++) {
        itemAmount[i] = itemAmount[i];
        itemBasePrice[i] = itemBasePrice[i];
        // print a message to confirm that the game was loaded successfully
        cout << "Game loaded successfully!" << endl;
        pauseGame();
    
    }
}

//function to bring up the save/load screen
void saveLoadScreen() {
    system("clear");
    printDisplay();
    cout << "\n\n";
    // display the save/load screen
    cout << "Save/Load Screen" << endl;
    cout << "1. Save Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        saveGame();
        break;
    case 2:
        loadGame();
        break;
    default:
       cout << "Invalid choice" << endl;
        break;
    }
}


/**
 * Reads a single character from the standard input without echoing it to the console.
 * This function is a Linux-specific implementation of the Windows `getch()` function.
 * It temporarily disables canonical mode and echo on the terminal, reads a single character,
 * and then restores the original terminal settings.
 *
 * @return The character read from the standard input.
 */
char getch() {
    char buf = 0;
    struct termios old = { 0 };
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

// function that works like system("pause") but for linux
void pauseGame() {
    cout << "Press any key to continue...\n";
    getch();
}


int main()
{
    char input;
    bool gameOver = false;
    displayTitle();
    pauseGame();
    generateWorldMap();


    while (gameOver == false)
    {


        printBoard();
        printDisplay();
        processInput();
        processTerrain();
        if (pHealth < 1)
        {
            cout << "you have died\n";
            gameOver = true;


        }



    }




    return 0;
}

void displayTitle()
{

    cout << RED + "          " + "   ______      __    ___          \n";
    cout << RED + "          " + "  / ____/___  / /_  / (_)___      \n";
    cout << RED + "          " + " / / __/ __ \\/ __ \\/ / / __ \\     \n";
    cout << RED + "          " + "/ /_/ / /_/ / /_/ / / / / / /     \n";
    cout << RED + "          " + "\\____/\\____/_.___/_/_/_/ /_/      \n";
    cout << RESET;
    processSaveLoad();

}


/// Prints the game display information, including the player's health, level, gold, strength, steps taken, and goblins killed. Also prints any terrain-specific messages.
void printDisplay()
{

    for (int x = 0; x < SIZE * 2; x++)
        cout << bgRED + BLACK + "=" + RESET;

    cout << endl;
    cout << "HP: " << pHealth << "   Level: " << pLevel << " Gold: " << money << "   Strength: " << pAttack << "  Steps: " << steps << " Goblins killed: " << goblinsKilled;
    cout << "\n" << terrainMessageTemp << "\n";
    cout << terrainMessage << "\n";
    terrainMessageTemp = terrainMessage;
    terrainMessage = " ";

}
/// Generates a random goblin name by combining first and last name components.
/// The name is generated using arrays of first and last name prefixes and suffixes.
/// The function returns the generated goblin name as a string.
string generateName()
{
    //string eTypeName[5] = { "","","","","" };

    string fname1[5] = { "Sn","Sk","Kr","Gr","B" };
    string fname2[5] = { "um","ar","ay","ee","oo" };
    string fname3[5] = { "po","py","bs","ble","gle" };
    string lname1[5] = { "Rub","Bum","Tum","Hum","Grum" };
    string lname2[5] = { "thum","bo","rum","tum","bum" };
    string lname3[5] = { "o","bles","gles","po","py" };
    string fNAME = fname1[getRandom(1, 5) - 1] + fname2[getRandom(1, 5) - 1] + fname3[getRandom(1, 5) - 1];
    string lNAME = lname1[getRandom(1, 5) - 1] + lname2[getRandom(1, 5) - 1] + lname3[getRandom(1, 5) - 1];
    string goblinNAME = (fNAME + " " + lNAME);

    return goblinNAME;


}

/// Processes the terrain and triggers various events based on the current terrain type.
/// This function checks the current terrain type and performs the following actions:
/// - If the terrain is gGROUNDrand, there is a 25% chance of triggering a battle with a randomly generated goblin.
/// - If the terrain is gGROUND, there is a 5% chance of gaining 1-2 gold plus the player's level.
/// - If the terrain is CASTLE, there is a 5% chance of opening the skill shop and a 25% chance of opening the regular shop.
/// - If the terrain is VILLA, there is a 25% chance of triggering a merchant event.
/// - If the terrain is GROUND, there is a 25% chance of leveling up the player, generating a new dungeon, and blocking the current tile.
/// - If the terrain is EXIT, the player is returned to the previous location.
/// The function also sets the appropriate terrain message based on the current terrain type.
void processTerrain()
{
    //string name = generateName();

    if (currentTerrain == gGROUNDrand && getRandom(1, 100) > 75)
        processBattle(gGROUNDrand, generateName());
    if (currentTerrain == gGROUND && getRandom(1, 100) > 95)
        money = money + getRandom(0, 1) + pLevel;
    if (currentTerrain == CASTLE && getRandom(1, 100) > 95)
        processSkillShop();
    if (currentTerrain == CASTLE && getRandom(1, 100) > 75)
        processShop();
    if (currentTerrain == VILLA && getRandom(1, 100) > 75)
        processMerchant();
    if (currentTerrain == GROUND && getRandom(1, 100) > 75)
    {
        board[playerPOS[0]][playerPOS[1]] = BLOCKER;
        board[playerPOS[0]][playerPOS[1]] = boardTemp[playerPOS[0]][playerPOS[1]];
        boardTemp = board;
        tempPlayerX = playerPOS[0];
        tempPlayerY = playerPOS[1];
        pLevel = pLevel + 1;
        generateDungeon();
    }

    if (currentTerrain == EXIT)
    {
        board = boardTemp;
        playerX = tempPlayerX;
        playerY = tempPlayerY;

        printBoard();

    }


    //terrainMessages
    if (currentTerrain == gGROUNDrand)
        terrainMessage = RED + "this area is infested with goblins" + RESET;
    if (currentTerrain == VILLA)
        terrainMessage = GREEN + "there are merchants in the area" + RESET;
    if (currentTerrain == GROUND)
        terrainMessage = RED + "the ground is unstable" + RESET;
    if (currentTerrain == CASTLE)
        terrainMessage = GREEN + "this area is has services" + RESET;
    if (currentTerrain == gGROUND)
        terrainMessage = YELLOW + "gold is in the area" + RESET;

}

/**
 * Processes the player's interaction with the shop, allowing them to purchase health for a random amount of gold.
 * The shop will remain open until the player chooses to exit or successfully purchases health.
 */
void processShop()
{
    bool shopOpen = true;
    char input = ' ';
    system("clear");
    printDisplay();
    cout << "\n\nWelcome to the Inn\n";
    while (shopOpen == true)
    {
        int randHP = getRandom(10, 25) * (pLevel + 1);
        int randGold = getRandom(10, 25) * (pLevel + 1);
        cout << "\n\nPurchase " << randHP << " HP for " << randGold << " gold ? (A) for YES/ (D) for NO \n\n";
        input = getch();
        input = toupper(input);
        if (input == 'A' && money >= randGold)
        {
            money = money - randGold;
            pHealth = pHealth + randHP;
            shopOpen = false;
            break;
        }
        else
        {
            shopOpen = false;
        }




    }

}

/**
 * Processes the player's interaction with a skill shop, allowing them to purchase a strength upgrade for a random amount of gold.
 * The shop will remain open until the player chooses to exit or successfully purchases the upgrade.
 */
void processSkillShop()
{
    bool shopOpen = true;
    char input = ' ';
    system("clear");
    printDisplay();
    cout << "\n\nA Mentor approaches\n";
    while (shopOpen == true)
    {
        int randHP = getRandom(10, 25);
        int randGold = (getRandom(10, 25) * (pLevel + 1));
        cout << "\n\nPurchase strength upgrade for " << randGold << " gold ? (A) for YES/ (D) for NO \n\n";
        input = getch();
        input = toupper(input);
        if (input == 'A' && money >= randGold)
        {
            money = money - randGold;
            pAttack = pAttack + 1;
            shopOpen = false;
            break;
        }
        else
        {
            shopOpen = false;
        }




    }

}

/**
 * Processes the player's interaction with a merchant, allowing them to purchase or sell items for a random amount of gold.
 * The shop will remain open until the player chooses to exit or successfully completes a transaction.
 */
void processMerchant()
{
    bool shopOpen = true;
    char input = ' ';
    system("clear");
    printDisplay();
    cout << "\n\nA merchant approaches\n";
    while (shopOpen == true)
    {
        int randAmount = getRandom(10, 25);
        int randItem = getRandom(1, 3);
        int randGold = getRandom(10, 25);
        int itemPriceLow = (itemBasePrice[randItem - 1] * randAmount) / 2;
        int itemPriceHigh = (itemBasePrice[randItem - 1] * randAmount) * 2;
        int itemPrice = getRandom(itemPriceLow, itemPriceHigh);
        cout << "(A)Purchase / (S)Sell / (D)Exit \n\n";
        input = getch();
        input = toupper(input);
        switch (input)
        {
        case 'A':

            cout << "Purchase " << randAmount << " " << itemNames[randItem - 1] << " for " << itemPrice << " gold ? (A) for YES / (D) for NO \n\n";
            input = getch();
            input = toupper(input);
            if (input == 'A' && money > itemPrice)
            {
                money = money - itemPrice;
                itemAmount[randItem - 1] = itemAmount[randItem - 1] + randAmount;
                shopOpen = false;
                break;
            }
            else
            {
                shopOpen = false;
            }

            break;
        case 'S':
            if (itemAmount[randItem - 1] > 0)
            {
                cout << "Sell " << itemAmount[randItem - 1] << " " << itemNames[randItem - 1] << " for " << itemPrice << " gold ? (A) for YES / (D) for NO \n\n";
                input = getch();
                input = toupper(input);
                if (input == 'A')
                {
                    money = money + itemPrice;
                    itemAmount[randItem - 1] = itemAmount[randItem - 1] - itemAmount[randItem - 1];
                    shopOpen = false;
                    break;
                }
                else
                {
                    shopOpen = false;
                }

            }
            else
            {
                cout << "They aren't buying.\n";
            }


            break;
        case 'D':
            shopOpen = false;
            break;
        }

    }

}

/**
 * Displays the player's inventory, showing the name and amount of each item.
 * This function clears the screen, prints the display, and then lists all the
 * items in the player's inventory along with the amount of each item.
 * After displaying the inventory, the function pauses the game to allow the
 * player to view the information.
 */
void processInventory()
{

    system("clear");
    printDisplay();
    cout << "\n\n";
    int size = *(&itemNames + 1) - itemNames;
    for (int i = 0; i < size; i++)
    {
        cout << itemNames[i] << "     " << itemAmount[i] << "\n";

    }
    pauseGame();
}

/**
 * Handles the logic for a battle between the player and an enemy.
 *
 * This function is responsible for the core gameplay loop of a battle encounter.
 * It displays the enemy's health, prompts the player for an action (attack or run away),
 * and calculates the results of the player's and enemy's attacks. The function continues
 * the battle loop until either the player or the enemy is defeated.
 *
 * @param TYPE The type of the enemy being encountered (e.g. "Goblin").
 * @param enemyType A more specific description of the enemy type.
 */
void processBattle(string TYPE, string enemyType)
{
    char input = ' ';
    bool battleOver = false;
    int eHealth = (getRandom(10, 20) * (pLevel + 1));

    system("clear");


    while (battleOver == false)
    {
        string randPlayerAttackMessage = playerAttackMessage[getRandom(1, 5) - 1];
        system("clear");
        printDisplay();
        int attack = (pAttack + getRandom(1, 5)) * (pLevel + 1);
        int eAttackLow = (getRandom(1, 3) * (pLevel + 1));
        int eAttackHigh = (getRandom(3, 7) * (pLevel + 1));
        int eAttack = getRandom(eAttackLow, eAttackHigh);
        cout << " Goblin Encounter \n\n" + enemyType + " HP: " << eHealth << "\n\n";
        cout << "(A)attack, (D)run away\n";
        input = getch();
        input = toupper(input);
        if (input == 'A')
        {
            cout << randPlayerAttackMessage + enemyType + " for " << attack << " damage.\n";
            eHealth = eHealth - attack;
            if (eHealth < 1)
            {
                int gold = (getRandom(1, 10) * (pLevel + 1));
                int dropChance = getRandom(1, 10);
                int dropItem = getRandom(1, 3);
                int dropAmount = getRandom(1, 3) * (pLevel + 1);
                cout << "you killed the pitiful " + enemyType + ".\n";
                cout << "you found " << gold << " gold.\n";
                money = money + gold;
                goblinsKilled = goblinsKilled + 1;
                if (dropChance > 7)
                {
                    cout << "you found " << dropAmount << " " << itemNames[dropItem - 1] << ".\n";
                    itemAmount[dropItem - 1] = dropAmount;
                }



                battleOver = true;
                break;
            }
        }
        if (input == 'D')
        {
            int gold = (getRandom(1, 5) * (pLevel + 1));
            if (money < (money - gold))
            {
                cout << "you run away.\n";
                battleOver = true;
                break;
            }
            cout << "you run away and drop " << gold << " gold.\n";
            money = money - gold;
            if (money < 1)
                money = 0;
            battleOver = true;
            break;
        }


        pauseGame();
        system("clear");
        printDisplay();
        cout << enemyType + " attacks you for " << eAttack << " damage.\n";
        pHealth = pHealth - eAttack;
        if (pHealth < 1)
        {
            cout << "you have fallen to the mighty " + enemyType + ".\n";
            battleOver = true;
            break;

        }
        pauseGame();

    }



    pauseGame();
}

/**
 * Generates a player object at a random valid position on the game board.
 *
 * This function searches the game board for a valid tile (not a blocker) and
 * places the player object on that tile. It also updates the playerPOS array
 * with the coordinates of the player's position.
 *
 * @param object The object to be placed on the board (e.g. "PLAYER").
 * @param TILE The tile type that the object can be placed on (e.g. "TILE").
 */
void generatePlayer(string object, string TILE)
{
    bool playerPlaced = false;
    int randomChance = getRandom(1, 10000);
    while (playerPlaced == false) {
        for (int i = 3; i < gridWidth - 3; i++) {
            for (int j = 3; j < gridHeight - 3; j++) {
                if (board[i][j] == TILE && (getRandom(1, 10000) > 9990) && playerPlaced == false)
                {
                    board[i][j] = object;
                    if (object == PLAYER)
                    {
                        playerPOS[0] = i;
                        playerPOS[1] = j;
                    }

                    playerPlaced = true;
                }




            }
        }
    }


}

/**
 * Processes user input for player movement and inventory.
 *
 * This function is called to handle user input for the game. It reads a character
 * from the keyboard using the `getch()` function, converts it to uppercase, and
 * then performs the appropriate action based on the input character.
 *
 * The supported input characters are:
 * - 'W': Move the player up, if possible
 * - 'A': Move the player left, if possible
 * - 'S': Move the player down, if possible
 * - 'D': Move the player right, if possible
 * - 'I': Process the player's inventory
 *
 * The function updates the player's position on the game board and the `tempTileA`,
 * `tempTileB`, and `tempTileC` variables accordingly. It also increments the `steps`
 * counter when the player moves.
 */
void processInput()
{
    char input = getch();
    input = toupper(input);

    switch (input)
    {
    case 'W':
        if ((playerPOS[0] != 0) && (board[playerPOS[0] - 1][playerPOS[1]] != BLOCKER))
        {
            tempTileA = board[playerPOS[0] - 1][playerPOS[1]];
            tempTileC = tempTileB;
            board[playerPOS[0] - 1][playerPOS[1]] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;

            playerPOS[0] = playerPOS[0] - 1;
            steps++;
        }

        break;
    case 'A':
        if (playerPOS[1] != 0 && board[playerPOS[0]][playerPOS[1] - 1] != BLOCKER)
        {
            tempTileA = board[playerPOS[0]][playerPOS[1] - 1];
            tempTileC = tempTileB;
            board[playerPOS[0]][playerPOS[1] - 1] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[1] = playerPOS[1] - 1;
            steps++;
        }

        break;
    case 'S':
        if (playerPOS[0] != SIZE - 1 && board[playerPOS[0] + 1][playerPOS[1]] != BLOCKER)
        {
            tempTileA = board[playerPOS[0] + 1][playerPOS[1]];
            tempTileC = tempTileB;
            board[playerPOS[0] + 1][playerPOS[1]] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[0] = playerPOS[0] + 1;
            steps++;
        }

        break;
    case 'D':
        if (playerPOS[1] != SIZE - 1 && board[playerPOS[0]][playerPOS[1] + 1] != BLOCKER)
        {
            tempTileA = board[playerPOS[0]][playerPOS[1] + 1];
            tempTileC = tempTileB;
            board[playerPOS[0]][playerPOS[1] + 1] = PLAYER;
            board[playerPOS[0]][playerPOS[1]] = tempTileC;
            tempTileB = tempTileA;
            playerPOS[1] = playerPOS[1] + 1;
            steps++;
        }

        break;
    case 'I':
        processInventory();

        break;
    case 'Q':
        saveLoadScreen();
        break;

    }
    currentTerrain = tempTileA;
}

/**
 * Processes the movement of the player on the game board.
 *
 * @param dx The change in the x-coordinate of the player's position.
 * @param dy The change in the y-coordinate of the player's position.
 */
void processMovement(int dx, int dy)
{
    tempTileA = board[playerPOS[0] + dx][playerPOS[1] + dy];
    tempTileC = tempTileB;
    board[playerPOS[0] + dx][playerPOS[1] + dy] = PLAYER;
    board[playerPOS[0]][playerPOS[1]] = tempTileC;
    tempTileB = tempTileA;
    playerPOS[1] = playerPOS[1] + 1;
}
// void processMovement(int dx, int dy)
// {
//     tempTileA = board[playerPOS[0] + dx][playerPOS[1] + dy];
//     tempTileC = tempTileB;
//     board[playerPOS[0] + dx][playerPOS[1] + dy] = PLAYER;
//     board[playerPOS[0]][playerPOS[1]] = tempTileC;
//     tempTileB = tempTileA;
//     playerPOS[1] = playerPOS[1] + 1;
// }

/**
 * Generates a world map for the game by initializing the game board, applying cellular automata algorithms to create a maze-like structure, adding random walkers, and generating the player's starting position.
 *
 * This function is responsible for the initial setup and generation of the game world. It calls various helper functions to create the game board, apply cellular automata algorithms, add random walkers, and generate the player's starting position.
 */
void generateWorldMap()
{
    initBoard();
    cellularAutomataMaze(4);
    cellularAutomata(2);
    cellularAuto(1);
    randGen();
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    cellularAutomataMiniMaze(7);
    cellularAutomataMiniMaze(5);
    cellularAutomataMiniMaze(3);
    cellularAutomataMiniMaze(2);
    cellularAutomataMiniMaze(2);
    runRuleTile(CASTLE, CASTLEwallUP, CASTLEwall);
    cellularAutomataBorder(5);
    destroyIslands(WALKER);
    crossRiver(4, WALKER, crossWATER, WATERrand);
    generatePlayer(PLAYER, WATERrand);
    //randomWalk(30, WALKER);
    printBoard();
}

/**
 * Generates a dungeon map for the game by initializing the game board, applying cellular automata algorithms to create a maze-like structure, adding random walkers, and generating the player's starting position and the exit.
 *
 * This function is responsible for the initial setup and generation of the game dungeon. It calls various helper functions to create the game board, apply cellular automata algorithms, add random walkers, and generate the player's starting position and the exit.
 */
void generateDungeon()
{


    system("clear");
    initBoard();
    cellularAutomataMaze(4);

    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    randomWalk(SIZE / 2, WALKER);
    changeTiles(GROUND, BLOCKER);
    //changeTiles(WALKER, WATER);
    generatePlayer(PLAYER, WALKER);
    tempTileB = WALKER;
    generatePlayer(EXIT, WATER);
    changeTiles(WALKER, gGROUNDrand);
    printBoard();

}

/**
 * Generates a random integer between the specified low and high values (inclusive).
 *
 * This function uses a random device to seed a Mersenne Twister pseudo-random number
 * generator, and then generates a random integer within the specified range using a
 * uniform integer distribution.
 *
 * @param low The lower bound of the range (inclusive).
 * @param high The upper bound of the range (inclusive).
 * @return A random integer between low and high (inclusive).
 */
int getRandom(int low, int high)
{
    // Set up a random device to seed the random number generator
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<int> distribution(low, high);
    int randomInteger = distribution(engine);

    return randomInteger;
}

/**
 * Prints the current state of the game board to the console.
 * 
 * This function clears the console and then prints the contents of the `board` array
 * to the console, with each element of the array represented as a string. The function
 * uses a nested loop to iterate over the rows and columns of the board, and the `printf`
 * function to output the board elements.
 */
void printBoard()
{
    system("clear");
    // print game board
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            //cout << board[i][j];
            printf("%s", board[i][j].c_str());
        }
        //cout << endl;
        printf("%s\n");
    }
    //this_thread::sleep_for(chrono::milliseconds(10));
}

/**
 * Initializes the game board by randomly setting each cell to either GROUND or WATER.
 * 
 * This function iterates over the grid and sets each cell to either GROUND or WATER based on a random chance.
 * The chance of a cell being set to GROUND is 50% (randChance > 5).
 */
void initBoard()
{
    int randChance = 0;
    //initialize grid
    for (int x = 0;x < gridWidth;x++) {
        for (int y = 0;y < gridHeight;y++) {
            randChance = getRandom(1, 10);
            if (randChance > 5)
                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }
}

/**
 * Performs a cellular automata simulation on the game board, updating the state of each cell based on the number of neighboring cells of the same type.
 *
 * This function iterates over the game board and updates the state of each cell based on the following rules:
 * - If a cell is water and has more than 2 neighboring ground cells, it becomes a ground cell.
 * - If a cell is ground and has more than 3 neighboring ground cells, it becomes a water cell.
 * - If a cell is ground and has less than 2 neighboring ground cells, it becomes a water cell.
 * - If a cell is water and has less than 2 neighboring ground cells, it becomes a ground cell.
 *
 * The function performs this update process for the specified number of iterations.
 *
 * @param iterations The number of times to perform the cellular automata update.
 */
void cellularAutomataMaze(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }
}

/**
 * Performs a cellular automata simulation on the game board, updating the state of each cell based on the number of neighboring cells of the same type.
 *
 * This function iterates over the game board and updates the state of each cell based on the following rules:
 * - If a cell is water and has more than 2 neighboring ground cells, it becomes a ground cell.
 * - If a cell is ground and has more than 3 neighboring ground cells, it becomes a water cell.
 * - If a cell is ground and has less than 3 neighboring ground cells, it becomes a water cell.
 *
 * The function performs this update process for the specified number of iterations.
 *
 * @param iterations The number of times to perform the cellular automata update.
 */
void cellularAutomata(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 3)
                    board[i][j] = WATER;
            }
        }
    }
}

/**
 * Performs a cellular automata simulation on the game board, updating the state of each cell based on the number of neighboring cells of the same type.
 *
 * This function iterates over the game board and updates the state of each cell based on the following rules:
 * - If a cell is water and has more than 1 neighboring ground cells, it becomes a ground cell.
 * - If a cell is ground and has less than 3 neighboring ground cells, it becomes a ground cell.
 * - If a cell is ground and has more than 1 neighboring ground cells, it becomes a ground cell.
 *
 * The function performs this update process for the specified number of iterations.
 *
 * @param iterations The number of times to perform the cellular automata update.
 */
void cellularAuto(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = gGROUND;
                if (board[i][j] == GROUND && neighbors < 3)
                    board[i][j] = gGROUND;
                if (board[i][j] == gGROUND && neighbors > 1)
                    board[i][j] = gGROUND;
            }
        }
    }
}

/**
 * Counts the number of neighboring cells of the specified type around the given cell.
 *
 * This function checks the 8 neighboring cells around the cell at the given row and column coordinates, and counts the number of cells that match the specified type.
 *
 * @param row The row coordinate of the cell to check.
 * @param column The column coordinate of the cell to check.
 * @param TYPE The type of cell to count the neighbors for.
 * @return The number of neighboring cells of the specified type.
 */
int countNeighbors(int row, int column, string TYPE)
{
    int dx = 0;
    int dy = 0;
    int neighborCount = 0;

    if ((row != 0) && (column != 0) && (row != gridWidth - 1) && (column != gridHeight - 1)) {
        int xPlus = (row + 1);
        int xMinus = (row - 1);
        int yPlus = (column + 1);
        int yMinus = (column - 1);

        if (board[xPlus][column] == TYPE)
            neighborCount++;
        if (board[row][yPlus] == TYPE)
            neighborCount++;
        if (board[xPlus][yPlus] == TYPE)
            neighborCount++;
        if (board[xMinus][column] == TYPE)
            neighborCount++;
        if (board[row][yMinus] == TYPE)
            neighborCount++;
        if (board[xMinus][yMinus] == TYPE)
            neighborCount++;
        if (board[xPlus][yMinus] == TYPE)
            neighborCount++;
        if (board[xMinus][yPlus] == TYPE)
            neighborCount++;

    }
    return neighborCount;
}

/**
 * Randomly generates ground, ground with random texture, and water with random texture on the game board.
 * This function iterates through the entire game board and randomly sets some cells to have a random ground or water texture.
 */
void randGen()
{
    int randChance = 0;
    //initialize grid
    for (int x = 0;x < gridWidth;x++) {
        for (int y = 0;y < gridHeight;y++) {
            //randChance = getRandom(1, 10);
            if ((getRandom(1, 10) > 6) && (board[x][y] == gGROUND))
                board[x][y] = gGROUNDrand;
            if ((getRandom(1, 10) > 4) && (board[x][y] == GROUND))
                board[x][y] = GROUNDrand;
            if ((getRandom(1, 10) > 6) && (board[x][y] == WATER))
                board[x][y] = WATERrand;
        }
    }
}

/**
 * Generates a mini maze-like area on the game board using cellular automata.
 *
 * This function randomly selects a starting position and size for the mini maze, then
 * initializes the cells within that area to be either ground or water. It then runs
 * a cellular automata simulation for the specified number of iterations, applying
 * rules to determine whether each cell should be ground or water. Finally, it
 * converts any remaining ground cells to castles and any remaining water cells to
 * villas.
 *
 * @param iterations The number of cellular automata iterations to run.
 */
void cellularAutomataMiniMaze(int iterations)
{
    int randStartX = getRandom(2, gridWidth - 8);
    int randStartY = getRandom(2, gridHeight - 8);
    int randWidth = getRandom(3, 8);
    int randHeight = getRandom(2, SIZE / 10);
    int randEndX = randStartX + randWidth;
    int randEndY = randStartY + randHeight;
    int neighbors = 0;

    int randChance = 0;
    //initialize grid
    for (int x = randStartX;x < randEndX;x++) {
        for (int y = randStartY;y < randEndY;y++) {
            randChance = getRandom(1, 10);
            if ((randChance > 5) && (row != 0) && (column != 0) && (row != gridWidth - 1) && (column != gridHeight - 1))

                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                if (board[i][j] == GROUND)
                    board[i][j] = CASTLE;
                if (board[i][j] == WATER)
                    board[i][j] = VILLA;
            }
        }
    }
}

/**
 * Generates a village area on the game board by randomly placing ground and water tiles, and then applying cellular automata rules to smooth the terrain.
 *
 * @param iterations The number of iterations to apply the cellular automata rules.
 */
void villageSpawn(int iterations)
{
    int randStartX = getRandom(2, gridWidth);
    int randStartY = getRandom(2, gridHeight);
    int randEndX = getRandom(randStartX, gridWidth);
    int randEndY = getRandom(randStartY, gridHeight);
    int neighbors = 0;
    int randChance = 0;
    //initialize grid
    for (int x = randStartX;x < randEndX;x++) {
        for (int y = randStartY;y < randEndY;y++) {
            randChance = getRandom(1, 10);
            if (randChance > 5)
                board[x][y] = GROUND;
            else
                board[x][y] = WATER;
        }
    }




    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, GROUND);
                if (board[i][j] == WATER && neighbors > 2)
                    board[i][j] = GROUND;
                if (board[i][j] == GROUND && neighbors > 3)
                    board[i][j] = WATER;
                if (board[i][j] == GROUND && neighbors < 2)
                    board[i][j] = WATER;
                if (board[i][j] == WATER && neighbors < 2)
                    board[i][j] = GROUND;
            }
        }
    }

    for (int x = 0;x < iterations;x++) {
        for (int i = randStartX; i < randEndX; ++i) {
            for (int j = randStartY; j < randEndY; ++j) {
                //count neighbors
                if (board[i][j] == GROUND)
                    board[i][j] = CASTLE;
                if (board[i][j] == WATER)
                    board[i][j] = VILLA;
            }
        }
    }
}

/**
 * Applies a cellular automata algorithm to the game board to create a border of shore tiles around water tiles.
 *
 * This function iterates over the entire game board and checks the number of neighboring ground tiles for each water tile. If a water tile has more than 1 neighboring ground tile, it is converted to a shore tile.
 *
 * @param iterations The number of iterations to run the cellular automata algorithm.
 */
void cellularAutomataBorder(int iterations)
{
    int neighbors = 0;
    for (int x = 0;x < iterations;x++) {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                //count neighbors
                neighbors = countNeighbors(i, j, gGROUND);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUNDrand);
                if (board[i][j] == WATER && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUND);
                if (board[i][j] == WATERrand && neighbors > 1)
                    board[i][j] = SHORE;
                neighbors = countNeighbors(i, j, gGROUNDrand);
                if (board[i][j] == WATERrand && neighbors > 1)
                    board[i][j] = SHORE;
            }
        }
    }
}

/**
 * Applies a random walk algorithm to the game board, placing tiles of the specified type within a defined region.
 *
 * This function selects a random starting point within the middle quarter of the game board, and then iterates a number of times, randomly moving in one of four directions (up, down, left, right) and placing tiles of the specified type along the path. The function ensures that the tiles are placed within the bounds of the game board.
 *
 * @param iterations The number of iterations to run the random walk algorithm.
 * @param TYPE The type of tile to place along the random walk path.
 */
void randomWalk(int iterations, string TYPE)
{
    int midPoint = SIZE / 2;
    int quarterPoint = midPoint / 2;
    int randStartX = getRandom(quarterPoint, midPoint);
    int randStartY = getRandom(quarterPoint, midPoint);
    int randEndX = getRandom(randStartX, midPoint + quarterPoint);
    int randEndY = getRandom(randStartY, midPoint + quarterPoint);
    int neighbors = 0;
    int randDir = getRandom(1, 4);

    for (int x = 0; x < iterations; x++) {
        board[randStartX][randStartY] = TYPE;

        for (int y = 0; y < iterations; y++) {
            int randDir = getRandom(1, 4);
            if (randDir == 1 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX + 1][randStartY] = TYPE;
                randStartX = randStartX + 1;
            }
            if (randDir == 2 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX - 1][randStartY] = TYPE;
                randStartX = randStartX - 1;
            }
            if (randDir == 3 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX][randStartY + 1] = TYPE;
                randStartY = randStartY + 1;
            }
            if (randDir == 4 && (randStartY != 0) && (randStartX != 0) && (randStartX != gridWidth - 1) && (randStartY != gridHeight - 1)) {
                board[randStartX][randStartY - 1] = TYPE;
                randStartY = randStartY - 1;
            }
        }
    }
}

/**
 * Applies a rule-based transformation to tiles of the specified type on the game board.
 *
 * This function iterates over the game board and checks for tiles of the specified type that have three adjacent tiles of the same type in either the vertical or horizontal direction. When such a pattern is found, the central tile is transformed to the corresponding vertical or horizontal tile type.
 *
 * @param TYPE The type of tile to check for the rule-based transformation.
 * @param vertTYPE The tile type to use for vertical transformations.
 * @param horTYPE The tile type to use for horizontal transformations.
 */
void runRuleTile(string TYPE, string vertTYPE, string horTYPE)
{
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if ((i != 0) && (j != 0) && (i != gridWidth - 1) && (j != gridHeight - 1))
            {
                if ((board[i][j] == TYPE) && (board[i + 1][j] == TYPE) && (board[i - 1][j] == TYPE))
                    board[i][j] = vertTYPE;
                if ((board[i][j] == TYPE) && (board[i][j + 1] == TYPE) && (board[i][j - 1] == TYPE))
                    board[i][j] = horTYPE;
            }

        }
    }
}

/**
 * Destroys any islands of tiles that are not of the specified type and have more than 6 neighboring tiles of the specified type.
 *
 * This function iterates over the game board and checks for tiles that are not of the specified type but have more than 6 neighboring tiles of that type. When such a pattern is found, the central tile is transformed to the specified type, effectively destroying the island.
 *
 * @param TYPE The type of tile to check for the island destruction.
 */
void destroyIslands(string TYPE)
{

    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if (board[i][j] != TYPE && countNeighbors(i, j, TYPE) > 6)
                board[i][j] = TYPE;

        }
    }
}

/**
 * Applies a rule-based transformation to tiles of the specified type on the game board.
 *
 * This function iterates over the game board and checks for tiles of the specified type that have three adjacent tiles of the same type in either the vertical or horizontal direction. When such a pattern is found, the central tile is transformed to the corresponding vertical or horizontal tile type.
 *
 * @param iterations The number of iterations to perform the transformation.
 * @param TYPE The type of tile to check for the transformation.
 * @param changeTYPE The tile type to use for the transformation.
 * @param clearTYPE The tile type to use to clear the transformed tiles.
 */
void crossRiver(int iterations, string TYPE, string changeTYPE, string clearTYPE)
{
    for (int x = 0; x < iterations; x++) {
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                if (board[i][j] == TYPE && countNeighbors(i, j, TYPE) < 4)
                    board[i][j] = changeTYPE;
                if (board[i][j] == changeTYPE && countNeighbors(i, j, changeTYPE) > 2)
                    board[i][j] = changeTYPE;
                if (board[i][j] == changeTYPE)
                    board[i][j] = clearTYPE;

            }
        }
    }

}

/**
 * Changes all tiles of the specified type to the given replacement type.
 *
 * This function iterates over the game board and replaces any tiles of the specified type with the given replacement type.
 *
 * @param TYPE The type of tile to change.
 * @param changeTYPE The new tile type to use as the replacement.
 */
void changeTiles(string TYPE, string changeTYPE)
{
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            if (board[i][j] == TYPE)
                board[i][j] = changeTYPE;


        }
    }
}
