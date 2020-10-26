import java.util.*;

class Array{

public static void main(String [] args)
{
	Scanner sc = new Scanner(System.in);
	int myarray[] = new int[5];
	System.out.println("Enter five number to store in array =");
	for(int i=0;i<5;i++)
	{
		myarray[i]=sc.nextInt();
	}
	
	for(int j=0;j<5;j++){
		
		System.out.println("This is array"+myarray[j]);
	}
}


}
