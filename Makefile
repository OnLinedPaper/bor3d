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

DEPS = engine.h viewport.h timeframe.h message.h message_handler.h environment.h object.h vec3d.h box.h camera.h hitline.h vec2d.h rect2d.h

OBJS:= engine.o viewport.o timeframe.o message.o message_handler.o environment.o object.o vec3d.o box.o camera.o hitline.o vec2d.o rect2d.o
DOBJS:= $(addprefix $(DBDIR)/,$(OBJS))
OBJS:= $(addprefix $(BDIR)/,$(OBJS))

SRCS = engine.cpp viewport.cpp timeframe.cpp message.cpp message_handler.cpp environment.cpp object.cpp vec3d.cpp box.cpp camera.cpp hitline.cpp vec2d.cpp rect2d.cpp

PATHS = . rect2d viewport timeframe vec2d message environment object vec3d camera rect2d/hitbox vec2d
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

mem:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(DDIR)/.v.out $(DDIR)/debug && \
	cat $(DDIR)/.v.out | awk '/HEAP SUMMARY/{p=1}p' > $(DDIR)/.v2.out && \
	sed 's/==.*== //' $(DDIR)/".v2.out" > $(DDIR)/"full-valgrind-out.txt" && \
	cat $(DDIR)/full-valgrind-out.txt > $(DDIR)/valgrind-out.txt 
	@rm $(DDIR)/.v.out $(DDIR)/.v2.out; less $(DDIR)/valgrind-out.txt;


