#include "pch.h"
#include <algorithm>
#include "BigInteger/BigInteger.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

long long Rand() {
	if (rand() % 10)
		return 0;
	return (long long)((rand() % 2) * 2 - 1) * (rand() * rand() + rand());
}

void InteractiveTest(long long temps) {
	for (long long i = 0; i < temps; i++) {
		long long a = Rand(), b = Rand();
		BigInteger A(a), B(b);
		int k = rand() % 17;
		switch (k)
		{
		case 0:
			ASSERT_EQ(a + b, (long long)(A + B)) << a << ' ' << b;
			break;
		case 1:
			ASSERT_EQ(a - b, (long long)(A - B));
			break;
		case 2:
			ASSERT_EQ(a * b, (long long)(A * B)) << a << ' ' << b;
			break;
		case 3:
			if (b != 0)
			ASSERT_EQ(a / b, (long long)(A / B)) << a << ' ' << b;
			break;
		case 4:
			if (b != 0)
			ASSERT_EQ(a % b, (long long)(A % B));
			break;
		case 5:
			ASSERT_EQ(-a, (long long)(-A));
			break;
		case 6:
			ASSERT_EQ(a < b, A < B);
			break;
		case 7:
			ASSERT_EQ(a > b, A > B);
			break;
		case 8:
			ASSERT_EQ(a <= b, A <= B) << a << ' ' << b;
			break;
		case 9:
			ASSERT_EQ(a >= b, A >= B);
			break;
		case 10:
			ASSERT_EQ(a != b, A != B);
			break;
		case 11:
			ASSERT_EQ(a == b, A == B);
			break;
		case 12:
			ASSERT_EQ(a += b, A += B);
			ASSERT_EQ(a, A);
			break;
		case 13:
			ASSERT_EQ(a -= b, A -= B);
			ASSERT_EQ(a, A);
			break;
		case 14:
			ASSERT_EQ(a *= b, A *= B);
			ASSERT_EQ(a, A);
			break;
		case 15:
			if (b == 0) break;
			ASSERT_EQ(a /= b, A /= B);
			ASSERT_EQ(a, A);
			break;
		case 16:
			if (b == 0) break;
			ASSERT_EQ(a %= b, A %= B);
			ASSERT_EQ(a, A);
			break;
		default:
			break;
		}
	}
}
TEST(ITest, Test1) {
	InteractiveTest(100);
}
TEST(ITest, Test2) {
	InteractiveTest(10000);
}
TEST(ITest, Test3) {
	InteractiveTest(1000000);
}
TEST(ITest, Test4) {
	InteractiveTest(10000000);
}