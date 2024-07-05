#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../packages/gmock.1.11.0/lib/native/src/gmock/src/gmock_main.cc"
#include "../Project/DeviceDriver.cpp"
#include "../Project/Application.cpp"
#include "MockFlashMemoryDevice.hpp"

#include <iostream>

using namespace std;
using namespace testing;

class DriverFixuter : public Test {
public:
	MockFlashMemoryDevice mockDevice;
	DeviceDriver driver;
	Application app;

protected:
	void SetUp() override {
		driver.injectDevice(&mockDevice);
		app.injectDriver(&driver);
	}
};

TEST_F(DriverFixuter, DEVICE_READ_5_COUNT) {
	EXPECT_CALL(mockDevice, read(_))
		.Times(5);

	driver.read(0x00);
}

TEST_F(DriverFixuter, DEVICE_READ_FAIL) {
	EXPECT_CALL(mockDevice, read(_))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(2));

	EXPECT_THROW(driver.read(0x00), ReadFailException);
}

TEST_F(DriverFixuter, DEVICE_WRITE_FAIL) {
	EXPECT_CALL(mockDevice, read(_))
		.Times(5)
		.WillRepeatedly(Return(0x0F));
	EXPECT_CALL(mockDevice, write(_, _))
		.Times(0);
	
	EXPECT_THROW(driver.write(0x00, 0x10), WriteFailException);
}

TEST_F(DriverFixuter, DEVICE_WRITE_SUCCESS) {
	EXPECT_CALL(mockDevice, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mockDevice, write(_, _));

	EXPECT_NO_THROW(driver.write(0x00, 0x11));
}

TEST_F(DriverFixuter, APP_READ_AND_PRINT) {
	ostringstream oss;
	auto oldCoutStreamBuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());

	EXPECT_CALL(mockDevice, read(_))
		.WillRepeatedly(Return(0xFF));

	app.readAndPrint(0x01, 0x05);

	cout.rdbuf(oldCoutStreamBuf);
	
	EXPECT_EQ(oss.str(), string{ "255 255 255 255 255 \n" });
}



//
//class TestFixture : public testing::Test {
//public:
//protected:
//	void SetUp() override {
//		// before process
//	}
//
//	void TearDown() override {
//		// after process
//	}
//};
//
//TEST_F(TestFixture, TestName) {
//	EXPECT_EQ(1, 1);
//	EXPECT_TRUE(true);
//	EXPECT_THAT(nullptr, testing::IsNull());
//}
//
//#define interface struct
//interface ITest {
//	virtual int value() = 0;
//	virtual int sum(int a, int b) = 0;
//};
//
//class MockTest : public ITest {
//public:
//	MOCK_METHOD(int, value, (), (override));
//	MOCK_METHOD(int, sum, (int a, int b), (override));
//	MOCK_METHOD(int, divide, (int a, int b), ());
//};
//
//TEST(MockTest, TestName) {
//	MockTest test;
//	EXPECT_CALL(test, value)
//		.WillRepeatedly(testing::Return(10));
//
//	EXPECT_CALL(test, sum(1, 2))
//		.WillRepeatedly(testing::Return(3));
//
//
//	EXPECT_EQ(test.value(), 10);
//	EXPECT_EQ(test.sum(1, 2), 3);
//}
//
//
//class MockTestFixture : public testing::Test {
//public:
//	MockTest test;
//
//protected:
//	void SetUp() override {
//		EXPECT_CALL(test, value)
//			.Times(3)
//			.WillOnce(testing::Return(1))
//			.WillOnce(testing::Return(2))
//			.WillRepeatedly(testing::Return(10));
//
//		EXPECT_CALL(test, sum(testing::_, testing::_))
//			.WillRepeatedly(testing::Return(10));
//
//		EXPECT_CALL(test, divide(testing::_, 0))
//			.WillRepeatedly(testing::Throw(std::invalid_argument("divide zero!")));
//
//		EXPECT_CALL(test, divide(1, 1))
//			.WillOnce(testing::Return(3))
//			.WillOnce(testing::Return(2))
//			.WillRepeatedly(testing::Return(1));
//	}
//
//	void TearDown() override {
//
//	}
//};
//
//TEST_F(MockTestFixture, TestName) {
//	EXPECT_EQ(test.value(), 1);
//	EXPECT_EQ(test.value(), 2);
//	EXPECT_EQ(test.value(), 10);
//
//	EXPECT_EQ(test.sum(3, 10), 10);
//
//	EXPECT_THROW(test.divide(1, 0), std::invalid_argument);
//	try {
//		test.divide(1, 0);
//		FAIL();
//	}
//	catch (std::exception& ex) {
//		EXPECT_THAT(ex.what(), testing::HasSubstr("zero"));
//		EXPECT_THAT(ex.what(), testing::StartsWith("divide"));
//	}
//
//	EXPECT_NO_THROW(test.divide(1, 1));
//	EXPECT_EQ(test.divide(1, 1), 2);
//	EXPECT_EQ(test.divide(1, 1), 1);
//	EXPECT_EQ(test.divide(1, 1), 1);
//}