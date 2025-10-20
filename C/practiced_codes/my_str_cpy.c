#include<stdio.h>
void my_str_cpy(const char *source, char *destination)
{
    int i = 0;
    while(source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // Null-terminate here
}

int main() 
{
    char *a = "pujit";
    char array[6];
    my_str_cpy(a, array);
    printf("%s\n", array);
}
