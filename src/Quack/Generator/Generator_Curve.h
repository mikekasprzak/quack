// - ------------------------------------------------------------------------------------------ - //
#ifndef __GENERATOR_GENERATOR_CURVE_H__
#define __GENERATOR_GENERATOR_CURVE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Vert/Vert.h>
// - ------------------------------------------------------------------------------------------ - //
template <typename IN, typename OUT>
inline void GenCurve( const IN& In, OUT& Out ) {
	Out.Reserve( In.Size() * 6 );
	Real Radius = 8;
	for ( st idx = 0; idx < In.Size()-1; idx++ ) {
		typename IN::Type::Type Ray = In[idx+1].Pos - In[idx+0].Pos;
		Real Mag = Ray.NormalizeRet();
		Ray = Ray.Tangent();
		
		Real Radius2 = Radius - Real::One;

		Out.PushBack().Pos = In[idx+1].Pos - (Ray*Radius2);
		Out.PushBack().Pos = In[idx+1].Pos + (Ray*Radius2);
		Out.PushBack().Pos = In[idx+0].Pos + (Ray*Radius);

		Out.PushBack().Pos = In[idx+0].Pos + (Ray*Radius);
		Out.PushBack().Pos = In[idx+0].Pos - (Ray*Radius);
		Out.PushBack().Pos = In[idx+1].Pos - (Ray*Radius2);
		
		Radius = Radius2;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GENERATOR_GENERATOR_CURVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
