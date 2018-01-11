#include "Header.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void printBorder() {
	int stripeLen = 41;
	printf_s("\n  ");
	for (int i = 0; i < stripeLen; i++) {
		printf_s("-");
	}
}

void printField(char field[FIELD_SIZE][FIELD_SIZE], int mode) {

	char ch = 'A';
	printf_s("  ");
	for (int i = 1; i <= FIELD_SIZE; i++) {
		printf_s("  %d ", i);
	}
	printBorder();
	printf_s("\n");
	for (int i = 0; i < FIELD_SIZE; i++) {
		printf_s("%c |", ch);
		for (int j = 0; j < FIELD_SIZE; j++) {
			if ((mode == 2) && (field[i][j] == 'o')) {
				printf_s("   |");
			}
			else {
				printf_s(" %c |", field[i][j]);
			}
		}
		printBorder();
		printf_s("\n");
		ch++;
	}
}

int getSumm(int arr[], int size) {
	int s = 0;
	for (int i = 0; i < size; i++) {
		s += arr[i];
	}
	return s;
}

void printShipsCount(int shipsCount[]) {
	printf_s("���������� �������:\n");
	for (int i = 0; i < 4; i++) {
		printf_s("��� %d: %d - ", i + 1, shipsCount[i]);
		for (int j = 0; j <= i; j++) {
			printf_s("o");
		}
		printf_s("\n");
	}
}



int checkNeighbours(char map[FIELD_SIZE][FIELD_SIZE], int currI, int currJ) {
	if (map[currI][currJ] != ' ') {
		return 0;
	}
	////////check top
	if ((map[currI - 1][currJ] != ' ') && (currI > 0)) {
		return 0;
	}
	////////check bot
	if ((map[currI + 1][currJ] != ' ') && (currI < 9)) {
		return 0;
	}
	////////check left
	if ((map[currI][currJ - 1] != ' ') && (currJ > 0)) {
		return 0;
	}
	////////check right
	if ((map[currI][currJ + 1] != ' ') && (currJ < 9)) {
		return 0;
	}
	///////////////���������

	////����� ������� ����
	if ((map[currI - 1][currJ - 1] != ' ') && (currI > 0) && (currJ > 0)) {
		return 0;
	}
	///����� ������ ����
	if ((map[currI + 1][currJ - 1] != ' ') && (currI < 9) && (currJ > 0)) {
		return 0;
	}
	////������ ������� ����
	if ((map[currI - 1][currJ + 1] != ' ') && (currI > 0) && (currJ < 9)) {
		return 0;
	}
	///������ ������ ����
	if ((map[currI + 1][currJ + 1] != ' ') && (currI < 9) && (currJ < 9)) {
		return 0;
	}


	return 1;//����� �� ������������ � ���������

}


int addShip(char map[FIELD_SIZE][FIELD_SIZE], struct Coordinate b, struct Coordinate e, int type) {//��������� �������
	if (type == 1) {
		int num2 = b.ch - 'A';
		if (checkNeighbours(map, num2, b.num - 1) == 0) {
			return 0;
		}
		map[num2][b.num - 1] = 'o';
	}
	else {
		int num1 = b.ch - 'A';
		int num2 = e.ch - 'A';


		for (int i = num1; i <= num2; i++) {
			for (int j = b.num; j <= e.num; j++) {
				if (checkNeighbours(map, i, j - 1) == 0) {
					return 0;
				}
			}
		}

		for (int i = num1; i <= num2; i++) {
			for (int j = b.num; j <= e.num; j++) {
				map[i][j - 1] = 'o';
			}
		}
	}
	return 1;//success
}

int getShipLen(struct Coordinate b, struct Coordinate e) {
	int s1 = e.ch - b.ch;
	int s2 = e.num - b.num;
	if (s1 > s2) {
		return s1;
	}
	return s2;

}



void fillBotField(char map[FIELD_SIZE][FIELD_SIZE]) {
	//int currI;
	int currJ;
	int endI;
	int endJ;
	struct Coordinate begin;
	struct Coordinate end;
	srand(time(NULL));//������������� rand
	int botShipsCount[] = { 4,3,2,1 };//o - 4, oo - 3, ooo - 2, oooo - 1
	while (getSumm(botShipsCount, 4) != 0) {
		for (int currType = 3; currType >= 0; currType--) {
			while (botShipsCount[currType] > 0) {//���� ������� ����� ���� �� �����������
				begin.ch = rand() % 10 + 'A';//'A'-'J'
				begin.num = rand() % 10 + 1;//1-10
				end.ch = '-';
				end.num = -1;
				int currI = begin.ch - 'A';
				if (currI + currType < 9) {
					end.ch = begin.ch + currType;//������������ ������������ �������
					end.num = begin.num;
				}
				else {
					if (begin.num + currType < 9) {
						end.num = begin.num + currType;
						end.ch = begin.ch;
					}
				}
				if ((end.ch != '-') && (end.num != -1)) {//���� ������� ������ � ����
														 //�������� �������� ������� �� ����
					if (addShip(map, begin, end, currType + 1) == 1) {//���� ������
						botShipsCount[currType]--;//������� ������� �� ������ ���������
					}
				}
				//printField(map);
				//printShipsCount(botShipsCount);
			}
		}
	}

}

int isKilled(struct Coordinate aim, char field[FIELD_SIZE][FIELD_SIZE]) {
	int c1 = aim.ch - 'A';
	int c2 = aim.num - 1;
	int checkCoordinate1;
	int checkCoordinate2;

	//��������� ����
	checkCoordinate1 = c1 - 1;

	while ((checkCoordinate1 >= 0) && (field[checkCoordinate1][c2] != ' ') && (field[checkCoordinate1][c2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[checkCoordinate1][c2] == 'o') {
			return 0;//������� ������������� ����� �������
		}
		checkCoordinate1--;
	}


	//��������� ���
	checkCoordinate1 = c1 + 1;

	while ((checkCoordinate1 <= 9) && (field[checkCoordinate1][c2] != ' ') && (field[checkCoordinate1][c2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[checkCoordinate1][c2] == 'o') {
			return 0;//������� ������������� ����� �������
		}
		checkCoordinate1++;
	}


	//��������� ����
	checkCoordinate2 = c2 - 1;

	while ((checkCoordinate2 >= 0) && (field[c1][checkCoordinate2] != ' ') && (field[c1][checkCoordinate2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[c1][checkCoordinate2] == 'o') {
			return 0;//������� ������������� ����� �������
		}
		checkCoordinate2--;
	}

	//��������� �����
	checkCoordinate2 = c2 + 1;

	while ((checkCoordinate2 <= 9) && (field[c1][checkCoordinate2] != ' ') && (field[c1][checkCoordinate2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[c1][checkCoordinate2] == 'o') {
			return 0;//������� ������������� ����� �������
		}
		checkCoordinate2++;
	}
	return 1;//������� ����
}

void destroyShip(struct Coordinate aim, char field[FIELD_SIZE][FIELD_SIZE], int shipCount[]) {
	int c1 = aim.ch - 'A';
	int c2 = aim.num - 1;
	int checkCoordinate1;
	int checkCoordinate2;
	int isHorizontal = 1;
	int shipLen = 0;//����� ������� - 1
	field[c1][c2] = '*';

	//��������� ����
	checkCoordinate1 = c1 - 1;

	while ((checkCoordinate1 >= 0) && (field[checkCoordinate1][c2] != ' ') && (field[checkCoordinate1][c2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[checkCoordinate1][c2] == 'x') {
			isHorizontal = 0;
			field[checkCoordinate1][c2] = '*';
			if (c2 - 1 >= 0) {
				field[checkCoordinate1][c2 - 1] = '.';
			}
			if (c2 + 1 <= 9) {
				field[checkCoordinate1][c2 + 1] = '.';
			}
			if ((checkCoordinate1 - 1 >= 0) && ((field[checkCoordinate1 - 1][c2] == ' ') || (field[checkCoordinate1 - 1][c2] == '.'))) {
				field[checkCoordinate1 - 1][c2] = '.';
				if (c2 - 1 >= 0) {
					field[checkCoordinate1 - 1][c2 - 1] = '.';
				}
				if (c2 + 1 <= 9) {
					field[checkCoordinate1 - 1][c2 + 1] = '.';
				}
			}
			shipLen++;
		}
		checkCoordinate1--;
	}



	//��������� ���
	checkCoordinate1 = c1 + 1;

	while ((checkCoordinate1 <= 9) && (field[checkCoordinate1][c2] != ' ') && (field[checkCoordinate1][c2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
		if (field[checkCoordinate1][c2] == 'x') {
			isHorizontal = 0;
			field[checkCoordinate1][c2] = '*';
			if (c2 - 1 >= 0) {
				field[checkCoordinate1][c2 - 1] = '.';
			}
			if (c2 + 1 <= 9) {
				field[checkCoordinate1][c2 + 1] = '.';
			}
			if ((checkCoordinate1 + 1 <= 9) && ((field[checkCoordinate1 + 1][c2] == ' ') || (field[checkCoordinate1 + 1][c2] == '.'))) {
				field[checkCoordinate1 + 1][c2] = '.';
				if (c2 - 1 >= 0) {
					field[checkCoordinate1 + 1][c2 - 1] = '.';
				}
				if (c2 + 1 <= 9) {
					field[checkCoordinate1 + 1][c2 + 1] = '.';
				}
			}
			shipLen++;
		}
		checkCoordinate1++;
	}

	if (isHorizontal == 1) {
		//��������� ����
		checkCoordinate2 = c2 - 1;

		while ((checkCoordinate2 >= 0) && (field[c1][checkCoordinate2] != ' ') && (field[c1][checkCoordinate2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
			if (field[c1][checkCoordinate2] == 'x') {
				field[c1][checkCoordinate2] = '*';
				if (c1 - 1 >= 0) {
					field[c1 - 1][checkCoordinate2] = '.';
				}
				if (c1 + 1 <= 9) {
					field[c1 + 1][checkCoordinate2] = '.';
				}
				if ((checkCoordinate2 - 1 >= 0) && ((field[c1][checkCoordinate2 - 1] == ' ') || (field[c1][checkCoordinate2 - 1] == '.'))) {
					field[c1][checkCoordinate2 - 1] = '.';
					if (c1 - 1 >= 0) {
						field[c1 - 1][checkCoordinate2 - 1] = '.';
					}
					if (c1 + 1 <= 9) {
						field[c1 + 1][checkCoordinate2 - 1] = '.';
					}
				}
				shipLen++;
			}
			checkCoordinate2--;
		}

		//��������� �����
		checkCoordinate2 = c2 + 1;

		while ((checkCoordinate2 <= 9) && (field[c1][checkCoordinate2] != ' ') && (field[c1][checkCoordinate2] != '.')) {//���� �� ����� �� ����� ���� ��� �� ����� �������� �������
			if (field[c1][checkCoordinate2] == 'x') {
				field[c1][checkCoordinate2] = '*';
				if (c1 - 1 >= 0) {
					field[c1 - 1][checkCoordinate2] = '.';
				}
				if (c1 + 1 <= 9) {
					field[c1 + 1][checkCoordinate2] = '.';
				}
				if ((checkCoordinate2 + 1 <= 9) && ((field[c1][checkCoordinate2 + 1] == ' ') || (field[c1][checkCoordinate2 + 1] == '.'))) {
					field[c1][checkCoordinate2 + 1] = '.';
					if (c1 - 1 >= 0) {
						field[c1 - 1][checkCoordinate2 + 1] = '.';
					}
					if (c1 + 1 <= 9) {
						field[c1 + 1][checkCoordinate2 + 1] = '.';
					}
				}
				shipLen++;
			}
			checkCoordinate2++;
		}
	}
	shipCount[shipLen]--;


	//�������� ������� � ������ ������� ������ ��� ������
	if (isHorizontal == 1) {
		if (c1 - 1 >= 0) {
			field[c1 - 1][c2] = '.';
		}
		if (c1 + 1 <= 9) {
			field[c1 + 1][c2] = '.';
		}
		if ((c2 - 1 >= 0) && (field[c1][c2 - 1] != '*')) {
			field[c1][c2 - 1] = '.';
			if (c1 - 1 >= 0) {
				field[c1 - 1][c2 - 1] = '.';
			}
			if (c1 + 1 <= 9) {
				field[c1 + 1][c2 - 1] = '.';
			}
		}
		if ((c2 + 1 <= 9) && (field[c1][c2 + 1] != '*')) {
			field[c1][c2 + 1] = '.';
			if (c1 - 1 >= 0) {
				field[c1 - 1][c2 + 1] = '.';
			}
			if (c1 + 1 <= 9) {
				field[c1 + 1][c2 + 1] = '.';
			}
		}
	}
	else {
		if (c2 - 1 >= 0) {
			field[c1][c2 - 1] = '.';
		}
		if (c2 + 1 <= 9) {
			field[c1][c2 + 1] = '.';
		}
		if ((c1 - 1 >= 0) && (field[c1 - 1][c2] != '*')) {
			field[c1 - 1][c2] = '.';
			if (c2 - 1 >= 0) {
				field[c1 - 1][c2 - 1] = '.';
			}
			if (c2 + 1 <= 9) {
				field[c1 - 1][c2 + 1] = '.';
			}
		}
		if ((c1 + 1 <= 9) && (field[c1 + 1][c2] != '*')) {
			field[c1 + 1][c2] = '.';
			if (c2 - 1 >= 0) {
				field[c1 + 1][c2 - 1] = '.';
			}
			if (c2 + 1 <= 9) {
				field[c1 + 1][c2 + 1] = '.';
			}
		}
	}
}



int nextTurn(struct Coordinate aim, char field[FIELD_SIZE][FIELD_SIZE], int shipCount[]) {
	///���� � �������� ������� �� ��� ����� ������� ����������, �� �������� ������ �� "x"
	//���� � �������� ������� ��� ����� ������� ����������(��� �� ���� 1), �� �������� ��� ������ ������� �� "*"

	int c1 = aim.ch - 'A';
	int c2 = aim.num - 1;

	if (field[c1][c2] == ' ') {//��������� ����
		field[c1][c2] = '.';
		return 0;
	}
	if (field[c1][c2] != 'o') {//��������� ����� ������ ��� �����
		return -1;
	}

	if (isKilled(aim, field) == 0) {
		field[c1][c2] = 'x';
		return 1;//������� '�����'
	}
	else {
		///�������� ��� ������ ������� �� *
		destroyShip(aim, field, shipCount);
	}
	if (getSumm(shipCount, 4) == 0) {
		return 3;//game over
	}
	return 2;//������� '����'
}



void printGameSpace(char player1[FIELD_SIZE][FIELD_SIZE], char player2[FIELD_SIZE][FIELD_SIZE], int botCount[], int playerCount[]) {
	printf_s("���� ����:\n");
	printField(player1, 1);// 1 - ����� 1
	printShipsCount(playerCount);
	printf_s("\n���� ����������:\n");
	printField(player2, 2);//2 - ����� 2
	printShipsCount(botCount);
}



int hitTarget(struct Coordinate target, char field[FIELD_SIZE][FIELD_SIZE], int shipCount[]) {

	//����
	struct Coordinate aim;
	aim.num = target.num;
	aim.ch = target.ch - 1;
	int x;

	if ((aim.ch - 'A' >= 0) && ((field[aim.ch - 'A'][aim.num - 1] == 'o') || (field[aim.ch - 'A'][aim.num - 1] == ' '))) {
		x = nextTurn(aim, field, shipCount);
		printf_s("\n%d%c\n", aim.num, aim.ch);
		while ((x == 1) && (aim.ch - 'A' - 1 >= 0)) {
			aim.ch--;
			x = nextTurn(aim, field, shipCount);
			printf_s("\n%d%c\n", aim.num, aim.ch);
		}
		if (x == 2) {
			return 1;//success
		}
		return -1;//������� �� ��������� ��������
	}

	//���
	aim.ch = target.ch + 1;
	if ((aim.ch - 'A' <= 9) && ((field[aim.ch - 'A'][aim.num - 1] == 'o') || (field[aim.ch - 'A'][aim.num - 1] == ' '))) {
		x = nextTurn(aim, field, shipCount);
		printf_s("\n%d%c\n", aim.num, aim.ch);
		while ((x == 1) && (aim.ch - 'A' + 1 <= 9)) {
			aim.ch++;
			x = nextTurn(aim, field, shipCount);
			printf_s("\n%d%c\n", aim.num, aim.ch);
		}
		if (x == 2) {
			return 1;//success
		}
		return -1;//������� �� ��������� ��������
	}
	//����
	aim.ch = target.ch;
	aim.num = target.num - 1;
	if ((aim.num > 0) && ((field[aim.ch - 'A'][aim.num - 1] == 'o') || (field[aim.ch - 'A'][aim.num - 1] == ' '))) {//>=0
		x = nextTurn(aim, field, shipCount);
		printf_s("\n%d%c\n", aim.num, aim.ch);
		while ((x == 1) && (aim.num - 1 > 0)) {//aim.num - 2 >= 0
			aim.num--;
			x = nextTurn(aim, field, shipCount);
			printf_s("\n%d%c\n", aim.num, aim.ch);
		}
		if (x == 2) {
			return 1;//success
		}
		return -1;//������� �� ��������� ��������
	}
	//�����
	aim.num = target.num + 1;
	if ((aim.num <= 10) && ((field[aim.ch - 'A'][aim.num - 1] == 'o') || (field[aim.ch - 'A'][aim.num - 1] == ' '))) {//<= 9
		x = nextTurn(aim, field, shipCount);
		printf_s("\n%d%c\n", aim.num, aim.ch);
		while ((x == 1) && (aim.num + 1 <= 10)) {
			aim.num++;
			x = nextTurn(aim, field, shipCount);
			printf_s("\n%d%c\n", aim.num, aim.ch);
		}
		if (x == 2) {
			return 1;//success
		}
		return -1;//������� �� ��������� ��������
	}
}

int search(char field[FIELD_SIZE][FIELD_SIZE], int shipCount[], struct Coordinate* aim) {
	//struct Coordinate aim;
	int currX = 3;
	int x;
	int currY = 0;
	while (currY < 10) {//������ ���������(����� ������� ����� 4)
		aim->ch = currX + 'A';
		aim->num = currY + 1;
		x = nextTurn(*aim, field, shipCount);
		if (x != -1) {
			printf_s("\n%d%c\n", aim->num, aim->ch);
		}
		if ((x != -1) && (x != 2)) {//���������� �����, ������ ���� ����� ������� ��� �������� ��� ����������� ������
			return x;
		}
		if (currX + 4 < 10) {
			currX += 4;
		}
		else {
			currX--;
			currX -= 4 * (int)(currX / 4);
			currY++;
		}
	}

	currX = 1;
	currY = 0;
	while (currY < 10) {//������ ��������� (����� �������� ����� 3 � 2)
		aim->ch = currX + 'A';
		aim->num = currY + 1;
		x = nextTurn(*aim, field, shipCount);
		if (x != -1) {
			printf_s("\n%d%c\n", aim->num, aim->ch);
		}
		if ((x != -1) && (x != 2)) {//���������� �����, ���� ����� ������� ��� �������� ��� ����������� ������

			return x;
		}
		if (currX + 4 < 10) {
			currX += 4;
		}
		else {
			currX--;
			currX -= 4 * (int)(currX / 4);
			currY++;
		}
	}
	for (int i = 0; i < 10; i++) {//����� �������� ����� 1
		for (int j = 0; j < 10; j++) {
			if ((field[i][j] == 'o') || (field[i][j] == ' ')) {
				aim->ch = i + 'A';
				aim->num = j + 1;
				x = nextTurn(*aim, field, shipCount);
				printf_s("\n%d%c\n", aim->num, aim->ch);
				if ((x != -1) && (x != 2)) {//���������� �����, ���� ����� ������� ��� �������� ��� ����������� ������
					return x;
				}

			}
		}
	}
}

struct Coordinate botTurn(char enemyField[FIELD_SIZE][FIELD_SIZE], char field[FIELD_SIZE][FIELD_SIZE], int botShipCount[], int playerShipCount[], struct Coordinate currAim) {
	///test 3.0
	int y = 0;//�������������� y
	int x;
	if ((currAim.ch == '0') && (currAim.num == 0)) {//���� ��� ������� ����
		x = search(enemyField, playerShipCount, &currAim);//������� �
	}
	else {
		x = 1;
	}

	if (x == 1) {//���� ���� ���������(���� ����)
		y = hitTarget(currAim, enemyField, playerShipCount);//�������� ������ ���� �������
	}
	else {
		currAim.ch = '0';//�������� ������� ����, �.�. ��������� ����
		currAim.num = 0;
	}
	//printGameSpace(enemyField, field, botShipCount, playerShipCount);
	if (y == 1) {//���� ���� ����������
		currAim.ch = '0';//�������� ������� ����
		currAim.num = 0;
		return botTurn(enemyField, field, botShipCount, playerShipCount, currAim);//������ ���� �.�. ��������� 
	}
	printGameSpace(enemyField, field, botShipCount, playerShipCount);////////////////////////////////////////////////
	//���� �� ����������, �� ��������� ������� ���� ��� ���������
	return currAim;
}

/*
struct Coordinate getCoordinate(char field[FIELD_SIZE][FIELD_SIZE]) {
	struct Coordinate c;
	int x = scanf_s("%d%c", &c.num, &c.ch);
	while ((x == 0) || (c.ch < 'A') || (c.ch > 'J') || (c.num < 1) || (c.num > 10)) {
		printf_s("\n���������� ������� ������ �������� �� ������ ����� �� 1 �� 10 � ����� �� 'A' �� 'J'.\n������� ������ ����������: ");
		//���������� �������� ����� ������
		x = getchar();
		while (x != '\n') {
			x = getchar();
		}
		//��������� ����� ������
		x = scanf_s("%d%c", &c.num, &c.ch);
	}
	if ((field[c.ch - 'A'][c.num - 1] != 'o') && (field[c.ch - 'A'][c.num - 1] != ' ')) {
		printf_s("\n������ ����� ��� ���������. ������� ����� ����������: ");
		return getCoordinate(field);
	}
	return c;
}
*/

struct Coordinate getCoordinate(char field[FIELD_SIZE][FIELD_SIZE]) {
	struct Coordinate c;
	char ch = '0';//������ ����� ���������
	int x = scanf_s("%d%c", &c.num, &c.ch);
	if (c.ch != '\n') {//���� ���� ������� �� ������ �����
		ch = getchar();//�������� ������ ����� �������� ���������
	}
	while ((c.ch < 'A') || (c.ch > 'J') || (c.num < 1) || (c.num > 10) || (ch != '\n') || (x != 2)) {
		printf_s("\n���������� ������� ������ �������� �� ������ ����� �� 1 �� 10 � ����� �� 'A' �� 'J'.\n������� ������ ����������: ");
		//���������� �������� ����� ������
		if ((ch != '\n') && (c.ch != '\n') || (x != 2)) {//���� ���� ������� ���-�� ����� ����� � �����
			x = getchar();
			while (x != '\n') {
				x = getchar();
			}
		}
		//��������� ����� ������
		x = scanf_s("%d%c", &c.num, &c.ch);
		if (c.ch != '\n') {//���� ���� ������� �� ������ �����
			ch = getchar();//�������� ������ ����� �������� ���������
		}
		else {
			ch = '0';//"��������" ������
		}
	}
	if ((field[c.ch - 'A'][c.num - 1] != 'o') && (field[c.ch - 'A'][c.num - 1] != ' ')) {
		printf_s("\n������ ����� ��� ���������. ������� ����� ����������: ");
		return getCoordinate(field);
	}
	return c;
}

/*
int getType() {
	int currType;
	char x;
	char ch;
	scanf_s("%d%c", &currType, &ch);
	while ((currType < 1) || (currType > 4) || (ch != '\n')) {//���� ����� �� �������� ���������� ��� ���� ��� ���� ������� �� ������ �����
		printf_s("������������ �������� ����. ������� ����� �� 1 �� 4: ");
		if (ch != '\n') {//���� ����� ���� ������� �� ������ ���� �����
			x = getchar();
			while (x != '\n') {//���������� �� �������� �����
				x = getchar();
			}
		}
		scanf_s("%d%c", &currType, &ch);//��������� ����� ������
	}
	return currType;
}
*/
int getType() {
	int currType;
	char ch;
	int x = scanf_s("%d%c", &currType, &ch);
	while ((x != 2) || (currType < 1) || (currType > 4) || (ch != '\n')) {//���� ����� �� �������� ���������� ��� ���� ��� ���� ������� �� ������ �����
		printf_s("������������ �������� ����. ������� ����� �� 1 �� 4: ");
		if ((ch != '\n')||(x != 2)) {//���� ����� ���� ������� �� ������ ���� ����� (�������� ������ �������� ������)
			x = getchar();
			while (x != '\n') {//���������� �� �������� �����
				x = getchar();
			}
		}
		x = scanf_s("%d%c", &currType, &ch);//��������� ����� ������
	}
	return currType;
}