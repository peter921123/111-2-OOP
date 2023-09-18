all: View.o Window.o Button.o Label.o TextInput.o Calculator.o
	g++ View.o Window.o Button.o Label.o TextInput.o hw3-1.cpp -o hw3-1
	g++ View.o Window.o Button.o Label.o TextInput.o Calculator.o hw3-2.cpp -o hw3-2

View.o:
	g++ View.cpp -c

Window.o:
	g++ Window.cpp -c

Button.o:
	g++ Button.cpp -c

Label.o:
	g++ Label.cpp -c

TextInput.o:
	g++ TextInput.cpp -c

Calculator.o:
	g++ Calculator.cpp -c

clean:
	rm -f *.o
	rm -f hw3-1
	rm -f hw3-2
