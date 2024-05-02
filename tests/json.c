#include <curl/curl.h>
#include <stdio.h>

int main(void)
{
	CURL *hnd;
	CURLcode result;

	hnd = curl_easy_init();
	if (hnd == NULL)
	{
		fprintf(stderr, "Error making a request\n");
		return (-1);
	}

	result = curl_easy_opt
}
