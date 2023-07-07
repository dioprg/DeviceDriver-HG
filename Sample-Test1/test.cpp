#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../DeviceDriver/DeviceDriver.cpp";

using namespace testing;

class MockFlashMemoryDevice : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, ThrowExceptionWhileRead) {
	MockFlashMemoryDevice mock;
	EXPECT_CALL(mock, read(0x00))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(0))
		.WillOnce(Return(1));
	DeviceDriver driver(&mock);
	EXPECT_THROW(driver.read(0x00), ReadFailException);
};

TEST(DeviceDriver, ReadSuccess) {
	MockFlashMemoryDevice mock;
	EXPECT_CALL(mock, read(0x00))
		.Times(5)
		.WillRepeatedly(Return(2));
	DeviceDriver driver(&mock);
	EXPECT_THAT(driver.read(0x00), Eq(2));
};