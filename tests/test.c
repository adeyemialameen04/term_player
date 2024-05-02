#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct MemoryStruct
{
	char *memory;
	size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

int main(void)
{
	CURL *curl;
	CURLcode result;
	MemoryStruct chunk;

	chunk.memory = malloc(1);
	chunk.size = 0;

	curl = curl_easy_init();
	if (curl == NULL)
	{
		fprintf(stderr, "HTTP request failed\n");
		return (-1);
	}

	curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	printf("Loading ");
	fflush(stdout);

	result = curl_easy_perform(curl);

	printf("\r\033[K");

	if (result != CURLE_OK)
	{
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return (-1);
	}

	printf("%s <--------- response string\n", chunk.memory);
	free(chunk.memory);
	curl_easy_cleanup(curl);	
	return (0);
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct  *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr)
	{
		printf("Not enough memory\n");
		return (0);
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	// Print a loading animation
	static int i = 0;
	static const char *loading_chars = "|/-\\";
	printf("\rLoading %c", loading_chars[i++ % 4]);
	fflush(stdout);
	usleep(100000); // Delay for 100 milliseconds
	return (realsize);
}

