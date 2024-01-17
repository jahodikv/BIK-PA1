#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 80
#define HTML_ERR_LEN 11
struct Dictionary
{

    char word[31];
};

void handleError(struct Dictionary *book, struct Dictionary *text)
{

    printf("Nespravny vstup.\n");
    free(book);
    free(text);
    exit(0);
}
int isInBook(struct Dictionary *book, char *word, int bookSize)
{

    for (size_t x = 0; x < bookSize; x++)
    {
        if (strcasecmp(word, book[x].word) == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{

    int bookSize = 0;
    int bookCap = 5;

    int textSize = 0;
    int textCap = 5;
    struct Dictionary *book = (struct Dictionary *)malloc(sizeof(struct Dictionary) * bookCap);
    struct Dictionary *text = (struct Dictionary *)malloc(sizeof(struct Dictionary) * textCap);
    char buffer[31];
    int res;
    int lineLen;
    printf("Slovnik:\n");
    while (1)
    {
        res = scanf("%30s", buffer);
        if (res != 1)
        {
            handleError(book, text);
        }
        if (feof(stdin))
        {
            handleError(book, text);
        }
        if (strcmp(buffer, "*****") == 0)
        {
            break;
        }
        if (bookCap == bookSize)
        {

            bookCap = bookCap * 2;
            book = (struct Dictionary *)realloc(book, sizeof(struct Dictionary) * bookCap);
        }
        strcpy(book[bookSize].word, buffer);
        book[bookSize].word[strlen(book[bookSize].word)] = '\0';

        bookSize++;
    }
    printf("Text:\n");
    while (1)
    {
        res = scanf("%30s", buffer);
        if (res != 1)
        {
            handleError(book, text);
        }

        if (textCap == textSize)
        {

            textCap = textCap * 2;
            text = (struct Dictionary *)realloc(text, sizeof(struct Dictionary) * textCap);
        }
        strcpy(text[textSize].word, buffer);
        text[textSize].word[strlen(text[textSize].word)] = '\0';

        textSize++;
        if (feof(stdin))
        {
            break;
        }
    }

    for (size_t i = 0; i < textSize; i++)
    {

        if (isInBook(book, text[i].word, bookSize) == 1)
        {
            if (strlen(text[i].word) + lineLen + HTML_ERR_LEN + 1 > MAX_LINE_LEN)
            {

                printf("\n");
                printf("<err>%s</err>", text[i].word);

                lineLen = strlen(text[i].word) + HTML_ERR_LEN;
            }
            else
            {
                lineLen = strlen(text[i].word) + lineLen + HTML_ERR_LEN + 1;
                printf(" <err>%s</err>", text[i].word);
            }
        }
        else
        {

            if (strlen(text[i].word) + lineLen > MAX_LINE_LEN)
            {

                printf("\n");
                lineLen = strlen(text[i].word);
                printf("%s", text[i].word);
            }
            else
            {
                printf(" %s", text[i].word);
                lineLen = strlen(text[i].word) + lineLen + 1;
            }
        }
    }

    printf("\n");

    free(book);
    free(text);
    return 0;
}