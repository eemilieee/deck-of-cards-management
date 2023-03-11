// Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)
#ifndef AUXILIARY_H_
#define AUXILIARY_H_

#define LMAX 101

typedef struct Card Card;

struct Card
{
	int value;
	char symbol[LMAX];
};

typedef struct Node Node;

struct Node
{
	void *data;
	Node *prev, *next;
};

typedef struct Deck_list Deck_list;

struct Deck_list
{
	Node *first, *last;
	int no_decks;
	int data_size;
};

void swap(int *a, int *b);
void init_known_commands(char commands[12][20]);
int number_of_words(char s[]);
int is_number(char s[]);
int only_numbers(char s[]);
int correct_command(char s[], char commands[12][20]);
int correct_info(Card info);
int compare(Card a, Card b);

Deck_list *create_deck_list();
Node *create_deck(int data_size);
Node *create_card(int data_size, const void *info);
int number_of_cards(Node *deck);
void insert_card(Node *deck, const void *info, int pos);
void show_cards(Node *deck);
void free_deck(Node *deck);
void free_deck_list(Deck_list *list);
void remove_card(Node *deck, int pos);

#endif  // AUXILIARY_H_
