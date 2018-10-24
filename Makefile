CC=g++
CFLAGS=-c -Wall
OBJECTS = test.o daf.o qualifier.o ori_point.o global.o angle.o \
  b_rel.o rel.o converse.o compose.o rel_util.o b_com.o cmdconfig.o

all:daf

daf:$(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
