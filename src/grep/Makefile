CC=gcc
CFLAGS=-Wall -Werror -Wextra
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
NAME = s21_grep

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o $(NAME)

clean:
	rm -rf *.o *.gcno *.gcda *.info *.a $(NAME) a b check_res test_grep a.out

test_grep:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) s21_grep.c -o test_grep

gcov_report: test_grep
	$(CC) s21_grep_test.c $(ALL_FLAGS) 
	./a.out
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o gcov_test