LDFLAGS = -lbcm2835

all:
	cc -o km km.c ${LDFLAGS}
	cc -o rowchk rowchk.c ${LDFLAGS}
