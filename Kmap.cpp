#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Getminterm(char* input,int len,int minterm[],int doncare[]);

int main(){
	
	FILE* inFile,*outFile;
	inFile = fopen("input.txt","r");
	if(!inFile){
	printf("Failed to open\n");
	}
	outFile = fopen("output.txt","w");
	if(!outFile){
	printf("Failed to open\n");
	}

	int i;
	static int Group[16];
	//init(Group);
	char min[50];
	int minterm[16],doncare[16];   //store minterm (decimal)
	for(i=0;i<16;i++){ 
		minterm[i] = -1;
		doncare[i] = -1;
	}
	char t[5] = "+";  //cut string with '+'

	while((fscanf(inFile,"%s",min))==1){
		printf("input : %s\n",min);
	}  //read input file 

	//cut string with '+'
	char *text = strtok(min,t);
	while(text!=NULL){
	printf("%s\n",text); 
	
	Getminterm(text,strlen(text),minterm,doncare);
	
	text = strtok(NULL,t);
	}	

	return 0;
}

//Getminterm funtction
void Getminterm(char* input,int len,int minterm[],int doncare[]){
	int i[4] = {0}; //for loop times
	int a[4] = {-1,-1,-1,-1};   //store abcd bit ,default 'X' = -1
	int j,k;  //for loop times
	int count=0; //the number of minterm
	int ca=0,cb=0,cc=0,cd=0;
	char c[16][5];   //store minterms (binary)
	int total = 0;     //minterm[total] = total
	char ch[3]="01";	//integer 0 or 1 cast to char '0' or '1'
	
	//a' = 0, a = 1, X = -1
	for(j=0;j<len;j++){
		switch(input[j]){ 
			case 97:
				if(input[j+1]== 39) a[0] = 0; 
				else a[0] = 1;
				break;
			case 98:
				if(input[j+1]== 39) a[1] = 0; 
				else a[1] = 1;
				break;
			case 99:
				if(input[j+1]== 39) a[2] = 0; 
				else a[2] = 1;
				break;
			case 100:
				if(input[j+1]== 39) a[3] = 0; 
				else a[3] = 1;
				break;

		}  //switch find a,b,c,d bits
	}
	//printf("binary = %d %d %d %d , -1 indicate X (don't care)\n",a[0],a[1],a[2],a[3]);
	
	//use for loop*4 to find binary minterms and store in char c 
	for(i[0]=0;i[0]<2;i[0]++){
		if(a[0]==-1){
			for(j=ca;j<8+ca;j++) c[j][0] = ch[i[0]];
		}
		else{
			for(j=0+ca;j<8+ca;j++) c[j][0] = ch[a[0]];
		}
		ca = ca+8;

		for(i[1]=0;i[1]<2;i[1]++){
			if(a[1]==-1){
				for(j=cb;j<cb+4;j++) c[j][1] = ch[i[1]];
			}	
			else{
				for(j=cb;j<cb+4;j++) c[j][1] = ch[a[1]];
			}
			cb = cb+4;

			for(i[2]=0;i[2]<2;i[2]++){
				if(a[2]==-1) {
					for(j=cc;j<cc+2;j++) c[j][2] = ch[i[2]];
				}
				else{
					for(j=cc;j<cc+2;j++) c[j][2] = ch[a[2]];
				}
				cc = cc+2;

				for(i[3]=0;i[3]<2;i[3]++){
					if(a[3]==-1) c[cd][3]=ch[i[3]];
					else c[cd][3] = ch[a[3]];
					cd++;

				}
			}
		}
	}
	
	/* print binary minterm 
	for(j=0;j<16;j++){
		total = 0;
		printf("binary minterm:");
		for(k=0;k<4;k++){ 
			printf("%c",c[j][k]);
		}
		printf("\n");
	}  
	*/

	//transform binary to decimal
	for(j=0;j<16;j++){
		total = 0;
		for(k=0;k<4;k++){
			total +=((c[j][k]-48) << 3-k);
		}
		if(input[0]!=40) minterm[total] = total; //doncare or not
		else doncare[total] = total;
	}
	
	printf("minterm : m(");
	for(j=0;j<16;j++){
		if(count!=0 && minterm[j]==j) printf(",");
		if(minterm[j]==j){
			printf("%d",minterm[j]); 
			count++;
		}
	}
	printf(")");
	printf(" + ");

	printf("d(");
	count=0;
	for(j=0;j<16;j++){
		if(count!=0 && doncare[j]==j) printf(",");
		if(doncare[j]==j){
			printf("%d",doncare[j]); 
			count++;
		}
	}
	printf(")\n");
	return;
}

