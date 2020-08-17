# Transcompiler for c 

This is a little Transcompiler from my own language defined by me to c(generating a c file).
Here is my language syntax:

	#define Linux(C)
	<int> hey=23;
	print `hey=`;
	input(hey);
	if hey == 1
	{
		print ` how are you?`;
	}
	forhile <int> i=0;i<hey;i++ {

		if i==1 
		{
			print `\n sad`;
		}
		print `helloword\n`;
		print hey;
		print hey;
	}
	<int> j=3;
		j=1+2;
	forhile j<2 {

		j++;
	}

-define Linux(c) - here we say to transcompile the code to c language (because i wanted to transcompile to bash or other languages)
There are no while or for loops just a loop capable of doing while and for.
-i called forhile(for while)
-print statement( synatx: print ` <what to print>` or print <variable_name>)
-input is cable of getting the input from user
