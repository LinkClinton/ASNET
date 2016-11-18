#pragma once
namespace ASNET {
	namespace Physics{

		//2维向量
		class Vector2 {
		public:
			float x, y;

			//返回距离
			static auto Distance(float x1, float y1, float x2, float y2)->float; 
		};

		//3维向量
		class Vector3 {
		public:
			float x, y, z;

			//向量加法
			Vector3 operator+(const Vector3 vector3);

			//向量减法
			Vector3 operator-(const Vector3 vector3);

			//向量乘法
			Vector3 operator*(const float value);
		};

		//4维向量
		class Vector4 {
		public:
			float x, y, z, w;

			//向量加法
			Vector4 operator+(const Vector4 vector4);

			//向量减法
			Vector4 operator-(const Vector4 vector4);

			//向量乘法
			Vector4 operator*(const float value);
		};

	}
}