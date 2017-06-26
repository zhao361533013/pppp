# pppp
package practice;
import java.util.*;
public class lab3 {
public static void main (String[] args)
{
LinkedList<String> words = new LinkedList<String>();
words.add("one");
words.add("two");
words.add("three");
words.add("four");

for (Iterator<String> it = words.iterator(); it.hasNext();)
if (it.next().contains("e"))
	{it.remove();
break;

}
for (String word : words)
	System.out.println(word);
}
}
