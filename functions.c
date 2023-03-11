// Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "auxiliary.h"

#define LMAX 101

// the function prints the number of cards contained by a certain deck
// of the given list
void deck_len(Deck_list *list, int pos)
{
	Node *aux;
	int nr = 0;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}
		printf("The length of deck %d is %d.\n", pos, number_of_cards(aux));
	}
}

// the function prints the number of decks contained by the given list
void deck_number(Deck_list *list)
{
	printf("The number of decks is %d.\n", list->no_decks);
}

// the function inserts a certain number of cards
// to the end-point of the chosen deck
// by using an auxiliary function (insert_card())
void add_cards(Deck_list *list, int pos, int number_cards)
{
	Node *aux;
	Card info;
	int nr = 0;
	char *pair;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}

		pair = (char *)malloc(LMAX * sizeof(char));
		nr = 0;

		// reading the card details and checking whether they are
		// correct or not until the number of inserted cards is reached
		while (nr < number_cards)
		{
			fgets(pair, LMAX, stdin);
			pair[strlen(pair) - 1] = '\0';
			if (number_of_words(pair) == 2)
			{
				strcpy(info.symbol, strrchr(pair, ' ') + 1);
				strcpy(strchr(pair, ' '), "");
				info.value = atoi(pair);
				if (correct_info(info) < 0)
					printf("The provided card is not a valid one.\n");
				else
				{
					insert_card(aux, &info, number_of_cards(aux));
					nr++;
				}
			}
			else
				printf("The provided card is not a valid one.\n");
		}

		free(pair);
		printf("The cards were successfully added to deck %d.\n", pos);
	}
}

// the function inserts a certain number of cards to a new deck
// that is added to a chosen position of the given list
// by using an auxiliary function (insert_card())
void add_deck(Deck_list *list, int pos, int number_cards)
{
	Node *aux, *new;
	Card info;
	char *pair;
	int nr = 0;

	if (list == NULL || (pos < 0 || pos > list->no_decks))
		return;
	else
	{
		// allocating memory for the new deck
		new = create_deck(sizeof(Node));
		pair = (char *)malloc(LMAX * sizeof(char));
		// reading the card details and checking whether they are
		// correct or not until the number of inserted cards is reached
		while (nr < number_cards)
		{
			fgets(pair, LMAX, stdin);
			pair[strlen(pair) - 1] = '\0';
			if (number_of_words(pair) == 2)
			{
				strcpy(info.symbol, strrchr(pair, ' ') + 1);
				strcpy(strchr(pair, ' '), "");
				info.value = atoi(pair);
				if (correct_info(info) < 0)
					printf("The provided card is not a valid one.\n");
				else
				{
					insert_card(new, &info, number_of_cards(new));
					nr++;
				}
			}
			else
				printf("The provided card is not a valid one.\n");
		}
		free(pair);
		// adding the new deck to the list based on the position
		// there are multiple cases:
		// - if the list is empty
		if (!list->no_decks)
		{
			list->first = new;
			list->last = new;
		}
		else
		{
			// - if the deck is added to the beginning of the list
			if (!pos)
			{
				new->next = list->first;
				list->first->prev = new;
				list->first = new;
			}
			// - if the deck is added to the end of the list
			else if (pos == list->no_decks)
			{
				list->last->next = new;
				new->prev = list->last;
				list->last = new;
			}
			// - if the deck is added wherever within the list
			else
			{
				// moving on to the chosen position in the list
				nr = 0;
				aux = list->first;
				while (nr < pos)
				{
					aux = aux->next;
					nr++;
				}
				// adding the deck
				new->next = aux->next;
				aux->next->prev = new;
				aux->next = new;
				new->prev = aux;
			}
		}
		// updating the number of existing decks
		list->no_decks++;
		printf("The deck was successfully created with %d cards.\n", number_cards);
	}
}

// the function prints the contained cards of a chosen deck of the given list
// by using an auxiliary function (show_cards())
void show_deck(Deck_list *list, int pos)
{
	Node *aux;
	int nr = 0;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on the to desired deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}
		printf("Deck %d:\n", pos);
		show_cards(aux);
	}
}

// the function prints the contained cards of all decks found in the list
void show_all(Deck_list *list)
{
	int i;
	for (i = 0; i < list->no_decks; i++)
		show_deck(list, i);
}

// the function removes a certain deck from the given list
// and deallocates its used memory by using an auxiliary function (free_deck)
void del_deck(Deck_list *list, int pos, int use)
{
	Node *del;
	int nr = 0;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// there are multiple cases when deleting a deck from the list:
		// - if there is an only deck
		if (list->no_decks == 1)
			free_deck(list->first);
		else
		{
			// - if the deck is removed from the beginning of the list
			if (!pos)
			{
				del = list->first;
				list->first = list->first->next;
				list->first->prev = NULL;
				del->next = NULL;
				free_deck(del);
			}
			// - if the deck is removed from the end of the list
			else if (pos == (list->no_decks - 1))
			{
				del = list->last;
				list->last = list->last->prev;
				list->last->next = NULL;
				del->prev = NULL;
				free_deck(del);
			}
			// - if the deck is removed from any mid-point of the list
			else
			{
				del = list->first;
				while (nr < pos)
				{
					del = del->next;
					nr++;
				}
				del->next->prev = del->prev;
				del->prev->next = del->next;
				del->next = NULL;
				del->prev = NULL;
				free_deck(del);
			}
		}
		// updating the number of existing decks
		list->no_decks--;
		if (use)
			printf("The deck %d was successfully deleted.\n", pos);
	}
}

// the function removes a certain card from a chosen deck from the given list
// and deallocates its used memory
// both operations take place using an auxiliary function (remove_card())
void del_card(Deck_list *list, int deck_pos, int card_pos)
{
	Node *aux;
	int nr = 0;

	if (list == NULL || (deck_pos < 0 || deck_pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck from which the card is erased
		aux = list->first;
		while (nr < deck_pos)
		{
			aux = aux->next;
			nr++;
		}
		if (card_pos < 0 || (card_pos >= number_of_cards(aux)))
			printf("The provided index is out of bounds for deck %d.\n", deck_pos);
		else
		{
			if (number_of_cards(aux) > 1)
			{
				remove_card(aux, card_pos);
				printf("The card was successfully deleted from deck %d.\n", deck_pos);
			}
			// if the deck contains a single card it is wholly removed
			else
			{
				del_deck(list, deck_pos, 0);
				printf("The card was successfully deleted from deck %d.\n", deck_pos);
			}
		}
	}
}

// the function shuffles a chosen deck from the given list
// by removing half of the cards from the beginning of the deck one by one
// and adding then to the end of the deck
void shuffle_deck(Deck_list *list, int pos)
{
	Node *aux, *first;
	Card info;
	int i, nr = 0;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving in to the chosen deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}
		// shuffling the deck
		for (i = 0; i < number_of_cards(aux) / 2; i++)
		{
			first = (Node *)aux->data;
			info = *((Card *)first->data);
			remove_card(aux, 0);
			insert_card(aux, &info, number_of_cards(aux));
		}
		printf("The deck %d was successfully shuffled.\n", pos);
	}
}

// the function prints the success message of the "merge" operation
// of two decks from a list
void print_merge_message(int pos1, int pos2, int ok)
{
	if (ok)
	{
		printf("The deck %d and the ", pos1);
		printf("deck %d were successfully merged.\n", pos2);
	}
	else
	{
		printf("The deck %d and the ", pos2);
		printf("deck %d were successfully merged.\n", pos1);
	}
}

// the function merges two chosen decks from a given list
// and removing them from the list
void merge_decks(Deck_list *list, int pos1, int pos2)
{
	Node *aux1, *aux2, *new, *c1, *c2;
	int nr = 0, ok = 1;

	if (list == NULL || (pos1 < 0 || pos1 >= list->no_decks))
		ok = 0;
	if (list == NULL || (pos2 < 0 || pos2 >= list->no_decks))
		ok = 0;
	if (pos1 == pos2)
		return;

	if (!ok)
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// allocating memory for the new deck
		new = create_deck(sizeof(Node));

		// moving on to the chosen decks
		aux1 = list->first;
		aux2 = list->first;
		while (nr < pos1) {
			aux1 = aux1->next;
			nr++;
		}
		nr = 0;
		while (nr < pos2) {
			aux2 = aux2->next;
			nr++;
		}
		nr = 0;
		// accesing the first cards from both decks
		c1 = (Node *)aux1->data;
		c2 = (Node *)aux2->data;
		// merging the decks by adding their cards alternatively
		// to the new deck
		while (c1 != NULL && c2 != NULL)
		{
			if (!(nr % 2)) {
				insert_card(new, c1->data, number_of_cards(new));
				c1 = c1->next;
			} else {
				insert_card(new, c2->data, number_of_cards(new));
				c2 = c2->next;
			}
			nr++;
		}
		// if the decks contain a different number of cards, the remaining
		// ones are added to the new deck
		while (c1 != NULL) {
			insert_card(new, c1->data, number_of_cards(new));
			c1 = c1->next;
		}
		while (c2 != NULL) {
			insert_card(new, c2->data, number_of_cards(new));
			c2 = c2->next;
		}
		// adding the new deck to the end of the list
		list->last->next = new;
		new->prev = list->last;
		list->last = new;

		// updating the total number of decks
		list->no_decks++;

		// removing the merged decks as they are not needed anymore
		if (pos2 < pos1)
		{
			swap(&pos1, &pos2);
			ok = 0;
		}
		del_deck(list, pos1, 0);
		del_deck(list, pos2 - 1, 0);
		print_merge_message(pos1, pos2, ok);
	}
}

// the function prints the success message of the "split" operation
// of a deck from a list
void print_split_message(int d_pos, int s_pos)
{
	printf("The deck %d was successfully split by index %d.\n", d_pos, s_pos);
}

// the function splits a chosen deck from the given list
// into two separate ones
void split_deck(Deck_list *list, int deck_pos, int split_pos)
{
	Node *aux, *new, *c;
	Card info;
	int nr = 0;

	if (list == NULL || (deck_pos < 0 || deck_pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck
		aux = list->first;
		while (nr < deck_pos)
		{
			aux = aux->next;
			nr++;
		}

		nr = 0;

		if (split_pos >= 0 && split_pos < number_of_cards(aux))
		{
			if (split_pos > 0)
			{
				// allocating memory for a new deck
				new = create_deck(sizeof(Node));

				c = (Node *)aux->data;

				// moving to the beginning of the card sequence
				// that will be contained by the new deck
				while (nr < split_pos)
				{
					c = c->next;
					nr++;
				}

				nr = split_pos;

				// adding the seqeunce of cards to the new deck
				while (c != NULL)
				{
					info = *((Card *)c->data);
					insert_card(new, &info, number_of_cards(new));
					c = c->next;
					nr++;
				}

				int len = number_of_cards(aux) - 1;

				// removing the sequence from the base deck
				while (len >= split_pos)
				{
					remove_card(aux, number_of_cards(aux) - 1);
					len--;
				}

				// adding the new deck right after the base one
				// there are two cases:
				// - if the deck is added within the list
				if ((deck_pos + 1) == list->no_decks)
				{
					list->last->next = new;
					new->prev = list->last;
					list->last = new;
				}
				// - if the deck is added at the end of the list
				else
				{
					new->next = aux->next;
					aux->next->prev = new;
					aux->next = new;
					new->prev = aux;
				}
				// updating the number of decks
				list->no_decks++;
			}
			print_split_message(deck_pos, split_pos);
		}
		else
			printf("The provided index is out of bounds for deck %d.\n", deck_pos);
	}
}

// the function reverses the order of the cards contained by a certain deck
// of the given list
void reverse_deck(Deck_list *list, int pos)
{
	Node *aux, *first, *last, *c1, *c2;
	Card i1, i2;
	int nr = 0, len;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}

		len = number_of_cards(aux);
		if (len)
		{
			// finding the first and the last card of the deck
			first = (Node *)aux->data;
			last = first;

			while (last->next != NULL)
				last = last->next;

			c1 = first;
			c2 = last;
			nr = 0;
			// swapping the card details
			// (one from the beginning and one from the end and advancing
			// until the mid-point of the list is reached)
			while (nr < len / 2)
			{
				i1 = *((Card *)c1->data);
				i2 = *((Card *)c2->data);
				memcpy((Card *)c1->data, &i2, sizeof(Card));
				memcpy((Card *)c2->data, &i1, sizeof(Card));
				c1 = c1->next;
				c2 = c2->prev;
				nr++;
			}
		}
		printf("The deck %d was successfully reversed.\n", pos);
	}
}

// the function sorts a certain deck of the given list
// depending on the cards' values and symbol priorities
void sort_deck(Deck_list *list, int pos)
{
	Node *aux, *c1, *c2;
	Card i1, i2;
	int nr = 0;

	if (list == NULL || (pos < 0 || pos >= list->no_decks))
		printf("The provided index is out of bounds for the deck list.\n");
	else
	{
		// moving on to the chosen deck
		aux = list->first;
		while (nr < pos)
		{
			aux = aux->next;
			nr++;
		}

		// sorting the cards by swapping their details
		// (finding the least significant card each iteration)
		c1 = (Node *)aux->data;
		while (c1 != NULL)
		{
			c2 = c1->next;
			while (c2 != NULL)
			{
				i1 = *((Card *)c1->data);
				i2 = *((Card *)c2->data);
				if (compare(i1, i2))
				{
					memcpy((Card *)c1->data, &i2, sizeof(Card));
					memcpy((Card *)c2->data, &i1, sizeof(Card));
				}
				c2 = c2->next;
			}
			c1 = c1->next;
		}
		printf("The deck %d was successfully sorted.\n", pos);
	}
}
