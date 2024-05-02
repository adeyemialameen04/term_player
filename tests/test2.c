#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>


int main(void)
{
	CURL *curl;
	CURLcode result;
	char url[2048];
	char value1[] = "A string with spaces";
	char value2[] = "Special characters %$*";

	char *v1safe = curl_easy_escape(curl, value1, 0);
	printf("v1safe: %s\n", v1safe);
	char *v2safe = curl_easy_escape(curl, value2, 0);
	printf("v2safe: %s\n", v2safe);

/*	sprintf(url, "http://localhost", ...) */
	/*
	curl = curl_easy_init();
	if (curl == NULL)
	{
		fprintf(stderr, "HTTP Request failed\n");
		return (-1);
	}

	curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/search?q=cats");

	result = curl_easy_perform(curl);
	if (result != CURLE_OK)
	{
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return (-1);
	}

	curl_easy_cleanup(curl);
	*/

	return (0);
}
