//Sukhveer Karlcut
//skarlcut@ucsc.edu
//CMPS 12-M
//charType.c
//This program takes two command line arguments giving the input and output file names respectively, 
//then classifies the characters on each line of the input file into the following categories: 
//alphabetic characters (upper or lower case), numeric characters (digits 0-9), punctuation, and white space (space, tab, or newline)

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>
#include<string.h>

#define MAX_STRING_LENGTH 100

void extract_chars(char* s, char* a, char* d, char* p, char* w);

int main(int argc, char* argv[]){
   FILE* in;
   FILE* out;
   char* line;
   char* alpha;
   char* digits;
   char* punc;
   char* whitesp;

   if( argc != 3 ){
      printf("Usage: %s input-file output-file\n", argv[0]);
      exit(EXIT_FAILURE);
   }
 
   if( (in=fopen(argv[1], "r"))==NULL ){
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   if( (out=fopen(argv[2], "w"))==NULL ){
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   line = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   alpha = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   digits = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   punc = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   whitesp = calloc(MAX_STRING_LENGTH+1, sizeof(char) );
   assert( line!=NULL && alpha!=NULL && digits!=NULL && punc!=NULL && whitesp!=NULL);
   int counter = 1;

   while( fgets(line, MAX_STRING_LENGTH, in) != NULL ){
      	extract_chars(line, alpha, digits, punc, whitesp);
      	int alphaTotal = strlen(alpha);
      	int digitsTotal = strlen(digits);
      	int puncTotal = strlen(punc);
      	int whitespTotal = strlen(whitesp);
      	fprintf(out, "line %d contains: \n", counter);
	if(alphaTotal != 1)
      		fprintf(out, "%d alphabetic characters: %s\n", alphaTotal, alpha);
	else
      		fprintf(out, "%d alphabetic character: %s\n", alphaTotal, alpha);
	if(digitsTotal != 1)
      		fprintf(out, "%d numeric characters: %s\n", digitsTotal, digits);
	else
      		fprintf(out, "%d numeric character: %s\n", digitsTotal, digits);
	if(puncTotal != 1)
      		fprintf(out, "%d punctuation characters: %s\n", puncTotal, punc);
	else
      		fprintf(out, "%d punctuation character: %s\n", puncTotal, punc);
	if(whitespTotal != 1)
      		fprintf(out, "%d whitespace characters: %s\n", whitespTotal, whitesp);
 	else
  		fprintf(out, "%d whitespace character: %s\n", whitespTotal, whitesp);
  	counter ++;
	}

	free(line);
	free(alpha);
	free(digits);
	free(punc);
	free(whitesp);

   fclose(in);
   fclose(out);

   return EXIT_SUCCESS;
}

void extract_chars(char* s, char* a, char* d, char* p, char* w){
   int i=0, j=0;
   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isalpha( (int) s[i]) ) a[j++] = s[i];
      i++;
   }
   a[j] = '\0';
   i=0;
   j=0;

   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isdigit( (int) s[i]) ) d[j++] = s[i];
      i++;
   }
   d[j] = '\0';
   i=0;
   j=0;

   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( ispunct( (int) s[i]) ) p[j++] = s[i];
      i++;
   }
   p[j] = '\0';
   i=0;
   j=0;

   while(s[i]!='\0' && i<MAX_STRING_LENGTH){
      if( isspace( (int) s[i]) ) w[j++] = s[i];
      i++;
   }
   w[j] = '\0';
}
