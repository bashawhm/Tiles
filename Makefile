CC ?= clang
CFLAGS += -pipe -march=native -Weverything -O3 -std=c11 `sdl2-config --cflags`
LDFLAGS += `sdl2-config --libs` -lSDL2_image -lSDL2_mixer

TARGET := tiles

SRC := main.c

DEPS := $(addprefix .build/,$(SRC:.c=.d))
OBJS := $(addprefix .build/,$(SRC:.c=.o))

.SUFFIXES:
.PRECIOUS: %/.dir
.PHONY: all clean depend
.DEFAULT: all

all: $(TARGET)
depend: $(DEPS)

$(TARGET): $(OBJS) $(DIR)
	@echo "LD $@"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

.build/%.o: src/%.c .build/%.d .build/.dir
	@echo "CC $(@F)"
	@$(CC) $(CFLAGS) -c -o $@ $<

.build/%.d: src/%.c .build/.dir
	@echo "DEP $(@F)"
	@$(CC) $(CFLAGS) -M -MP -MT $(subst .c,.o,$(subst src/,.build/,$<)) $< > $@ 2>/dev/null

%/.dir:
	@echo "MKDIR $(@D)"
	@mkdir -p "$(@D)"
	@touch "$@"

clean:
	-rm -rf .build $(TARGET)
