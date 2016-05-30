#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>
#include "helper.h"

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

int main(int argc, char *argv[]){
	printf("PSC Trab03 01:\n\n");

	// https://jansson.readthedocs.io/en/2.7/apiref.html   (jasson API reference)

	char *url = "https://api.forecast.io/forecast/a24ba3a9fa25f1c267c234aa4cfeb843/38.72,-9.14";
	char *fname = "forecast.json";

	// S3.II.1
	printf("%d", http_get(url, fname));

}

