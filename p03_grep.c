#include <stdio.h>
#include <string.h>

int main(int len, char **args) {
    char *mode = "output";
    char *pattern = NULL;
    int file_start = 0;

    for (int i = 1; i < len; ++i)
        if (strcmp(args[i], "-?") == 0) {
            printf("-?  Print this message\n"
                   "-c  Count the number of occurrences\n"
                   "-o  Display the matched parts\n"
                   "-h  Display the matched lines\n"
                   "-l  Display the matched file names\n"
                   "-n  Display the matched lines with line numbers\n"
                   "-v  Display unmatched lines\n");
            return 0;
        }
        else if (strcmp(args[i], "-c") == 0) mode = "count";
        else if (strcmp(args[i], "-o") == 0) mode = "output";
        else if (strcmp(args[i], "-h") == 0) mode = "matched lines";
        else if (strcmp(args[i], "-l") == 0) mode = "file names";
        else if (strcmp(args[i], "-n") == 0) mode = "line numbers";
        else if (strcmp(args[i], "-v") == 0) mode = "inverse";
        else if (pattern == NULL) pattern = args[i];
        else if (file_start == 0) file_start = i;

    if (pattern == NULL) return printf("Please provide a pattern!!");
    if (file_start == 0) return printf("Please provide at least one file!!");

    int count = 0;
    for (int i = file_start; i < len; ++i) {
        FILE *fp = fopen(args[i], "r");
        char buffer[100];
        int line_numbers = 0;

        while (++line_numbers, fgets(buffer, 100, fp) != NULL)
            if (strstr(buffer, pattern) != NULL) {
                if (strcmp(mode, "output") == 0) printf("%s\n", pattern);
                else if (strcmp(mode, "matched lines") == 0) printf("%s", buffer);
                else if (strcmp(mode, "file names") == 0) { printf("%s", args[i]); break; }
                else if (strcmp(mode, "line numbers") == 0) printf("%2d: %s", line_numbers, buffer);
                else if (strcmp(mode, "count") == 0) count++;
            } else if (strcmp(mode, "inverse") == 0) printf("%s", buffer);
        fclose(fp);
    }


    if (strcmp(mode, "count") == 0)
        printf("%d", count);

    return 0;
}