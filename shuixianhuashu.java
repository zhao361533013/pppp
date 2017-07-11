package day7;

public class shuixianhuashu {
	public static void main(String[] args){
	  int n =1000;
	  for(int i = 100; i<n;i++) {
		  if (check(i)) 
		  System.out.printf("%d is shuixianhuashu\n",i);
		  }
	  }
	
	public static boolean check (int q ) {
		
		int a = q %10;
		int b = (q /10)%10;
		int c = q/100;
		return ((a*a*a+b*b*b+c*c*c==q)); 
}
}
