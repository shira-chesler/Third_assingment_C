#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES_IN_TXT 250
#define LINE 256
#define WORD 30

char txt[MAX_LINES_IN_TXT][LINE + 1];

int read_from_file() //returns number of lines that were read
{
    int line = 0;
    int col = 0;
    char cur_char;
    while ((cur_char=fgetc(stdin)) != EOF)
    {
        if(cur_char=='\n')
        {
            txt[line][col] = cur_char;
            line++;
            col = 0;
        }
        else
        {
            txt[line][col] = cur_char;
            col++;
        }
        
    }
    txt[line][col] = '\n';
    line++;
    return line;
}

int get_num_of_words_at_line(int line)
{
    int counter=0;
    for (int i = 0; i < LINE + 1; i++)
    {
        char cur_char = txt[line][i];
        if (cur_char=='\n'){
            counter++;
            break;
        }
        if (cur_char==' ' || cur_char=='\t' || cur_char=='\r')
        {
            counter++;
        }
    }
    return counter;

}

int get_word_length_at_index(int line_num, int index)
{
    int word_length = 0;
    char cur_char = txt[line_num][index];
    while (cur_char != ' ' && cur_char != '\n' && cur_char != '\t' && cur_char!='\r')
    {
        index++;
        word_length++;
        cur_char = txt[line_num][index];
    }
    return word_length;
}

char* get_word_at_index(int line, int index)
{
    int length_of_word = get_word_length_at_index(line, index);
    char* word = (char*) malloc((length_of_word+1)*sizeof(char));
    if (word == NULL)
    {
        printf("wtf");
        exit(-1);
    }
    
    for (int i = 0; i < length_of_word; i++)
    {
        word[i] = txt[line][index + i];
    }
    word[length_of_word] = '\0';
    return word;
}

int substring(char *str1, char *str2)
{
    int len_str1 = strlen(str1);
    int len_str2 = strlen(str2);
    int index_in_1 = 0;
    if (len_str2 > len_str1)
    {
        return 0;
    }
    while (index_in_1<len_str1)
    {
        int index_in_substr = 1; //if we're getting inside the 'if', it's already correct for [0]
        if(*(str1+index_in_1) == *(str2))
        {
            int check_substr = 1; //boolean - should we continue to check
            while (index_in_substr < len_str2 && check_substr)
            {
                if (*(str1+index_in_1+index_in_substr) != *(str2+index_in_substr))
                {
                    check_substr = 0;
                }
                index_in_substr++;   
            }
            if (check_substr)
            {
                return 1;
            }   
        }
        index_in_1++;
    }
    return 0;
}

void copy_without_specific_char(char* copy_from, char* copy_into, int dont_copy)
{
    int string_size = strlen(copy_from);
    if (string_size < dont_copy)
    {
        return;//doesn't suppose to happen
    }
    int j = 0;
    for (int i = 0; i < string_size; i++)
    {
        if (i!=dont_copy)
        {
            copy_into[j] = copy_from[i];
            j++;
        }
        
    }
    copy_into[string_size-1] = '\0';
    return;
}

int similar_by_one(char *s, char *t)
{
    int strs_len = strlen(s);
    int strt_len = strlen(t);
    if(strcmp(t, s)==0)
    {
        return 1;
    }
    if (strs_len-strt_len!=1)
    {
        return 0;
    }

    char s_without_char[strs_len];
    for (int i = 0; i < strs_len; i++)
    {
        copy_without_specific_char(s, s_without_char, i);
        //printf("%s\n", s_without_char);
        if (strcmp(t, s_without_char)==0)
        {
            return 1;
        }
        
    }
    return 0;
}

void print_lines(char *str)
{
    int num_of_lines = read_from_file();
    for (int i = 0; i < num_of_lines; i++)
    {
        int exist_in = substring(txt[i], str);
        if (exist_in)
        {
            int col = 0;
            while (txt[i][col]!='\n')
            {
                printf("%c", txt[i][col]);
                col++;
            }
            printf("\n");
            
        }
        
    }
    

}

void print_similar_words(char *str)
{
    int num_of_lines = read_from_file();
    for (int i = 0; i < num_of_lines; i++)
    {
        int num_of_words_at_line = get_num_of_words_at_line(i);
        int index_of_word = 0;
        for (int j = 0; j < num_of_words_at_line; j++)
        {
            char *word = get_word_at_index(i, index_of_word);
            int word_length = get_word_length_at_index(i, index_of_word);
            index_of_word = index_of_word + word_length + 1;
            if(similar_by_one(word, str))
            {
                printf("%s\n", word);
            }
            free(word);
        } 
    }
}

int main()
{
    char desired_word[WORD];
    char cur_char;
    int loc=0;
    scanf("%c", &cur_char);
    while (cur_char != ' ')
    {
        desired_word[loc] = cur_char;
        loc++;
        scanf("%c", &cur_char);
    }
    desired_word[loc] = '\0'; 
    char function;
    scanf("%c", &function);
    if (function == 'a')
    {
        scanf("%c", &cur_char); // \n
        scanf("%c", &cur_char); // \n
        printf("%c", cur_char);
        print_lines(desired_word);
    }
    else if (function == 'b')
    {
        scanf("%c", &cur_char); // \n
        scanf("%c", &cur_char); // \n
        print_similar_words(desired_word);
    }
    return 0;
}
