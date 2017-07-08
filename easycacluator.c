#include  <stdio.h>
int main (void){
	double a =0.0, b=0.0;
	char c ;
	printf ("qing shu ru liang ge shu ");
	scanf("%lf%c%lf" ,&a,&c,&b );
	switch (c)
	{
	case '+':	
	 printf("jie guo shi %lf \n",a+b);	
	 break;	 
	 case '-': 
	 printf("jie guo shi %lf\n",a-b);
	 break;
	
	
	case '*':
	 printf("jie guo shi %lf\n",a*b);
	 break;
	
	 case '/':
    printf("jie guo shi %lf\n",a/b);
	break;
	
	default  :
		printf ("wu jie guo ");
} 
}
