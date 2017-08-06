CFLAGS = -Wall

SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

MKDIR_P = mkdir -p


all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS)  -o $@ $<

# runtest: 
