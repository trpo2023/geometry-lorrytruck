#include "../thirdparty/ctest.h"

#include "../src/libgeometry/headers/Circle.h"
#include "../src/libgeometry/headers/LineStatus.h"
#include "../src/libgeometry/headers/Vector2.h"

CTEST(ctest, getCirclePosition) {

  Vector2 pos = getCirclePosition("circle(3 0, 1.5)");
  ASSERT_EQUAL(pos.x, 3);
  ASSERT_EQUAL(pos.y, 0);
}

CTEST(ctest, getCircleRadius) {
  float rad = getCircleRadius("circle(3 0, 1.5)");
  ASSERT_EQUAL(rad, 1.5);
}

CTEST(ctest, checkLine) {
  LineStatus s1 = checkLine("circle(3 0, 1.5)");
  LineStatus s2 = checkLine("circle(3 0, 1.5");
  LineStatus s3 = checkLine("circle(3 01.5)");
  LineStatus s4 = checkLine("circWle(3 0, 1.5)");

  ASSERT_TRUE(s1 == LineStatus::fine);
  ASSERT_TRUE(s2 == LineStatus::bracketsException);
  ASSERT_TRUE(s3 == LineStatus::inBracketsIncorrectException);
  ASSERT_TRUE(s4 == LineStatus::nameException);
}