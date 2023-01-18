# simple hacky way to convert strings to lowercase, usage: NEW_VAR = $(call lc,$(VAR))
lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

CC=gcc
STD=c99
CFLAGS=-I. -Wall -MMD -MP
LFLAGS=-lSDL2
BUILD_TARGET=debug

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)
DEPENDS=$(patsubst %.c,%.d,$(SRCS_C))
bin=gfx_demo

ifeq ($(call lc,$(BUILD_TARGET)),debug)
	CFLAGS+=-O0 -g
else
	ifeq ($(call lc,$(BUILD_TARGET)),release)
		CFLAGS+=-O3
	else
		ifeq ($(call lc,$(BUILD_TARGET)),relwithdebinfo)
			CFLAGS+=-O3 -g
		else
$(error Invalid Build Target: "$(BUILD_TARGET)")
		endif
	endif
endif

all: $(bin)

%.o: %.c
	$(CC) --std=$(STD) $(CFLAGS) -c $< -o $@

$(bin): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@

.PHONY: clean
.PHONY: run

run: $(bin)
	@./$(bin)

clean:
	$(RM) $(bin) $(OBJS) $(DEPENDS)


