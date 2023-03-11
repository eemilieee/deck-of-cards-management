// Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "auxiliary.h"

#define LMAX 101

// the function swaps the values of two given integers
void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

// the function initializes the array of known commands
// that eases the process of their validation
void init_known_commands(char commands[13][20])
{
	strcpy(commands[0], "ADD_DECK");
	strcpy(commands[1], "DEL_DECK");
	strcpy(commands[2], "DEL_CARD");
	strcpy(commands[3], "ADD_CARDS");
	strcpy(commands[4], "DECK_NUMBER");
	strcpy(commands[5], "DECK_LEN");
	strcpy(commands[6], "SHUFFLE_DECK");
	strcpy(commands[7], "MERGE_DECKS");
	strcpy(commands[8], "SPLIT_DECK");
	strcpy(commands[9], "REVERSE_DECK");
	strcpy(commands[10], "SHOW_DECK");
	strcpy(commands[11], "SHOW_ALL");
	strcpy(commands[12], "SORT_DECK");
}

// the function returns the number of words contained by a given command
int number_of_words(char s[])
{
	char aux[LMAX], *word;
	int nr = 0;

	strcpy(aux, s);

	word = strtok(aux, " ");

	while (word != NULL)
	{
		nr++;
		word = strtok(NULL, " ");
	}

	return nr;
}

// the function decides whether a "word" from a given command
// represents a valid number or not
int is_number(char s[])
{
	unsigned int i;

	if (!strchr("+-0123456789", s[0]))
		return 0;

	for (i = 1; i < strlen(s); i++)
		if (!strchr("0123456789", s[i]))
			return 0;

	return 1;
}

// the function checks if all the arguments of a given command
// are valid numbers
int only_numbers(char s[])
{
	char aux[LMAX];

	strcpy(aux, s);

	while (strchr(aux, ' '))
	{
		if (!is_number(strrchr(aux, ' ') + 1))
			return 0;
		strcpy(strrchr(aux, ' '), "");
	}

	return 1;
}

// the function validates a given command:
// - if it is known;
// - if it has the correct number of parameters;
// - if the parameters are the accepted type;
int correct_command(char s[], char commands[13][20])
{
	int i, pos = -1;

	// erasing any trailing whitespaces
	while (s[strlen(s) - 1] == ' ')
		strcpy(s + strlen(s) - 1, s + strlen(s));

	while (s[0] == ' ')
		strcpy(s, s + 1);

	for (i = 0; i < 13 && pos < 0; i++)
		if (!(strstr(s, commands[i]) - s))
			pos = i;

	if (pos >= 0)
	{
		if (pos == 4 || pos == 11)
			if (number_of_words(s) != 1)
				pos = -1;
		if (!pos || pos == 1 || pos == 5 || pos == 6
				|| pos == 9 || pos == 10 || pos == 12)
		{
			if (number_of_words(s) != 2)
				pos = -1;
			if (!only_numbers(s))
				pos = -1;
		}
		if (pos == 2 || pos == 3 || pos == 7 || pos == 8)
		{
			if (number_of_words(s) != 3)
				pos = -1;
			if (!only_numbers(s))
				pos = -1;
		}
	}

	return pos;
}

// the function checks if a certain card meets the conditions
int correct_info(Card info)
{
	char symbols[4][10] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
	int i;

	if (info.value < 1 || info.value > 14)
		return -1;

	for (i = 0; i < 4; i++)
		if (!strcmp(info.symbol, symbols[i]))
			return i;
	return -1;
}

// the function allocates the needed memory for a list of decks
Deck_list *create_deck_list()
{
	Deck_list *list;

	list = (Deck_list *)malloc(sizeof(Deck_list));

	list->no_decks = 0;
	list->data_size = sizeof(Node);

	list->first = NULL;
	list->last = NULL;

	return list;
}

// the function allocates the needed memory for a deck of cards
Node *create_deck(int data_size)
{
	Node *deck;

	deck = (Node *)malloc(data_size);

	deck->data = NULL;
	deck->prev = NULL;
	deck->next = NULL;

	return deck;
}

// the function allocates the needed memory for a card
Node *create_card(int data_size, const void *info)
{
	Node *card;

	card = (Node *)malloc(sizeof(Node));
	card->data = (Card *)malloc(data_size);

	card->prev = NULL;
	card->next = NULL;

	memcpy(card->data, info, data_size);

	return card;
}

// the function returns the number of cards contained by a certain deck
int number_of_cards(Node *deck)
{
	Node *aux;
	int nr = 0;

	aux = (Node *)deck->data;

	while (aux != NULL)
	{
		aux = aux->next;
		nr++;
	}

	return nr;
}

// the function inserts a given card at a certain position
// within a chosen deck found in the list
void insert_card(Node *deck, const void *info, int pos)
{
	Node *aux, *new, *first;
	int nr = 0;

	if (pos < 0 || pos > number_of_cards(deck))
		return;
	else
	{
		// there are multiple cases when the card is added:
		// - if it represents the first card of the deck
		if (!number_of_cards(deck))
			deck->data = (Node *)create_card(sizeof(Card), info);
		else
		{
			// allocating memory for the new card
			new = (Node *)create_card(sizeof(Card), info);

			first = (Node *)deck->data;
			// - if it is added to the beginning of the deck
			if (!pos)
			{
				new->next = first;
				first->prev = new;
				first = new;
			}
			// - if it is added to the end of the deck
			else if (pos == number_of_cards(deck))
			{
				aux = first;
				while (nr < (pos - 1))
				{
					aux = aux->next;
					nr++;
				}
				aux->next = new;
				new->prev = aux;
			}
			// - if it is added wherever within the deck
			else
			{
				aux = first;
				while (nr < pos)
				{
					aux = aux->next;
					nr++;
				}
				new->next = aux->next;
				aux->next->prev = new;
				aux->next = new;
				new->prev = aux;
			}
		}
	}
}

// the function iterates through the deck and prints
// each card's details
void show_cards(Node *deck)
{
	Node *aux;
	Card info;
	aux = (Node *)deck->data;
	while (aux != NULL)
	{
		info = *((Card *)aux->data);
		printf("\t%d %s\n", info.value, info.symbol);
		aux = aux->next;
	}
}

// the function deallocates the memory used for saving a whole deck
void free_deck(Node *deck)
{
	Node *del, *p;
	if (deck != NULL)
	{
		del = (Node *)deck->data;
		if (del != NULL)
		{
			// deallocating each found card
			while (del->next != NULL)
			{
				p = del->next;
				free(del->data);
				free(del);
				del = p;
			}
			free(del->data);
			free(del);
		}
		// deallocating the deck
		free(deck);
	}
}

// the function deallocates the memory used for saving a whole list of decks
void free_deck_list(Deck_list *list)
{
	Node *del, *p;
	if (list != NULL && list->no_decks)
	{
		del = list->first;
		// deallocating each found deck
		while (del->next != NULL)
		{
			p = del->next;
			free_deck(del);
			del = p;
		}
		if (del != NULL)
			free_deck(del);
	}
	// deallocating the list
	free(list);
}

// the function removes a certain card located at a chosen position
// from a given deck
void remove_card(Node *deck, int pos)
{
	Node *del, *first, *last;
	int nr = 0;
	first = (Node *)deck->data;
	if (first == NULL)
		return;
	// there are multiple cases when removing the card:
	// - if the card is found at the beginning of the deck
	if (!pos)
	{
		del = first->next;
		memcpy(first->data, del->data, sizeof(Card));
		if (number_of_cards(deck) > 2)
		{
			del->next->prev = del->prev;
			del->prev->next = del->next;
			del->next = NULL;
			del->prev = NULL;
		}
		else
		{
			last = first;
			while (last->next->next != NULL)
				last = last->next;
			del = last->next;
			last->next = NULL;
			del->prev = NULL;
		}
		free(del->data);
		free(del);
	}
	// - if the card is found at the end of the deck
	else if (pos == (number_of_cards(deck) - 1))
	{
		last = first;
		while (last->next->next != NULL)
			last = last->next;
		del = last->next;
		del->prev = NULL;
		last->next = NULL;
		free(del->data);
		free(del);
	}
	// - if the card is found wherever within the deck
	else if (pos > 0 && pos < (number_of_cards(deck) - 1))
	{
		del = first;
		while (nr < pos)
		{
			del = del->next;
			nr++;
		}
		del->next->prev = del->prev;
		del->prev->next = del->next;
		del->next = NULL;
		del->prev = NULL;
		free(del->data);
		free(del);
	}
}

// the function determines the precedence of two given cards
// based on the values and the symbols
int compare(Card a, Card b)
{
	char order[4][20] = {"HEART", "SPADE", "DIAMOND", "CLUB"};
	int i, oa = -1, ob = -1;

	if (a.value > b.value)
		return 1;

	for (i = 0; i < 4 && oa < 0; i++)
		if (!strcmp(order[i], a.symbol))
			oa = i;

	for (i = 0; i < 4 && ob < 0; i++)
		if (!strcmp(order[i], b.symbol))
			ob = i;

	if (a.value == b.value && oa > ob)
		return 1;

	return 0;
}
