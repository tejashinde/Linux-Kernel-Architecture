#include<stdio.h>
#include<stdlib.h>
int main()
{
	int msize;
	int pagesize,nofpage;
	int *p;
	int frameno,offset;
	int logadd,phyadd;
	int i;

	printf("\nMemory Size : ");
	scanf("%d",&msize);
	printf("\nPage Size : ");
	scanf("%d",&pagesize);

	nofpage=msize/pagesize;
	printf("\n Page Value : %d",nofpage);
	p=(int*)malloc(nofpage*sizeof(int));

	for(i=0;i<nofpage;i++)
	{
		printf("\nFrame of Page :",i);
		scanf("%d",&p[i]);
	}

	printf("\nEnter a logical address:");
	scanf("%d",&logadd);
	frameno=logadd/pagesize;
	printf("\n Frame Number = %d",frameno);
	printf("\n P[frameno] = %d ",p[frameno]);
	offset=logadd%pagesize;
	phyadd=frameno+offset;
	printf("\nPhysical address is : %d",phyadd);
	printf("\n Offset is : %d",offset);
	printf("\n\n");
	return 0;
}
