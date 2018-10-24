CC=g++
CFLAGS=-c -Wall
OBJECTS = test.o daf.o qualifier.o ori_point.o global.o angle.o \
  b_rel.o rel.o converse.o compose.o rel_util.o b_com.o cmdconfig.o

all:daf

daf:$(OBJECTS)
# use TAB rather than space...
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $<
# another way: "%.o: %.cpp" single-suffix

clean:
	rm -rf *.o
