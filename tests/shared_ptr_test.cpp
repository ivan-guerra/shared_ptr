#include "memory/shared_ptr.hpp"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

TEST(SharedPtrTest, ConstructEmptySharedPtr) {
  memory::SharedPtr<int> ptr;
  ASSERT_TRUE(ptr.Empty());
}

TEST(SharedPtrTest, ConstructNonEmptySharedPtr) {
  memory::SharedPtr<int> ptr(new int(1));
  ASSERT_FALSE(ptr.Empty());
}

TEST(SharedPtrTest, DereferenceNonEmptySharedPtr) {
  const int kValue = 1;
  memory::SharedPtr<int> ptr(new int(kValue));
  ASSERT_EQ(*ptr, kValue);
}

TEST(SharedPtrTest, DereferenceEmptyPtrThrowsRuntimeError) {
  memory::SharedPtr<int> ptr;
  ASSERT_THROW(*ptr, std::runtime_error);
}

TEST(SharedPtrTest, RefCountOfNullSharedPtrThrowsRuntimeError) {
  memory::SharedPtr<int> ptr;
  ASSERT_THROW(ptr.RefCount(), std::runtime_error);
}

TEST(SharedPtrTest, IncrementRefCountViaCopyCtor) {
  memory::SharedPtr<int> ptr1(new int(1));
  ASSERT_EQ(ptr1.RefCount(), 1);

  memory::SharedPtr<int> ptr2(ptr1);
  ASSERT_EQ(ptr1.RefCount(), 2);
  ASSERT_EQ(ptr2.RefCount(), 2);
  ASSERT_EQ(*ptr1, *ptr2);
}

TEST(SharedPtrTest, IncrementRefCountViaCopyAssignment) {
  memory::SharedPtr<int> ptr1(new int(1));
  ASSERT_EQ(ptr1.RefCount(), 1);

  memory::SharedPtr<int> ptr2 = ptr1;
  ASSERT_EQ(ptr1.RefCount(), 2);
  ASSERT_EQ(ptr2.RefCount(), 2);
  ASSERT_EQ(*ptr1, *ptr2);
}

TEST(SharedPtrTest, DecrementRefCountViaDescope) {
  memory::SharedPtr<int> ptr1(new int(1));
  ASSERT_EQ(ptr1.RefCount(), 1);

  {
    memory::SharedPtr<int> ptr2 = ptr1;
    ASSERT_EQ(ptr1.RefCount(), 2);
    ASSERT_EQ(ptr2.RefCount(), 2);
    ASSERT_EQ(*ptr1, *ptr2);
  }

  ASSERT_EQ(ptr1.RefCount(), 1);
}

TEST(SharedPtrTest, ResetSharedPtrWithRefCountOfOne) {
  const int kValue1 = 1;
  const int kValue2 = 2;

  memory::SharedPtr<int> ptr(new int(kValue1));
  ASSERT_EQ(*ptr, kValue1);
  ASSERT_EQ(ptr.RefCount(), 1);

  /* The reset triggers ptr1 to release its pointer to kValue1 and acquire the
   * pointer to kValue2. The refcount remains unchanged. */
  ptr.Reset(new int(kValue2));
  ASSERT_EQ(*ptr, kValue2);
  ASSERT_EQ(ptr.RefCount(), 1);
}

TEST(SharedPtrTest, ResetSharedPtrWithRefCountGreaterThanOne) {
  const int kValue1 = 1;
  const int kValue2 = 2;

  memory::SharedPtr<int> ptr1(new int(kValue1));
  ASSERT_EQ(*ptr1, kValue1);
  ASSERT_EQ(ptr1.RefCount(), 1);

  /* Up the refcount. */
  memory::SharedPtr<int> ptr2 = ptr1;
  ASSERT_EQ(*ptr1, *ptr2);
  ASSERT_EQ(ptr1.RefCount(), ptr2.RefCount());

  /* Reset causes ptr1 to hold the new value of kValue2 with a refcount of 1. */
  ptr1.Reset(new int(kValue2));
  ASSERT_EQ(*ptr1, kValue2);
  ASSERT_EQ(ptr1.RefCount(), 1);

  /* The reset of ptr1 reduces the refcount of ptr2 by 1. */
  ASSERT_EQ(ptr2.RefCount(), 1);
}

TEST(SharedPtrTest, MoveConstructSharedPtr) {
  memory::SharedPtr<int> ptr1(new int(1));
  memory::SharedPtr<int> ptr2(std::move(ptr1));

  /* ptr2 now takes over the resources of ptr1. */
  ASSERT_EQ(*ptr2, 1);
  ASSERT_EQ(ptr2.RefCount(), 1);

  /* ptr1 is left empty post move. */
  ASSERT_TRUE(ptr1.Empty());
}
