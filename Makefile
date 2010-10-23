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

SERIALEXE = serial
SERIALDEBUG = serial.debug

BINDIR = bin/

INCLUDES = -I.

ifeq "$(DEBUG)" "OFF"
CCFLAGS = -std=c99 -O3
EXE = $(SERIALEXE)
else
LDFLAGS = -pg
CCFLAGS = -std=c99 -g -pg -DDEBUG
EXE = $(SERIALDEBUG)
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

$(EXE): $(FINALOBJ)
	$(CC) $(LDFLAGS) $(PROFILE) $(FINALOBJ) -o $(BINDIR)$@

obj/optimized/%.o: %.c
	$(CC) -c $(CCFLAGS) $(INCLUDES) -DRAND_SEED=$(RAND_SEED) $< -o $@
	
obj/debug/%.o: %.c
	$(CC) -c $(CCFLAGS) $(INCLUDES) -DRAND_SEED=$(RAND_SEED) $< -o $@

clean:
	rm -f $(addprefix obj/optimized/,$(BASEOBJ)) $(addprefix obj/debug/,$(BASEOBJ)) $(BINDIR)$(SERIALEXE) $(BINDIR)$(SERIALDEBUG)
