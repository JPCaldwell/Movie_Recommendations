#  Makefile: Editing of Tim Budd's "Makefile" by Bina Ramamurthy and 
#  Ken Regan, Fall 1996, and again by KWR in Spring 2000.
#  Tailored for FlexMake2RSW.make by RSW for CSE250 - HW5, Spring 2014.
#
#  USAGE---enter at command prompt in directory:  make -f PeekClientRSW.make


# Unix Macros---choose which compiler and options here!

CC     = g++
# CC     = g++ -fhandle-exceptions -frtti
# CC     = CC     # name of the Sun C++ compiler---NOT available on timberlake
                  # if you have a command-line installation at home (as
                  # opposed to an IDE like Eclipse), put your compiler here.
# CC = gfilt

LIBS   = -lm
OBJ    = .o
RM     = rm -fr


# SYNTAX: Dependencies must be on same line as ":".  Actions must
# follow on succeeding line(s), and have at least one TAB indent.
# Hence, be careful mouse-copying makefile text if tabs convert to spaces.

all:	Proj2JPCRSW

# Invoke this via "make -f FlexClientRSW.make clean".  No "-" before "clean"!
clean:
	$(RM) *$(OBJ)    # ISR/*$(OBJ)---etc. for any subdirectories

# Below I hard-coded ".o" in place of the variable "$(OBJ)" to save room.

MovieBaseJPC.o: MovieBaseJPC.h MovieBaseJPC.cpp
	$(CC) -c MovieBaseJPC.cpp

UserBaseRSW.o: UserBaseRSW.cpp UserBaseRSW.h 
	$(CC) -c UserBaseRSW.cpp

Proj2JPCRSW: MovieBaseJPC.o UserBaseRSW.o clientJPCRSW.cpp
	$(CC) -o Proj2JPCRSW UserBaseRSW.o MovieBaseJPC.o clientJPCRSW.cpp

# The .o file with main should come before all the other object files in the
# final linking stage.

