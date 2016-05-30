#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

size_t memwrite(char* data, size_t size, size_t nmemb, void* stream){
  size_t byteCount = size * nmemb;
  Buffer *bufptr = (Buffer *) stream;

  // grow the buffer in order to hold more byteCount bytes
  bufptr->memory = realloc(bufptr->memory, bufptr->size + byteCount + 1);
  if (bufptr->memory == NULL) {
    fprintf(stderr, "error: not enough memory\n");
    return -1;
  }

  // copy data block
  memcpy(bufptr->memory + bufptr->size, data, byteCount);
  // update size and close the C string
  bufptr->size += byteCount;
  bufptr->memory[bufptr->size] = '\0';
  return byteCount;
}






