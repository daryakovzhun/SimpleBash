CC=gcc
CFLAGS=-Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
NAME = s21_cat

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o $(NAME)

clean:
	rm -rf *.o *.gcno *.gcda *.info *.a $(NAME) a b check_res test_cat a.out

test_cat:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) s21_cat.c -o test_cat

gcov_report: test_cat
	$(CC) s21_cat_test.c $(ALL_FLAGS) 
	./a.out
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o gcov_test
