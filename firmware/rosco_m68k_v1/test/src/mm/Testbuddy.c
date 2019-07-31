#include "unity.h"
#include "mm/buddy.h"

void test_alloc_page() {
  TEST_ASSERT_EQUAL(0, alloc_page());
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_alloc_page);
  
  return UNITY_END();
}

