// Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "auxiliary.h"

#define LMAX 101

int main()
{
	Deck_list *list;
	char known_commands[13][20], command[LMAX];
	int c, deck_pos, split_pos, card_pos, no_cards, pos1, pos2;

	list = create_deck_list();
	init_known_commands(known_commands);
	fgets(command, LMAX, stdin);

	while (!strstr(command, "EXIT"))
	{
		strcpy(command + strlen(command) - 1, command + strlen(command));
		c = correct_command(command, known_commands);
		if (c >= 0)
		{
			if (!c) {
				no_cards = atoi(strrchr(command, ' ') + 1);
				add_deck(list, list->no_decks, no_cards);
			} else if (c == 1) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				del_deck(list, deck_pos, 1);
			} else if (c == 2) {
				card_pos = atoi(strrchr(command, ' ') + 1);
				strcpy(strrchr(command, ' '), "");
				deck_pos = atoi(strrchr(command, ' ') + 1);
				del_card(list, deck_pos, card_pos);
			} else if (c == 3) {
				no_cards = atoi(strrchr(command, ' ') + 1);
				strcpy(strrchr(command, ' '), "");
				deck_pos = atoi(strrchr(command, ' ') + 1);
				add_cards(list, deck_pos, no_cards);
			} else if (c == 4) {
				deck_number(list);
			} else if (c == 5) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				deck_len(list, deck_pos);
			} else if (c == 6) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				shuffle_deck(list, deck_pos);
			} else if (c == 7) {
				pos2 = atoi(strrchr(command, ' ') + 1);
				strcpy(strrchr(command, ' '), "");
				pos1 = atoi(strrchr(command, ' ') + 1);
				merge_decks(list, pos1, pos2);
			} else if (c == 8) {
				split_pos = atoi(strrchr(command, ' ') + 1);
				strcpy(strrchr(command, ' '), "");
				deck_pos = atoi(strrchr(command, ' ') + 1);
				split_deck(list, deck_pos, split_pos);
			} else if (c == 9) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				reverse_deck(list, deck_pos);
			} else if (c == 10) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				show_deck(list, deck_pos);
			} else if (c == 11) {
				show_all(list);
			} else if (c == 12) {
				deck_pos = atoi(strrchr(command, ' ') + 1);
				sort_deck(list, deck_pos);
			}
		}
		else
			printf("Invalid command. Please try again.\n");
		fgets(command, LMAX, stdin);
	}
	free_deck_list(list);
}
