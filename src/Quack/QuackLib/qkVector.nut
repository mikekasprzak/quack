// - ------------------------------------------------------------------------------------------ - //
// 2D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec2 {
	x = 0.0;
	y = 0.0;

	constructor (...) {
		if ( vargv.len() >= 2 ) {
			x = vargv[0];
			y = vargv[1];
		}
		else if ( vargv.len() >= 1 ) {
			if ( typeof vargv[0] == "vec2" ) {
				x = vargv[0].x;
				y = vargv[0].y;
//				this = clone vargv[0];
			}
		}
	}

	function _get(idx) {
		if ( idx == 0 )
			return x;
		else if ( idx == 1 )
			return y;
		throw null;
	}
	
	function _add(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec2( x+vs, y+vs );
		return ::vec2( x+vs.x, y+vs.y );
	}
	function _sub(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec2( x-vs, y-vs );
		return ::vec2( x-vs.x, y-vs.y );
	}
	function _mul(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec2( x*vs, y*vs );
		return ::vec2( x*vs.x, y*vs.y );
	}
	function _div(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec2( x/vs, y/vs );
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
	
	function toarray() {
		return [x,y];
	}

	function dot(vs) {
		return (x*vs.x) + (y*vs.y);
	}
	
	function magnitude() {
		return sqrt((x*x) + (y*y));
	}
	function magnitudesquared() {
		return (x*x) + (y*y);
	}
	function manhattan() {
		return abs(x) + abs(y);
	}
	function sumof() {
		return x+y;
	}
	function productof() {
		return x*y;
	}

	function normal() {
		local Mag = magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		return this / Mag2;
	}
	function normalize() {
		local Mag = magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		this /= Mag2;
		return this;
	}
	function normalizeret() {
		local Mag = magnitude();
		local Mag2 = ::vec2(Mag,Mag);
		this /= Mag2;
		return Mag;
	}
		
	function tangent() {
		return ::vec2( y, -x );
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// 3D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec3 {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	
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
		else if ( vargv.len() >= 1 ) {
			if ( typeof vargv[0] == "vec3" ) {
				x = vargv[0].x;
				y = vargv[0].y;
				z = vargv[0].z;
				
//				this = clone vargv[0];
			}
		}
	}
	
	function _clone(orig) {
		Log("IMA CLONE");
	}
	
	function _get(idx) {
		if ( idx == 0 )
			return x;
		else if ( idx == 1 )
			return y;
		else if ( idx == 2 )
			return z;
		throw null;
	}
	
	function _add(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec3( x+vs, y+vs, z+vs );
		return ::vec3( x+vs.x, y+vs.y, z+vs.z );
	}
	function _sub(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec3( x-vs, y-vs, z-vs );
		return ::vec3( x-vs.x, y-vs.y, z-vs.z );
	}
	function _mul(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec3( x*vs, y*vs, z*vs );
		return ::vec3( x*vs.x, y*vs.y, z*vs.z );
	}
	function _div(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec3( x/vs, y/vs, z/vs );
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

	function toarray() {
		return [x,y,z];
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

	function magnitude() {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	function magnitudesquared() {
		return (x*x) + (y*y) + (z*z);
	}
	function manhattan() {
		return abs(x) + abs(y) + abs(z);
	}
	function sumof() {
		return x+y+z;
	}
	function productof() {
		return x*y*z;
	}

	function normal() {
		local Mag = magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		return this / Mag3;
	}
	function normalize() {
		local Mag = magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		this /= Mag3;
		return this;
	}
	function normalizeret() {
		local Mag = magnitude();
		local Mag3 = ::vec3(Mag,Mag,Mag);
		this /= Mag3;
		return Mag;
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// 4D Vector //
// - ------------------------------------------------------------------------------------------ - //
class vec4 {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;

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
		else if ( vargv.len() >= 1 ) {
			if ( typeof vargv[0] == "vec4" ) {
				x = vargv[0].x;
				y = vargv[0].y;
				z = vargv[0].z;
				w = vargv[0].w;
//				this = clone vargv[0];
			}
		}
	}
	
	function _get(idx) {
		if ( idx == 0 )
			return x;
		else if ( idx == 1 )
			return y;
		else if ( idx == 2 )
			return z;
		else if ( idx == 3 )
			return w;
		throw null;
	}
		
	function _add(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec4( x+vs, y+vs, z+vs, w+vs );
		return ::vec4( x+vs.x, y+vs.y, z+vs.z, w+vs.w );
	}	
	function _sub(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec4( x-vs, y-vs, z-vs, w-vs );
		return ::vec4( x-vs.x, y-vs.y, z-vs.z, w-vs.w );
	}
	function _mul(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec4( x*vs, y*vs, z*vs, w*vs );
		return ::vec4( x*vs.x, y*vs.y, z*vs.z, w*vs.w );
	}
	function _div(vs) {
		if ( typeof vs == "integer" )
			vs = vs.tofloat();
		if ( typeof vs == "float" )
			return ::vec4( x/vs, y/vs, z/vs, w/vs );
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

	function toarray() {
		return [x,y,z,w];
	}
	
	function dot(vs) {
		return (x*vs.x) + (y*vs.y) + (z*vs.z) + (w*vs.w);
	}
	
	function magnitude() {
		return sqrt((x*x) + (y*y) + (z*z) + (w*w));
	}
	function magnitudeSquared() {
		return (x*x) + (y*y) + (z*z) + (w*w);
	}
	function manhattan() {
		return abs(x) + abs(y) + abs(z) + abs(w);
	}
	function sumof() {
		return x+y+z+w;
	}
	function productof() {
		return x*y*z*w;
	}
	
	function normal() {
		local Mag = magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		return this / Mag4;
	}
	function normalize() {
		local Mag = magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		this /= Mag4;
		return this;
	}
	function normalizeRet() {
		local Mag = magnitude();
		local Mag4 = ::vec4(Mag,Mag,Mag,Mag);
		this /= Mag4;
		return Mag;
	}
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// 1D Vector (i.e. float, so we don't use a class, but instead set delegates) //
// - ------------------------------------------------------------------------------------------ - //
{
	// - -------------------------------------------------------------------------------------- - //
	local fd = sqext_getfloatdelegate();
	// - -------------------------------------------------------------------------------------- - //
	fd.magnitude <- function() {
		return abs(this);
	}
	// - -------------------------------------------------------------------------------------- - //
	fd.magnitudesquared <- function() {
		return this*this;
	}
	// - -------------------------------------------------------------------------------------- - //
	fd.manhattan <- function() {
		return abs(this);
	}
	// - -------------------------------------------------------------------------------------- - //
	fd.normal <- function() {
		if ( this > 0.0 )
			return 1.0;
		else if ( this < 0.0 )
			return -1.0;
		else
			return 0.0;
	}
	// - -------------------------------------------------------------------------------------- - //
	fd.normalize <- function() {
		if ( this > 0.0 )
			this = 1.0;
		else if ( this < 0.0 )
			this = -1.0;
		else
			this = 0.0;
		return this;
	}
	// - -------------------------------------------------------------------------------------- - //
	fd.normalizeret <- function() {
		local Ret = this.magnitude();
		if ( this > 0.0 )
			this = 1.0;
		else if ( this < 0.0 )
			this = -1.0;
		else
			this = 0.0;
		return Ret;
	}
	// - -------------------------------------------------------------------------------------- - //
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
