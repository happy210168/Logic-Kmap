#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Getminterm(char* input,int len,int minterm[],int dontcare[]);  //127L
int  GetGroupTerm(char* input,int len,int term[]); //530L
int GetGroup(char* PI); //630L
int Circle16(); //250L
void Circle8(); 
void Circle4();
void Circle2();
void Circle1();

char s8[50],s4[50],s2[50],s1[50];  //store abcd in size n circle  ex: d+b+c  
char PI[100];   //F(A,B,C,D) Answer 
unsigned int Kmap[4][4]; //store in decimal 
int kmap[4][4];	//store in binary
int Circle[4][4]={0}; //Circle[i][j] stores circle times at kmap each position
/* Minterm : Line40 , Initialize Kmap : Line 81*/ 
static int Groupnum=0;



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
	int minterm[16],dontcare[16],term[16];   //store minterm (decimal) //term[16] for last group 
	int count=0; //the number of minterm
	for(i=0;i<16;i++){ 
		minterm[i] = -1;
		dontcare[i] = -1;
		term[i] = -1;
	} //initialize array

	/////* begin find minterm *///// 

	while((fscanf(inFile,"%s",min))==1){
		printf("input : %s\n",min);
	}  //read input file 

	///*use strtok to cut string*///
	char t[5] = "+";  //cut string with '+'
	char *text = strtok(min,t);
	while(text!=NULL){ 
	
	Getminterm(text,strlen(text),minterm,dontcare); //call Getminterm function
	
	text = strtok(NULL,t);
	}	
	///*use strtok to cut string
	
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
	printf("Initialize Kmap:\nCD＼AB 00 01 11 10\n     -------------");

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
		if(i==0) printf("\n   00 |");
		else if(i==1) printf("   01 |");
		else if(i==2) printf("   11 |");
		else  printf("   10 |");
		for(j=0;j<4;j++){
			if(kmap[i][j]==-1) printf("X  ");
			else printf("%d  ",kmap[i][j]);
		}
		printf("\n");
	}  //print K map

	/////* end initialize Kmap */////

	/////* begin Circle  */////
	if(Circle16(kmap,Circle,Kmap)){	//Circle for size 16
		printf("Group 1:0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15\nSimplification:X\nF(A,B,C,D)= X");	
	}

	Circle8(kmap,Circle,Kmap);  //Circle for size 8
	printf("s8:%s\n",s8);
	///*use strtok to cut string*///
	char *buf = strtok(s8,t);
	while(buf!=NULL){ 	
		if(GetGroupTerm(buf,strlen(buf),term)){	//call Getminterm function
			strcat(PI,buf);
			strcat(PI,"+");
		}
		buf = strtok(NULL,t);
	}	
	///*use strtok to cut string
 	


	Circle4(kmap,Circle,Kmap);  //Circle for size 4
	printf("s4:%s\n",s4);

	///*use strtok to cut string*///
	buf = strtok(s4,t);
	while(buf!=NULL){ 
		if(GetGroupTerm(buf,strlen(buf),term)){	//call Getminterm function
			strcat(PI,buf);
			strcat(PI,"+");
		}
		buf = strtok(NULL,t);
	}	
	///*use strtok to cut string




	Circle2(kmap,Circle,Kmap);	//Circle for size 2
	printf("s2:%s\n",s2);
	///*use strtok to cut string*///
	buf = strtok(s2,t);
	while(buf!=NULL){ 
		if(GetGroupTerm(buf,strlen(buf),term)){	//call Getminterm function
			strcat(PI,buf);
			strcat(PI,"+");
		}
		buf = strtok(NULL,t);
	}
	///*use strtok to cut string


	Circle1(kmap,Circle,Kmap);  //Circle for size 1
	printf("s1:%s\n",s1);
	///*use strtok to cut string*///
	buf = strtok(s1,t);
	while(buf!=NULL){ 
		if(GetGroupTerm(buf,strlen(buf),term)){	//call Getminterm function
			strcat(PI,buf);
			strcat(PI,"+");
		}
		buf = strtok(NULL,t);
	}
	///*use strtok to cut string
	PI[strlen(PI)-1]=32;
	printf("F(A,B,C,D):%s\n",PI);

	/////* end Circle Kmap *////




	return 0;
}

//Getminterm funtction
void Getminterm(char* input,int len,int minterm[],int dontcare[]){
	int i[4] = {0}; //for loop times
	int a[4] = {-1,-1,-1,-1};   //store abcd bit ,default 'X' = -1
	int j,k;  //for loop times
	int ca=0,cb=0,cc=0,cd=0;//use for find binary term
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
			total += ((c[j][k]-48) << (3-k));
		}
		if(input[0]!=40) minterm[total] = total; //dontcare or not  ASCII code 40 = '('
		else dontcare[total] = total;
	}

	return;
}

/* Circle16 begin */
int Circle16(){
	int i,j;
	char* s="";
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(kmap[i][j]==0) return 0;
		}	
  }
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			Circle[i][j]++;
		}	
  }

	return 1;
}
/* Circle16 end */

/* Circle8 begin */
/*void Circle8(int kmap[][4],int Circle[][4]){
	int i,j,k,n,count=0; //for loop times 
	int ii,jj; //for circle upper left in any [i][j]
	int flag=0;  //double for loop break flag
	for(i=0;i<4;i++){       
		for(j=0;j<4;j++){
	//position for loop star
			if(i==0) ii = i+3;		//[i][j] circle upper left [0][j] and [0][jj] and [i][0] and [ii][0]
			else ii = i-1; 
			if(j==0) jj = j+3;
			else jj = j-1;
			
			for(k=0;k<4;k++){
				for(n=j;count<2;){
					if(kmap[k][n]==0){
						flag = 1;
						break;
					}
					if(n==3) n=0;
					else n++;
					count++;
				}
				count=0;
				if(flag) break;
		 	}  //all number in Circle != 0
			
	 
			if(flag!=1 && Circle[i][j]==0){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=0;k<4;k++){
					for(n=j;count<2;){
						Circle[k][n]++;
						if(n==3) n=0;
						else n++;
						count++;
					}
					count=0;
				}
				flag = 0;
				continue;
			}
				
			for(k=0;k<4;k++){
				for(n=jj;count<2;){
					if(kmap[k][n]==0){
						flag = 1;
						break;
					}
					if(n==3) n=0;
					else n++;
					count++;
				}
				count=0;
				if(flag) break;
		 	}  //each number in Circle !=0
	 
			if(flag!=1 && Circle[i][j]==0){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=0;k<4;k++){
					for(n=jj;count<2;){
						Circle[k][n]++;
						if(n==3) n=0;
						else n++;
						count++;
					}
					count=0;
				}
				flag = 0;
				continue;
			}

			for(k=0;k<4;k++){
				for(n=i;count<2;){
					if(kmap[n][k]==0){
						flag = 1;
						break;
					}
					if(n==3) n=0;
					else n++;
					count++;
				}
				count=0;
				if(flag) break;
		 	}  //all number in Circle != 0
	 
			if(flag!=1 && Circle[i][j]==0){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=0;k<4;k++){
					for(n=i;count<2;){
						Circle[n][k]++;
						if(n==3) n=0;
						else n++;
						count++;
					}
					count=0;
				}
				flag = 0;
				continue;
			}

			for(k=0;k<4;k++){
				for(n=ii;count<2;){
					if(kmap[n][k]==0){
						flag = 1;
						break;
					}
					if(n==3) n=0;
					else n++;
					count++;
				}
				count=0;
				if(flag) break;
		 	}  //all number in Circle != 0
	 
			if(flag!=1 && Circle[i][j]==0){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=0;k<4;k++){
					for(n=ii;count<2;){
						Circle[n][k]++;
						if(n==3) n=0;
						else n++;
						count++;
					}
					count=0;
				}
				flag = 0;
				continue;
			}
	//position for loop end
		}	 
	}

	printf("\n");
  for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf("%d ",Circle[i][j]);
		}
		printf("\n");
	}
	return;	
}*/
/* Circle8 end */

void Circle8(){
	int i,j,k,m,n=0;
	char binary[16][4]; //store the number in size 8 circle with binary term
	char* s ="";   // if cannot get  any size 8  circle return s
	int num=0;	
	int count=0;
	int flag=0;  //for loop break
	for(k=0;k<4;k++){
		for(i=k;count<2;count++){
			for(j=0;j<4;j++){
				if(kmap[i][j]==0 || Circle[k][0]!=0 || kmap[k][0]==-1){
					flag=1;
					break;
				}
			}
			if(i==3) i=0;
			else i++;
			if(flag) break;
		}
		count=0;
		
		/* simplify and Circle */
		if(flag==0){
			for(i=k;count<2;count++){
				for(j=0;j<4;j++){
					Circle[i][j]++;

					/*get binary of Group and store in char*/
					for(m=0;m<4;m++){
					binary[n][m]=(((Kmap[i][j] >> (3-m)) & 1)+48);	
					}
					/*get binary of Group and store in char*/
					n++;
				}
				if(i==3) i=0;
				else i++;
			}

			/* Simplify */
			for(m=0;m<4;m++){
				for(n=0;n<8;n++){
					if(binary[n][m]-48) num++;
				}
				if(num==8){ s8[strlen(s8)] = m+97;
					strcat(s8,"+"); }
				if(num==0){ s8[strlen(s8)] = m+97; 
					strcat(s8,"'+"); }

				num=0;
			}
			n=0;

			/* Simplify */

			count=0;
		}
		/* simplify and Circle */
		else flag=0;
	}

////////////////////

	for(k=0;k<4;k++){
		for(j=k;count<2;count++){
			for(i=0;i<4;i++){
				if(kmap[i][j]==0 || Circle[0][k]!=0 || kmap[0][k]==-1){
					flag=1;
					break;
				}
			}
			if(j==3) j=0;
			else j++;
			if(flag) break;
		}
		count=0;
		
		/* simplify and Circle */
		if(flag==0){
			for(j=k;count<2;count++){
				for(i=0;i<4;i++){
					Circle[i][j]++;

					/*get binary of Group and store in char*/
					for(m=0;m<4;m++){
					binary[n][m]=(((Kmap[i][j] >> (3-m)) & 1)+48);	
					}
					/*get binary of Group and store in char*/
					n++;
				}
				if(j==3) j=0;
				else j++;
			}

			/* Simplify */
			for(m=0;m<4;m++){
				for(n=0;n<8;n++){
					if(binary[n][m]-48) num++;
				}	
				if(num==8){ s8[strlen(s8)] = m+97; 
					strcat(s8,"+"); }
				if(num==0){ s8[strlen(s8)] = m+97; 
					strcat(s8,"'+"); }

				num=0;
			}
			/* Simplify */

			count=0;
		}
		/* simplify and Circle */
		else flag=0;
	}
}

void Circle4(){
	int i,j,k,m=0,n=0,nn=0,count=0,count2=0; //for loop times 
	int ii=0,jj=0; //for circle upper left in any [i][j]
	int num=0;
	char binary[8][5];
	int flag=-1;  //double for loop break flag
	int b=0;
	kmap[0][2]=1;//test
	
	for(k=0;k<4;k++){
			for(j=0;j<4;j++){
				if(kmap[k][j]==0 || Circle[k][0]!=0 || kmap[k][0]==-1){
					b=1;
					break;
				}
			}
		/* simplify and Circle */
		if(b==0){
				for(j=0;j<4;j++){
					Circle[k][j]++;

					/*get binary of Group and store in char*/
					for(m=0;m<4;m++){
					binary[n][m]=(((Kmap[k][j] >> (3-m)) & 1)+48);	
					}
					/*get binary of Group and store in char*/
					n++;
				}
			/* Simplify */
			for(m=0;m<4;m++){
				for(n=0;n<4;n++){
					if(binary[n][m]-48) num++;
				}
				if(num==4){ s4[strlen(s4)] = m+97;
					if(m==3) strcat(s4,"+"); }
				if(num==0){ s4[strlen(s4)] = m+97; 
					strcat(s4,"'");
					if(m==3) strcat(s4,"+");}
				
				num=0;
			}
			if(s4[strlen(s4)-1]!=43) strcat(s4,"+");
			n=0;
			/* Simplify */
		}
		/* simplify and Circle */
		else b=0;
	}

	
	for(k=0;k<4;k++){
			for(i=0;i<4;i++){
				if(kmap[i][k]==0 || Circle[0][k]!=0 || kmap[0][k]==-1){
					b=1;
					break;
				}
			}
		/* simplify and Circle */
		if(b==0){
				for(i=0;i<4;i++){
					Circle[i][k]++;

					/*get binary of Group and store in char*/
					for(m=0;m<4;m++){
					binary[n][m]=(((Kmap[i][k] >> (3-m)) & 1)+48);	
					}
					/*get binary of Group and store in char*/
					n++;
				}

			/* Simplify */
			for(m=0;m<4;m++){
				for(n=0;n<4;n++){
					if(binary[n][m]-48) num++;
				}	
				if(num==4){ s4[strlen(s4)] = m+97; 
					if(m==3) strcat(s4,"+"); }
				if(num==0){ s4[strlen(s4)] = m+97; 
					strcat(s4,"'");
					if(m==3) strcat(s4,"+"); }
				num=0;
			}
			if(s4[strlen(s4)-1]!=43) strcat(s4,"+");
			n=0;
			/* Simplify */
		}
		/* simplify and Circle */
		else b=0;
	}

	for(i=0;i<4;i++){       
		for(j=0;j<4;j++){
	//position for loop star		
			
			if(i==3) ii=0; //lower right
		 	else ii = i+1;
			if(j==3) jj=0;
			else jj = j+1;
			if((kmap[i][j]!=0) && (kmap[i][jj]!=0) && (kmap[ii][j]!=0) && (kmap[ii][jj]!=0)){
					flag = 1;
			}	 

			if(flag==1 && (kmap[i][j]==1) && Circle[i][j]==0){  //Each number in this circle != 0 and circle times = 0 	 	
				for(k=i;count2<2;count2++){
					for(n=j;count<2;count++){
						Circle[k][n]++;

						/*get binary of Group and store in char*/
							for(m=0;m<4;m++){
							binary[nn][m]=((((Kmap[k][n] >> (3-m)) & 1))+48);
							}	
						/*get binary of Group and store in char*/
						if(n==3) n=0;
						else n++;
						nn++;
					}
					count=0;
					if(k==3) k=0;
					else k++;
				}
				count2 =0;
				/* Simplify */
				for(m=0;m<4;m++){
					for(nn=0;nn<4;nn++){
						if(binary[nn][m]&1) num++;
						printf("num:%d ",num);
					}
					printf("\n");
					if(num==4){ 
						s4[strlen(s4)] = m+97;
						if(m==3) strcat(s4,"+");
					}
					if(num==0){ 
						s4[strlen(s4)] = m+97; 
						strcat(s4,"'"); 
						if(m==3) strcat(s4,"+");
					}
					num=0;
				}
				/* Simplify */
				flag = -1;
				continue;
			}
			flag=-1;
			
			if(i==3) ii=0;  //lower left
			else ii = i+1;  
			if(j==0) jj=3;
			else jj = j-1;
			if(kmap[i][j]!=0 && kmap[i][jj]!=0 && kmap[ii][j]!=0 && kmap[ii][jj]!=0){
					flag=1;	
			} 
			if(flag==0 && Circle[i][j]==0 && kmap[i][j]==1){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=i;count2<2;count2++){
					for(n=jj;count<2;count++){
						Circle[k][n]++;
							
							for(m=0;m<4;m++){
							binary[nn][m]=(((Kmap[k][n] >> (3-m)) & 1)+48);	
							}
						
						//get binary of Group and store in char
						if(n==3) n=0;
						else n++;
						nn++;
					}
					count=0;
					if(k==3) k=0;
					else k++;
				}
				nn=0;
				// Simplify //
				for(m=0;m<4;m++){
					for(nn=0;nn<4;nn++){
						num += binary[nn][m]-48;
					}
					if(num==4){ s4[strlen(s4)] = m+97; 
						if(m==3)strcat(s4,"+");}
					if(num==0){ s4[strlen(s4)] = m+97; 
						strcat(s4,"'");if(m==3)strcat(s4,"+");}

				num=0;
				}
				// Simplify //
				count2=0;
				flag = 1;
				continue;					
			}
			flag=-1;

			if(i==0) ii=3;  //upper left
			else ii = i-1;  
			if(j==0) jj=3;
			else jj = j-1;
			if(kmap[i][j]!=0 && kmap[i][jj]!=0 && kmap[ii][j]!=0 && kmap[ii][jj]!=0){
					flag=1;
			}	 
			if(flag==1 && Circle[i][j]==0 && kmap[i][j]==1){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=ii;count2<2;count2++){
					for(n=jj;count<2;count++){
						Circle[k][n]++;

						//get binary of Group and store in char//
				
							for(m=0;m<4;m++){
							binary[nn][m]=(((Kmap[k][n] >> (3-m)) & 1)+48);
							}
						
						//get binary of Group and store in char//
						if(n==3) n=0;
						else n++;
						nn++;
					}
					count=0;
					if(k==3) k=0;
					else k++;
				}
				nn=0;
				// Simplify //
				for(m=0;m<4;m++){
					for(nn=0;nn<4;nn++){
						num += binary[nn][m] - 48;
					}
					if(num==4){ s4[strlen(s4)] = m+97; 
						if(m==3)strcat(s4,"+");}
					if(num==0){ s4[strlen(s4)] = m+97; 
						strcat(s4,"'");if(m==3)strcat(s4,"+");}

				num=0;
				}
				// Simplify //
				count2=0;
				flag = 1;
				continue;					
			}
			flag=-1;

			if(i==0) ii=3;  //upper right
			else ii = i-1;  
			if(j==3) jj=0;
			else jj = j+1;
			if(kmap[i][j]!=0 && kmap[i][jj]!=0 && kmap[ii][j]!=0 && kmap[ii][jj]!=0){
					flag=1;
			}	 
			if(flag==1 && Circle[i][j]==0 && kmap[i][j]==1){ //Each number in this circle != 0 and circle times = 0 ,so circle them
				for(k=ii;count2<2;count2++){
					for(n=j;count<2;count++){
						Circle[k][n]++;

						//get binary of Group and store in char//
							for(m=0;m<4;m++){
							binary[nn][m]=(((Kmap[k][n] >> (3-m)) & 1)+48);
							}
						
						//get binary of Group and store in char//
						if(n==3) n=0;
						else n++;
						nn++;
					}
					count=0;
					if(k==3) k=0;
					else k++;
				}
				nn=0;
				//Simplify //
				for(m=0;m<4;m++){
					for(nn=0;nn<4;nn++){
						num += binary[nn][m]-48;

					}
					if(num==4){ s4[strlen(s4)] = m+97; 
						if(m==3)strcat(s4,"+");}
					if(num==0){ s4[strlen(s4)] = m+97; 
						strcat(s4,"'");if(m==3)strcat(s4,"+");}

				num=0;
				}
				// Simplify //
				count2=0;
				flag = 1;
				continue;					
			} 
			flag=-1;
			//position for loop end
		}
	}
}

void Circle2(){
return;
}

void Circle1(){
return;
}

//GetGroupTerm funtction
int GetGroupTerm(char* input,int len,int term[]){
	int i[4] = {0}; //for loop times
	int a[4] = {-1,-1,-1,-1};   //store abcd bit ,default 'X' = -1
	int j,k,m,n;  //for loop times
	int Bool = 0; //whether this input is essential or not
	int count=0; //
	int ca=0,cb=0,cc=0,cd=0;//use for find binary term
	char c[16][5];   //store minterms (binary)
	int total = 0;     //minterm[total] = total
	char ch[3]="01";	//integer 0 or 1 cast to char '0' or '1'
	for(j=0;j<16;j++) term[j]=-1;	
	
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
			total +=((c[j][k]-48) << (3-k));
//find group position and check whether this group is essential primary inplicant 
			
		}
		for(m=0;m<4;m++){
			for(n=0;n<4;n++){
				if(total==Kmap[m][n]){
					if(Circle[m][n]==1){
						Bool = 1;
					}
				}	
			}
		}
	  term[total] = total; 
	}

	if(Bool){
		Groupnum++;
		printf("Group%d : m(",Groupnum);
	for(j=0;j<16;j++){
		if(count!=0 && term[j]==j) printf(",");
		if(term[j]==j){
			printf("%d",term[j]); 
			count++;
		}
	}
	printf(")\n");
	}

	return Bool;
}

int GetGroup(char* PI){
	return 0;
}
