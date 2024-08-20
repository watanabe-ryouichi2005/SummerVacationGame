#include "Vector3.h"
#include "Matrix4x4.h" 
#include"AABB.h"
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeRotateXMatrix(float radian);	

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
bool IsCollision(const AABB&aabb1,const AABB&aabb2);
Vector3 Transform(const Vector3& vector,const Matrix4x4& matrix);
// 単項演算子オーバーロード
//Vector3 operator+(const Vector3& v);
//Vector3 operator-(const Vector3& v);
// 代入演算子オーバーロード
//Vector3& operator +=(Vector3& lhs, const Vector3& rhv);
//Vector3& operator -=(Vector3& lhs, const Vector3& rhv);
//Vector3& operator*=(Vector3& v, float s);
//Vector3& operator/=(Vector3& v, float s);
//// 2項演算子オーバーロード
//const Vector3 operator+(const Vector3& v1, const Vector3& v2);
//const Vector3 operator-(const Vector3& v1, const Vector3& v2);
//const Vector3 operator*(const Vector3& v, float s);
//const Vector3 operator*(float s, const Vector3& v);
//const Vector3 operator/(const Vector3& v, float s);
//
// 単項演算子オーバーロード
Vector3 operator+(const Vector3& v);
Vector3 operator-(const Vector3& v);
// 代入演算子オーバーロード
Vector3& operator+=(Vector3& lhs, const Vector3& rhv);
Vector3& operator-=(Vector3& lhs, const Vector3& rhv);
Vector3& operator*=(Vector3& v, float s);
Vector3& operator/=(Vector3& v, float s);
// 2項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator+(Vector3& v, float s);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);




