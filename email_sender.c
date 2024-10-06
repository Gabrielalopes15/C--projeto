#include <stdio.h>
#include <curl/curl.h>
#include "email_sender.h"

void envia_email(const char *para, const char *assunto, const char *mensagem) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *recipients = NULL;
        curl_easy_setopt(curl, CURLOPT_USERNAME, "gabylopes2000@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "mklj rmvw xrlc vaon");
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<gabylopes2000@gmail.com>");
        recipients = curl_slist_append(recipients, para);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_READDATA, mensagem);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}
