// - ------------------------------------------------------------------------------------------ - //
// 2D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec2 {
	constructor (...) {
		if ( vargv.len() >= 2 ) {
			x = vargv[0];
			y = vargv[1];
		}	
	}
	
	function _add(vs) {
		return ::vec2( x+vs.x, y+vs.y );
	}
	function _sub(vs) {
		return ::vec2( x-vs.x, y-vs.y );
	}
	function _mul(vs) {
		return ::vec2( x*vs.x, y*vs.y );
	}
	function _div(vs) {
		return ::vec2( x/vs.x, y/vs.y );
	}
	
	function _unm() {
		return ::vec2( -x, -y );
	}
	
	function _typeof() {
		return "vec2";
	}

	function _tostring() {
		return "(" + x + "," + y + ")";
	}

	function dot(vs) {
		return (x*vs.x) + (y*vs.y);
	}
	
	function Magnitude() {
		return sqrt((x*x) + (y*y));
	}
	function MagnitudeSquared() {
		return (x*x) + (y*y);
	}
	function Manhattan() {
		return abs(x) + abs(y);
	}
	function SumOf() {
		return x+y;
	}
	function ProductOf() {
		return x*y;
	}

	function Normal() {
		local Mag = Magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		return this / Mag2;
	}
	function Normalize() {
		local Mag = Magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		this /= Mag2;
		return this;
	}
	function NormalizeRet() {
		local Mag = Magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		this /= Mag2;
		return Mag;
	}
		
	function Tangent() {
		return ::vec2( y, -x );
	}
	
	x = 0.0;
	y = 0.0;	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// 3D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec3 {
	constructor (...) {
		if ( vargv.len() >= 3 ) {
			x = vargv[0];
			y = vargv[1];
			z = vargv[2];
		}	
		else if ( vargv.len() >= 2 ) {
			x = vargv[0];
			y = vargv[1];
			z = 0.0;
		}	
	}
	
	function _add(vs) {
		return ::vec3( x+vs.x, y+vs.y, z+vs.z );
	}
	function _sub(vs) {
		return ::vec3( x-vs.x, y-vs.y, z-vs.z );
	}
	function _mul(vs) {
		return ::vec3( x*vs.x, y*vs.y, z*vs.z );
	}
	function _div(vs) {
		return ::vec3( x/vs.x, y/vs.y, z/vs.z );
	}
	
	function _unm() {
		return ::vec3( -x, -y, -z );
	}

	function _typeof() {
		return "vec3";
	}

	function _tostring() {
		return "(" + x + "," + y + "," + z + ")";
	}

	function dot(vs) {
		return (x*vs.x) + (y*vs.y) + (z*vs.z);
	}
	function cross(vs) {
		return ::vec3( 
			(y * vs.z) - (z * vs.y),
			(z * vs.x) - (x * vs.z),
			(x * vs.y) - (y * vs.x)
			);
	}

	function Magnitude() {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	function MagnitudeSquared() {
		return (x*x) + (y*y) + (z*z);
	}
	function Manhattan() {
		return abs(x) + abs(y) + abs(z);
	}
	function SumOf() {
		return x+y+z;
	}
	function ProductOf() {
		return x*y*z;
	}

	function Normal() {
		local Mag = Magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		return this / Mag3;
	}
	function Normalize() {
		local Mag = Magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		this /= Mag3;
		return this;
	}
	function NormalizeRet() {
		local Mag = Magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		this /= Mag3;
		return Mag;
	}
			
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// 4D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec4 {
	constructor (...) {
		if ( vargv.len() >= 4 ) {
			x = vargv[0];
			y = vargv[1];
			z = vargv[2];
			w = vargv[3];
		}	
		if ( vargv.len() >= 3 ) {
			x = vargv[0];
			y = vargv[1];
			z = vargv[2];
			w = 0.0;
		}	
		else if ( vargv.len() >= 2 ) {
			x = vargv[0];
			y = vargv[1];
			z = 0.0;
			w = 0.0;
		}	
	}
	
	function _add(vs) {
		return ::vec4( x+vs.x, y+vs.y, z+vs.z, w+vs.w );
	}	
	function _sub(vs) {
		return ::vec4( x-vs.x, y-vs.y, z-vs.z, w-vs.w );
	}
	function _mul(vs) {
		return ::vec4( x*vs.x, y*vs.y, z*vs.z, w*vs.w );
	}
	function _div(vs) {
		return ::vec4( x/vs.x, y/vs.y, z/vs.z, w/vs.w );
	}

	function _unm() {
		return ::vec4( -x, -y, -z, -w );
	}

	function _typeof() {
		return "vec4";
	}
	
	function _tostring() {
		return "(" + x + "," + y + "," + z + "," + w + ")";
	}
	
	function dot(vs) {
		return (x*vs.x) + (y*vs.y) + (z*vs.z) + (w*vs.w);
	}
	
	function Magnitude() {
		return sqrt((x*x) + (y*y) + (z*z) + (w*w));
	}
	function MagnitudeSquared() {
		return (x*x) + (y*y) + (z*z) + (w*w);
	}
	function Manhattan() {
		return abs(x) + abs(y) + abs(z) + abs(w);
	}
	function SumOf() {
		return x+y+z+w;
	}
	function ProductOf() {
		return x*y*z*w;
	}
	
	function Normal() {
		local Mag = Magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		return this / Mag4;
	}
	function Normalize() {
		local Mag = Magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		this /= Mag4;
		return this;
	}
	function NormalizeRet() {
		local Mag = Magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		this /= Mag4;
		return Mag;
	}
	
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Dot Product - Call the internal Dot Product function //
// - ------------------------------------------------------------------------------------------ - //
function dot(a,b) {
	return a.dot(b);
}
// - ------------------------------------------------------------------------------------------ - //
// Cross Product - Call the internal Cross Product function //
// - ------------------------------------------------------------------------------------------ - //
function cross(a,b) {
	return a.cross(b);
}
// - ------------------------------------------------------------------------------------------ - //
