#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

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



int http_get(const char *uri, const char *filename){ // S3.II.1
	
	FILE *fp;
	CURL *curl_handle;
	CURLcode curl_result;

	curl_handle = curl_easy_init();
	if(!curl_handle) return 1;
	fp = fopen(filename, "wb");
	curl_easy_setopt(curl_handle, CURLOPT_URL, uri);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, NULL);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
	curl_result = curl_easy_perform(curl_handle);
	curl_easy_cleanup(curl_handle);
	fclose(fp);
	return 0;
}

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

json_t* http_get_json_data(const char *uri){	// S3.II.2

	Buffer buffer = { .size = 0, .memory = NULL };
	
	json_t *result;
	json_error_t error;

	CURL *curl_handle;
	CURLcode curl_result;

	curl_handle = curl_easy_init();
	if(!curl_handle) return NULL;
	curl_easy_setopt(curl_handle, CURLOPT_URL, uri);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, memwrite);
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &buffer);
	curl_result = curl_easy_perform(curl_handle);
	
	result = json_loads(buffer.memory, 0, &error);

	curl_easy_cleanup(curl_handle);
	curl_global_cleanup();

	//fprintf(stderr, "%zu bytes received\n", (long)buffer.size);
	//fprintf(stderr, "%.*s", (int)buffer.size, buffer.memory);
	//fprintf(stderr, "%s", buffer.memory);

	return result;	
}

int main(int argc, char *argv[]){
	printf("grab json file example:\n\n");

	// https://jansson.readthedocs.io/en/2.7/apiref.html   (jasson API reference)

	char *url = "https://api.forecast.io/forecast/a24ba3a9fa25f1c267c234aa4cfeb843/38.72,-9.14";
	//char *fname = "forecast.json";

	// S3.II.1
	//printf("%d", http_get(url, fname));

	// S3.II.2
	json_t *root = http_get_json_data(url);
	printf("%d\n", json_typeof(root)); // return 0 (json object)
	json_t *timezone = json_object_get(root, "timezone");
	if(json_is_string(timezone)) printf("%s\n", json_string_value(timezone)); // Europe/Lisbon

	


}

