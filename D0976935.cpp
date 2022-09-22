#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 10001

struct op{
	char op1[MAX];
	long long int opcode;
}optable;

//SIC Assembler的說明: 
//我一直在找他卡死的原因，發現是在Process2的Function，但是一直找不到在哪。 
//我懷疑是一次開太多TXT檔的關係，導致它處理沒辦法馬上讀檔後做完處理又馬上寫檔。 
//因為他有時會成功，有時會失敗。照理來說，有錯應該會每次都卡死，然後直接結束，
//但是它卻是有機率性的會成功跟失敗。 
//06/05已修正此問題

int Process1(){
	char op[MAX],op1[MAX],op2[MAX],op3[MAX],by[MAX],sym[MAX],label[MAX],filename[MAX];
	int loc=0x0,addr=0x0,start=0x0,count=0x0;
	int i,j,k,r,f,l;
	FILE *fp,*fl,*fin,*fob,*fop,*fsym; 
	printf("關於要一直重複執行的原因，我有打在註解了，在Process1()上面\n\n");
	printf("如果未顯示出:(Object File 寫入完成)");
	printf("請關掉exe檔，再執行一次! 直到顯示出(Object File 寫入完成)就可以了!\n\n");
	printf("06/05已修正此問題\n\n");
//	printf("Enter the file name(Ex.123.txt):");
//	scanf("%s",filename);
	fp=fopen("SICP.txt","r");
	if(fp==NULL){
		printf("NO program File!!"); 
		return 0;
	} 
	fob=fopen("OJ Program.txt","w");
	fsym=fopen("Symbol Table.txt","w+");
	fop=fopen("OpTable.txt","r");
	if(fop==NULL){
		printf("No OpTable File!!"); 
		return 0;
	}
	fin=fopen("LocCtr.txt","w");
	fgets(by,MAX,fp);
	sscanf(by,"%s %s %s",label,op1,op2);
	if(strcmp(op1,"START")==0){
		loc=atoi(op2);	
		while(loc>0){
			start=start+(loc%10)*pow(16,count);
			loc=loc/10;
			count++;
		}
		loc=start;
        fprintf(fin,"%X\t%s\t%s\t%s\n",start,label,op1,op2);
	}
	else{
		loc=0x0;
	}
	while(!feof(fp)){
		fgets(by,MAX,fp);
		r=sscanf(by,"%s%s%s",label,op1,op2);
		if(label[0]!='.'){
			if(r==1){
				strcpy(op1,label);
				fprintf(fin,"%04X\t\t%s\n",loc,op1);
			}
			if(r==2){
				strcpy(op2,op1);
				strcpy(op1,label);
				fprintf(fin,"%X\t\t%s\t%s\n",loc,op1,op2);
			}
			if(r==3){ 
				rewind(fsym);
				while(!feof(fsym)){
					f=0;
					fscanf(fsym,"%s%X",&sym,&addr);
					if(strcmp(label,sym)==0){
						f=1;
						printf("\n噴錯的標籤: %s",label);
						return 0;
					}
				}		
				if(f==0){	
					fprintf(fsym,"%s\t%X\n",label,loc);
					fprintf(fin,"%X\t%s\t%s\t%s\n",loc,label,op1,op2);
				}
			}
			rewind(fop);
			while(!feof(fop)){	
				fscanf(fop,"%s%s",op3,&op);
				if(f==1){
					printf("\n%s Nothing in OpTable!",op1);
					return 0;
				}
				if(strcmp(op1,op3)==0){
					loc+=3;
					f=0;
					break;
				}
				else if(strcmp(op1,"RESW")==0){	
					loc+=3*atoi(op2);
					f=0;
					break;
				}
				else if(strcmp(op1,"RESB")==0){	
					loc+=atoi(op2);
					f=0;
					break;
				}
				else if(strcmp(op1,"WORD")==0){	
					loc+=3;
					f=0;
					break;
				}
				else if(strcmp(op1,"BYTE")==0){
					j=strlen(op2);
					if(op2[0]!='C'&&op2[0]!='X'){	
						loc+=1;
						f=0;
						break;
					}
					else if(strcmp(op1,"BYTE")==0&&op2[0]=='C'){
						loc+=j-3;	
						f=0;
						break;
					}
					else if(strcmp(op1,"BYTE")==0&&op2[0]=='X'){	
						if((j-3)%2!=0){
							loc+=(j-3)/2+1;
						}	
						else{
							loc+=(j-3)/2;
						}	
						f=0;
						break;
					}
					else{
						f=1;
					}
				}
			}
		}
		if(strcmp(op1,"END")==0){
			break;
		}
	}
	printf("\n已產生Symbol Table\n");
	printf("\n已產生LocCtr\n");
	printf("\n已產生Program Length\n");
	fl=fopen("Program Length.txt","w");
	l=loc-start;
	fprintf(fl,"%X",l);
	fclose(fp);
	fclose(fsym);
	fclose(fop);
	fclose(fin);
	fclose(fl);
	fclose(fob);
//	system("PAUSE");
} 

int Process2(){
	int a=0x0,l=0x0,t1=0x0,ta=0x0,ai=0x0,rl=0x0,loc=0x0,addr=0x0,start=0x0,count=0x0;
	int i,j,k,r,os;
	char op[MAX],op1[MAX],op2[MAX],op3[MAX],co[MAX],by[MAX],sym[MAX],opcode[MAX],label[MAX];
	long long int ask,bsk;
	FILE *fin,*fsym,*fop,*fl,*fob;
	
	fin=fopen("LocCtr.txt","r");
	if(fin==NULL){
		printf("\nNo LocCtr File!"); 
		return 0;
	}
    fsym=fopen("Symbol Table.txt","r");
    if(fsym==NULL){
		printf("\nNo Symbol Table File!"); 
		return 0;
	}
    fop=fopen("OpTable.txt","r");
    if(fop==NULL){
		printf("\nNo OpTable File!"); 
		return 0;
	}
    fl=fopen("Program Length.txt","r");
    if(fl==NULL){
		printf("\nNo Program Length File!"); 
		return 0;
	}
    fscanf(fin,"%X%s%s%s",&loc,&label,&op1,&op2);
    fob=fopen("OJ Program.txt","w");
	if(strcmp(op1,"START")==0){
        start=(int)strtol(op2,NULL,16);
        fscanf(fl,"%X",&l);
        fprintf(fob,"H^%-6s^%06X^%06X",label,start,l);
    	fprintf(fob,"\nT^%06X^00^",start);
    	bsk=ftell(fob);
	}  
    fgets(by,MAX,fin);
	while(!feof(fin)){
		fgets(by,MAX,fin);
		r=sscanf(by,"%X%s%s%s",&loc,label,op1,op2);
		if(r==2){ 
			strcpy(op1,label);
		}
		else if(r==3){	
			strcpy(op2,op1);
			strcpy(op1,label);
		}
		if(strcmp(op1,"END")==0||strcmp(op1,"RESW")==0||strcmp(op1,"RESB")==0||count>=0x3C){
			ask=ftell(fob);
			fseek(fob,-(ask-bsk)-3L,1);
			rl=count/0x2;
			fprintf(fob,"%02X^",rl);
			fseek(fob,0L,2);
			if(strcmp(op1,"END")==0){
				break;
			}
			a=loc;
			if(strcmp(op1,"RESW")!=0){
				fprintf(fob,"\nT^%06X^00^",a);
			}
			bsk=ftell(fob);
			count=0x0;
		}	
		rewind(fop);
		os=0;
		while(!feof(fop)){
			fscanf(fop,"%s%s",op3,op);
			if(strcmp(op1,op3)==0){
				strcpy(opcode,op);
				os=1;
				break;
			}
		}
		if(os==1&&op2[j-1]=='X'&&op2[j-2]==','){
			j=strlen(op2);
			op2[j-2]='\0';
			rewind(fsym);
			fscanf(fsym,"%s%X",sym,&addr);
			while(!feof(fsym)){
				if(strcmp(op2,sym)==0){
					ta=addr;
					ta+=0x80;
					break;
				}
			}
			fprintf(fob,"%2s%04X^",opcode,ta);
			count=count+0x6;
			continue;
		}
		else if(os==1&&strcmp(op1,"RSUB")==0){
			fprintf(fob,"%s0000^",opcode);
			count=count+0x6;
			continue;
		}
		else if(os==1&&strcmp(op1,"RSUB")!=0){
			rewind(fsym);
			while(!feof(fsym)){
				fscanf(fsym,"%s%X",sym,&addr);
				if(strcmp(op2,sym)==0){
					ta=addr;
					break;
				}
			}
			fprintf(fob,"%2s%04X^",op,ta);
			count=count+0x6;
			continue;
		}
		else{	
			if(strcmp(op1,"WORD")==0){
				t1=(int)strtol(op2,NULL,10);
				fprintf(fob,"%06X^",t1);
				count=count+0x6;
				continue;
			}
			else if(strcmp(op1,"BYTE")==0){
				if(op2[0]=='C'){
					for(k=0;k<strlen(op2)-3;k++){
						t1=0x0;
						t1=t1+(int)op2[k+2];
						ai=ai*0x100+t1;
					}			
					fprintf(fob,"%6X^",ai);
					count=count+strlen(op2)-0x3;
				}
				else{	
					for(k=0;k<strlen(op2)-3;k++){
						co[k]=op2[k+2];
					}   
					co[k]='\0';
					fprintf(fob,"%s^",co);
					count=count+(strlen(co)+0x0);
				}
				continue;
			}
			else{
				continue;
			}
		}
	}
	fprintf(fob,"\nE^%06X",start);
	printf("\nObject File 寫入完成\n");
	fclose(fin);
	fclose(fsym);
	fclose(fop);
	fclose(fl);
	fclose(fob);
}

int main(){
    Process1();
    Process2();
    return 0;
}
