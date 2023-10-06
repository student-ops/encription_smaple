#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 256
#define swap(a,b){a+=b;b=a-b;a-=b;}

int *KSA(char *,int *);
char *PRGA(char *,char *,int);

int main(void){
  
  int size;
  //配列keyに暗号化に用いるパスワード(暗号鍵)を格納します。
  char key[]="password12345678";
  char *result;  

  char plain[101];
  printf("入力文字列をRC4で暗号化します。\n");
  printf("100文字以内で入力してください。\n");
  printf(">> ");
  scanf("%100s*[^\n]%*c",plain);
  getchar();
  
  size=strlen(plain);

  printf("----------------------------------\n");
  
  //PRGA関数を用いて暗号化する。
  result=PRGA(key,plain,size);
  printf("暗号化された文字列\t>> %s\n",result);

  printf("----------------------------------\n");

  //PRGA関数を用いて復号する。
  result=PRGA(key,result,size);
  printf("復号された文字列\t>> %s\n",result);
  
  return 0;
  
}



int *KSA(char *key,int *s){

  s=malloc(sizeof(int)*N);

  int i,j;

  for(i=0;i<N;i++){
    s[i]=i;
  }
  j=0;
  for(i=0;i<N;i++){
    j=(j+s[i]+key[i%16])%256;
    swap(s[i],s[j])
  }

  return s;
}


char *PRGA(char *key,char *text,int size){

  int i=0;
  int j=0;
  int *s;
  char *result;
  result=malloc(sizeof(char)*(size+1));
  
  s=KSA(key,s);

  int z=0;

  while(i<size){

    i=i+1;
    j=(j+s[i])%256;

    swap(s[i],s[j]);
    z=s[(s[i]+s[j])%256]%128;
    result[i-1]=(unsigned char)(text[i-1]^z);
  }
  result[size]='\0';

  return result;

}
