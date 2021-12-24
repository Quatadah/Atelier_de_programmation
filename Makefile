SET_DIR = set
SEN_DIR = sentinel
DYN_DIR = dynamic
LINK_DIR = link

BIN = sentinel_struc link_struc dynamic_struc sentinel_func link_func dynamic_func

CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} -I ${LINK_DIR} -I ${DYN_DIR}
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =

.PHONY: all test build clean

all: build test

build: ${BIN}

test: build
	@for e in ${BIN}; do \
	echo $${e}; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN} *~

#sentinel
set_sentinel.o: ${SEN_DIR}/set_sentinel.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/set_sentinel.c -c

test_sentinel_struc.o: ${SEN_DIR}/test_sentinel_struc.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/test_sentinel_struc.c -c

sentinel_struc: test_sentinel_struc.o set_sentinel.o
	${CC} test_sentinel_struc.o set_sentinel.o -o $@ ${LDFLAGS}

#pour l'exercice 12
test_sentinel_func.o: ${SET_DIR}/test_set_func.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DSENTINEL ${SET_DIR}/test_set_func.c -c -o $@

sentinel_func: test_sentinel_func.o set_sentinel.o
	${CC} test_sentinel_func.o set_sentinel.o -o $@ ${LDFLAGS}

#dynamic
set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

test_dynamic_struc.o: ${DYN_DIR}/test_dynamic_struc.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc.c -c

dynamic_struc: test_dynamic_struc.o set_dynamic.o
	${CC} test_dynamic_struc.o set_dynamic.o -o $@ ${LDFLAGS}

test_dynamic_func.o: ${SET_DIR}/test_set_func.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DDYNAMIC $< -c -o $@

dynamic_func: test_dynamic_func.o set_dynamic.o
	${CC} test_dynamic_func.o set_dynamic.o -o $@ ${LDFLAGS}


#link
set_link.o : ${LINK_DIR}/set_link.c ${LINK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} $< -c

link.o : ${LINK_DIR}/link.c ${LINK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} $< -c

test_link_struc.o:  ${LINK_DIR}/test_link_struc.c ${LINK_DIR}/link.h ${LINK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} $< -c 

link_struc: test_link_struc.o link.o set_link.o
	${CC} test_link_struc.o link.o set_link.o -o $@ ${LDFLAGS}
	
test_link_func.o: ${SET_DIR}/test_set_func.c ${LINK_DIR}/set_link.h ${LINK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} -DLINK $< -c -o $@

link_func: test_link_func.o set_link.o link.o
	${CC} test_link_func.o set_link.o link.o -o $@
