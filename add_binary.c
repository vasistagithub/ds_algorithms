#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char *s1, *s2;

    s1 = (char*)calloc(100,sizeof(char));
    s2 = (char*)calloc(100,sizeof(char));

    printf("Enter the first binary num:");
    scanf("%s",s1);
    printf("Enter the second binary num:");
    scanf("%s",s2);

    s3 = addBinary(s1,s2);

    printf("Added binary string of %s and %s is %s\n",
            s1,s2,s3);

    return 0;
}

char* addBinary(char *a, char *b)
{
    int len1,len2;
    char carry = '0';

    len1 = strlen(a);
    len2 = strlen(b);

    ret_str = (char*)calloc(len1+len2+1,sizeof(char));

    len1--;
    len2--;

    while(len1 >= 0  && len2 >= 0) {
        if(a[len1]=='1' && b[len2] == '1') {
            if(carry == '1') {
                ret_str[i++] = '1';
            }
        } else if(a[len1] == '0' && b[len2] == '0') {
            if(carry == '1') {
                ret_str[i++] = '1';
            } else {
                ret_str[i++] '0';
            }
            carry = '0';
        } else {
            if(carry == '1') {
                ret_str[i++] = '0';
            } else {
                ret_str[i++] = '1';
                carry = '0';
            }
        }
        len1--;
        len2--;
    }

    if(len1 < 0) {
        if(carry == '1') {
            if(b[len2]) == '1') {
                ret_str[]
        while(len2 >= 0) {
            if(carry == )



