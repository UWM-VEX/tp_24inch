#ifndef AUTO_H_
#define AUTO_H_

#define DO_NOTHING 0
#define TEST 1
#define MOTION_PROFILE 2
#define TWO_CAPS 3

struct AutonomousInfo {

	int mode;
	int alliance;

}typedef AutonomousInfo;

extern AutonomousInfo autonomousInfoStruct;

#endif