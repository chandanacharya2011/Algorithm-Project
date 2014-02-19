# variable definition

CC = g++
MAINSRCS = p2.C
OTHSRCS = 
TEMPLATESRCS = two-three-tree.C
HEADERS = two-three-tree.h
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.C=.o)
TARGETS = $(MAINSRCS:.C=)
MEMCHECKARGS = < database.in

CFLAGS = -g -Wall

%.o: %.C
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS) tags

tags: $(SRCS) $(HEADERS) $(TEMPLATESRCS)
	ctags $^

.PHONY: all memcheck clean tags
