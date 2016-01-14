
all: printprogram java

printprogram: 
	gcc -o printprogram printprogram.c -L/usr/X11R6/lib -lXt -lSM -lICE -lX11

java:
	javac *.java

clean:
	rm -f *.class printprogram *.o

