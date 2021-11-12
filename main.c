#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int finder(FILE *fpt, char *sub_string, int substr_len);
void soutput(FILE *fpt, char special_char);
void uoutput(FILE *fpt, char special_char);
struct curl_slist *header_seter(struct curl_slist *head);
struct curl_slist *csrf_seter(struct curl_slist *head, FILE *fptr, CURL *curl);
void imageDownloader(FILE *fpt,CURL *curl,char*file_name);

void webpage(CURL *curl);

int main()
{
    struct curl_slist *header = NULL;
    header = header_seter(header);

    CURL *curl;
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curl, CURLOPT_COOKIE, "");

    webpage(curl);

    FILE *fptr = fptr = fopen("webpage.txt", "r");

    char substr[50] = "<script type=\"text/javascript\">window._sharedData";
    printf("%d\n\n", finder(fptr, substr, 50));

    {
        char csrf_string[14] = "csrf_token\":\"";
        finder(fptr, csrf_string, 14);
        header = csrf_seter(header, fptr, curl);

        char bio_string[13] = "biography\":\"";
        finder(fptr, bio_string, 13);
        soutput(fptr, '\"');

        char followers_string[28] = "edge_followed_by\":{\"count\":";
        finder(fptr, followers_string, 28);
        soutput(fptr, '}');

        char following_string[23] = "edge_follow\":{\"count\":";
        finder(fptr, following_string, 23);
        soutput(fptr, '}');

        char fullname_string[13] = "full_name\":\"";
        finder(fptr, fullname_string, 13);
        soutput(fptr, '\"');

        char highlighted_reel_string[23] = "highlight_reel_count\":";
        finder(fptr, highlighted_reel_string, 23);
        soutput(fptr, ',');

        char is_verified_string[14] = "is_verified\":";
        finder(fptr, is_verified_string, 14);
        soutput(fptr, ',');

        header = curl_slist_append(curl, "Accept: image/webp,*/*");
        // curl_easy_setopt(curl, CURLOPT_HTTPHEADER,header);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);





        char profile_pic_string[19] = "profile_pic_url\":\"";
        finder(fptr, profile_pic_string, 19);
        uoutput(fptr, '\"');

        printf("\n\n\n");

        char profile_pic_hd_string[22] = "profile_pic_url_hd\":\"";
        finder(fptr, profile_pic_hd_string, 22);
        uoutput(fptr, '\"');

        finder(fptr, "GraphImage", 10);

        char display_url_string[15] = "display_url\":\"";
        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');

        finder(fptr, display_url_string, 15);
        uoutput(fptr, '\"');
    }

    fclose(fptr);

    FILE *urlfptr = fopen("url.txt","r");
    
    imageDownloader(urlfptr,curl,"out/pic1.jpg");
    imageDownloader(urlfptr,curl,"out/pic2.jpg");
    imageDownloader(urlfptr,curl,"out/pic3.jpg");
    imageDownloader(urlfptr,curl,"out/pic4.jpg");
    imageDownloader(urlfptr,curl,"out/pic5.jpg");
    imageDownloader(urlfptr,curl,"out/pic6.jpg");
    imageDownloader(urlfptr,curl,"out/pic7.jpg");
    imageDownloader(urlfptr,curl,"out/pic8.jpg");
    imageDownloader(urlfptr,curl,"out/pic9.jpg");

    fclose(urlfptr);
    

    curl_easy_cleanup(curl);
    return 0;
}

struct curl_slist *header_seter(struct curl_slist *head)
{
    head = curl_slist_append(head, "Upgrade-insecure-requests: 1");
    head = curl_slist_append(head, "Accept: */*");
    head = curl_slist_append(head, "Cache-control: max-age=0");
    head = curl_slist_append(head, "Sec-fetch-site: same-origin");
    head = curl_slist_append(head, "Sec-fetch-mode: navigate");
    head = curl_slist_append(head, "Sec-fetch-dest: document");
    head = curl_slist_append(head, "Accept-Language: en-US,en;q=0.5");
    head = curl_slist_append(head, "Referer: https://www.instagram.com/");
    head = curl_slist_append(head, "Connection: close");
    head = curl_slist_append(head, "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:92.0) Gecko/20100101 Firefox/92.0");

    return head;
}

void webpage(CURL *curl)
{
    FILE *fileptr = fopen("webpage.txt", "w");
    char user[70] = "https://instagram.com/";
    printf("Enter the username : ");
    scanf("%s",&user[22]);
    printf("\n%s",user);

    // curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl, CURLOPT_URL,user);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fileptr);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    curl_easy_perform(curl);

    fclose(fileptr);
    printf("Downloaded");
}

int finder(FILE *fpt, char *sub_string, int substr_len)
{

    int pre_match = 0;
    int i = 0, j = 0;
    char ch;
    while (pre_match != 1 || j != (substr_len - 1))
    {
        ch = getc(fpt);
        if (ch == sub_string[j])
        {
            pre_match = 1;
            j++;
        }
        else
        {
            pre_match = 0;
            j = 0;
        }
        i++;
    }

    return i;
}

void soutput(FILE *fpt, char special_char)
{
    FILE *fptw = fopen("output.txt", "a");

    char ch = getc(fpt);
    while (ch != special_char)
    {
        fprintf(fptw, "%c", ch);
        ch = getc(fpt);
    }
    fprintf(fptw, "\n");

    fclose(fptw);
}

void uoutput(FILE *fpt, char special_char)
{

    
    FILE *out_url = fopen("url.txt", "a");
    int i = 0;

    char ch = getc(fpt);
    while (ch != special_char)
    {

        if (ch == '\\')
        {
            for (int i = 0; i < 5; i++)
            {
                getc(fpt);
            }
            ch = getc(fpt);
            fprintf(out_url, "&");
            i++;
        }
        fprintf(out_url, "%c", ch);
        ch = getc(fpt);
        i++;
    }
    fprintf(out_url, "\n");
    fclose(out_url);
   
    
}

struct curl_slist *csrf_seter(struct curl_slist *head, FILE *fptr, CURL *curl)
{
    char csrf[32];

    int i = 0;
    char ch = getc(fptr);
    while (ch != '\"')
    {
        csrf[i] = ch;
        ch = getc(fptr);
        i++;
    }

    char csrf_for_cookie[45] = "X-CSRFToken: ";
    char csrf_for_header[42] = "csrftoken=";
    // cookie: bPavNUKyc0bl60vfa3MeABoMYoqGbgpe

    for (int i = 0, j = 13, k = 10; i < 32; i++, j++, k++)
    {
        csrf_for_cookie[j] = csrf[i];
        csrf_for_header[k] = csrf[i];
    }

    head = curl_slist_append(head, csrf_for_cookie);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, head);
    // curl_easy_setopt(curl, CURLOPT_COOKIE, csrf_for_header);
    return head;
}

void imageDownloader(FILE *fpt,CURL *curl,char *file_name)
{
    char url[325];
    fscanf(fpt,"%s",url);
   // printf("%s\n",url);

   FILE *imageptr = fopen(file_name, "wb");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, imageptr);
    curl_easy_perform(curl);

    fclose(imageptr);
}

