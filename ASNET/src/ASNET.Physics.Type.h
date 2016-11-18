#pragma once
namespace ASNET {
	namespace Physics{

		//2ά����
		class Vector2 {
		public:
			float x, y;

			//���ؾ���
			static auto Distance(float x1, float y1, float x2, float y2)->float; 
		};

		//3ά����
		class Vector3 {
		public:
			float x, y, z;

			//�����ӷ�
			Vector3 operator+(const Vector3 vector3);

			//��������
			Vector3 operator-(const Vector3 vector3);

			//�����˷�
			Vector3 operator*(const float value);
		};

		//4ά����
		class Vector4 {
		public:
			float x, y, z, w;

			//�����ӷ�
			Vector4 operator+(const Vector4 vector4);

			//��������
			Vector4 operator-(const Vector4 vector4);

			//�����˷�
			Vector4 operator*(const float value);
		};

	}
}