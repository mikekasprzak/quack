// - ------------------------------------------------------------------------------------------ - //
// RTCD - Real Time Collision Detection (Book) //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __RTCD_RTCD_H__
#define __RTCD_RTCD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
// - ------------------------------------------------------------------------------------------ - //
namespace RTCD {
// - ------------------------------------------------------------------------------------------ - //
struct Vec2 {
	typedef Vec2 Vec;
	float x,y;
	
	inline Vec2() { }
	inline Vec2( const float _x, const float _y ) :
		x(_x), y(_y) { }
		
	inline Vec operator + ( const Vec& Vs ) const {
		return Vec(x+Vs.x,y+Vs.y);
	}
	inline Vec operator - ( const Vec& Vs ) const {
		return Vec(x-Vs.x,y-Vs.y);
	}
	inline Vec operator * ( const Vec& Vs ) const {
		return Vec(x*Vs.x,y*Vs.y);
	}
	inline Vec operator / ( const Vec& Vs ) const {
		return Vec(x/Vs.x,y/Vs.y);
	}
};
// - ------------------------------------------------------------------------------------------ - //
struct Vec3 {
	typedef Vec3 Vec;
	float x,y,z;

	inline Vec3() { }
	inline Vec3( const float _x, const float _y, const float _z ) :
		x(_x), y(_y), z(_z) { }
		
	inline Vec operator + ( const Vec& Vs ) const {
		return Vec(x+Vs.x,y+Vs.y,z+Vs.z);
	}
	inline Vec operator - ( const Vec& Vs ) const {
		return Vec(x-Vs.x,y-Vs.y,z-Vs.z);
	}
	inline Vec operator * ( const Vec& Vs ) const {
		return Vec(x*Vs.x,y*Vs.y,z*Vs.z);
	}
	inline Vec operator / ( const Vec& Vs ) const {
		return Vec(x/Vs.x,y/Vs.y,z/Vs.z);
	}
};
typedef Vec3 Point;
// - ------------------------------------------------------------------------------------------ - //
inline float Dot( const Vec2& a, const Vec2& b ) {
	return (a.x*b.x) + (a.y*b.y);
}
// - ------------------------------------------------------------------------------------------ - //
inline float Dot( const Vec3& a, const Vec3& b ) {
	return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}
// - ------------------------------------------------------------------------------------------ - //
inline Vec3 Cross( const Vec3& a, const Vec3& b ) {
	return Vec3(
		a.y*a.z - b.y*a.z,
		b.x*a.z - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}
// - ------------------------------------------------------------------------------------------ - //
inline float MagnitudeSquared( const Vec2& a ) {
	return a.x*a.x + a.y*a.y;
}
// - ------------------------------------------------------------------------------------------ - //
inline float MagnitudeSquared( const Vec3& a ) {
	return a.x*a.x + a.y*a.y + a.z*a.z;
}
// - ------------------------------------------------------------------------------------------ - //
inline float Magnitude( const Vec2& a ) {
	return sqrt( MagnitudeSquared(a) );
}
// - ------------------------------------------------------------------------------------------ - //
inline float Magnitude( const Vec3& a ) {
	return sqrt( MagnitudeSquared(a) );
}
// - ------------------------------------------------------------------------------------------ - //
inline Vec2 Normalize( const Vec2& a ) {
	float Mag = Magnitude( a );
	return Vec2(a.x/Mag, a.y/Mag);
}
// - ------------------------------------------------------------------------------------------ - //
inline Vec3 Normalize( const Vec3& a ) {
	float Mag = Magnitude( a );
	return Vec3(a.x/Mag, a.y/Mag, a.z/Mag);
}
// - ------------------------------------------------------------------------------------------ - //
// Barycentric Coordinates -- Page 47 //
inline void Barycentric( const Point& a, const Point& b, const Point& c, const Point& p, float& u, float& v, float& w ) {
	Vec3 v0 = b-a, v1 = c-a, v2 = p-a;
	float d00 = Dot(v0,v0);
	float d01 = Dot(v0,v1);
	float d11 = Dot(v1,v1);
	float d20 = Dot(v2,v0);
	float d21 = Dot(v2,v1);
	float denom = d00 * d11 - d01 * d01;
	v = (d11 * d20 - d01 * d21) / denom;
	w = (d00 * d21 - d01 * d20) / denom;
	u = 1.0f - v - w;
}
// - ------------------------------------------------------------------------------------------ - //
// Triangle Area 2D -- Page 51 //
// - ------------------------------------------------------------------------------------------ - //
// Test Point in Triangle -- Page 52 //
// - ------------------------------------------------------------------------------------------ - //
// Compute Plane -- Page 55 //
struct Plane {
	Vec3 n;		// Plane Normal. Points (x) on the plane satisfy Dot(n,x) == d
	float d;	// d = dot(n,p), where p is a point on the plane
};

inline Plane ComputePlane( const Point& a, const Point& b, const Point& c ) {
	Plane p;
	p.n = Normalize(Cross(b-a,c-a));
	p.d = Dot(p.n,a);
	return p;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
}; // RTCD //
// - ------------------------------------------------------------------------------------------ - //
#endif // __RTCD_RTCD_H__ //
// - ------------------------------------------------------------------------------------------ - //
