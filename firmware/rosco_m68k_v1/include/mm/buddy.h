/*
 *------------------------------------------------------------
 *                                  ___ ___ _   
 *  ___ ___ ___ ___ ___       _____|  _| . | |_ 
 * |  _| . |_ -|  _| . |     |     | . | . | '_|
 * |_| |___|___|___|___|_____|_|_|_|___|___|_,_| 
 *                     |_____|       firmware v1                 
 * ------------------------------------------------------------
 * Copyright (c)2019 Ross Bamford
 * See top-level LICENSE.md for licence information.
 *
 * Binary buddy page allocator
 * ------------------------------------------------------------
 */
#ifndef _ROSCOM68K_MM_BUDDY_H
#define _ROSCOM68K_MM_BUDDY_H

#define PAGE_SIZE 1024

typedef struct __PAGE {
  void          *data;
  struct __PAGE *next;
} mm_page;

mm_page *alloc_page();

#endif

