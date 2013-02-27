/*WHAT PROG DOES :
 * 	>Read i/p file, break into chunks of identical length & print them.
 * 	BUT, do "fair" distribution of spaces, so that every line starts & ends with a word.
 *
 * LOGIC :
 * 	>Read the i/p file upto the fixed len. As we read, store every "word" in array of pointers.
 * 	>Also, get the count of no. of words, no. of characters.
 * 	>From this, we know how many extra spaces we need to put.
 *
 * 	>Eg : Lets say, fixed len=30, no.of words=5 , no.of characters=23.
 * 	So extra_spaces=30-23 = 7.
 *
 * 	NOW , divisor=5-1=4.
 * 	SO, quo=7/4=1 , ie between every word there will be 1 space.
 * 	AND, rem=7%4=3 , ie between 4 words , there will be 1-1 extra space.
 *
 * 	FINAL O/P will be : (W1)__(W2)__(W3)__(W4)_(W5) , where W1=word1 & so on
 */

#include<stdio.h>
#include<string.h>


#define ALIGNMENT_LENGTH 20
#define TRUE 1
#define FALSE 0

int main(){
	char filename[]="temp.c";
	FILE *fp=fopen(filename , "r" );
	int t=ALIGNMENT_LENGTH+1;
	/*coz at the end of array, I have to put '\0', so one extra */

	char aligned_line[t];
	char broken_word[ALIGNMENT_LENGTH];
	int i=0 , j, space_count;

	char *word_pointers[ALIGNMENT_LENGTH];
	 
	while(1){
		word_count=0;
		for( ; i<t && ( *(aligned_line+i)=(char)fgetc(fp) ) != EOF ; i++ ){
			while(isspace( *(aligned_line+i) ) ){
				/*word found, so put in array pointers */
				*(aligned_line+i)='\0';
				space_count++;	
				i++;
				(*aligned_line+i)=(char)fgetc(fp) ;

			}

		}

		char *temp=aligned_line+(i-1);
		/*basically, we are supposed to put '\0' at temp,
		 * but before doing so, lets check if temp has read half word 
		 * or something like that.
		 *
		 */
		if( *(temp+1)==EOF ){
			*(temp+1)='\0';
			printf("%s", aligned_line );

			break ;
		}

		else if( *temp==' ' || *temp=='\t' ){
			broken_word[0]=*temp;
			*temp='\0';
			i=0;
		}
		else{
			for(i=0 ; !isspace(*temp) ; i++ ){
				*(broken_word+i)=*temp;
				temp--;
			}
			*(temp+1)='\0' ;
			--i;
		}

		printf("%s$$\n", aligned_line);

		/*now fill the aligned_line, by broken_word, but in reverse order */
		int k=0;
		while(i>-1){
			*(aligned_line+k)=*(broken_word+i);
			k++;
			i--;
		}
		i=k;

	}

return 0;

}

