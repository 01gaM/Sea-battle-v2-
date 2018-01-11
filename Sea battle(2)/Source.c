#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "Header.h"

//
int main() {
	setlocale(LC_ALL, "RUS");
	printf_s("Óñëîâíûå îáîçíà÷åíèÿ:\n");
	printf_s("o - ÷àñòü êîðàáëÿ\n");
	printf_s(". - ïóñòàÿ êëåòêà\n");
	printf_s("x - ïîâðåæä¸ííàÿ ÷àñòü êîðàáëÿ\n");
	printf_s("* - ïîòîïëåííûé êîðàáëü\n");
	char field[FIELD_SIZE][FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			field[i][j] = ' ';//"îáíóëÿåì" ïîëå
		}
	}
	printField(field, 1);

	int shipsCount[] = { 4,3,2,1 };//o - 4, oo - 3, ooo - 2, oooo - 1
	
	while (getSumm(shipsCount, 4) != 0) {////////////////öèêë ðàññòàíîâêè êîðàáëåé
		printShipsCount(shipsCount);
		int currType;
		int x;
		struct Coordinate beginning;
		struct Coordinate ending;
		printf_s("Âûáåðèòå òèï êîðàáëÿ: ");
		currType = getType();
		while (shipsCount[currType - 1] == 0) {
			printf_s("Êîðàáëè äàííîãî òèïà çàêîí÷èëèñü. Âûáåðèòå äðóãîé òèï: ");
			currType = getType();
		}
		if (currType == 1) {
			printf_s("Óêàæèòå åãî êîîðäèíàòû: ");
			beginning = getCoordinate(field);

		}
		else {
			printf_s("Óêàæèòå êîîðäèíàòû íà÷àëà êîðàáëÿ: ");
			beginning = getCoordinate(field);

			printf_s("Óêàæèòå êîîðäèíàòû êîíöà êîðàáëÿ: ");
			ending = getCoordinate(field);

			//////êîîðäèíàòû äîëæíû áûòü íà îäíîé ëèíèè
			while ((beginning.ch != ending.ch) && (beginning.num != ending.num)) {
				printf_s("Êîîðäèíàòû íà÷àëà è êîíöà êîðàáëÿ äîëæíû áûòü íà îäíîé ëèíèè.\n");
				printf_s("Óêàæèòå êîîðäèíàòû íà÷àëà êîðàáëÿ: ");
				beginning = getCoordinate(field);
				printf_s("Óêàæèòå êîîðäèíàòû êîíöà êîðàáëÿ: ");
				ending = getCoordinate(field);
			}

			/////////beginning<ending
			while ((beginning.ch > ending.ch) || (beginning.num > ending.num)) {
				printf_s("Êîîðäèíàòû íà÷àëà äîëæíû áûòü ìåíüøå êîîðäèíàò êîíöà êîðàáëÿ.\n");
				printf_s("Óêàæèòå êîîðäèíàòû íà÷àëà êîðàáëÿ: ");
				beginning = getCoordinate(field);
				printf_s("Óêàæèòå êîîðäèíàòû êîíöà êîðàáëÿ: ");
				ending = getCoordinate(field);
			}

			//////////ïðîâåðêà äëèíû êîðàáëÿ 

			while (getShipLen(beginning, ending) != currType - 1) {
				printf_s("Äëèíà äîëæíà ñîîòâåòñòâîâàòü òèïó %d, óêàæèòå äðóãèå êîîðäèíàòû.\n", currType);
				printf_s("Óêàæèòå êîîðäèíàòû íà÷àëà êîðàáëÿ: ");
				beginning = getCoordinate(field);

				printf_s("Óêàæèòå êîîðäèíàòû êîíöà êîðàáëÿ: ");
				ending = getCoordinate(field);

			}
		}

		////////ïðîâåðêà íà ñîïðèêàñàíèå êîðàáëåé
		if (addShip(field, beginning, ending, currType) == 0) {
			printf_s("Êîðàáëü ïåðåñåêàåòñÿ ñ ñîñåäíèìè. Âûáåðèòå äðóãîé êîðàáëü.\n");
		}
		else {
			shipsCount[currType - 1]--;
		}
		printField(field, 1);
	}
	

	char botField[FIELD_SIZE][FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			botField[i][j] = ' ';//"îáíóëÿåì" ïîëå
		}
	}

	fillBotField(botField);//çàïîëíÿåì ïîëå áîòà

	struct Coordinate aim;
	struct Coordinate botAim;
	botAim.ch = '0';//îáíóëÿåì òåêóùóþ öåëü áîòà 
	botAim.num = 0;
	int playerShipsCount[] = { 4,3,2,1 };//îñòàâøèåñÿ êîðàáëè èãðîêà
	int botShipsCount[] = { 4,3,2,1 };//îñòàâøèåñÿ êîðàáëè ïðîòèâíèêà
	printGameSpace(field, botField, botShipsCount, playerShipsCount);
	//èãðîâîé öèêë
	while ((getSumm(playerShipsCount, 4) != 0) && (getSumm(botShipsCount, 4) != 0)) {
		//õîä èãðîêà

		printf_s("\nÂâåäèòå êîîðäèíàòû öåëè: ");
		aim = getCoordinate(botField);
		int t = nextTurn(aim, botField, botShipsCount);
		while ((t == 1) || (t == 2)) {//åñëè èãðîê ïîïàë ïî öåëè, òî ñëåäóþùèé õîä ïåðåõîäèò åìó
			printGameSpace(field, botField, botShipsCount, playerShipsCount);
			printf_s("\nÂâåäèòå êîîðäèíàòû öåëè: ");
			aim = getCoordinate(botField);
			t = nextTurn(aim, botField, botShipsCount);
		}

		printGameSpace(field, botField, botShipsCount, playerShipsCount);
		if (t == 3) {//åñëè âñå êîðàáëè ïðîòèâíèêà óáèòû
			break;
		}

		//õîä áîòà
		printf_s("\nÕîä ïðîòèâíèêà\n");
		botAim = botTurn(field, botField, botShipsCount, playerShipsCount, botAim);

	}
	if (getSumm(playerShipsCount, 4) == 0) {
		printf_s("\nÂû ïðîèãðàëè!");
	}
	else {
		printf_s("\nÂû âûéãðàëè!");
	}

	int x = getchar();
	while (x != '\n') {//ñáðàñûâàåì âñ¸ ââåä¸ííîå ðàíåå
		x = getchar();
	}
	printf_s("\nÂâåäèòå ëþáîé ñèìâîë äëÿ âûõîäà: ");//ñ÷èòûâàåì íîâûå äàííûå
	getchar();
	return 0;
}

