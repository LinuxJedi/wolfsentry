/*
 * wolfsentry_ll.h
 *
 * Copyright (C) 2021 wolfSSL Inc.
 *
 * This file is part of wolfSentry.
 *
 * wolfSentry is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSentry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

#ifndef WOLFSENTRY_LL_H
#define WOLFSENTRY_LL_H

struct wolfsentry_list_ent_header {
    struct wolfsentry_list_ent_header *prev, *next;
};

struct wolfsentry_list_header {
    struct wolfsentry_list_ent_header *head, *tail;
    /* note no cmp_fn slot */
};

#define WOLFSENTRY_LIST_HEADER_RESET(list) (list).head = (list).tail = NULL

static inline void wolfsentry_list_ent_prepend(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header *ent) {
    ent->prev = NULL;
    if (list->head) {
        list->head->prev = ent;
        ent->next = list->head;
        list->head = ent;
    } else {
        ent->next = NULL;
        list->head = list->tail = ent;
    }
}

static inline void wolfsentry_list_ent_append(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header *ent) {
    ent->next = NULL;
    if (list->tail) {
        list->tail->next = ent;
        ent->prev = list->tail;
        list->tail = ent;
    } else {
        ent->prev = NULL;
        list->head = list->tail = ent;
    }
}

static inline void wolfsentry_list_ent_insert_after(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header *point_ent, struct wolfsentry_list_ent_header *new_ent) {
    if (point_ent == NULL) {
        wolfsentry_list_ent_prepend(list, new_ent);
        return;
    }
    new_ent->prev = point_ent;
    if (point_ent->next)
        new_ent->next = point_ent->next;
    else
        list->tail = new_ent;
    point_ent->next = new_ent;
}

static inline void wolfsentry_list_ent_delete(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header *ent) {
    if (ent == list->head) {
        list->head = ent->next;
        if (list->head)
            ent->next->prev = NULL;
        else
            list->tail = NULL;
    } else if (ent == list->tail) {
        list->tail = ent->prev;
        list->tail->next = NULL;
    } else {
        ent->next->prev = ent->prev;
        ent->prev->next = ent->next;
    }
}

static inline void wolfsentry_list_ent_get_first(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header **ent) {
    *ent = list->head;
}

static inline void wolfsentry_list_ent_get_last(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header **ent) {
    *ent = list->tail;
}

static inline void wolfsentry_list_ent_get_next(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header **ent) {
    (void)list;
    *ent = (*ent)->next;
}

static inline void wolfsentry_list_ent_get_prev(struct wolfsentry_list_header *list, struct wolfsentry_list_ent_header **ent) {
    (void)list;
    *ent = (*ent)->prev;
}

#endif /* WOLFSENTRY_LL_H */
