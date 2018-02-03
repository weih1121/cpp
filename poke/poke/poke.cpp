#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
//�����˿˵Ļ�ɫ
enum Suit {
	heart,
	spade,
	diamond,
	club,
	joker1,
	joker2
};
//һ���Ƶ�����
#define CARD_COUNT 54
//�����˿�
typedef struct Card {
	int value;//�Ƶĵ�����1��ʼ
	enum Suit suit;//��ɫ
}Card;
//�������
typedef struct Player {
	char name[64];//��ҵ�����
	Card ** cards;//��ҷֵ����ơ�ÿ����һ��ָ�룬ָ��ԭʼһ���������е�һ��������Խ�ʡ�ռ�
	int cardsCount;//��ҷֵ����Ƶ�����
}Player;
//������ɺ���õĺ���������
typedef int(*COMPARE)(Card*, Card*);
//����������
char* getCardName(const Card*);
Card** shuffle(const Card*);
void dispatchCards(Player**, int, const Card**);
void sort(Card**, int, COMPARE);
int compare1(Card*, Card*);
int compare2(Card*, Card*);
void initOnePack();
//ԭʼһ�������ڵ�����
Card pokers[CARD_COUNT];
//��ں���
int main(void)
{
	//��ʼ��һ����
	initOnePack();

	//ϴ�ƣ�shuffledPokers����ϴ�������
	Card** shuffledPokers = shuffle(pokers);
	//�����������
	Player player1;
	strcpy(player1.name, "��������");
	player1.cards = NULL;
	player1.cardsCount = 0;
	Player player2;
	strcpy(player2.name, "С��");
	player2.cards = NULL;
	player2.cardsCount = 0;
	Player player3;
	strcpy(player3.name, "���й���");
	player3.cards = NULL;
	player3.cardsCount = 0;
	//�����ŵ�һ�������У��Դ��뷢�ƺ�����
	Player* players[] = { &player1,&player2,&player3 };
	//����
	dispatchCards(players, sizeof(players) / sizeof(Player*), shuffledPokers);
	//ϴ����������ˣ��ͷ�֮
	free(shuffledPokers);
	int i;
	//��ӡ��ÿ��������е���
	for (i = 0; i<sizeof(players) / sizeof(Player*); i++) {
		//�ȴ�ӡ��ҵ�����
		printf("%s\n", players[i]->name);
		//��Ҫ��������е�������
		sort(players[i]->cards, players[i]->cardsCount, compare1);
		//��ӡ����������е���
		int j;
		for (j = 0; j<players[i]->cardsCount; j++) {
			char * name = getCardName(players[i]->cards[j]);
			printf("%s ", name);
			free(name);
		}
		//ÿ����Ҷ���Ҫ��һ����
		printf("\n");
	}
	//�ͷ���������Ƶ�����
	for (i = 0; i<sizeof(players) / sizeof(Player*); i++) {
		free(players[i]->cards);
	}
	return 0;
}
//����һ����
void initOnePack() {
	int i = 0;
	//ǰ52��
	for (; i<CARD_COUNT - 2; i++) {
		pokers[i].value = i / 4 + 1;
		pokers[i].suit = i % 4;
	}
	//ʣ�µ����ţ�������С��
	//joker1
	pokers[i].value = i / 4 + 1;
	pokers[i].suit = joker1;
	//joker2
	pokers[i + 1].value = i / 4 + 2;
	pokers[i + 1].suit = joker2;
}
//ϴ�ƣ�������ԭʼ��һ���ƣ�����ϴ������
Card** shuffle(const Card* pokers) {
	int i;
	//���Ʒ�����������ڴ�ռ�
	Card** retPokers = malloc(CARD_COUNT * sizeof(Card*));
	//Ϊ�˲��Ķ�ԭʼ��һ���ƣ���һ�����飬����ԭʼ�Ƶ�ָ�루ע��ÿ����ƣ������Ƶ�ָ�룩
	Card** pokers2 = malloc(CARD_COUNT * sizeof(Card*));
	for (i = 0; i<CARD_COUNT; i++) {
		pokers2[i] = &pokers[i];
	}
	//����������ӡ�����ȡ���ǵ�ǰʱ�䣬
	//���Ա�֤��ÿ�����г���ʱ����������������в�ͬ
	srand(time(NULL));
	//ȡ�������ţ���pokers2ȡ�������ָ����������μӵ�retPokers�С�
	for (i = 0; i<CARD_COUNT; i++) {
		unsigned int index = rand() % CARD_COUNT;
		if (pokers2[index] != NULL) {
			retPokers[i] = pokers2[index];
			pokers2[index] = NULL;
		}
		else {
			i--;
		}
	}
	free(pokers2);

	//����ϴ��������
	return retPokers;
}
//����
//players���������
//playerCount���������
//shuffledCards��ϴ����һ����
void dispatchCards(Player** players, int playerCount, const Card** shuffledCards) {
	//����ÿ����������Ƶ���������������ÿ��������е��Ʋ�һ����
	//���Ͳ�һ�ţ���1��Ϊ�˱�֤�������Ŀռ��㹻���ɷֵ����ơ�
	int numberCards = CARD_COUNT / playerCount + 1;
	//Ϊÿ����ҵ����������ռ�
	int i;
	for (i = 0; i<playerCount; i++) {
		Card* cards = malloc(numberCards * sizeof(Card*));
		players[i]->cards = cards;
	}
	//������ÿ����ҷ���
	for (i = 0; i<CARD_COUNT; i++) {
		//ȡ��ǰ���
		Player *curPlayer = players[i%playerCount];
		//����ҷ���
		curPlayer->cards[curPlayer->cardsCount] = shuffledCards[i];
		//�������ʵ�ʵ���������
		curPlayer->cardsCount++;
	}
}
//������
//cards��Ҫ������ƣ�ÿһ�����Ƶ�ָ��
//cardsCount���Ƶ�����
//compare_func�ǱȽϺ���
void sort(Card** cards, int cardsCount, COMPARE compare_func) {
	int i;
	for (i = 0; i<cardsCount - 1; i++) {
		int j;
		for (j = 0; j<cardsCount - i - 1; j++) {
			if (compare_func(cards[j], cards[j + 1])) {
				int tmp = cards[j];
				cards[j] = cards[j + 1];
				cards[j + 1] = tmp;
			}
		}
	}
}
//�ȽϺ������ȱȽϵ����ٱȽϻ�ɫ
int compare1(Card* a, Card* b) {
	if (a->value > b->value) {
		return 1;
	}
	else if (a->value < b->value) {
		return 0;
	}
	else {
		if (a->suit > b->suit)
			return 1;
		else
			return 0;
	}
}
//�ȽϺ������ȱȽϵ����ٱȽϻ�ɫ
int compare2(Card* a, Card* b) {
	if (a->value > b->value) {
		return 0;
	}
	else if (a->value < b->value) {
		return 1;
	}
	else {
		if (a->suit > b->suit)
			return 0;
		else
			return 1;
	}
}
//��ȡ�Ƶ�����
//�����Ƶ������ַ������������������Ҫfree()֮��
char* getCardName(const Card* card) {
	//��Ż�ɫ����
	char suitStr[16] = { 0 };//0=='\0'
	switch (card->suit) {
	case heart:
		strcpy(suitStr, "����");
		break;
	case spade:
		strcpy(suitStr, "����");
		break;
	case diamond:
		strcpy(suitStr, "����");
		break;
	case club:
		strcpy(suitStr, "÷��");
		break;
	}
	//��ŵ�������
	char valueStr[16];
	switch (card->value) {
	case 1:
		strcpy(valueStr, "A");
		break;
	case 11:
		strcpy(valueStr, "J");
		break;
	case 12:
		strcpy(valueStr, "Q");
		break;
	case 13:
		strcpy(valueStr, "K");
		break;
	case 14:
		strcpy(valueStr, "С��");
		break;
	case 15:
		strcpy(valueStr, "����");
		break;
	default:
		sprintf(valueStr, "%d", card->value);
		break;
	}
	//��̬�����㹻�Ŀռ�
	char * ret = malloc(16);
	//���������ֺϲ���ret��
	sprintf(ret, "%s%s", suitStr, valueStr);
	return ret;
}