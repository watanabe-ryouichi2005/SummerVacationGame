

#include <cmath>
#include "MyMath.h"
#include <assert.h>
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = Multiply(
	    Multiply(MakeRotateXMatrix(rotate.x), MakeRotateYMatrix(rotate.y)),
	    MakeRotateZMatrix(rotate.z));

	result.m[0][0] *= scale.x;
	result.m[0][1] *= scale.x;
	result.m[0][2] *= scale.x;

	result.m[1][0] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[1][2] *= scale.y;

	result.m[2][0] *= scale.z;
	result.m[2][1] *= scale.z;
	result.m[2][2] *= scale.z;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

	Matrix4x4 MakeRotateXMatrix(float radian) {
		float cosTheta = std::cos(radian);
		float sinTheta = std::sin(radian);
		return {1.0f, 0.0f, 0.0f,0.0f,0.0f,cosTheta,sinTheta,0.0f,
			0.0f, -sinTheta, cosTheta, 0.0f, 0.0f, 0.0f,0.0f,1.0f};
	}

	Matrix4x4 MakeRotateYMatrix(float radian) {
		float cosTheta = std::cos(radian);
		float sinTheta = std::sin(radian);
		return {cosTheta, 0.0f, -sinTheta, 0.0f, 0.0f,1.0f, 0.0f, 0.0f, sinTheta,0.0f, cosTheta,  0.0f, 0.0f,0.0f, 0.0f, 1.0f};

	}

	Matrix4x4 MakeRotateZMatrix(float radian){

        // X軸とY軸の回転行列を作る関数を参考に考えてみよう
	    float cosTheta = std::cos(radian);
	    float sinTheta = std::sin(radian);
		
        return {cosTheta, -sinTheta, 0.0f, 0.0f, sinTheta, cosTheta, 0.0f, 0.0f,
        0.0f, 0.0f, 0.1f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    }


	

	Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

		Matrix4x4 result;

		result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] +
		                 m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
		result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] +
		                 m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
		result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] +
		                 m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
		result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] +
		                 m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
		result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] +
		                 m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
		result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] +
		                 m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
		result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] +
		                 m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
		result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] +
		                 m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
		result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] +
		                 m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
		result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] +
		                 m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
		result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] +
		                 m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
		result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] +
		                 m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
		result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] +
		                 m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
		result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] +
		                 m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
		result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] +
		                 m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
		result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] +
		                 m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

		return result;
	}
	bool IsCollision(const AABB & aabb1, const AABB & aabb2)
	{
		return (aabb1.min.x<=aabb2.max.x&&aabb1.max.x>=aabb2.min.x)&&
			(aabb1.min.y<=aabb2.max.y&&aabb1.max.y>=aabb2.min.y)&&
			(aabb1.min.z<=aabb2.max.z&&aabb1.max.z>=aabb2.min.z);




	}
	// 単項演算子オーバーロード
Vector3 operator+(const Vector3& v) { return v; }
Vector3 operator-(const Vector3& v) { return Vector3(-v.x, -v.y, -v.z); }
Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;
	return lhv;
}
Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;
	return lhv;
}
Vector3& operator*=(Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}
Vector3& operator/=(Vector3& v, float s) {
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return v;
}
// 2項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 operator*(float s, const Vector3& v) { return v * s; }

const Vector3 operator/(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp /= s;
}

const Vector3 operator+(Vector3& v, float s) {
	v.x += s;
	v.y += s;
	v.z += s;
	return v;
}


	// 単項演算子オーバーロード
//Vector3 operator+(const Vector3& v) { 
//	return v;
//}
//Vector3 operator-(const Vector3& v) {
//	return Vector3(-v.x, -v.y, -v.z); 
//}
//Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
//	lhv.x += rhv.x;
//	lhv.y += rhv.y;
//	lhv.z += rhv.z;
//	return lhv;
//}
//Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
//	lhv.x -= rhv.x;
//	lhv.y -= rhv.y;
//	lhv.z -= rhv.z;
//	return lhv;
//}
//Vector3& operator*=(Vector3& v, float s) {
//	v.x *= s;
//	v.y *= s;
//	v.z *= s;
//	return v;
//}
//Vector3& operator/=(Vector3& v, float s) {
//	v.x /= s;
//	v.y /= s;
//	v.z /= s;
//	return v;
//}
//// 2項演算子オーバーロード
//const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
//	Vector3 temp(v1);
//	return temp += v2;
//}
//const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
//	Vector3 temp(v1);
//	return temp -= v2;
//}
//const Vector3 operator*(const Vector3& v, float s) {
//	Vector3 temp(v);
//	return temp *= s;
//}
//const Vector3 operator*(float s, const Vector3& v) { return v * s; }
//const Vector3 operator/(const Vector3& v, float s) {
//	Vector3 temp(v);
//	return temp /= s;
//}
Matrix4x4 MakeIdentityMatrix()
{
	static const Matrix4x4 result{1.0,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f};
	return result;

}
Vector3 Transform(const Vector3 & vector, const Matrix4x4 & matrix)
{
//w=1がデカルト座標であるので(x,y,1)のベクトルとしてmatrixとの積をとる
Vector3 result;
result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f*matrix.m[3][0];
result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f*matrix.m[3][1];
result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f*matrix.m[3][2];

float w  = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f*matrix.m[3][3];
assert(w!=0.0f);
result.x /=w;
result.y/=w;
result.z/=w;
return result ;
}
