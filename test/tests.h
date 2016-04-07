#ifndef __TESTS_H__
#define __TESTS_H__

#include "../globalInclude.h"

class Tests {
public:
  static bool intersectionTestOne();
  static bool intersectionTestTwo();
  static bool intersectionTestThree();
  static bool pointBetweenTest();
  static bool vertSortTest();
  static bool vertReverseTest();
  static bool edgeIsOnTest();
  static bool detectIfConvexTest();
  static bool adjacentsTest();
  static bool convexSplitTest();
  static bool concaveSplitTest();
  static bool trimeshCreationTest();
  static bool angleTests();
};

#endif
