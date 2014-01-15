#include "normalize.h"

int main(int argc,char** argv)
{
	if(strcmp(argv[1],"1")==0){
		readftr(argv[2]);
		calc();
		return 0;
	}
	else if(strcmp(argv[1],"2")==0)
	{
		if(argc<4)
		{
			printf("file1 : ftrfile\n");
			printf("file2 : avgfile\n");
			printf("file3 : outputfile\n");
			return -1;
		}
		//readavg(argv[3]);

		scale(argv[2],argv[3],argv[4]);
	}

}