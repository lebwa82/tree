#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
typedef struct tnode
{
    char* word;
    int count;
    struct tnode*left;
    struct tnode*right;
} tnode;

int getword(char *word,FILE*file)
{
    int c=fgetc(file),i=0;
    while(isalpha(c)==0)
    {
        c=fgetc(file);
        if(feof(file)!=0)
        {
            return 0;
        }
    }
    while(isalpha(c))
    {
       if(feof(file)!=0)
        {
            return 0;
        }
        word[i]=c;
        i++;
        c=fgetc(file);
    }
    word[i]='\0';
    //printf("word=%s\n",word);
    return 1;
}


tnode*create(char*word)
{
    tnode*p=(tnode*)malloc(sizeof(tnode));
    p->word=word;
    p->count=1;
    p->left=NULL;
    p->right=NULL;
    return p;
}

int shet(tnode*root)
{
    int count=0;
    if(root->left!=NULL)
    {
        count+=shet(root->left);
    }
    if(root->right!=NULL)
    {
        count+=shet(root->right);
    }
    count+=root->count;
    return count;
}

void print(tnode*root,FILE*file3)
{
    if(root->left!=NULL)
    {
        print(root->left,file3);
    }
    fprintf(file3,"%s %d\n",root->word,root->count);
    if(root->right!=NULL)
    {
        print(root->right,file3);
    }
}

int add(char*word,tnode*root)
{
    int x=strcmp(word,root->word);
    //printf("x=%d\n",x);
    if(x==0)
    {
        root->count++;
    }
    if(x>0)//те надо отправить слово направо
    {
        if(root->right==NULL)
        {
            root->right=create(word);
        }
        else
        {
            add(word,root->right);
        }
    }
    if(x<0)//те надо отправить слово налево
    {
        if(root->left==NULL)
        {
            root->left=create(word);
        }
        else
        {
            add(word,root->left);
        }
    }
    return 0;
}

int main(int argc,char*argv[])
{
    tnode*root=(tnode*)malloc(sizeof(tnode));
    //printf("%s\n",argv[1]);
    FILE *file = fopen(argv[1],"rb");
    FILE *file3 = fopen(argv[2],"wb");
    char*word=(char*)malloc(30*sizeof(char));
    getword(word,file);
    //printf("word=%s",word);
    root=create(word);
    while(1)
    {
        if(feof(file)!=0)
        {
            break;
        }
        char*word1=(char*)malloc(30*sizeof(char));
        if(getword(word1,file))
        {
          add(word1,root);
        }


    }
    print(root,file3);
    puts("");
    int x=shet(root);
    printf("count of words in file is %d\n",x);

    return 0;
}
