#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>

#include "vector3.h"


namespace Microsoft{
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template<>
			static std::wstring ToString<LumixRayTracer::Vector3>(const LumixRayTracer::Vector3 &v) {
				std::wstringstream ss;
				ss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
				return ss.str();
			}

		}
	}
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_math
{		
	TEST_CLASS(Vector3Test)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}
		
		TEST_METHOD(Constructor_empty)
		{
			LumixRayTracer::Vector3 tmp;
			LumixRayTracer::Vector3 tmp2;
			tmp2.x = 0.0f;
			tmp2.y = 0.0f;
			tmp2.z = 0.0f;
			Assert::AreEqual(tmp2, tmp);
		}

		TEST_METHOD(Constructor_values)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2;
			tmp2.x = 0.0f;
			tmp2.y = 1.0f;
			tmp2.z = 2.0f;
			Assert::AreEqual(tmp2, tmp);
		}

		TEST_METHOD(Constructor_copy)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(tmp);
			LumixRayTracer::Vector3 tmp3;
			tmp2.x = 0.0f;
			tmp2.y = 1.0f;
			tmp2.z = 2.0f;
			Assert::AreEqual(tmp3, tmp2);
		}

		TEST_METHOD(operator_mult_assign)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			tmp *= 5.0f;
			LumixRayTracer::Vector3 tmp2(0.0f, 5.0f, 10.0f);
			Assert::AreEqual(tmp2, tmp);
		}

		TEST_METHOD(operator_mult)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2 = tmp * 5.0f;
			LumixRayTracer::Vector3 tmp3;
			tmp2.x = 0.0f;
			tmp2.y = 5.0f;
			tmp2.z = 10.0f;
			Assert::AreEqual(tmp3, tmp2);
		}

		TEST_METHOD(operator_mult2)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2 = 5.0f * tmp;
			LumixRayTracer::Vector3 tmp3;
			tmp2.x = 0.0f;
			tmp2.y = 5.0f;
			tmp2.z = 10.0f;
			Assert::AreEqual(tmp3, tmp2);
		}

		TEST_METHOD(dot)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(1.0f, 6.0f, -3.0f);
			float tmp3 = LumixRayTracer::Vector3::Dot(tmp, tmp2);
			Assert::AreEqual(0.0f, tmp3);
		}

		TEST_METHOD(cross)
		{
			LumixRayTracer::Vector3 tmp(0.0f, 1.0f, 2.0f);
			LumixRayTracer::Vector3 tmp2(1.0f, 6.0f, -3.0f);
			LumixRayTracer::Vector3 tmp3 = LumixRayTracer::Vector3::Cross(tmp, tmp2);
			LumixRayTracer::Vector3 tmp4(-15.0f, 2.0f, -1.0f);
			Assert::AreEqual(tmp4, tmp3);
		}

	};
}