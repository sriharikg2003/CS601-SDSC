SSE_ARCH_FLAGS=-msse3

CC=g++
ARCH=-m64 $(SSE_ARCH_FLAGS)
BLASINCLUDE=/home/resiliente/cs410software/openblas_0_3_21_install/include
BLASLIB=/home/resiliente/cs410software/openblas_0_3_21_install/lib

CFLAGS=  $(ARCH) -DPARALLEL -I$(BLASINCLUDE) -L$(BLASLIB) -lopenblas 
LDFLAGS=$(ARCH)
LIBS=-lrt



all: matvec 
	./matvec

matvec: matvec.o timeutil.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

matvec.o: matvec.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

timeutil.cpp: timeutil.h

lol: matmul_3 
	./matmul_3

matmul_3: matmul_3.o timeutil.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

matmul_3.o: matmul_3.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

timeutil.cpp: timeutil.h

# all: matvec 

# matvec: matvec.o timeutil.o
# 	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# matvec.o: matvec.cpp
# 	$(CC) -c -o $@ $(CFLAGS) $<

# timeutil.cpp: timeutil.h

# matmul_schedule : matmul.o
# 	$(CC) $(CFLAGS) -o $@ $^ -DJKI_LOOP

# matmul.o:
# 	$(CC) -c -o matmul.cpp
# clean:
# 	$(RM) *.o matvec

matmul_blas: sgemm sdot
	./bin/sgemm.out
	./bin/sdot.out
# SGEMM MATMUL
sgemm: bin/sgemm.out
bin/sgemm.out : src/matmul.cpp 
	$(CC) $(CFLAGS) $< -o $@ -DSGEMM -DCBLAS 

# SDOT MATMUL
sdot: bin/sdot.out
bin/sdot.out : src/matmul.cpp
	$(CC) $(CFLAGS) $< -o $@ -DSDOT -DCBLAS 



matmul_schedule: bin/ijk.out bin/jki.out bin/kij.out bin/kji.out bin/ikj.out bin/jik.out
	./bin/ijk.out
	./bin/jki.out 
	./bin/kij.out 
	./bin/kji.out 
	./bin/ikj.out 
	./bin/jik.out
# Rule to compile ijk version
bin/ijk.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DIJK_LOOP  

# Rule to compile jki version
bin/jki.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DJKI_LOOP  

# Rule to compile kij version
bin/kij.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DKIJ_LOOP  

# Rule to compile kji version
bin/kji.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DKJI_LOOP  
# Rule to compile kji version
bin/jik.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DJIK_LOOP  
# Rule to compile kji version
bin/ikj.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DIKJ_LOOP  

matmul_optlevel: bin/matmul_no.out bin/matmul_o1.out bin/matmul_o2.out bin/matmul_o3.out bin/matmul_o4.out
	./bin/matmul_no.out 
	./bin/matmul_o1.out 
	./bin/matmul_o2.out 
	./bin/matmul_o3.out 
	./bin/matmul_o4.out
bin/matmul_no.out: src/matmul.cpp
	$(CC) $(CFLAGS)  -o $@ $< -DIJK_LOOP  

bin/matmul_o1.out: src/matmul.cpp
	$(CC) -O1 $(CFLAGS)  -o $@ $< -DIJK_LOOP  

bin/matmul_o2.out: src/matmul.cpp
	$(CC) -O2 $(CFLAGS)  -o $@ $< -DIJK_LOOP  

bin/matmul_o3.out: src/matmul.cpp
	$(CC) -O3 $(CFLAGS)  -o $@ $< -DIJK_LOOP  

bin/matmul_o4.out: src/matmul.cpp
	$(CC) -O4 $(CFLAGS)  -o $@ $< -DIJK_LOOP  

clean:
	rm -f *.out

.PHONY: clean all