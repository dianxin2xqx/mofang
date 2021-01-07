#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// cube definition:
//
//             |************|
//             |*U1**U2**U3*|
//             |************|
//             |*U4**U5**U6*|
//             |************|
//             |*U7**U8**U9*|
//             |************|
// ************|************|************|************|
// *L1**L2**L3*|*F1**F2**F3*|*R1**R2**R3*|*B1**B2**B3*|
// ************|************|************|************|
// *L4**L5**L6*|*F4**F5**F6*|*R4**R5**R6*|*B4**B5**B6*|
// ************|************|************|************|
// *L7**L8**L9*|*F7**F8**F9*|*R7**R8**R9*|*B7**B8**B9*|
// ************|************|************|************|
//             |************|
//             |*D1**D2**D3*|
//             |************|
//             |*D4**D5**D6*|
//             |************|
//             |*D7**D8**D9*|
//             |************|
//
// -> U1U2U3U4U5U6U7U8U9R1R2R3R4R5R6R7R8R9F1F2F3F4F5F6F7F8F9D1D2D3D4D5D6D7D8D9L1L2L3L4L5L6L7L8L9B1B2B3B4B5B6B7B8B9

const int U1 =  0, U2 =  1, U3 =  2, U4 =  3, U5 =  4, U6 =  5, U7 =  6, U8 =  7, U9 =  8,
          R1 =  9, R2 = 10, R3 = 11, R4 = 12, R5 = 13, R6 = 14, R7 = 15, R8 = 16, R9 = 17,
          F1 = 18, F2 = 19, F3 = 20, F4 = 21, F5 = 22, F6 = 23, F7 = 24, F8 = 25, F9 = 26,
          D1 = 27, D2 = 28, D3 = 29, D4 = 30, D5 = 31, D6 = 32, D7 = 33, D8 = 34, D9 = 35,
          L1 = 36, L2 = 37, L3 = 38, L4 = 39, L5 = 40, L6 = 41, L7 = 42, L8 = 43, L9 = 44,
          B1 = 45, B2 = 46, B3 = 47, B4 = 48, B5 = 49, B6 = 50, B7 = 51, B8 = 52, B9 = 53;

const char *move2str[18] = {
    "U", "U2", "U'",
    "R", "R2", "R'",
    "F", "F2", "F'",
    "D", "D2", "D'",
    "L", "L2", "L'",
    "B", "B2", "B'"
};

const int PRE_MOVE_LENGTH = 5;

// cube[idx1] -> cube[idx2] -> cube[idx3] -> cube[idx4] -> cube[idx1], rep+1 times
void swap4(int *cube, int idx1, int idx2, int idx3, int idx4, int rep) {
    int tmp;
    for (int i = 0; i <= rep; ++i) {
        tmp = cube[idx4];
        cube[idx4] = cube[idx3];
        cube[idx3] = cube[idx2];
        cube[idx2] = cube[idx1];
        cube[idx1] = tmp;
    }
}

//move = axis * 3 + power
//axis: U=0, R=1, F=2, D=3, L=4, B=5
//power: 0=clockwise, 1=180 degrees, 2=anti-clockwise
void doMove(int *cube, int move) {
    int tmp;
    int axis = move / 3;
    int power = move % 3;
    switch (axis) {
    case 0:
        swap4(cube, U1, U3, U9, U7, power);
        swap4(cube, U2, U6, U8, U4, power);
        swap4(cube, F1, L1, B1, R1, power);
        swap4(cube, F2, L2, B2, R2, power);
        swap4(cube, F3, L3, B3, R3, power);
        break;
    case 1:
        swap4(cube, R1, R3, R9, R7, power);
        swap4(cube, R2, R6, R8, R4, power);
        swap4(cube, U3, B7, D3, F3, power);
        swap4(cube, U6, B4, D6, F6, power);
        swap4(cube, U9, B1, D9, F9, power);
        break;
    case 2:
        swap4(cube, F1, F3, F9, F7, power);
        swap4(cube, F2, F6, F8, F4, power);
        swap4(cube, U7, R1, D3, L9, power);
        swap4(cube, U8, R4, D2, L6, power);
        swap4(cube, U9, R7, D1, L3, power);
        break;
    case 3:
        swap4(cube, D1, D3, D9, D7, power);
        swap4(cube, D2, D6, D8, D4, power);
        swap4(cube, F7, R7, B7, L7, power);
        swap4(cube, F8, R8, B8, L8, power);
        swap4(cube, F9, R9, B9, L9, power);
        break;
    case 4:
        swap4(cube, L1, L3, L9, L7, power);
        swap4(cube, L2, L6, L8, L4, power);
        swap4(cube, U1, F1, D1, B9, power);
        swap4(cube, U4, F4, D4, B6, power);
        swap4(cube, U7, F7, D7, B3, power);
        break;
    case 5:
        swap4(cube, B1, B3, B9, B7, power);
        swap4(cube, B2, B6, B8, B4, power);
        swap4(cube, U3, L1, D7, R9, power);
        swap4(cube, U2, L4, D8, R6, power);
        swap4(cube, U1, L7, D9, R3, power);
        break;
    }
}

int distance(int *cube1, int *cube2) {
    int distanceEdge = 0;
    int distanceCorn = 0;
    for (int i = 0; i < 54; ++i) {
        if (cube1[i] == cube2[i]) {
            continue;
        }
        if (i % 9 % 2 == 0) {
            distanceCorn++;
        } else {
            distanceEdge++;
        }
    }
    return distanceEdge * 100 + distanceCorn;
}

void copyCube(int *dist, const int *src) {
    for (int i = 0; i < 54; ++i) {
        dist[i] = src[i];
    }
}

void initSolvedCube(int *cube) {
    for (int i = 0; i < 54; ++i) {
        cube[i] = i / 9;
    }
}

int invMove(int move) {
    return move / 3 * 3 + 2 - move % 3;
}

void solve(int *cube) {
    int solvedCube[54];
    int cubeTmp[54];
    int algMoves[8];
    int preMoveList[PRE_MOVE_LENGTH];
    int algStartIdx;
    initSolvedCube(solvedCube);
    int curDistance = distance(cube, solvedCube);
    int tmpDistance;

    while (curDistance != 0) {
        copyCube(cubeTmp, cube);

        if (curDistance / 100 == 2) { //odd parity
            doMove(cubeTmp, 0);
            printf("U ");
            curDistance = 10000;
        }

        for (int i = 0; i < PRE_MOVE_LENGTH; ++i) {
            preMoveList[i] = rand() % 18;
            doMove(cubeTmp, preMoveList[i]);
        }

        algMoves[0] = rand() % 18;
        algMoves[1] = rand() % 18;
        algMoves[2] = invMove(algMoves[0]);
        algMoves[3] = rand() % 18;
        algMoves[4] = algMoves[0];
        algMoves[5] = invMove(algMoves[1]);
        algMoves[6] = invMove(algMoves[0]);
        algMoves[7] = invMove(algMoves[3]);

        algStartIdx = rand() % 8;
        for (int i = 0; i < 8; ++i) {
            doMove(cubeTmp, algMoves[(i + algStartIdx) % 8]);
        }

        for (int i = PRE_MOVE_LENGTH - 1; i >= 0; --i) {
            doMove(cubeTmp, invMove(preMoveList[i]));
        }

        tmpDistance = distance(cubeTmp, solvedCube);
        if (tmpDistance < curDistance + 2 && distance(cubeTmp, cube) != 0) {
            if (tmpDistance < curDistance) {
                curDistance = tmpDistance;
            }
            copyCube(cube, cubeTmp);

            for (int i = 0; i < PRE_MOVE_LENGTH; ++i) {
                printf("%s ", move2str[preMoveList[i]]);
            }
            for (int i = 0; i < 8; ++i) {
                printf("%s ", move2str[algMoves[(i + algStartIdx) % 8]]);
            }
            for (int i = PRE_MOVE_LENGTH - 1; i >= 0; --i) {
                printf("%s ", move2str[invMove(preMoveList[i])]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int cube[54];
    srand((unsigned) time(NULL));
    initSolvedCube(cube);
    for (int i = 0; i < 1000; ++i) {
        int move = rand() % 18;
        doMove(cube, move);
    }
    solve(cube);
    return 0;
}                    