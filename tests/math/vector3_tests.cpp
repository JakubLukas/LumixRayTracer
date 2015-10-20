#include "stdafx.h"
#include "CppUnitTest.h"

#include "vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_math
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Constructor_empty)
		{
			LumixRayTracer::Vector3 tmp();
			//tmp.x;
			Assert::Fail();
		}

		TEST_METHOD(Constructor_values)
		{
			LumixRayTracer::Vector3(0.0f, 1.0f, 2.0f);
			Assert::Fail();
		}

		TEST_METHOD(Constructor_copy)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(tmp);
			Assert::Fail();
		}

		TEST_METHOD(operator_mult_assign)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			tmp *= 5.0f;
			Assert::Fail();
		}

		TEST_METHOD(operator_mult)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			tmp * 5.0f;
			Assert::Fail();
		}

		TEST_METHOD(operator_mult2)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			5.0f * tmp;
			Assert::Fail();
		}

		TEST_METHOD(operator_dot)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(1.0f, 6.0f, -3.0f);
			LumixRayTracer::Vector3::Dot(tmp, tmp2);
			Assert::Fail();
		}

		TEST_METHOD(operator_cross)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(1.0f, 6.0f, -3.0f);
			LumixRayTracer::Vector3::Cross(tmp, tmp2);
			Assert::Fail();
		}

	};
}