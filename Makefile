CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: test

# To create the executable file count we need the object files
# Heap.o, LinkedList.o, and Hashtable.o:
#
test:  Heap.o Linked_List.o Hashtable.o Game_Logic.o Test.o User_Move.o common.o AI_Move.o
	$(CC) $(CFLAGS) -o test Heap.o Linked_List.o Hashtable.o Game_Logic.o Test.o User_Move.o common.o AI_Move.o

# To create the object file Heap.o, we need the source
# files Heap.c, Heap.h:
#
Heap.o:  Heap.c Heap.h 
	$(CC) $(CFLAGS) -c Heap.c

# To create the object file LinkedList.o, we need the source files
# LinkedList.c and LinkedList.h:
#
Linked_List.o:  Linked_List.c Linked_List.h 
	$(CC) $(CFLAGS) -c Linked_List.c

# To create the object file Hashtable.o, we need the source files
# Hashtable.c and Hashtable.h:
#
Hashtable.o:  Hashtable.c Hashtable.h 
	$(CC) $(CFLAGS) -c Hashtable.c

# To create the object file Pieces_Moves.o, we need the source files
# Pieces_Moves.c and Pieces_Moves.h:
#
common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c

# To create the object file Pieces_Moves.o, we need the source files
# Pieces_Moves.c and Pieces_Moves.h:
#
AI_Move.o: AI_Move.c AI_Move.h
	$(CC) $(CFLAGS) -c AI_Move.c

# To create the object file Pieces_Moves.o, we need the source files
# Pieces_Moves.c and Pieces_Moves.h:
#
User_Move.o: User_Move.c User_Move.h
	$(CC) $(CFLAGS) -c User_Move.c

# To create the object file Game_Logic.o, we need the source files
# Game_Logic.c and Game_Logic.h:
#
Game_Logic.o:  Game_Logic.c Game_Logic.h 
	$(CC) $(CFLAGS) -c Game_Logic.c

Test.o: Test.c
	$(CC) $(CFLAGS) -c Test.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~
	$(RM) count *.gch *~
