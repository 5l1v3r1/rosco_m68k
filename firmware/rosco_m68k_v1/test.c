#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN ((16-1))

typedef enum {
  OK,
  OOM,
  CLASH,
  FAILURE
} RegisterLibraryResult;

typedef struct _library {
  uint32_t          key;
  uint32_t          magic;
  void*             library;
  struct _library   *next;
} Library;

static Library *first = NULL;

static uint32_t make_key(char *name) {
  int len = strlen(name);
  char * end;

  if (len > 6) {
    len = 6;
  }
    
  return strtol(name, &end, 36);
}
  
RegisterLibraryResult RegisterLibrary(char *name, uint32_t magic, void* library) {
  uint32_t key = make_key(name);

  if (first == NULL) {
    // first lib - just register
    first = malloc(sizeof(Library));

    if (first == NULL) {
      return OOM;
    } else {

      first->key = key;
      first->magic = magic;
      first->library = library;
      first->next = NULL;

      return OK;
    }
  } else {
    Library *cur = first;
    Library *prev = NULL;

    while (key > cur->key && cur->next != NULL) {
      prev = cur;
      cur = cur->next;
    }

    if (key > cur->key && cur->next == NULL) {
      // add at end
      cur->next = malloc(sizeof(Library));
      cur = cur->next;

      if (cur == NULL) {
        return OOM;
      } else {
        cur->key = key;
        cur->magic = magic;
        cur->library = library;
        cur->next = NULL;
      }
    } else {
      // is equal?
      if (cur->key == key) {
        return CLASH;
      } else {
        // insert here
        Library *new = malloc(sizeof(Library));

        if (new == NULL) {
          return OOM;
        } else {
          new->key = key;
          new->magic = magic;
          new->library = library;

          if (prev == NULL) {
            // at start of list
            new->next = cur;
            first = new;
          } else {

            // middle of list
            new->next = prev->next;
            prev->next = new;
          }
        }
      }
    }

    return OK;
  }
}

void* FindLibrary(char *name, uint32_t magic) {

}

int main() {
  RegisterLibrary("2", 0x1234, "library 2");
  RegisterLibrary("3", 0x4321, "library 3");
  RegisterLibrary("1", 0x4321, "library 1");
  RegisterLibrary("5", 0x4321, "library 5");
  RegisterLibrary("4", 0x4321, "library 4");
  RegisterLibrary("ao", 0x4321, "library ao");
  RegisterLibrary("aa", 0x4321, "library aa");

  Library *cur = first;

  while (cur != NULL) {
    printf("Library %s : key: 0x%08x : magic 0x%08x\n", (char*)cur->library, cur->key, cur->magic);

    cur = cur->next;
  }
}

