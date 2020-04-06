#include<stdio.h>
#include<stdlib.h>
#include<string.h>






struct defineVars{

			char * name;
			char * typeVar;
			char * valueStore;
			struct defineVars * next ;

};




void scannText(char * text);
char * aloc(int n);
char ** alocScan(int  n,int l);
void interpretData(char ** al);
void * readLineByLine(char * filename);
void clearStiv(char * stiv);
void createCFile(char * filename);
void writeCFile(char * filename);
int evaluateFunctions(char * func);
void finishCfile(char * filename);
void writeToCFile(char * filename,char * whatToWrite);
void executeCommandsLinux();

char * FILENAME;

int main(int num__,char ** filename){

	FILENAME=aloc(1000);
	char * save_filename=aloc(100);
	strcpy(save_filename,filename[1]);
	strcat(filename[1],".c");
	strcpy(FILENAME,filename[1]);
	createCFile(FILENAME);
	printf(" ");
	//writeCFile(FILENAME);
	readLineByLine(save_filename);
	finishCfile(FILENAME);
	writeToCFile(FILENAME,"char * aloChar(int n){char * name;name=(char *)malloc(n*sizeof(char));if ( name == NULL){printf(\"memory error\");}return name;}");
	executeCommandsLinux();


	return 0;
}




void * readLineByLine(char * filename){
	char * buffer=aloc(3000);
	char * buffer2=aloc(3000);
	FILE * f;
	char c;
	int saveSpaces=0;
	int yi=0;
	f=fopen(filename,"r");
	while((c=fgetc(f))!=EOF){
		if(c=='`'){
			saveSpaces+=1;
			if(saveSpaces%2==0){
				saveSpaces=0;
			}
		}
		if(saveSpaces==1){
				if(c!='\n'  && c!='\0' && c!='\t' && c!='\r'){
					buffer[yi]=c;
			//		printf("%c----\n",c );
					yi++;
				}
		}else{
			if(c!='\n'  && c!=' ' && c!='\0' && c!='\t' && c!='\r'){
				buffer[yi]=c;
			//	printf("%c----\n",c );
				yi++;
			}
		}

	}

	//printf("%s",buffer);
	//buffer="#define Linux import stdio import { stdio.h,stdlib.h,string.h }print `hello  world`  print 2+3<int> var1<float> var5 var2 = {int};//accept just int";
		if(strcmp(buffer," ")!=0 || buffer[0]=='\0'){
			scannText(buffer);
		}

	fclose(f);

}


void scannText(char * text){


	int z=0;
	int l=0;
	char * specialCharacters;
	char ** al=alocScan(3000,3000);
	char * stiv=aloc(3000);

	for(int i=0;i<strlen(text);i++){

		if(text[i]=='`' || text[i]==',' || text[i]=='=' || text[i]=='+' || text[i]=='/' || text[i]=='-' || text[i]=='*'  || text[i] == '(' || text[i] == '<' || text[i] == '>' ||  text[i] == ')' ||  text[i] == '|' ||  text[i] == '&' ||  text[i] == ';' || text[i] == '{' || text[i] == '}' || text[i] == '#' ){
			if(strlen(stiv)==0){
				//if is empty stiv
				al[z][0]=text[i];

				z++;
			}else{
				//printf("1-%s-%c\n",stiv,text[i]);
				//if stiv has something in it
				for(int y=0;y<=l;y++){

						al[z][y]=stiv[y];

				}
				//printf("11-%s-%c-%d\n",stiv,text[i],z);

				clearStiv(stiv);
				l=0;

				z++;
				al[z][0]=text[i];
				z++;
			}


		}else{
			stiv[l]=text[i];
			//printf("2-%s-%c\n",stiv,text[i]);
			l++;
			if(strcmp(stiv,"print")==0 || strcmp(stiv,"true")==0 || strcmp(stiv,"false")==0 || strcmp(stiv,"bool")==0 ||strcmp(stiv,"if")==0 || strcmp(stiv,"forhile")==0 || strcmp(stiv,"int")==0 ||  strcmp(stiv,"else")==0 || strcmp(stiv,"elif")==0 || strcmp(stiv,"float")==0 || strcmp(stiv,"import")==0 || strcmp(stiv,"Linux(C)")==0 || strcmp(stiv,"define")==0 || strcmp(stiv,"input")==0 || strcmp(stiv,"import")==0){

				for(int y=0;y<=l;y++){
					if(stiv[y]!=' '  || stiv[y]!='\n'){
						al[z][y]=stiv[y];
					}
				}
				clearStiv(stiv);

				z++;
				l=0;
			}

		}


	}

	interpretData(al);
	free(*al);
	free(al);
	free(stiv);
}

void createCFile(char * filename){

	FILE * f;
	f=fopen(filename,"w");
	fprintf(f,"#include<stdio.h>\n#include<string.h>\n#include<stdio.h>\nchar * aloChar(int n);\nint main() \n{ ");
	fclose(f);

}

void writeCFile(char * filename){
	FILE * f;
	f=fopen(filename,"a");
	fprintf(f,"#include<stdio.h>\n#include<string.h>\n#include<stdio.h>\nchar * aloChar(int n);\nint main() \n{ ");

	fclose(f);
}

void writeToCFile(char * filename,char * whatToWrite){
	FILE * f;
	f=fopen(filename,"a");
	fprintf(f,"%s",whatToWrite);

	fclose(f);
}
void finishCfile(char * filename){
	FILE * f;
	f=fopen(filename,"a");
	fprintf(f,"\n\treturn 0;\n}");

	fclose(f);
}

void clearStiv(char * stiv){
	for(int i=0;i<3000;i++){
		stiv[i]='\0';
	}
}

void interpretData(char ** al){

	char ** al1=alocScan(3000,3000);

	for(int y=0;y<3000;y++){
		for(int k=0;k<3000;k++){
			if(al[y][k]!=' '){
				al1[y][k]=al[y][k];
			}
		}
	}
	int y=0;
	//printf("__________________________");
	int ok__=0;
	int on=0;
	int f=0;
	while(al[y][0]!='\0'){

				//evaluateFunctions(al[y]);
			//	printf("%s\n",al[y]);

				if(strcmp(al[y],"print")==0 && al[y+1][0]=='`'){
					writeToCFile(FILENAME,"\n\tprintf(\"");

					for( f=y+2;al[f][0]!='`';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,"\");");
					y=f+1;
						on=1;
				}else if(strcmp(al[y],"print")==0 && al[y+1][0]!='`'){
					writeToCFile(FILENAME,"\n\tprintf(\"%d\"");

					for( f=y+1;al[f][0]!=';';f++){
						writeToCFile(FILENAME,",");
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,");");
					y=f;
					on=1;
				}
				if(al[y][0]=='<' && strcmp(al[y+1],"int")==0 &&al[y+2][0]=='>' ){
					writeToCFile(FILENAME,"\n\tint ");
					for( f=y+3;al[f][0]!=';';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,";");
					y=f;
					on=1;
				}
				if(al[y][0]=='<' && strcmp(al[y+1],"float")==0 &&al[y+2][0]=='>' ){
					writeToCFile(FILENAME,"\n\tfloat ");
					for( f=y+3;al[f][0]!=';';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,";");
					y=f;
					on=1;
				}
				if(al[y][0]=='<' && strcmp(al[y+1],"bool")==0 &&al[y+2][0]=='>' ){
					writeToCFile(FILENAME,"\n\tint ");
					for( f=y+3;al[f][0]!=';';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,";");
					y=f;
					on=1;
				}
				if(al[y][0]=='<' && strcmp(al[y+1],"char")==0 &&al[y+2][0]=='>' ){
					writeToCFile(FILENAME,"\n\tchar ");
					for( f=y+3;al[f][0]!=';';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,";");
					y=f;
					on=1;
				}
				if(al[y][0]=='<' && strcmp(al[y+1],"string")==0 &&al[y+2][0]=='>' ){
					//int countWords=0;
					//int startWords=0;
					writeToCFile(FILENAME,"\n\tchar * ");
					for( f=y+3;al[f][0]!=';';f++){
						writeToCFile(FILENAME,al[f]);
						if (al[f][0]=='='){
							writeToCFile(FILENAME,"aloChar(100);\n\t");
							writeToCFile(FILENAME,al[f-1]);
							writeToCFile(FILENAME,"=");
						}
						/*if(startWords==1 || al[f][0]=='"'){
							if(al[f][0]=='"'){
								startWords+=1;
							}
							countWords++;
						}*/
					}
					writeToCFile(FILENAME,";");
					y=f;
					on=1;
				}


				if(strcmp(al[y],"forhile")==0 ){
					int isWhile=0;
					for( f=y+1;al[f][0]!='{';f++){
						if(al[f][0]==';'){
							isWhile=1;
						}
					}
					if(isWhile==0){
						writeToCFile(FILENAME,"\n\t while( ");
					}else if( isWhile==1){
						writeToCFile(FILENAME,"\n\t for( ");
					}
					for( f=y+1;al[f][0]!='{';f++){
						if(al[f][0]=='<' && al[f+2][0]=='>' &&  strcmp(al[f+1],"int")==0  ){
							writeToCFile(FILENAME," int ");
							f+=2;
							y+=1;
						}else{
							writeToCFile(FILENAME,al[f]);
						}
						if(al[f][0]==';' &&  al[f+1][0]==')'){
							writeToCFile(FILENAME,"){");
							f+=3;
							//y+=f;
						}//else if(isWhile==0){
						//	writeToCFile(FILENAME," )");
						//}
					}

					writeToCFile(FILENAME,"){");
					y=f;
					on=1;
				}
				if(al[y][0]=='}' && (al[y-1][0]==';' || al[y-1][0]=='{')){
					writeToCFile(FILENAME,"\n\t}");
					on=1;
					//y=f;
				}
				if(strcmp(al[y],"if")==0){
					writeToCFile(FILENAME,"\n\t if (");
					for( f=y+1;al[f][0]!='{';f++){
						writeToCFile(FILENAME,al[f]);
					}
					writeToCFile(FILENAME,"){");
					on=1;
					y=f;
				}
				if(strcmp(al[y],"input")==0 && al[y+1][0]=='(' && al[y+3][0]==')'){
					writeToCFile(FILENAME,"\n\tscanf(");
					writeToCFile(FILENAME,"\"%d\",");
					writeToCFile(FILENAME,"&");
					writeToCFile(FILENAME,al[y+2]);
					writeToCFile(FILENAME,");");
					on=1;
					y=y+4;
				}
				if(al[y]=="#"){
						if(strcmp(al[y+1],"define")==0){
							printf("\n ERROR 2 : no define %s",al[y] );
							ok__=1;
						}

						if(strcmp(al[y+2],"Linux")==0 || strcmp(al[y+2],"linux")==0){
								printf("\n ERROR 3 : no operating system ");
								ok__=2;
						}

						if(ok__!=0){
							break;
						}
					y=y+2;
					on=1;
				}
			if(on!=1){
				writeToCFile(FILENAME,al[y]);
			}else{
				on=0;
			}

		y++;
	}
	free(*al1);
	free(al1);
}






int evaluateFunctions(char * func){
		char * alocSave;
		alocSave=aloc(strlen(func)+3);
		int p=0;

		for(int i=0;i<strlen(func);i++){
			if(func[i]!=' ' || func[i]!='\0'|| func[i]!='\n'){
				alocSave[p]=func[i];
				p++;
			}
		}
		//printf("--%s--\n",alocSave);
		if(strcmp(alocSave,"print")==0){

			//printf("-----------------hey!!!!!");
			return 1;
		}else if(strcmp(alocSave,"define")==0){


		}
	free(alocSave);

	return 0;
	//return 0 if is ok and 1 if isnt
}

char * aloc(int n){

	char * al;
	al=(char *)malloc(n*sizeof(char));
	if(al==NULL){
		exit(1);
	}
	return al;
}


void executeCommandsLinux(){
	char  addCompile1[100]="gcc -o ";
	char  remove[100];
	strcat(addCompile1,"pr_1.out ");
	strcat(addCompile1,FILENAME);
	strcat(addCompile1," -w");
	system(addCompile1);
	strcat(remove,"rm ");
	strcat(remove,FILENAME);
//	system(remove);
	system("./pr_1.out");
}


char ** alocScan(int  n,int l){

	char ** vec;

	vec=(char **)malloc(n*sizeof(char*));
	for(int i=0;i<n;i++){

		vec[i]=(char *)malloc(l*sizeof(char));
	}
	return vec;
}
