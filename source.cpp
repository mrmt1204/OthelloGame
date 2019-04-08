#include <stdio.h>
using namespace std;

#define B 10
#define BLACK 1
#define WHITE 2
#define EMPTY 0
#define WALL -1

int board[B][B];

void init_board(int board[B][B]){

	for (int i = 0; i < B; i++) {
		for (int j = 0; j < B; j++) {
			board[i][j] = -1;
		}
	}
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			board[i][j] = 0;
		}
	}
	board[4][5] = board[5][4] = 1;
	board[4][4] = board[5][5] = 2;
}

void board_style(int board[B][B]){

	printf("   a b c d e f g h \n");
	printf("  -----------------\n");
	for (int i = 1; i <= 8; i++) {
		printf("%d|", i);
		for (int j = 1; j <= 8; j++) {
			printf("%2d", board[i][j]);
		}
		printf(" |\n");
	}
	printf("  -----------------\n");
}

#define chng(player) (3-(player))

int count_turn_over(int board[B][B], int player, int p, int q, int r, int s) {
	int i;

	for (i = 1; board[p + i * r][q + i * s] == chng(player); i++) {};

	if (board[p + i * r][q + i * s] == player) {
		return i - 1;
	}
	else {
		return 0;
	}
}

int is_legal_move(int board[B][B], int player, int p, int q) {
	if (p < 1 || p > 8 || q < 1 || q > 8) {
		return 0;
	}
	else if (board[p][q] != 0) {
		return 0;
	}else{
		for (int r = -1; r <= 1; r++) {
			for (int s = -1; s <= 1; s++) {
				if (count_turn_over(board, player, p, q, r, s)) return 1;
			}
		}
	}
	return 0;
}

int exist_legal_move(int board[B][B], int player) {

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (is_legal_move(board, player, i, j)) return 1;
		}
	}
	return 0;
}

void get_move(int board[B][B], int player, int *p, int *q) {
	char str[100];

	printf("Player %d ", player);
	while (1) {
		printf("> ");
		fgets(str, sizeof(str), stdin);
		*q = str[0] - 'a' + 1;
		*p = str[1] - '1' + 1;
		if (is_legal_move(board, player, *p, *q)) return;
	}
}

void set_and_turn_over(int board[B][B], int player, int p, int q) {
	int count = 0;

	for (int d = -1; d <= 1; d++) {
		for (int e = -1; e <= 1; e++) {
			if (d == 0 && e == 0) continue;
			count = count_turn_over(board, player, p, q, d, e);
			for (int i = 1; i <= count; i++) {
				board[p + i * d][q + i * e] = player;
			}
		}
	}
	board[p][q] = player;
}

void count_stone(int board[B][B], int* cnt1, int* cnt2, int* cnt0) {

	*cnt1 = 0;
	*cnt2 = 0;
	*cnt0 = 0;

	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (board[i][j] == 1) {
				(*cnt1)++;
			}else if(board[i][j] == 2) {
				(*cnt2)++;
			}else {
				(*cnt0)++;
			}
		}
	}
}

int game() {
	int p, q, player, c1, c2, c3;
	int board[B][B];

	init_board(board);
	player = 1;
	while (1) {
		board_style(board);
		if (!exist_legal_move(board, player)) {
			printf("Player %d has no legal moves > pass\n", player);
			player = chng(player);
			if (!exist_legal_move(board, player)) {
				printf("Player %d has no legal moves > pass\n", player);
				break;
			}
		}
		get_move(board, player, &p, &q);
		set_and_turn_over(board, player, p, q);
		player = chng(player);
	}
	count_stone(board, &c1, &c2, &c3);
	printf("Game Over!\nPlayer 1 : %d\nPlayer 2 : %d\nEmpty : %d\n", c1, c2, c3);
	if (c1 > c2) {
		printf("Player 1 wins!");
	}
	else {
		printf("Player 2 wins!");
	}
	return c1 - c2;
}

int main() {
	//string name[100];
	char ans[100];
	printf("Let's play Othello!\nYour name?\n");
	//scanf_s("%s", name, 100);
	printf("Please enter this: ex.c4, g7\n");
	do {
		game();
		printf("Play again? (Y/N) > ");
		scanf_s("%s", ans, 100);
	} while (ans[0] == 'y' || ans[0] == 'Y');
	return 0;
}
