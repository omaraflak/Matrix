COMPILER = g++
MAIN = test.cpp
OUTFLAGS = -o
OUTFILE = compiled

REMOVE = rm
REMOVEFLAGS = -rf

compile:
	${COMPILER} ${MAIN} ${OUTFLAGS} ${OUTFILE}
clean:
	${REMOVE} ${REMOVEFLAGS} ${OUTFILE}
run:
	./${OUTFILE}