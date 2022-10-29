/*
 * DO NOT EDIT THIS FILE. Generated by checkmk.
 * Edit the original source file "test.check" instead.
 */

#include <check.h>

#line 1 "test.check"
#include "s21_cat.h"

START_TEST(emty_option) {
#line 4
system("cat s21_cat.h > a");
system("./test_cat s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(b_option) {
#line 9
system("cat -b s21_cat.h > a");
system("./test_cat -b s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(E_option) {
#line 14
system("cat -e s21_cat.h > a");
system("./test_cat -E s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(n_option) {
#line 19
system("cat -n s21_cat.h > a");
system("./test_cat -n s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(s_option) {
#line 24
system("cat -s s21_cat.h > a");
system("./test_cat -s s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(T_option) {
#line 29
system("cat -t s21_cat.h > a");
system("./test_cat -T s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bE_option) {
#line 34
system("cat -be s21_cat.h > a");
system("./test_cat -bE s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bn_option) {
#line 39
system("cat -bn s21_cat.h > a");
system("./test_cat -bn s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bs_option) {
#line 44
system("cat -bs s21_cat.h > a");
system("./test_cat -bs s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bT_option) {
#line 49
system("cat -bt s21_cat.h > a");
system("./test_cat -bT s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(En_option) {
#line 54
system("cat -en s21_cat.h > a");
system("./test_cat -En s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(Es_option) {
#line 59
system("cat -es s21_cat.h > a");
system("./test_cat -Es s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(ET_option) {
#line 64
system("cat -et s21_cat.c > a");
system("./test_cat -ET s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(ns_option) {
#line 69
system("cat -ns s21_cat.h > a");
system("./test_cat -ns s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(nT_option) {
#line 74
system("cat -nt s21_cat.c > a");
system("./test_cat -nT s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(sn_option) {
#line 79
system("cat -sn s21_cat.h > a");
system("./test_cat -sn s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(sT_option) {
#line 84
system("cat -st s21_cat.h > a");
system("./test_cat -sT s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEn_option) {
#line 89
system("cat -ben s21_cat.c > a");
system("./test_cat -bEn s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEs_option) {
#line 94
system("cat -bes s21_cat.h > a");
system("./test_cat -bEs s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEt_option) {
#line 99
system("cat -bet s21_cat.h > a");
system("./test_cat -bEt s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bns_option) {
#line 104
system("cat -bns s21_cat.h > a");
system("./test_cat -bns s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bnT_option) {
#line 109
system("cat -bnt s21_cat.c > a");
system("./test_cat -bnT s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(Ens_option) {
#line 114
system("cat -ens s21_cat.h > a");
system("./test_cat -Ens s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(EnT_option) {
#line 119
system("cat -ent s21_cat.h > a");
system("./test_cat -EnT s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(nsT_option) {
#line 124
system("cat -nst s21_cat.h > a");
system("./test_cat -nsT s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEns_option) {
#line 129
system("cat -bens s21_cat.h > a");
system("./test_cat -bEns s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEnT_option) {
#line 134
system("cat -bent s21_cat.c > a");
system("./test_cat -bEnT s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(EnsT_option) {
#line 139
system("cat -enst s21_cat.h > a");
system("./test_cat -EnsT s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(bEnsT_option) {
#line 144
system("cat -benst s21_cat.c > a");
system("./test_cat -bEnsT s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(s_empty_end) {
system("cat -s s21_cat.c  > a");
system("./test_cat -s s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(many_flag_many_files) {
system("cat -benst s21_cat.c s21_cat.h > a");
system("./test_cat -bEnsT s21_cat.c s21_cat.h > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(n_e_option) {
system("cat -n -e s21_cat.c  > a");
system("./test_cat -n -e s21_cat.c > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

START_TEST(not_file) {
system("cat www > a");
system("./test_cat www > b");
ck_assert_int_eq(system("diff a b"), 0);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, emty_option);
    tcase_add_test(tc1_1, b_option);
    tcase_add_test(tc1_1, E_option);
    tcase_add_test(tc1_1, n_option);
    tcase_add_test(tc1_1, s_option);
    tcase_add_test(tc1_1, T_option);
    tcase_add_test(tc1_1, bE_option);
    tcase_add_test(tc1_1, bn_option);
    tcase_add_test(tc1_1, bs_option);
    tcase_add_test(tc1_1, bT_option);
    tcase_add_test(tc1_1, En_option);
    tcase_add_test(tc1_1, Es_option);
    tcase_add_test(tc1_1, ET_option);
    tcase_add_test(tc1_1, ns_option);
    tcase_add_test(tc1_1, nT_option);
    tcase_add_test(tc1_1, sn_option);
    tcase_add_test(tc1_1, sT_option);
    tcase_add_test(tc1_1, bEn_option);
    tcase_add_test(tc1_1, bEs_option);
    tcase_add_test(tc1_1, bEt_option);
    tcase_add_test(tc1_1, bns_option);
    tcase_add_test(tc1_1, bnT_option);
    tcase_add_test(tc1_1, Ens_option);
    tcase_add_test(tc1_1, EnT_option);
    tcase_add_test(tc1_1, nsT_option);
    tcase_add_test(tc1_1, bEns_option);
    tcase_add_test(tc1_1, bEnT_option);
    tcase_add_test(tc1_1, EnsT_option);
    tcase_add_test(tc1_1, bEnsT_option);
    tcase_add_test(tc1_1, s_empty_end);
    tcase_add_test(tc1_1, many_flag_many_files);
    tcase_add_test(tc1_1, n_e_option);
    tcase_add_test(tc1_1, not_file);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
