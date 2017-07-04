package cc;
import java.util.*;


public class Selection{
	private Selection(){
		}	
	public static void sort(Comparable[] arr){
		
		int n = arr.length;
		for(int i=0;i<n;i++)
		{
			int minIndex = i ;
			for (int j=i+1; j<n; j++ )
			if (arr[j].compareTo(arr[minIndex])<0)
				minIndex =j ;
			
			swap (arr, i, minIndex);
			
		}
		
		
	}
	private static void swap(Object[] arr, int i, int j){
		Object t = arr[i];
		arr [i]= arr[j];
		arr [j]=t;
		}
	
	public static void main (String[] args){
		
	Double[] b = {12.1,45.2,411.1,4.50,2.1,65.60,84.5,455.5,11.4,55.2};
		Selection.sort (b);
		for( int i= 0; i<b.length; i++ ){
			
		System.out.print(b[i]);
		System.out.print(" ");
		}
		System.out.println();
	
	
	
	
	Integer[] a = {1,25,11,44,551,5,441,52,41,36,85};
	Selection.sort (a);
	for( int i= 0; i<a.length; i++ ){
		
	System.out.print(a[i]);
	System.out.print(" ");
	}
	System.out.println();
	
	
	String[]c= {"D","C","B","A"};
	Selection.sort (c);
	for( int i= 0; i<c.length; i++ ){
		
	System.out.print(c[i]);
	System.out.print(" ");
	}
	System.out.println();

	
	Student[] d = new Student[5];
	d[0] = new Student("D",98);
	d[1] =  new Student("C",95);
	d[2] =  new Student("B",95);
	d[3] = new Student("A",90);
	d[4] = new Student("zhangsan", 88);
	Selection.sort(d);
	for(Student i : d){
		System.out.println(i);
	
	}
	}	
	}
