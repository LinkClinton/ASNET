#pragma once
namespace ASNET {
	namespace Physics{

		class Vector2 {
		public:
			float x, y;

			static auto Distance(float x1, float y1, float x2, float y2)->float;
		};

		class Vector3 {
		public:
			float x, y, z;

			Vector3 operator+(const Vector3 vector3);

			Vector3 operator-(const Vector3 vector3);

			Vector3 operator*(const float value);
		};

		class Vector4 {
		public:
			float x, y, z, w;

			Vector4 operator+(const Vector4 vector4);

			Vector4 operator-(const Vector4 vector4);

			Vector4 operator*(const float value);
		};

	}
}