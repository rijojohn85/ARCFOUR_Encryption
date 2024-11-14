#include "munit/munit.h"
#include "safestr.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// int munit_suite_main(const MunitSuite *suite, void *user_data, int argc,
//                      char *const *argv);
MunitResult test_length(const MunitParameter params[],
                        void *user_data_or_fixture);
MunitResult test_init(const MunitParameter params[],
                      void *user_data_or_fixture);
MunitResult test_concat(const MunitParameter params[],
                        void *user_data_or_fixture);
MunitTest tests[] = {
    {
        "/test_length",               // name of test
        test_length,                  // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_init",                 // name of test
        test_init,                    // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    {
        "/test_concat",               // name of test
        test_concat,                  // test function
        NULL,                         // setup
        NULL,                         // teardown
        MUNIT_TEST_OPTION_NONE, NULL, /* parameters */

    },
    // {
    //     "/test_escape",               // name of test
    //     test_escape,                  // test function
    //     NULL,                         // setup
    //     NULL,                         // teardown
    //     MUNIT_TEST_OPTION_NONE, NULL, /* parameters */
    // },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite suite = {
    "/safestr-tests", /* name of the test suit */
    tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
MunitResult test_length(const MunitParameter params[],
                        void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  size_t len = length("hello!");
  munit_assert_long(len, =, 5);
  return MUNIT_OK;
}
MunitResult test_init(const MunitParameter params[],
                      void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  String *str = init_string("hello, World!");
  munit_assert_string_equal(str->data, "hello, World!");
  munit_assert_long(str->size, =, 13);
  return MUNIT_OK;
}
MunitResult test_concat(const MunitParameter params[],
                        void *user_data_or_fixture) {
  (void)params;
  (void)user_data_or_fixture;
  String *str = init_string("hello");
  concat(str, "world");
  munit_assert_string_equal(str->data, "helloworld");
  munit_assert_long(str->size, =, 10);
  return MUNIT_OK;
}
