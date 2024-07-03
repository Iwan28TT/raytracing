#include "pch.h"
#include <sphere.h>
TEST(SphereTest, Intersection) {
	sphere s = sphere(1, { 0,0,3 }); bardrix::ray ray({ 0,0,0 }, { 0,0,1 }, 5);
	auto intersection = s.intersection(ray);
	ASSERT_TRUE(intersection.has_value());
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);

}