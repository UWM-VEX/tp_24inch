#ifndef AUTO_H_
#define AUTO_H_

#define DO_NOTHING 0
#define TEST 1
#define TWO_CAPS 2

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;

#endif