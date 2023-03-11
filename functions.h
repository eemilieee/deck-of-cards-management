// Copyright 2022 Arpasanu Emilia-Oana 311CA (emilia.arpasanu@stud.acs.upb.ro)
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "auxiliary.h"

void deck_len(Deck_list *list, int pos);
void deck_number(Deck_list *list);
void add_cards(Deck_list *list, int pos, int number_cards);
void add_deck(Deck_list *list, int pos, int number_cards);
void show_deck(Deck_list *list, int pos);
void show_all(Deck_list *list);
void del_deck(Deck_list *list, int pos, int use);
void del_card(Deck_list *list, int deck_pos, int card_pos);
void shuffle_deck(Deck_list *list, int pos);
void merge_decks(Deck_list *list, int pos1, int pos2);
void split_deck(Deck_list *list, int deck_pos, int split_pos);
void reverse_deck(Deck_list *list, int pos);
void sort_deck(Deck_list *list, int pos);

#endif  // FUNCTIONS_H_
