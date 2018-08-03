#include <check.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "generic_array.h"
#include "custom_array.h"


string_array *array;
uint8_array *byte_array;
size_t counter = 0;

void header_setup(void) {

    counter = 0;
    void *data = NULL;
    array = string_array_new(data);
};

void header_teardown(void) {

    string_array_free(array);
};

static void foreach_cb(void *user, char *entry, size_t index) {

    ck_assert(entry != NULL);
    ck_assert(user == NULL);
    ck_assert(counter++ == index);
};


void custom_header_setup(void) {

    counter = 0;
    void *data = NULL;
    byte_array = uint8_array_new(data);
};

void custom_header_teardown(void) {

    uint8_array_free(byte_array);
};

static void custom_foreach_cb(void *user, uint8_t entry, size_t index) {

    ck_assert(entry != 0);
    ck_assert(user == NULL);
    ck_assert(counter++ == index);
};


START_TEST(test_array_create) {
    string_array *temp;
    void *data = NULL;
    temp = string_array_new(data);
    ck_assert_msg(temp != NULL, "Failed to initialize an string_array");
    string_array_free(temp);
}
END_TEST

START_TEST(test_array_push) {
    string_array_push(array, "hello");
    ck_assert_msg(array->length == 1, "Failed to insert into string_array");
}
END_TEST

START_TEST(test_array_pop) {

    string_array_push(array, "hello");
    ck_assert_msg(strcmp(string_array_pop(array), "hello") == 0, "Failed to pop array");
}
END_TEST

START_TEST(test_array_set) {
    string_array_push(array, "hello");
    ck_assert_msg(string_array_pop(array) != NULL, "Failed set array test as pop is NULL");
    string_array_set(array, 0, "hello");
    ck_assert_msg(string_array_pop(array) == NULL, "Failed set array test as pop is not NULL");
}
END_TEST

START_TEST(test_array_get) {
    string_array_push(array, "hello");
    string_array_push(array, "world");
    ck_assert_msg(strcmp(string_array_get(array, 1), "world") == 0, "Array failed to get in bounds value");
    ck_assert_msg(string_array_get(array, 2) == NULL, "Array got out of bounds value");
}
END_TEST

START_TEST(test_array_foreach) {
    string_array_push(array, "hello");
    string_array_push(array, "world");   
    string_array_foreach(array, foreach_cb);
}
END_TEST



// custom arrays
START_TEST(test_custom_array_create) {
    uint8_array *temp;
    void *data = NULL;
    temp = uint8_array_new(data);
    ck_assert_msg(temp != NULL, "Failed to initialize an uint8_array");
    uint8_array_free(temp);
}
END_TEST


START_TEST(test_custom_array_push) {
    uint8_array_push(byte_array, 1);
    ck_assert_msg(byte_array->length == 1, "Failed to insert into uint8_array");
}
END_TEST


START_TEST(test_custom_array_pop) {

    uint8_array_push(byte_array, 1);
    ck_assert_msg(uint8_array_pop(byte_array) == 1, "Failed to pop array");
}
END_TEST

START_TEST(test_custom_array_set) {
    uint8_array_push(byte_array, 1);
    ck_assert_msg(uint8_array_pop(byte_array) != 0, "Failed set array test as pop is NULL");
    uint8_array_set(byte_array, 0, 1);
    ck_assert_msg(uint8_array_pop(byte_array) == 0, "Failed set array test as pop is not NULL");
}
END_TEST

START_TEST(test_custom_array_get) {
    uint8_array_push(byte_array, 1);
    uint8_array_push(byte_array, 2);
    ck_assert_msg(uint8_array_get(byte_array, 1) != 0, "Array failed to get in bounds value");
    ck_assert_msg(uint8_array_get(byte_array, 2) == 0, "Array got out of bounds value");
}
END_TEST

START_TEST(test_custom_array_foreach) {
    uint8_array_push(byte_array, 1);
    uint8_array_push(byte_array, 2);   
    uint8_array_foreach(byte_array, custom_foreach_cb);
}
END_TEST



Suite* MapSuite(void) {
    
    Suite* a;
    TCase* tc_array;
    TCase* tc_array_custom;

    a = suite_create("Generic Arrays");
    tc_array = tcase_create("Built-in arrays");

    tcase_add_checked_fixture(tc_array, header_setup, header_teardown);
    tcase_add_test(tc_array, test_array_create);
    tcase_add_test(tc_array, test_array_push);
    tcase_add_test(tc_array, test_array_pop);
    tcase_add_test(tc_array, test_array_set);
    tcase_add_test(tc_array, test_array_get);
    tcase_add_test(tc_array, test_array_foreach);
    suite_add_tcase(a, tc_array);

    tc_array_custom = tcase_create("User defined arrays");

    tcase_add_checked_fixture(tc_array_custom, custom_header_setup, custom_header_teardown);
    tcase_add_test(tc_array_custom, test_custom_array_create);
    tcase_add_test(tc_array_custom, test_custom_array_push);
    tcase_add_test(tc_array_custom, test_custom_array_pop);
    tcase_add_test(tc_array_custom, test_custom_array_set);
    tcase_add_test(tc_array_custom, test_custom_array_get);
    tcase_add_test(tc_array_custom, test_custom_array_foreach);

    suite_add_tcase(a, tc_array_custom);

    return a;
};




int main(void) {
    
    int number_failed;
    Suite* s;
    SRunner* sr;

    s = MapSuite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}