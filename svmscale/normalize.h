#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <errno.h>
#include <string.h>

#include <iostream>
int ftrnum=0;
int fline=0;

int cls[500000];
long double ftr[500000][100];
double ftravg[1024]={0};
double ftrdis[1024]={0};


void initialize()
{

	for(int i=0;i<fline;i++)
	{
		for(int j=0 ; j<ftrnum;j++){
			ftravg[j]=0;
			ftr[i][j]=0.0;
		}
	}
	fline=0;
	ftrnum=0;
}

int readnum(char* filename){

	initialize();
	char c;
	char errmsg[CHAR_MAX];
	wchar_t errmsgon[1024];
	size_t ret;
	FILE *fp;
	if(fopen_s(&fp,filename,"r")!=0)
	{
		strerror_s(errmsg,errno);
		printf("%s\n",errmsg);
		mbstowcs_s(&ret,errmsgon,100,errmsg,_TRUNCATE);
		//MessageBox( NULL,errmsgon,L"INPUT", MB_OK );
		exit(1);
	}
	while((c=fgetc(fp))!=EOF)
	{
		if(fline==0&&c==':')
		{ftrnum++;
		}
		else if(c=='\n')
		{
			fline++;
		}
	}


	fclose(fp);
	return ftrnum;
}

int readftr(char* filename){
	readnum(filename);

	FILE *fp;

	char c;
	char errmsg[CHAR_MAX];
	wchar_t errmsgon[1024];
	size_t ret;
	if(fopen_s(&fp,filename,"r")!=0)
	{
		strerror_s(errmsg,errno);
		printf("%s\n",errmsg);
		mbstowcs_s(&ret,errmsgon,100,errmsg,_TRUNCATE);
		//MessageBox( NULL,errmsgon,L"INPUT", MB_OK );
		exit(1);
	}
	int tmp=fline;
	int tmpftr=ftrnum;
	int st;
	for(int i=0;i<tmp;i++)
	{
		if(fline!=tmp)
		{
			break;
		}
		fscanf_s(fp,"%d ",&cls[i]);
		for(int j=0; j<tmpftr;j++)
		{
			fscanf_s(fp,"%d:%lf ",&st,&ftr[i][j]);
			//ftr[i][j]=-log(ftr[i][j]-0.5);
		}

	}

	fline=tmp;
	ftrnum=tmpftr;
	fclose(fp);
	return 0;
}
int calc(){
	int tmp=fline;
	int tmpftr=ftrnum;

	for(int i=0;i<tmp;i++)
	{
		for(int j=0 ; j<tmpftr;j++){
			ftravg[j] += ftr[i][j]/tmp;
		}
	}
		for(int j=0; j<tmpftr;j++)
	{
		double tmpdis=0;
		for(int i=0;i<tmp;i++)
		{
			tmpdis+=pow((ftr[i][j]-ftravg[j]),2.0);

		}
		ftrdis[j]=sqrt(tmpdis);
	}

	for(int i=0;i<tmpftr;i++)
	{
		printf("%d:%lf %lf ",i+1,ftravg[i],ftrdis[i]);
	}
	return 0;
}

int readavg(char* filename){//file to readthe averagedata;

	FILE *fp;

	int tmp=fline;
	int st;
	int tmpftr=ftrnum;
	fopen_s(&fp,filename,"r");

	for(int j=0 ; j<tmpftr;j++){
		fscanf_s(fp,"%d:%lf %lf ",&st,&ftravg[j],&ftrdis[j]);

	}
	fclose(fp);
	return 0;
}

int scale(char* filename1,char* filename2,char *filename3)//file1:ftrfiletoconvert file2:avgfile; file3: outputgile
{
	FILE *fp,*fout;

	int s;
	//readnum(filename1);
	readftr(filename1);
	readavg(filename2);

	int tmpftr=ftrnum;
	int tmp=fline;

	fopen_s(&fout,filename3,"w");


	for(int i=0;i<tmp;i++)
	{
		if(fline!=tmp)
		{
			break;
		}
		if(cls[i]!=NULL){
			printf("%d ",cls[i]);
		fprintf(fout,"%d ",cls[i]);
		}
		for(int j=0; j<tmpftr;j++)
		{
			if(ftrdis[j]!=0){
				fprintf_s(fout,"%d:%lf ",j+1,(ftr[i][j]-ftravg[j])/ftrdis[j]);
			}
			else{
				fprintf_s(fout,"%d:%lf ",j+1,(ftr[i][j]-ftravg[j]));
			}
		}
		fprintf_s(fout,"\n");
	}
	fclose(fout);
	return 0;
}