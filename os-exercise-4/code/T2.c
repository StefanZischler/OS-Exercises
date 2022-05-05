#include <stdio.h>
#include <stdlib.h>


int readLinesCount(const char * str){
    //TODO implement readlinesCount which returns the total number of lines within the input file
	char ch;
	const char *file = str;
	int linesCount = 0;
	FILE *fp;
	// open file to read
	fp = fopen(str, "r");
	if(fp==NULL) {
      printf("File \"%s\" does not exist!\n", file);
      return -1;
   }
   //read character by character and check for new line
   while((ch=fgetc(fp))!=EOF) {
      if(ch=='\n')
         linesCount++;
   }
   //close the file
   fclose(fp);
 return 0;
}
void writeLinesCount(const char * str, int count_line){
//TODO implement writeLinesCount which writes a new line in file str has count_line 
	FILE *fp;
	int line_count = count_line;
	printf("line count: %d", line_count);   
	// open file to write
	fp = fopen(str, "w");
	if(fp == NULL) {
      printf("Error! Cannot open file.");   
      exit(1);             
   	}
	// write to file
    fprintf(fp,"%d",line_count);
	fclose(fp);

}
int main(int argc, char * argv[])
{
	
	int files_count=atoi(argv[1]);
	int i=0;
	while(i<files_count){
		int num_lines=readLinesCount(argv[2+i]);
		writeLinesCount("output.txt", num_lines);
		i++;
	}

}
