CC=g++
LFLAGS= -lncurses

DEPS = engine.h viewport.h
OBJS:= engine.o viewport.o
SRCS = engine.cpp viewport.cpp

BDIR = build

$(BDIR)/%.o: %.cpp %.h
	@mkdir -p $(BDIR)
	@printf "building %s\n" $@
	@$(CC) $(CFLAGS) -c -o $@ $<

make: $(OBJS) main_driver.cpp
	$(CC) $(CFLAGS) -o run $^ $(LFLAGS)

clean:
	@$(RM) *.o *.gch run $(BDIR)/*.o $(BDIR)/*.gch

