#include"ASNET.Physics.h"
namespace ASNET {
	namespace Physics {
		
		
		Vector3 ASNET::Physics::Vector3::operator+(const Vector3 vector3)
		{
			Vector3 Out;
			Out.x = x + vector3.x;
			Out.y = y + vector3.y;
			Out.z = z + vector3.z;
			return Out;
		}

		Vector3 ASNET::Physics::Vector3::operator-(const Vector3 vector3)
		{
			Vector3 Out;
			Out.x = x - vector3.x;
			Out.y = y - vector3.y;
			Out.z = z - vector3.z;
			return Out;
		}

		Vector3 ASNET::Physics::Vector3::operator*(const float value)
		{
			Vector3 Out;
			Out.x = x*value;
			Out.y = y*value;
			Out.z = z*value;
			return Out;
		}

		Vector4 ASNET::Physics::Vector4::operator+(const Vector4 vector4)
		{
			Vector4 Out;
			Out.x = x + vector4.x;
			Out.y = y + vector4.y;
			Out.z = z + vector4.z;
			Out.w = w + vector4.w;
			return Out;
		}

		Vector4 ASNET::Physics::Vector4::operator-(const Vector4 vector4)
		{
			Vector4 Out;
			Out.x = x - vector4.x;
			Out.y = y - vector4.y;
			Out.z = z - vector4.z;
			Out.w = w - vector4.w;
			return Out;
		}

		Vector4 ASNET::Physics::Vector4::operator*(const float value)
		{
			Vector4 Out;
			Out.x = x*value;
			Out.y = y*value;
			Out.z = z*value;
			Out.w = w*value;
			return Out;
		}
	}
}