#-----------------------
# IMPORTANTE: The values of the parameters for exercise?_test have to be conveniently adjusted.
# It is assumed that the name of the source files is exercise1.c, exercise2.c,...,exercise.h
#-----------------------

CC      = gcc
CSTD    = -ansi -pedantic
CFLAGS  = $(CSTD) -Wall -g -O0
EXE     = exercise1 exercise2 exercise3 exercise4 exercise5

# Directorio de salida de tests
TEST_DIR := tests

# Valgrind
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all \
           --track-origins=yes

all : $(EXE)

.PHONY : clean memcheck valgrind_tests dirs \
         exercise1_test exercise2_test exercise3_test exercise4_test exercise5_test \
         exercise1_mid_test exercise2_mid_test exercise3_mid_test exercise4_mid_test exercise5_mid_test \
         exercise1_big_test exercise2_big_test exercise3_big_test exercise4_big_test exercise5_big_test \
         vg_exercise1 vg_exercise2 vg_exercise3 vg_exercise4 vg_exercise5 \
         vg_exercise1_big vg_exercise2_big vg_exercise3_big vg_exercise4_big vg_exercise5_big

dirs:
	@mkdir -p $(TEST_DIR)

clean :
	rm -f *.o core $(EXE) *.log
	rm -rf $(TEST_DIR)

$(EXE) : % : %.o sorting.o times.o permutations.o
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -o $@ $@.o sorting.o times.o permutations.o

permutations.o : permutations.c permutations.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

sorting.o : sorting.c sorting.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

times.o : times.c times.h
	@echo "#---------------------------"
	@echo "# Generating $@ "
	@echo "# Depepends on $^"
	@echo "# Has changed $<"
	$(CC) $(CFLAGS) -c $<

# -------- Tests --------
exercise1_test: dirs exercise1
	@echo Running exercise1
	@./exercise1 -limInf 1 -limSup 5 -numN 10 > $(TEST_DIR)/exercise1_test.txt

exercise2_test: dirs exercise2
	@echo Running exercise2
	@./exercise2 -size 10 -numP 50 > $(TEST_DIR)/exercise2_test.txt

exercise3_test: dirs exercise3
	@echo Running exercise3
	@./exercise3 -size 10 -numP 50 > $(TEST_DIR)/exercise3_test.txt

exercise4_test: dirs exercise4
	@echo Running exercise4
	@./exercise4 -size 20 > $(TEST_DIR)/exercise4_test.txt

exercise5_test: dirs exercise5
	@echo Running exercise5
	@./exercise5 -num_min 10 -num_max 100 -incr 10 -numP 100 -outputFile $(TEST_DIR)/exercise5.txt

#----------mid test---------
exercise1_mid_test: dirs exercise1
	@echo Running exercise1
	@./exercise1 -limInf 1 -limSup 100 -numN 1000000 > $(TEST_DIR)/e1_mid_test.txt

exercise2_mid_test: dirs exercise2
	@echo Running exercise2
	@./exercise2 -size 20 -numP 10000 > $(TEST_DIR)/exercise2_mid_test.txt

exercise3_mid_test: dirs exercise3
	@echo Running exercise3
	@./exercise3 -size 20 -numP 1000 > $(TEST_DIR)/exercise3_mid_test.txt

exercise4_mid_test: dirs exercise4
	@echo Running exercise4
	@./exercise4 -size 500 > $(TEST_DIR)/exercise4_mid_test.txt

exercise5_mid_test: dirs exercise5
	@echo Running exercise5
	@./exercise5 -num_min 1 -num_max 1000 -incr 10 -numP 1000 -outputFile $(TEST_DIR)/exercise5_mid_test.txt

# ---------Big test---------
exercise1_big_test: dirs exercise1
	@echo Running exercise1
	@./exercise1 -limInf 1 -limSup 2000 -numN 100000000 > $(TEST_DIR)/e1_big_test.txt

exercise2_big_test: dirs exercise2
	@echo Running exercise2
	@./exercise2 -size 30 -numP 1000000 > $(TEST_DIR)/exercise2_big_test.txt

exercise3_big_test: dirs exercise3
	@echo Running exercise3
	@./exercise3 -size 30 -numP 100000 > $(TEST_DIR)/exercise3_big_test.txt

exercise4_big_test: dirs exercise4
	@echo Running exercise4
	@./exercise4 -size 100 > $(TEST_DIR)/exercise4_big_test.txt

exercise5_big_test: dirs exercise5
	@echo Running exercise5
	@./exercise5 -num_min 1 -num_max 1000 -incr 10 -numP 100000 -outputFile $(TEST_DIR)/exercise5_big_test.txt

# -------- Valgrind wrappers --------
# Guardamos logs de Valgrind en tests/*.log (stderr) y, si aplica, stdout en tests/*.out
vg_exercise1: dirs exercise1
	$(VALGRIND) ./exercise1 -limInf 1 -limSup 5 -numN 10 > $(TEST_DIR)/vg_exercise1.out 2> $(TEST_DIR)/vg_exercise1.log

vg_exercise2: dirs exercise2
	$(VALGRIND) ./exercise2 -size 1 -numP 5 > $(TEST_DIR)/vg_exercise2.out 2> $(TEST_DIR)/vg_exercise2.log

vg_exercise3: dirs exercise3
	$(VALGRIND) ./exercise3 -size 1 -numP 5 > $(TEST_DIR)/vg_exercise3.out 2> $(TEST_DIR)/vg_exercise3.log

vg_exercise4: dirs exercise4
	$(VALGRIND) ./exercise4 -size 100 > $(TEST_DIR)/vg_exercise4.out 2> $(TEST_DIR)/vg_exercise4.log

vg_exercise5: dirs exercise5
	$(VALGRIND) ./exercise5 -num_min 10 -num_max 10000 -incr 10 -numP 1000 -outputFile $(TEST_DIR)/exercise5.log 2> $(TEST_DIR)/vg_exercise5.log

#-------- Memcheck all --------
memcheck: vg_exercise1 vg_exercise2 vg_exercise3 vg_exercise4 vg_exercise5

#-------- valgrind big tests --------
vg_exercise1_big: dirs exercise1_big_test
	$(VALGRIND) ./exercise1 -limInf 1 -limSup 100 -numN 1000000 > $(TEST_DIR)/vg_exercise1_big.out 2> $(TEST_DIR)/vg_exercise1_big.log

vg_exercise2_big: dirs exercise2_big_test
	$(VALGRIND) ./exercise2 -size 100 -numP 1000 > $(TEST_DIR)/vg_exercise2_big.out 2> $(TEST_DIR)/vg_exercise2_big.log

vg_exercise3_big: dirs exercise3_big_test
	$(VALGRIND) ./exercise3 -size 100 -numP 1000 > $(TEST_DIR)/vg_exercise3_big.out 2> $(TEST_DIR)/vg_exercise3_big.log

vg_exercise4_big: dirs exercise4_big_test
	$(VALGRIND) ./exercise4 -size 100 > $(TEST_DIR)/vg_exercise4_big.out 2> $(TEST_DIR)/vg_exercise4_big.log

vg_exercise5_big: dirs exercise5_big_test
	$(VALGRIND) ./exercise5 -num_min 1 -num_max 10000 -incr 10 -numP 100000 -outputFile $(TEST_DIR)/exercise5_big_test.log 2> $(TEST_DIR)/vg_exercise5_big.log
