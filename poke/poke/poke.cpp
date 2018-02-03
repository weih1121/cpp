#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
//定义扑克的花色
enum Suit {
	heart,
	spade,
	diamond,
	club,
	joker1,
	joker2
};
//一副牌的数量
#define CARD_COUNT 54
//定义扑克
typedef struct Card {
	int value;//牌的点数从1开始
	enum Suit suit;//花色
}Card;
//定义玩家
typedef struct Player {
	char name[64];//玩家的名字
	Card ** cards;//玩家分到的牌。每项是一个指针，指向原始一副牌数组中的一项，这样可以节省空间
	int cardsCount;//玩家分到的牌的数量
}Player;
//分牌完成后调用的函数的类型
typedef int(*COMPARE)(Card*, Card*);
//函数声明们
char* getCardName(const Card*);
Card** shuffle(const Card*);
void dispatchCards(Player**, int, const Card**);
void sort(Card**, int, COMPARE);
int compare1(Card*, Card*);
int compare2(Card*, Card*);
void initOnePack();
//原始一副牌所在的数组
Card pokers[CARD_COUNT];
//入口函数
int main(void)
{
	//初始化一副牌
	initOnePack();

	//洗牌，shuffledPokers保存洗后的牌们
	Card** shuffledPokers = shuffle(pokers);
	//构建三个玩家
	Player player1;
	strcpy(player1.name, "隔壁老王");
	player1.cards = NULL;
	player1.cardsCount = 0;
	Player player2;
	strcpy(player2.name, "小明");
	player2.cards = NULL;
	player2.cardsCount = 0;
	Player player3;
	strcpy(player3.name, "田中龟孙");
	player3.cards = NULL;
	player3.cardsCount = 0;
	//把三放到一个数组中，以传入发牌函数中
	Player* players[] = { &player1,&player2,&player3 };
	//发牌
	dispatchCards(players, sizeof(players) / sizeof(Player*), shuffledPokers);
	//洗后的牌用完了，释放之
	free(shuffledPokers);
	int i;
	//打印出每个玩家手中的牌
	for (i = 0; i<sizeof(players) / sizeof(Player*); i++) {
		//先打印玩家的名字
		printf("%s\n", players[i]->name);
		//需要对玩家手中的牌排序
		sort(players[i]->cards, players[i]->cardsCount, compare1);
		//打印玩家手中所有的牌
		int j;
		for (j = 0; j<players[i]->cardsCount; j++) {
			char * name = getCardName(players[i]->cards[j]);
			printf("%s ", name);
			free(name);
		}
		//每个玩家都需要换一次行
		printf("\n");
	}
	//释放玩家手中牌的数组
	for (i = 0; i<sizeof(players) / sizeof(Player*); i++) {
		free(players[i]->cards);
	}
	return 0;
}
//构造一副牌
void initOnePack() {
	int i = 0;
	//前52张
	for (; i<CARD_COUNT - 2; i++) {
		pokers[i].value = i / 4 + 1;
		pokers[i].suit = i % 4;
	}
	//剩下的两张：大王和小王
	//joker1
	pokers[i].value = i / 4 + 1;
	pokers[i].suit = joker1;
	//joker2
	pokers[i + 1].value = i / 4 + 2;
	pokers[i + 1].suit = joker2;
}
//洗牌，参数是原始的一副牌，返回洗完后的牌
Card** shuffle(const Card* pokers) {
	int i;
	//分牌返回牌数组的内存空间
	Card** retPokers = malloc(CARD_COUNT * sizeof(Card*));
	//为了不改动原始的一副牌，另建一个数组，保存原始牌的指针（注意每项不是牌，而是牌的指针）
	Card** pokers2 = malloc(CARD_COUNT * sizeof(Card*));
	for (i = 0; i<CARD_COUNT; i++) {
		pokers2[i] = &pokers[i];
	}
	//种下随机种子。种子取的是当前时间，
	//所以保证了每次运行程序时，产生的随机数序列不同
	srand(time(NULL));
	//取得随机序号，从pokers2取出序号所指的项，把它依次加到retPokers中。
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

	//返回洗完后的数组
	return retPokers;
}
//发牌
//players是玩家数组
//playerCount是玩家数量
//shuffledCards是洗完后的一副牌
void dispatchCards(Player** players, int playerCount, const Card** shuffledCards) {
	//计算每个玩家手中牌的数组的容量，如果每个玩家手中的牌不一样，
	//最多就差一张，加1是为了保证数组分配的空间足够容纳分到的牌。
	int numberCards = CARD_COUNT / playerCount + 1;
	//为每个玩家的牌数组分配空间
	int i;
	for (i = 0; i<playerCount; i++) {
		Card* cards = malloc(numberCards * sizeof(Card*));
		players[i]->cards = cards;
	}
	//轮流向每个玩家发牌
	for (i = 0; i<CARD_COUNT; i++) {
		//取当前玩家
		Player *curPlayer = players[i%playerCount];
		//向玩家发牌
		curPlayer->cards[curPlayer->cardsCount] = shuffledCards[i];
		//玩家手中实际的牌数增加
		curPlayer->cardsCount++;
	}
}
//排序函数
//cards是要排序的牌，每一项是牌的指针
//cardsCount是牌的数量
//compare_func是比较函数
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
//比较函数，先比较点数再比较花色
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
//比较函数，先比较点数再比较花色
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
//获取牌的名字
//返回牌的名字字符串，调用者用完后需要free()之。
char* getCardName(const Card* card) {
	//存放花色名字
	char suitStr[16] = { 0 };//0=='\0'
	switch (card->suit) {
	case heart:
		strcpy(suitStr, "红桃");
		break;
	case spade:
		strcpy(suitStr, "黑桃");
		break;
	case diamond:
		strcpy(suitStr, "方块");
		break;
	case club:
		strcpy(suitStr, "梅花");
		break;
	}
	//存放点数名字
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
		strcpy(valueStr, "小王");
		break;
	case 15:
		strcpy(valueStr, "大王");
		break;
	default:
		sprintf(valueStr, "%d", card->value);
		break;
	}
	//动态分配足够的空间
	char * ret = malloc(16);
	//将两个名字合并到ret中
	sprintf(ret, "%s%s", suitStr, valueStr);
	return ret;
}