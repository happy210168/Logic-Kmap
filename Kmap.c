#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Getminterm(char* input,int len,int minterm[],int dontcare[]);

/* Minterm : Line33 , Initialize Kmap : Line 71*/ 




int main(){
	 
	/////* File processing */////
	FILE* inFile,*outFile;
	inFile = fopen("input.txt","r");
	if(!inFile){
	printf("Failed to open\n");
	}
	outFile = fopen("output.txt","w");
	if(!outFile){
	printf("Failed to open\n");
	}
	/////* File processing */////

	int i,j;   //for loop times
	char min[50];  //store input string
	int minterm[16],dontcare[16];   //store minterm (decimal)
	int count=0; //the number of minterm
	for(i=0;i<16;i++){ 
		minterm[i] = -1;
		dontcare[i] = -1;
	} //initialize array

	/////* begin find minterm *///// 
	char t[5] = "+";  //cut string with '+'

	while((fscanf(inFile,"%s",min))==1){
		printf("input : %s\n",min);
	}  //read input file 

	//use strtok to cut string 
	char *text = strtok(min,t);
	while(text!=NULL){
	printf("%s\n",text); 
	
	Getminterm(text,strlen(text),minterm,dontcare); //call Getminterm function
	
	text = strtok(NULL,t);
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
		if(count!=0 && dontcare[j]==j) printf(",");
		if(dontcare[j]==j){
			printf("%d",dontcare[j]); 
			count++;
		}
	}
	printf(")\n");
	/////* end find minterm */////

	/////* begin initialize Kmap */////
	int Kmap[4][4]; //store in decimal 
	int kmap[4][4];	//store in binary
	int ii,jj;  //for loop count 3 to 4 and 4 to 3
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			ii = i;
			jj = j;
			if(j==2) jj = j+1;
			if(j==3) jj = j-1;
			if(i==2) ii = i+1;
			if(i==3) ii = i-1;
			Kmap[i][j] = ii + 4*jj;
		}
	} //initialize (decimal)

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(minterm[Kmap[i][j]]==-1 && dontcare[Kmap[i][j]]==-1) kmap[i][j] = 0;
			else if(minterm[Kmap[i][j]]!=-1) kmap[i][j] = 1;
			else kmap[i][j] = -1;
		}
	} //initialize (binary)

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(kmap[i][j]==-1) printf("X ");
			else printf("%d ",kmap[i][j]);
		}
		printf("\n");
	}  //print K map

	/////* end initialize Kmap */////

	/////* begin Group and simplificaKmap */////
	if(group16()){break;}
	else if(group8()){break;}
	else if(group4()){break;}
	else {group2();}
	



	/////* end Group Kmap *////


	return 0;
}

//Getminterm funtction
void Getminterm(char* input,int len,int minterm[],int dontcare[]){
	int i[4] = {0}; //for loop times
	int a[4] = {-1,-1,-1,-1};   //store abcd bit ,default 'X' = -1
	int j,k;  //for loop times
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
		if(input[0]!=40) minterm[total] = total; //dontcare or not  ASCII code 40 = '('
		else dontcare[total] = total;
	}
	
	return;
}

