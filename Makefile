

#wuyujie
#objects := $(patsubst %.c,%.o,$(wildcard *.c))

SRC := $(wildcard *.cpp *.c)

DIR :=$(notdir $(SRC))

INCLUDE := -I./include  -I./ -I./include/util/ -I./include/util/detail

LIB     :=-L./utils/lib -L./ -ltarsutil


objects := $(patsubst %.cpp,%.o,$(DIR))


server:
	g++ -o  $@  $(INCLUDE) $(LIB) $(DIR)



all:
	@echo $(SRC)




