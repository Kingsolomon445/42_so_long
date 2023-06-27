// #include <stdio.h>

// #define ROWS 6
// #define COLS 34

// // Function to check if the given position is valid and not a wall
// int isValidMove(int row, int col, char map[ROWS][COLS]) {
//     if (row >= 0 && row < ROWS && col >= 0 && col < COLS && map[row][col] != '1') {
//         return 1;
//     }
//     return 0;
// }

// // Recursive flood fill function
// void floodFill(int row, int col, char map[ROWS][COLS], int visited[ROWS][COLS]) {
//     // Check if the current position is valid and not visited
//     if (!isValidMove(row, col, map) || visited[row][col]) {
//         return;
//     }

//     // Mark the current position as visited
//     visited[row][col] = 1;

//     // Recursively flood fill in all four directions
//     floodFill(row - 1, col, map, visited); // Up
//     floodFill(row + 1, col, map, visited); // Down
//     floodFill(row, col - 1, map, visited); // Left
//     floodFill(row, col + 1, map, visited); // Right
// }

// // Function to check if the map has a valid path
// int hasValidPath(char map[ROWS][COLS]) {
//     int playerRow, playerCol, exitRow, exitCol;
//     int hasPlayer = 0;
//     int hasExit = 0;

//     // Find the player's initial position and the exit position
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             if (map[i][j] == 'P') {
//                 playerRow = i;
//                 playerCol = j;
//                 hasPlayer = 1;
//             } else if (map[i][j] == 'E') {
//                 exitRow = i;
//                 exitCol = j;
//                 hasExit = 1;
//             }
//         }
//     }

//     // If player or exit is missing, return false
//     if (!hasPlayer || !hasExit) {
//         return 0;
//     }

//     // Create a visited array to keep track of visited cells
//     int visited[ROWS][COLS] = {0};

//     // Perform flood fill starting from the player's position
//     floodFill(playerRow, playerCol, map, visited);

//     // Check if all collectibles have been visited
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             if (map[i][j] == 'C' && !visited[i][j]) {
//                 return 0; // A collectible was not visited
//             }
//         }
//     }

//     // Return whether the exit position was visited
//     return visited[exitRow][exitCol];
// }

// int main() {
//     // Define the map
//     char map[ROWS][COLS] = {
//         "1111111111111111111111111111111111",
//         "1E0000000000000C00000C000000000001",
//         "1010010100100000101001000000010101",
//         "1010010010101010001001000000010101",
//         "1P0000000C00C0000000000000000000C1",
//         "1111111111111111111111111111111111"
//     };

//     // Check if the map has a valid path
//     if (hasValidPath(map)) {
//         printf("The map has a valid path!\n");
//     } else {
//         printf("The map does not have a valid path.\n");
//     }

//     return 0;
// }
