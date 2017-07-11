#include <stdio.h>
 
int chackSuShu(int n)
{   int i; 
	if (n = 2 ) 
	{
	return 1;
    }
    for(int i = 2;i<n; i++ );
	{
	  if(n%i == 0)
	   return 0;
	}
}
int chackZhiYingShu(int num,int zys)
{
 if (num%zys== 0)
 return 1;
 else
  return 0;
}
int getNextSuShu(int gss)
{
	int i = 1;
	int n = i+gss;
	if (chackSuShu(n))
	{
	return n;
	}
	else 
	i++;
}
int getMinZYS(int num)
{
  
	for (int i=2;i <num;i++)
	{
      if (chackZhiYingShu(num,i))
      return i;
	}
	
}
 
int main()
{
	int n;
    scanf("%d",&n);
    int m = getMinZYS(n);
    printf("%d = %d",n,m);
    int next = n/m;
    while (next!=1)
    {
      m = getMinZYS(next);
      printf ("x%d",m);
      next = next / m;
	}
}
