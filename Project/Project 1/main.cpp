/*
 * File:   main.cpp
 * Author: John Huynh
 * Date:   November 11, 2025
 * Purpose: Recreate the game battleship using structures and arrays.
 */

// ====== Libraries ======

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// ====== Files =======

const char *HISTORY_FILE = "history.bin"; // Record game history
const char *STATS_FILE = "stats.dat"; // Record player stats

// ====== Structures ======

// Create Ships
struct Ship {
  const char *name; // Ship name
  unsigned char size; // Ship size
};

// Create Board
struct Board {
  unsigned char shipId[10][10];
  unsigned char hasShip[10][10];
};

// Shot Grid
struct Shots {
  unsigned char hitMarker[10][10];
};

// Game Record
struct GameRecord {
  unsigned int gameId; 
  unsigned int timeStamp;
  unsigned char gameWinner;
  unsigned char playerShots[10][10]; // Player shots
  unsigned char cpuShots[10][10]; // Computer shots
};

// Statistics
struct Stats {
  unsigned int totalGames;
  unsigned int userWins; 
};

// Current position player is at to place ship
struct Cursor {
  int row, column;
  bool vertical;
};

// ====== Global Variables ======

/* Standard Game Fleet */
const Ship std_fleet[5] = {
    {"Carrier", 5},
    {"Battleship", 4},
    {"Destroyer", 3},
    {"Submarine", 3},
    {"Patrol Boat", 2}
};

/* Quick Game Fleet */
const Ship sm_fleet[3] = {
    {"Destroyer", 3},
    {"Submarine", 3},
    {"Patrol Boat", 2}
};

/* Game Fleet points to standard fleet, can change */
const Ship *fleet = std_fleet;

/* Identify movement direction on board */
enum Direction {
  DIR_NONE,
  DIR_UP,
  DIR_DOWN,
  DIR_LEFT,
  DIR_RIGHT
};

/* Initialize standard game mode  */
int gameBoard = 10;
int fleetCount = 5;
int totalTargets = 5 + 4 + 3 + 3 + 2;

// ====== Prototypes ======

void moveCursor(Direction direction, int &row, int &column);
int targetCount(const Ship *fleet, int shipCount);
void mainMenu();
void playGame();
void gameHistory();
void playerStats();
void clearBoard(Board &board);
void clearShots(Shots &shot);
void printHeader();
void printOwnBoard(const Board &board, const Shots &shot);
void printShots(const Shots &shot);
void drawPlacementView(const Board &board, const Cursor &cur, const Ship &ship);
bool canPlace(const Board &board, int row, int column, bool vertical, unsigned char size);
void placeShip(Board &board, int row, int column, bool vertical, unsigned char size, unsigned char id);
void placeComputer(Board &boardoard);
void keepShipOnBoard(Cursor &cur, unsigned char size);
bool placePlayerFleet(Board &board);
bool parseTarget(const string &in, int &row, int &col);
bool processShot(Board &target, Shots &shots, int row, int column, int *shipHits, int *shipsLeft, bool &wasHit, bool &sunk, int &sunkId);
void computerPickShot(const Shots &cpuShots, int &row, int &column);
const char *shipNameById(int id);
void gameplay(unsigned int gameId, Stats &stats);
bool appendHistory(const GameRecord &rec, const char *path);
bool readStats(Stats &stats, const char *path);
bool writeStats(const Stats &stats, const char *path);
unsigned int lastGameId(const char *path);
void invalidInput(const string &prompt);
void gameMode();

// ====== Main Process ======

int main() {

  /* Time stamp game */
  srand(static_cast<unsigned int>(time(0)));
  /* Run main menu sequence */
  mainMenu();
  /* Exit stage right */
  return 0;

}

// ====== Functions ======

// Move Cursor of Player
void moveCursor(Direction direction, int &row, int &column) {

  switch (direction) {
    case DIR_UP:
      --row;
      break;
    case DIR_DOWN:
      ++row;  
      break;
    case DIR_LEFT:
      --column;         
      break;
    case DIR_RIGHT:
      ++column;         
      break;
    default:
      break;
  }

}

// Keep Game in Bounds
bool inBounds(int row, int column) {

  bool inBounds = false;

  /* True if row and column value are inside game boundaries */
  if(row >= 0 && row < gameBoard && column >= 0 && column < gameBoard) {
    inBounds = true;
  };

  return inBounds;
}

// Calculate Number of Targets
int targetCount(const Ship *fleet, int shipCount) {

  int targets = 0;

  /* Loop through ship count, add up ship sizes */
  for (int i = 0; i < shipCount; ++i) {
    targets += fleet[i].size;
  }

  return targets;
}

// Main Menu
void mainMenu() {

  int choice; 

  do {

    cout << "\nBattleship!\n";
    cout << string(20, '-') << '\n';
    cout << "1. Play Battleship\n";
    cout << "2. View Game History\n";
    cout << "3. Stats\n";
    cout << "4. Quit\n";
    cout << "\nChoose: ";
    cin >> choice;

    if (!choice) {
      invalidInput("Invalid choice. Please enter a number.");
      continue;
    }

    switch (choice) {
      case 1:
        playGame();
        break;
      case 2:
        gameHistory();
        break;
      case 3:
        playerStats();
        break;
      case 4:
        cout << "Thanks for playing!\n";
        return;
      default:
        invalidInput("Invalid choice.");

    }

  } while (choice != 4);

}

// Play Game
void playGame() {

  /* User selects game mode */ 
  gameMode();
  
  /* Open stat file */
  Stats stats{};
  readStats(stats, STATS_FILE);

  /* Assign game ID */
  unsigned int gameId = lastGameId(HISTORY_FILE) + 1;

  /* Start gameplay */
  gameplay(gameId, stats);

}

// Game History
void gameHistory() {
  
  ifstream in(HISTORY_FILE, ios::binary);

  /* If player hasn't played a game yet */
  if (!in) {
    cout << "You haven't played a game yet!\n";
    return;
  }

  GameRecord rec;

  // Read each record and process as long as read succeeds
  while (in.read((char*)&rec, sizeof(rec))) {

    /* Show game number and winner  */
    cout << "\n=== Game #" << rec.gameId << " | " << (rec.gameWinner ? "Player" : "Computer") << " Won ===\n";

    /* Create player and computer boards */
    Shots playerShots{}, cpuShots{};

    /* Show fleet, hits and misses */
    for (int row = 0; row < 10; ++row) {

      for (int column = 0; column < 10; ++column) {

        playerShots.hitMarker[row][column] = rec.playerShots[row][column];
        cpuShots.hitMarker[row][column]   = rec.cpuShots[row][column];

      }

    }

    /* Display enemy board with fleet, hits and misses */
    cout << "\nEnemy Board:\n\n";
    printShots(playerShots);

    /* Show player board with computer hits and misses */
    cout << "\nYour Board:\n\n";
    printShots(cpuShots);

    cout << "\nX - Hits | O - Misses \n";

  }

}

// Player Stats 
void playerStats() {

    /* Create holder for statistics */
    Stats s{};

    /* If no stat file exists */
    if (!readStats(s, STATS_FILE)) {
        cout << "No stats yet.\n";
        return;
    }

    /* Calculate player win percentage */
    int pct = (s.totalGames ? (100 * s.userWins / s.totalGames) : 0);

    /* Display stats */
    cout << "\n=== Stats ===\n";
    cout << "Games played : " << s.totalGames << "\n";
    cout << "Player wins  : " << s.userWins << "\n";
    cout << fixed << "Win percent  : " << pct << "%\n";

}

// Clear Board
void clearBoard(Board &board) {

  for (int row = 0; row < 10; ++row) {

    for (int column = 0; column < 10; ++column) {

      /* Zero the board */
      board.shipId[row][column] = board.hasShip[row][column] = 0;

    }

  }

}

// Clear Shots
void clearShots(Shots &shot) {

  for (int row = 0; row < 10; ++row) {

    for (int column = 0; column < 10; ++column) {

      /* Zero the hitmarker overlay */
      shot.hitMarker[row][column] = 0;

    } 

  } 

}

// Header for board
void printHeader() {

    cout << "    "; 

    /* Generate Column Header (A B C...) to match gameplay option */
    for (int column = 0; column < gameBoard; ++column) {
        cout << setw(2) << (char)('A' + column);
    }

    cout << "\n    "; 

    /* Separate header from gameplay grid */
    for (int i = 0; i < gameBoard; ++i) {
        cout << "--"; 
    }

    cout << "\n"; 

}

// Print Player Board
void printOwnBoard(const Board &board, const Shots &shot) {

  /* Display Header */
  printHeader();

  for (int row = 0; row < gameBoard; ++row) {

    /* Row numbers */
    cout << setw(2) << row << " |";

    /* Game grid */
    for (int column = 0; column < gameBoard; ++column) {

      /* Empty space*/
      char ch = '.';

      /* Show player boat positions */
      if (board.hasShip[row][column]) {
        ch = '1';
      }

      /* Show misses by computer */
      if (shot.hitMarker[row][column] == 1) {
        ch = 'O';
      }
        
      /* Show hits by computer */
      if (shot.hitMarker[row][column] == 2) {
        ch = 'X';
      }
        
      /* Display marker with space */
      cout << setw(2) << ch;
    }

    cout << "\n";

  }

}

// Print Shots
void printShots(const Shots &shot) {

  /* Display Header */
  printHeader();

  for (int row = 0; row < gameBoard; ++row) {

    /* Row Numbers */ 
    cout << setw(2) << row << " |";
    
    for (int column = 0; column < gameBoard; ++column) {

      /* Empty space*/
      char ch = '.';

      /* Show misses by player */
      if (shot.hitMarker[row][column] == 1) {
        ch = 'O';
      }
      
      /* Show hits by player */
      if (shot.hitMarker[row][column] == 2) {
        ch = 'X';
      }
       
      /* Display marker with space */
      cout << setw(2) << ch;

    }

    cout << "\n";

  }

}

// Draw Placement View
void drawPlacementView(const Board &board, const Cursor &cur, const Ship &ship) {

  /* Simulate real-time board update with spacing */
  cout << string(40, '\n');

  /* Show current ship placement and orientation */
  cout << "Place: " << ship.name << " (size " << (int)ship.size << ", " << (cur.vertical ? "vertical" : "horizontal") << ")\n";

  /* List controls */
  cout << "Controls: W/A/S/D move | C rotate | P place | Q quit\n\n";

  /* Display header */
  printHeader();

  /* Show board */
  for (int row = 0; row < gameBoard; ++row) {

    /* Row label */
    cout << setw(2) << row << " |";

    for (int column = 0; column < gameBoard; ++column) {

      /* Track if ship passes through cell */
      bool ghost = false;
      
      /* Check each part of ship for clipping */
      for (int k = 0; k < ship.size; ++k) {

        int rowPos = cur.row + (cur.vertical ? k : 0);
        int colPos = cur.column + (cur.vertical ? 0 : k);
        
        /* If current ship placement clips already placed ship */
        if (rowPos == row && colPos == column) {
          ghost = true;
          break;
        }

      }

      /* Show ship placements */
      char ch = ghost ? 'X' : (board.hasShip[row][column] ? '1' : '.');
      
      cout << setw(2) << ch;

    }

    cout << "\n";
  
  }

}

// Check Ship Placement
bool canPlace(const Board &board, int row, int column, bool vertical, unsigned char size) {

  /* Check each part of ship */
  for (int k = 0; k < size; ++k) {

    /* Get position of each ship's cell */
    int rowPos = row + (vertical ? k : 0);
    int colPos = column + (vertical ? 0 : k);

    /* Check if ship is in bounds */
    if (rowPos < 0 || rowPos >= gameBoard || colPos < 0 || colPos >= gameBoard) {
      return false;
    }

    /* Check if ship overlaps another ship */
    if (board.shipId[rowPos][colPos] != 0) {
      return false;
    }
      
  }

  return true;

}

// Place Ship
void placeShip(Board &board, int row, int column, bool vertical, unsigned char size, unsigned char id) {

  /* Fill the array cells the ship occupies */
  for (int k = 0; k < size; ++k) {

    /* Get the position of ship segment */
    int rowPos = row + (vertical ? k : 0);
    int colPos = column + (vertical ? 0 : k);

    /* Assign the ship ID and mark as occupied */
    board.shipId[rowPos][colPos] = id;
    board.hasShip[rowPos][colPos] = 1;

  }

}

// Place Computer
void placeComputer(Board &board) {

  /* Loop each ship */
  for (int ship = 0; ship < fleetCount; ++ship) {

    bool placed = false;

    /* Loop until position of boat fits board */
    do {

      bool vertical = rand() % 2;
      int row = rand() % gameBoard;
      int column = rand() % gameBoard;

      /* Check if boat can be placed */
      if (canPlace(board, row, column, vertical, fleet[ship].size)) {
        placeShip(board, row, column, vertical, fleet[ship].size, ship + 1);
        placed = true;
      }

    } while (!placed);

  }

}

// Keep Ship Placement on Board
void keepShipOnBoard(Cursor &cur, unsigned char size) {

  /* If current orientation is vertical */
  if (cur.vertical) {

    /* Prevent ship from clipping top */
    if (cur.row < 0) {
      cur.row = 0;
    }

    /* Prevent ship from clipping bottom */
    if (cur.row > gameBoard - size) {
      cur.row = gameBoard - size;
    }

    /* Prevent ship from clipping left */
    if (cur.column < 0) {
      cur.column = 0;
    }

    /* Prevent ship from clipping right */
    if (cur.column > gameBoard - 1) {
      cur.column = gameBoard - 1;
    }
      
  } 

  /* If current orientation is horizontal */
  else {

    /* Prevent ship from clipping top */
    if (cur.row < 0) {
      cur.row = 0;
    }

    /* Prevent ship from clipping bottom */
    if (cur.row > gameBoard - 1) {
      cur.row = gameBoard - 1;
    }

    /* Prevent ship from clipping left */
    if (cur.column < 0) {
      cur.column = 0;
    }
      
    /* Prevent ship from clipping right */
    if (cur.column > gameBoard - size) {
      cur.column = gameBoard - size;
    }
  }
}

// Place Player Fleet
bool placePlayerFleet(Board &board) {

  Cursor cur{0, 0, false};

  for (int s = 0; s < fleetCount; ++s) {

    const Ship &ship = fleet[s];
    keepShipOnBoard(cur, ship.size);

    /* Track when this ship has been successfully placed */
    bool placed = false;

    do {

      // Draw board and ghost ship
      drawPlacementView(board, cur, ship);
      cout << "\nEnter command: ";

      char ch;
      cin >> ch;

      // Uppercase player input
      ch = (char)toupper((unsigned char)ch);

      switch (ch) {

        /* Move cursor up */
        case 'W':
          moveCursor(DIR_UP, cur.row, cur.column);
          break;

        /* Move cursor down */
        case 'S':
          moveCursor(DIR_DOWN, cur.row, cur.column);
          break;

        /* Move cursor left */
        case 'A':
          moveCursor(DIR_LEFT, cur.row, cur.column);
          break;

        /* Move cursor right */
        case 'D':
          moveCursor(DIR_RIGHT, cur.row, cur.column);
          break;

        /* Rotate boat orientation */
        case 'C':
          cur.vertical = !cur.vertical;
          break;

        /* Quit placement / game setup */
        case 'Q':
          return false;

        /* Attempt to place the ship */
        case 'P':
          if (canPlace(board, cur.row, cur.column, cur.vertical, ship.size)) {
              placeShip(board, cur.row, cur.column, cur.vertical, ship.size, s + 1);
              placed = true;   // Done with this ship, exit loop
          } else {
              cout << "Overlap. Press Enter...";
              cin.ignore(10000, '\n');
              cin.get();
          }
          break;

        /* Ignore invalid keys */
        default:
          break;

      }

      // Keep cursor inside legal placement area
      keepShipOnBoard(cur, ship.size);

    } while (!placed);

  }

  return true;

}

// Parse Player Target
bool parseTarget(const string &in, int &row, int &col) {

  char letter;
  int num;
  
  /* Attempt to read letter + number */
  if (sscanf(in.c_str(), " %c%d", &letter, &num) == 2) {

    /* Uppercase letter if not already */
    letter = (char)toupper((unsigned char)letter);

    /* Check if letter and number are within game bounds*/
    if (letter >= 'A' && letter < 'A' + gameBoard && num >= 0 && num < gameBoard) {

      /* Minus A to account for index */
      col = letter - 'A';
      row = num;
      
      return true;

    }

  }

  return false;

}

// Process Shot
bool processShot(Board &target, Shots &shots, int row, int column, int *shipHits, int *shipsLeft, bool &wasHit, bool &sunk, int &sunkId) {

  /* Reset result flags for this shot */
  wasHit = false;
  sunk = false;
  sunkId = 0;

  /* Check if cell was already shot at */
  if (shots.hitMarker[row][column]) {
    return false;
  }

  /* Check if the target cell contains a ship */
  if (target.shipId[row][column]) {

    shots.hitMarker[row][column] = 2;
    wasHit = true;

    int id = target.shipId[row][column];

    /* Is ship still standing? */
    if (shipHits[id - 1]) {

      /* Reduce boat health */
      shipHits[id - 1]--;

      /* Reduce total hit points */
      (*shipsLeft)--;

      /* If hit points hit 0 */
      if (shipHits[id - 1] == 0) {
        sunk = true;
        sunkId = id;
      }

    }

  } else {
    
    /* Missed Shot */
    shots.hitMarker[row][column] = 1;

  }

  return true;

}

// Computer Shot
void computerPickShot(const Shots &cpuShots, int &row, int &column) {

    do {

        /* Randomly select row and column */
        row = rand() % gameBoard;
        column = rand() % gameBoard; 

    } while (cpuShots.hitMarker[row][column] != 0);

}

// Create Ship With Name and ID
const char *shipNameById(int id) {

  if (id >= 1 && id <= fleetCount) {
    return fleet[id - 1].name;
  }

  return "";
}

// Initialize Gameplay
void gameplay(unsigned int gameId, Stats &stats) {

  /* Create boards */
  Board playerBoard{}, computerBoard{};
    
  /* Create shot grid (dynamic for rubric: new/delete) */
  Shots *playerShots = new Shots;
  Shots *cpuShots = new Shots;

  /* Clean boards and shot grids */
  clearBoard(playerBoard);
  clearBoard(computerBoard);
  clearShots(*playerShots);
  clearShots(*cpuShots);

  /* Randomly set the computer's ships */
  placeComputer(computerBoard);

  /* Header to show while positioning fleet */
  cout << "=== Player Fleet Placement (" << gameBoard << "x" << gameBoard
       << ") ===\n";

  /* If user quits during position phase, exit gameplay */
  if (!placePlayerFleet(playerBoard)) {
    return;
  }
    
  /* Create arrays to hold ships hit */
  int cpuShipHits[5] = {0, 0, 0, 0, 0};
  int pShipHits[5] = {0, 0, 0, 0, 0};

  /* Update remaining hit points for hit ships */
  for (int i = 0; i < fleetCount; i++) {
    cpuShipHits[i] = fleet[i].size;
    pShipHits[i] = fleet[i].size;
  }

  /* Determine ships left based on targets left */
  int cpuLeft = totalTargets;
  int pLeft = totalTargets;
    

  /* Display updated game boards until either player or computer lose */
  while (cpuLeft > 0 && pLeft > 0) {

    /* Create large gap between turns to simulate real-time change */
    cout << string(30, '\n');

    /* Show player board with enemy hitmarkers */
    cout << "Your Board:\n";
    printOwnBoard(playerBoard, *cpuShots);

    /* Show computer board with player hitmarkers */
    cout << "\nEnemy Board:\n";
    printShots(*playerShots);

    // Player turn
    bool shotTaken = false;

    do {

      bool hit, sunk;
      int row, col, sunkId;
      string target;

      /* Get player's input for target */
      cout << "\nEnter target (i.e. A0) or Q to quit: ";
      cin >> target;

      /* Allow player to quit mid-game */
      if (toupper((unsigned char)target[0]) == 'Q') {
        return;
      }

      /* Check if player's input is a valid coordinate */
      if (!parseTarget(target, row, col)) {
        cout << "Invalid.\n";
        continue;
      }

      /* Check if player has already fired at this target */
      if (!processShot(computerBoard, *playerShots, row, col, cpuShipHits, &cpuLeft, hit, sunk, sunkId)) {
        cout << "Already shot.\n";
        continue;
      }

      shotTaken = true;

      /* Output result of shot */
      cout << (hit ? "HIT!" : "Miss.");

      /* If a ship sank, display its name */
      if (sunk) {
        cout << " Sunk " << shipNameById(sunkId) << "!";
      }

      cout << "\n";

      /* If all CPU ship cells are gone, let user see final board */
      if (cpuLeft == 0) {
        cout << "Press Enter...";
        cin.ignore(10000, '\n');
        cin.get();
      }

    } while (!shotTaken);

    /* Exit loop if we sank the computer, no rebuttal, the enemy's ships have been sank */
    if (cpuLeft == 0) {
      break;
    }

    /* Didn't kill the computer? Now it's the computer's turn */
    bool hit, sunk;
    int compRow, compCol, sunkId;
    
    /* Computer determines target to shoot based off past result */
    computerPickShot(*cpuShots, compRow, compCol);

    /* The computer shoots... */
    processShot(playerBoard, *cpuShots, compRow, compCol, pShipHits, &pLeft, hit, sunk, sunkId);

    /* Output the result of the computer's shot */
    cout << "Computer fires " << (char)('A' + compCol) << compRow << " -> " << (hit ? "HIT!" : "miss.") << "\n";

    /* Did the computer sink a boat? */
    if (sunk) {
      cout << "Your " << shipNameById(sunkId) << " was sunk!\n";
    }
      
    /* Start next turn */
    cout << "Press Enter...";
    cin.ignore(10000, '\n');
    cin.get();

  }

  /* Flag if player won */
  bool gameWinner = (cpuLeft == 0);

  /* Announce winner */
  cout << string(20, '\n') << (gameWinner ? "YOU WIN!\n" : "YOU LOSE.\n");

  /* Record game results */
  GameRecord rec{};  
  rec.gameId = gameId;
  rec.timeStamp = (unsigned)time(0);
  rec.gameWinner = gameWinner ? 1 : 0;

  /* Record player and computer shots */
  for (int row = 0; row < 10; ++row) {
      
    for (int column = 0; column < 10; ++column) {
      rec.playerShots[row][column] = playerShots->hitMarker[row][column];
      rec.cpuShots[row][column] = cpuShots->hitMarker[row][column];
    }

  }

  /* Write game record to file */
  appendHistory(rec, HISTORY_FILE);

  /* Update total games played */
  stats.totalGames++; 

  /* Updated player win count */
  if (gameWinner) {
    stats.userWins++;
  }

  /* Write updated states to stat file */
  writeStats(stats, STATS_FILE);

  /* Delete Pointers */
  delete playerShots;
  delete cpuShots;
}

// Append the game to history file
bool appendHistory(const GameRecord &rec, const char *path) {
  
  /* Open history file to update game history */
  ofstream out(path, ios::app);

  /* Exit if file can't open */
  if (!out) {
    return false;
  }
  
  /* Write current game to file */
  out.write((const char*)&rec, sizeof(GameRecord));
  
  return out.good();

}

// Read stat file
bool readStats(Stats &stats, const char *path) {

  /* Open stat file */
  ifstream in(path);
  
  /* Exit if file can't open */
  if (!in) {
    stats.totalGames = 0;
    stats.userWins = 0;
    return false;
  }
  
  /* Read the file */
  in.read((char*)&stats, sizeof(Stats));
  
  /* If file can't be read, set stat values to 0 */
  if (!in) {
    stats.totalGames = 0;
    stats.userWins = 0;
    return false;
  }
  
  return in.good();

}

// Write to stat file
bool writeStats(const Stats &stats, const char *path) {
  
  /* Open Stat file */
  ofstream out(path);
  
  /* If file can't be opened */
  if (!out) {
    return false;
  }
  
  /* Update stat file */
  out.write((const char*)&stats, sizeof(Stats));
  
  return out.good();

}

// Get Last Game ID From History File 
unsigned int lastGameId(const char *path) {

  /* Open history file in binary read mode */
  ifstream in(path, ios::binary);

  /* If file doesn't exist, there is no last game ID */
  if (!in) {
    return 0;
  }

  /* Move to end of file to determine size */
  in.seekg(0, ios::end);
  streamoff fileSize = in.tellg();

  /* If file doesn't have anything */
  if (fileSize < static_cast<streamoff>(sizeof(GameRecord))) {
    return 0;
  }

  /* Jump directly to the last record */
  in.seekg(-static_cast<streamoff>(sizeof(GameRecord)), ios::end);

  GameRecord rec{};

  /* Read the last record */
  if (!in.read(reinterpret_cast<char*>(&rec), sizeof(GameRecord))) {
    return 0;
  }

  /* Return the game ID */
  return rec.gameId;
}

// Invalid Input
void invalidInput(const string &prompt) {

  cin.clear();
  cin.ignore(10000, '\n');
  cout << prompt << "\n";

}

// Choose Game Mode
void gameMode() {

  int choice;

  cout << "\nChoose game mode:\n";
  cout << "1. Standard\n";
  cout << "2. Rapid\n";
  cout << "Select 1 or 2: ";

  cin >> choice;

  do {

    switch (choice) {

      case 1:
        gameBoard = 10;
        fleet = std_fleet;
        fleetCount = 5;
        totalTargets = targetCount(fleet, fleetCount);
        return;

      case 2:
        gameBoard = 5;
        fleet = sm_fleet;
        fleetCount = 3;
        totalTargets = targetCount(fleet, fleetCount);
        return;

      default:
        invalidInput("Invalid input. Please choose a game mode.");
        break;
      
    }
  } while (choice != 1 || choice != 2);

}
