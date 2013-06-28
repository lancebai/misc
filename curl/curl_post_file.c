/* example of using libcrl to upload file with http post, rfc2388*/
#include <stdio.h>
#include <string.h>

#include <curl/curl.h>

int main(int argc, char *argv[])
{
  CURL *curl;
  struct curl_httppost *post = NULL;
  struct curl_httppost *last = NULL;


  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if(curl)
  {
    curl_formadd(&post, &last, 
        CURLFORM_COPYNAME, "file",
        CURLFORM_FILE, "testcurl.txt",
        CURLFORM_END);

    curl_easy_setopt(curl, CURLOPT_URL, "http://somewhere.com/some_request_url");
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
 
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* then cleanup the formpost chain */
    curl_formfree(post);
  }

  return 0;
}
