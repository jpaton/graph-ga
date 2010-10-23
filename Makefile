DEBUG = OFF

CC = gcc

TYPEDIR = DataTypes/

TYPESRC = genetic.c \
		  graph.c
		  
ENGINEDIR = Engines/

ENGINESRC = basic.c \

UTILDIR = Utils/

UTILSRC = sorting.c \
		  #rng.c \

MAINSRC = main.c 

VPATH = $(TYPEDIR):$(ENGINEDIR):$(UTILDIR)

SRC = $(MAINSRC) \
	$(addprefix $(TYPEDIR),$(TYPESRC)) \
	$(addprefix $(UTILDIR),$(UTILSRC)) \
	$(addprefix $(ENGINEDIR),$(ENGINESRC))

BINDIR = bin/

INCLUDES = -I.

ifeq "$(SERIAL)" "ON"
# no parallelization
EXEPREFIX = "serial"
PARFLAGS = -DSERIAL
else
# enable parallelization
EXEPREFIX = "openmp"
endif

ifeq "$(DEBUG)" "OFF"
CCFLAGS = -std=c99 -O3 -fopenmp
LDFLAGS = -fopenmp
EXE = $(EXEPREFIX).opt
else
CCFLAGS = -std=c99 -g -pg -DDEBUG -fopenmp
LDFLAGS = -pg -fopenmp
EXE = $(EXEPREFIX).debug
endif

OBJS = $(SRC:.c=.o)

BASEOBJ = $(notdir $(OBJS))

ifeq "$(DEBUG)" "OFF"
FINALOBJ = $(addprefix obj/optimized/,$(BASEOBJ))
else
FINALOBJ = $(addprefix obj/debug/,$(BASEOBJ))
endif

# random number generator seed
RAND_SEED = 12938
	
default: $(EXE)

debug:
	make DEBUG=ON

serial:
	make SERIAL=ON

$(EXE): $(FINALOBJ)
	$(CC) $(LDFLAGS) $(PROFILE) $(FINALOBJ) -o $(BINDIR)$@ -lm

obj/optimized/%.o: %.c
	$(CC) -c $(CCFLAGS) $(INCLUDES) $(PARFLAGS) -DRAND_SEED=$(RAND_SEED) $< -o $@
	
obj/debug/%.o: %.c
	$(CC) -c $(CCFLAGS) $(INCLUDES) $(PARFLAGS) -DRAND_SEED=$(RAND_SEED) $< -o $@

clean:
	rm -f $(addprefix obj/optimized/,$(BASEOBJ)) $(addprefix obj/debug/,$(BASEOBJ)) $(BINDIR)openmp.opt $(BINDIR)openmp.debug $(BINDIR)serial.opt $(BINDIR)serial.debug 
