import java.util.*;
import java.util.Scanner;

import java.util.Scanner; 

public class Main
{

	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		System.out.print("qing shu ru/n");//多项式
		Scanner in = new Scanner(System.in);
		int[] a,b; //存放两个多项式
		int max=0;  //存放最高幂数组的长度
		//第一个多项式开始
		int n=in.nextInt(); //读入幂并临时保存到n
		int x=in.nextInt(); //读入系数并临时保存到x
		a=new int[n+1]; //以最大幂确定数组的长度并实例化数组
		a[n]=x;
		do
		{
			n=in.nextInt(); //读入幂
			x=in.nextInt(); //读入系数
			a[n]=x;
			
		}while(n!=0); //如果n为则第一个多项读入结束，循环结束。
		
		//第二个多项开始
		n=in.nextInt();
		x=in.nextInt();
		b=new int[n+1];
		do
		{
			n=in.nextInt();
			x=in.nextInt();
			b[n]=x;
			
		}while(n!=0);
		
		if(a.length>b.length)  //计算最长数组长度
		{
			max=a.length;
		}
		else
		{
			max=b.length;
		}
	for(int j=max-1;j>=0;j--)
	{
		int sum=0;
		if(j<a.length&&a[j]!=0)
		{
			sum=sum+a[j];
		}
		if(j<b.length&&b[j]!=0)
		{
			sum=sum+b[j];
		}
		if(sum==0) //如果系数为零则跳出本次循环
			continue;
		if(j>1)  //幂大于1时的输出格式
		{
			System.out.print(sum+"x"+j+"+"); 
		}else if(j==0) //幂为时的输出格式
			
		{
			System.out.print(sum); 
		} else if(j==1)//幂1为时的输出格式
		{
			System.out.print(sum+"x"+"+"); 
		}
	}
	}
}
