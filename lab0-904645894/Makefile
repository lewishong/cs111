TARGET = lab0
OBJECTS = lab0.o
TAROUTPUT = lab0-904645894.tar.gz
TARINPUT = lab0.c Makefile README backtrace.png breakpoint.png
VERSION = ` date +%Y%m%d-%H%M%S `
ARCHIVEDIR = archive

default: lab0.c
	gcc -g lab0.c -o lab0

check:
	echo "testing" > input.txt;\
	
	./lab0 --input input.txt --output output.txt;\
	if [ $$? -ne 0 ];\
	then\
		echo "fail0";\
	else\
		echo "pass0";\
	fi;\
	
	./lab0 --bad;\
	if [ $$? -ne 1 ];\
	then\
		echo "fail1";\
	else\
		echo "pass1";\
	fi;\
	
	rm -f dummy.txt;\
	./lab0 --input dummy.txt --output.txt;\
	if [ $$? -ne 2 ];\
	then\
		echo "fail2.";\
	else\
		echo "pass2.";\
	fi;\
	
	chmod u-w output.txt;\
	./lab0 --input input.txt --output output.txt;\
	if [ $$? -ne 3 ];\
	then\
		echo "fail3";\
	else\
		echo "pass3";\
	fi;\
	
	./lab0 --segfault --catch;\
	if [ $$? -ne 4 ];\
	then\
		echo "fail4";\
	else\
		echo "pass4";\
	fi;\
	rm -f input.txt output.txt	

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS) $(TAROUTPUT)
	
dist:
	tar -czvf $(TAROUTPUT) $(TARINPUT)

.PHONY: archive

archive:
	tar -cvzf $(ARCHIVEDIR)/$(TARGET)-$(VERSION).tar.gz $(TARINPUT)

