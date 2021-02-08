CC=g++
DIR := ${CURDIR}
CFLAGS = -Wall -Wpedantic --std=c++17 -I$(DIR)
OFLAGS = -O3
DFLAGS = -g -ggdb -O0
LFLAGS= -lncurses
BDIR = build
XDIR = bin
DDIR = debugging
DBDIR = build/dbuild

DEPS = engine.h viewport.h timeframe.h message.h message_handler.h

OBJS:= engine.o viewport.o timeframe.o message.o message_handler.o
DOBJS:= $(addprefix $(DBDIR)/,$(OBJS))
OBJS:= $(addprefix $(BDIR)/,$(OBJS))

SRCS = engine.cpp viewport.cpp timeframe.cpp message.cpp message_handler.cpp

PATHS = . rec2d viewport timeframe vec2d message
VPATH = $(addprefix src/,$(PATHS))

$(BDIR)/%.o: %.cpp %.h
	@mkdir -p $(BDIR)
	@printf "building %s\n" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJS) main_driver.cpp
	@mkdir -p $(XDIR)
	@printf "final compilation..."
	@$(CC) $(CFLAGS) $(OFLAGS) -o $(XDIR)/$@ $^ $(LFLAGS)
	@printf "compiled\ndone\n"

$(DBDIR)/%.o: %.cpp %.h
	@mkdir -p $(BDIR)
	@mkdir -p $(DBDIR)
	@printf "building debug object %s\n" $@
	@$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

debug: $(DOBJS) main_driver.cpp
	@mkdir -p $(BDIR)
	@mkdir -p $(DBDIR);
	@mkdir -p $(DDIR)
	@printf "final debug compilation... "
	@$(CC) $(CFLAGS) $(DFLAGS) -o $(DDIR)/$@ $^ $(LFLAGS);
	@printf "compiled\ndone\n"

clean:
	@$(RM) -r *.o *.gch run $(BDIR)/* $(XDIR)/*

