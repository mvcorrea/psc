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

Weather* get_weather(Location* location, Date* date ){
	
	char* url = "https://api.forecast.io/forecast/a24ba3a9fa25f1c267c234aa4cfeb843/";
	char* dt = parseDate( *date );
	Weather* results = (Weather*)malloc(sizeof(Weather));
	
	char str[120] ;
	sprintf(str, "%s%.3f,%.3f,%s?units=ca", url, location->latitude, location->longitude, dt);
	printf("url: %s\n", str);

	json_t *root = http_get_json_data(str);

	if(json_typeof(root) == 0){
		json_t *daily_data = json_array_get(json_object_get(json_object_get(root, "daily"),"data"), 0);
		
		json_t* tempMin = json_object_get(daily_data, "temperatureMin");
		json_t* tempMax = json_object_get(daily_data, "temperatureMax");
		json_t* wind    = json_object_get(daily_data, "windSpeed");
		json_t* humidity= json_object_get(daily_data, "humidity");
		json_t* cloud   = json_object_get(daily_data, "cloudCover");

		results->min_temp = json_number_value(tempMin);
		results->max_temp = json_number_value(tempMax);
		results->wind     = json_number_value(wind);
		results->humidity = json_number_value(humidity);
		results->cloud    = json_number_value(cloud);
/*
		printf(">> %.2f\n", json_number_value(tempMin));
		printf(">> %.2f\n", json_number_value(tempMax));
		printf(">> %.2f\n", json_number_value(wind));
		printf(">> %.2f\n", json_number_value(humidity));
		printf(">> %.2f\n", json_number_value(cloud));
*/	
	}

	return results;
}

int main(int argc, char *argv[]){	
	printf("TRAB PSC: %s\n\n", argv[0]);

	Location *lx = (Location*)malloc(sizeof(Location));
	lx->name = "Lisbon";
	lx->latitude = 38.72;
	lx->longitude = -9.14;

	Date *dt = (Date*)malloc(sizeof(Date));
	dt->year = 2016;
	dt->month = 7;
	dt->day = 1;
	dt->hour = 12;
	dt->minute = 0;
	dt->second = 0;
	dt->deviation_hour = 0;
	dt->deviation_minute = 0;

	Weather *w = get_weather(lx, dt);

	printf("%f, %f, %f, %f, %f\n", w->min_temp, w->max_temp, w->wind, w->humidity, w->cloud);

}		

