
//=============================================================================
//
//	elf2bin.c	.elf File→.bin File
//
//	概要：mwldarmコマンドで吐き出された.elfファイルをデータのバイナリファイルにする
//		  mwldarmのオプションで、アセンブラの.oファイルから生成されたテキストファイルのelfにのみ対応
//
//=============================================================================

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static	const	char	DataTopLabel[]={"			*** EXECUTABLE CODE (.text) ***"};

void	main(int argc,char *argv[])
{
	FILE	*fp_r,*fp_w;
	int		i,j,cnt,size;
	char	buf[256];
	char	w_name[80];
	char	Comment1[80];
	char	Comment2[80];
	unsigned	long	Opcode;

	if(argc<2){
		printf("usage:elf2bin .elfFileName\n");
		exit(-1);
	}

	if((fp_r=fopen(argv[1],"rb"))==NULL){
		printf("FileOpenError! %s\n",argv[1]);
		exit(-1);
	}

	for(i=strlen(argv[1]);i>0;i--){
		if(argv[1][i]=='.'){
			break;
		}
	}
	if(i){
		for(j=0;j<i;j++){
			w_name[j]=argv[1][j];
		}
		w_name[j]='\0';
	}
	else{
		strcpy(w_name,argv[1]);
	}
	strcat(w_name,".bin");

	fp_w=fopen(w_name,"wb");

	//データ部のラベルを検索
	while(fgets(buf,256L,fp_r)!=NULL){
		if(strncmp(buf,DataTopLabel,strlen(DataTopLabel))==0){
			break;
		}
	}

	//3行読み飛ばす
	fgets(buf,256L,fp_r);
	fgets(buf,256L,fp_r);
	fgets(buf,256L,fp_r);

	while(fgets(buf,256L,fp_r)!=NULL){
		if(strlen(buf)>2){
			sscanf(buf,"%s%s",&Comment1, &Comment2);
			if(Comment2[strlen(Comment2)-1]!=':'){
				sscanf(buf,"%s%x",&Comment1, &Opcode);
				fputc((Opcode&0x000000ff)>> 0,fp_w);
				fputc((Opcode&0x0000ff00)>> 8,fp_w);
				fputc((Opcode&0x00ff0000)>>16,fp_w);
				fputc((Opcode&0xff000000)>>24,fp_w);
			}
		}
	}

	printf("%s finish!\n",w_name);
	
	fclose(fp_r);
	fclose(fp_w);
}
