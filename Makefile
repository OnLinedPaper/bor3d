CC=g++
DIR := ${CURDIR}
CFLAGS = -Wall -Wpedantic --std=c++17 -O3 -I$(DIR)
LFLAGS= -lncurses
BDIR = build
XDIR = bin

DEPS = engine.h viewport.h timeframe.h

OBJS:= engine.o viewport.o timeframe.o
OBJS:= $(addprefix $(BDIR)/,$(OBJS))

SRCS = engine.cpp viewport.cpp timeframe.cpp

PATHS = . rec2d viewport timeframe vec2d
VPATH = $(addprefix src/,$(PATHS))

$(BDIR)/%.o: %.cpp %.h
	@mkdir -p $(BDIR)
	@printf "building %s\n" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJS) main_driver.cpp
	@mkdir -p $(XDIR)
	@printf "final compilation..."
	@$(CC) $(CFLAGS) -o $(XDIR)/$@ $^ $(LFLAGS)
	@printf "compiled\ndone\n"

clean:
	@$(RM) *.o *.gch run $(BDIR)/*.o $(BDIR)/*.gch

