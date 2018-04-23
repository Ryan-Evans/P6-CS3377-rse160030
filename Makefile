# Ryan Evans
# rse160030@gmail.com
# CS 3377.002
#
# Makefile

CXX = g++
CXXFLAGS =
CPPFLAGS = -Wall -I /scratch/perkins/include -Wno-write-strings -g

PROJECTNAME = "CS3377-Program6"

EXECFILE = program6

OBJS = cdkexample.o

LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcurses -lcdk

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE)

$(EXECFILE):	$(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS)  $(LDLIBS) -o $@

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@tar -cf $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
