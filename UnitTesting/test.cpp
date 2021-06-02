#include "pch.h"
#include "PWMClass.h"

struct PWMTest : testing::Test {
	PWM<int>* TestPWM;

	PWMTest() {
		TestPWM = new PWM<int>(100, 0);
	}

	virtual ~PWMTest() {
		delete TestPWM;
	}
};

TEST_F(PWMTest, DutySet) {
  EXPECT_EQ(TestPWM-> getDuty(), 100);
  TestPWM->setDuty(125);
  EXPECT_EQ(TestPWM->getDuty(), 125);
}

TEST_F(PWMTest, PWMOutput) {
	int totalSum = 0, totalSwitches = 0, previousValue = 0, outputValue = 0, testCycles = 5000000, dutyCycle = 0;
	int expected = (TestPWM->getDuty()) * testCycles;

	for (dutyCycle = 0; dutyCycle < 255; dutyCycle++) {

		TestPWM->setDuty(dutyCycle);
		expected = dutyCycle * testCycles;
		totalSum = 0;
		totalSwitches = 0;

		for (int i = 0; i < (255 * testCycles); i++) {
			outputValue = (*TestPWM)();
			totalSum += outputValue;
			if (previousValue != outputValue) {
				totalSwitches++;
				previousValue = outputValue;
			}
		}

		if (dutyCycle == 0 || dutyCycle == 255) {
			testCycles = 0;
		}
		
		EXPECT_EQ(totalSum, expected);
		EXPECT_EQ(totalSwitches, testCycles * 2);
	}
}