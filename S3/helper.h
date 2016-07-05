#ifndef HEADER_FILE
#define HEADER_FILE
#define SIZE 3

typedef struct _Buffer {
  size_t size;
  char *memory;
} Buffer;

typedef struct weather {
  float min_temp;
  float max_temp;
  float wind;
  float humidity;
  float cloud;
} Weather;

typedef struct location {
  const char *name;
  float latitude;
  float longitude;
} Location;

typedef struct date {
  unsigned int year;
  unsigned short month; unsigned short day;
  unsigned short hour;  unsigned short minute;
  unsigned short second;
  short deviation_hour;
  unsigned short deviation_minute;
} Date;

typedef struct locations {
  size_t length;
  Location* loc_ptr[];
} Locations;

typedef struct weathers {
  size_t length;
  Weather* weathers_ptr[];
} Weathers;


size_t memwrite(char* data, size_t size, size_t nmemb, void* stream);
char* parseDate(Date dt);

#endif
