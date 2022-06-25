#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//选取俩个较大的质数,和E
#define P 54013
#define Q 47129
#define E 11743

const unsigned long long p=P;
const unsigned long long q=Q;
//计算 n、F值
unsigned long long n = (unsigned long long)P * (unsigned long long)Q;
unsigned long long f= ((unsigned long long)P - 1) * ((unsigned long long)Q - 1);
//选取e
const unsigned long long e=E;
// 讲道理这个应该算出来的，不算写代码了，就直接放上来吧
const unsigned long long d=1837087807;
const int s=31;

//加解密函数
unsigned long long* Encoding(char* source);
unsigned char* Decoding(unsigned long long* encode);
//快速取余函数
unsigned long long quickMod(unsigned long long a, unsigned long long b,unsigned long long c);

int getLength(unsigned long long* code);
int main(int argc,char* argv[])
{
    printf("p=%llu\n", p);
    printf("q=%llu\n", q);
    printf("f=(p-1)*(q-1)=%llu\n", n);
    printf("n=p*q=%llu\n", f);
    printf("e=%llu\n", e);
    printf("d=%llu\n", d);
    printf("s=%d\n", s);
    //加解密部分
    char source[100];
    printf("Source:\n");
    gets_s(source,100);
    unsigned long long * encode= Encoding(source);
    unsigned char * decode= Decoding(encode);
    //输出结果
    printf("Encode:\n");
    for(int i=0;*(encode+i)!=0;i++){
        printf("%llx ",*(encode+i));
    }
    printf("Decode:\n");
    for(int i=0;*(decode+i)!=0;i++){
        printf("%d ",*(decode+i));
    }
    printf("\nDecryption:\n");
    for(int i=0;*(decode+i)!=0;i++){
        printf("%c",*(decode+i));
    }
    return 0;
}
unsigned long long* Encoding(char* source){
    unsigned int length= strlen(source);
    unsigned long long* encode=(unsigned long long*) malloc((length+1)*sizeof (unsigned long long));
    for(int i=0;i<length;i++){
        unsigned long long temp=*(source+i);
        *(encode+i)= quickMod(temp,e,n);
    }
    *(encode+length)=0;
}
unsigned char* Decoding(unsigned long long* encode){
    int length= getLength(encode);
    unsigned char* decode=(unsigned char*) malloc(sizeof (unsigned char)*(length+1));
    int i;
    for(i=0;i<length;i++){
        unsigned long long temp= quickMod(*(encode+i),d,n);
        *(decode+i)=temp;
    }
    *(decode+i)=0;
    return decode;
}
int getLength(unsigned long long * encode){
    int i=0;
    while(*(encode+i)!=0)
        i++;
    return i;
}
unsigned long long quickMod(unsigned long long a,unsigned long long b,unsigned long long c)
{
    unsigned long long ans = 1;
    while (b)
    {

        if (b % 2 == 1)
            ans = (ans * a) % c;
        b /= 2;
        a = (a * a) % c;
    }
    return ans;
}
