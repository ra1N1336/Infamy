#pragma once

#define square( x ) ( x * x )


	extern inline void SinCos( float radians, float *sine, float *cosine );
	extern void VectorAngles( const Vector& forward, QAngle &angles );
	extern void AngleVectors( const QAngle& angles, Vector *forward );
	extern void AngleVectors( const QAngle &angles, Vector *forward, Vector *right, Vector *up );
	extern void AngleVectors2D(Vector& vecAngles, Vector& vecForward);
	extern void VectorAngles2D(Vector& vecForward, Vector& vecAngles);
	extern void NormalizeAngles2D(Vector& vecAngles);
	extern void CalcAngle(Vector, const Vector, QAngle&);
	extern float GetFov( const QAngle& viewAngle, const QAngle& aimAngle );
	extern float VectorDistance( Vector v1, Vector v2 );
	extern void VectorTransform( Vector& in1, matrix3x4a_t& in2, Vector &out );
	extern float GetDelta( float hspeed, float maxspeed, float airaccelerate );
	extern Vector ExtrapolateTick( Vector p0, Vector v0 );
	extern float DotProduct(const Vector& a, const Vector& b);
	extern inline float RandFloat( float M, float N );

	double inline __declspec ( naked ) __fastcall FASTSQRT( double n )
	{
		_asm fld qword ptr[esp + 4]
		_asm fsqrt
		_asm ret 8
	}

	inline float sseSqrt( float x )
	{
		float root = 0.0f;

		__asm sqrtss xmm0, x
		__asm movss root, xmm0

		return root;
	}
