#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <stdbool.h>
#include <json.h>
#include <libintl.h>

#include <locale.h>
#define _(STRING) gettext(STRING)

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\x1B[0m"

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}


int main(int argc, char *argv[])
{
    setlocale (LC_ALL, "");
    bindtextdomain ("pushpanel", getenv("PWD"));
    textdomain ("pushpanel");
    struct json_object *jobj;
    struct passwd *pw = getpwuid(getuid());
    char *homedir = pw->pw_dir;
    char *config_file = "/.pushpanel";
    const char *path = strcat(homedir, config_file);
    char token_t[21];
    long http_code = 0;
    if (access(path, R_OK) == 0) {
        FILE *fp;
        fp = fopen(path, "r");
        fscanf(fp, "%s\n", token_t);
    }
    else {
        printf(_("Please put your token into %s file. \n"), path);
    }

    const char *token = token_t;
    char post[2048] = " ";
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    struct curl_slist *list = NULL;
    char str[300] = "https://dash.pushpanel.io/api/";

    if (argc >= 2) {

    strcat(str, argv[1]);

        for (int i = 2; i < argc; ++i) {
            if (argv[i][0] == '-')
            {
                memmove(argv[i], argv[i]+1, strlen(argv[i]));
                strcat(post,argv[i]);
                strcat(post,"&");
            }
            else
            {
                strcat(str, "/");
                strcat(str, argv[i]);
            }
        }
        strcat(str, "/");
        curl = curl_easy_init();
//        printf("Connection failed: %s\n", str);
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, str);
            if (token != NULL) {
                char tkn[] = "Authorization: Bearer ";
                strcat(tkn, token);
                list = curl_slist_append(list, tkn);
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list); // Inject the token into the header
            }
            if ( post[0] != ' ') {
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
            }
            struct string s;
            init_string(&s);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

            //        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, _("Connection failed: %s\n"),
                        curl_easy_strerror(res));
                curl_easy_cleanup(curl);
            }
            char *ct = NULL;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
    

            if (http_code == 200 && res != CURLE_ABORTED_BY_CALLBACK)
            {
            
            if ( strcmp(ct, "application/json;charset=utf-8" )== 0 ) {
     jobj = json_tokener_parse(s.ptr);
  printf("%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));} 
  else {
                 printf("%s\n", s.ptr);
                 }
                 
                free(s.ptr);
            }
            else
            {
                free(s.ptr);
                if (http_code == 401)
                {
                    printf(_("PushPanel: no authorization. Check yout token. \n"));
                } else {
                    printf(_("PushPanel does not recoginize this command, error in data or no authorization. Try %s pp help %s %s \n"),KGRN,argv[1],RESET);
                }

            }
        }
        else
        {
            printf(_("Connection problem with PushPanel. \n"));
        }
        curl_global_cleanup();
    }
    else
    {
        printf(_("Missing arguments, please try https://pushpanel.io/docs/ .\n"));
    }
    return 0;
}