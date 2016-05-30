#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>
#include "helper.h"

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
	printf("PSC Trab03 02:\n\n");

	// https://jansson.readthedocs.io/en/2.7/apiref.html   (jasson API reference)

	char *url = "https://api.forecast.io/forecast/a24ba3a9fa25f1c267c234aa4cfeb843/38.72,-9.14";

	// S3.II.2
	json_t *root = http_get_json_data(url);
	printf("%d\n", json_typeof(root)); // return 0 (json object)
	json_t *timezone = json_object_get(root, "timezone");
	if(json_is_string(timezone)) printf("%s\n", json_string_value(timezone)); // Europe/Lisbon

}

