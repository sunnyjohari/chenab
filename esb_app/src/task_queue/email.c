#include <stdio.h>
#include <string.h>

#include <curl/curl.h>


#define FROM ""
#define CC ""

struct upload_status
{
    int lines_read;
};

int send_mail(char *to, char *file_path)
{
    printf("Sending to %s\n", to);

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if (curl)
    {
        /* Set username and password */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "");

        /* URL for mail server */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

      
        /* FROM address */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        /* Recipients */
        recipients = curl_slist_append(recipients, to);
        recipients = curl_slist_append(recipients, CC);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

      
        //curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        FILE *fp = fopen(file_path, "r");
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

       /* Gives information about whats running inside libcurl */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

   
 return (int)res;
}


int main()
{ //  char *path = payload_to_xml();
    int t = send_mail("", "file.txt");
    printf("%d", t);
    return 0;
}

