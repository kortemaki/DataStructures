ParenTest: clean BalancedParens
	cat sampleStrings.txt | xargs -I{} -d"\n" ./a.out {}

BalancedParens: clean
	gcc BalancedParentheses.c Stack.c LinkedList.c

Stack: clean
	gcc StackTester.c Stack.c LinkedList.c

LinkedList: clean
	gcc LinkedListTester.c LinkedList.c

clean:
	rm -f *~
	rm -f *.gch

