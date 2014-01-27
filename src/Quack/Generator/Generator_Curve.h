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
	
	typename IN::Type::Type OldRay = IN::Type::Type::Zero;

	for ( st idx = 0; idx < In.Size()-1; idx++ ) {
		typename IN::Type::Type Ray = In[idx+1].Pos - In[idx+0].Pos;
		Real Mag = Ray.NormalizeRet();
		Ray = Ray.Tangent();
		
		Real Radius2 = Radius - Real::Half;

//		Out.PushBack().Pos = In[idx+1].Pos - (Ray*Radius2);
//		Out.PushBack().Pos = In[idx+1].Pos + (Ray*Radius2);
//		Out.PushBack().Pos = In[idx+0].Pos + (Ray*Radius);
//
//		Out.PushBack().Pos = In[idx+0].Pos + (Ray*Radius);
//		Out.PushBack().Pos = In[idx+0].Pos - (Ray*Radius);
//		Out.PushBack().Pos = In[idx+1].Pos - (Ray*Radius2);

		Real Skew(2);
		Real UnSkew(0.75);

		Out.PushBack().Pos = In[idx+1].Pos - (Ray*(Radius2*Skew));
		Out.PushBack().Pos = In[idx+1].Pos + (Ray*(Radius2));
		Out.PushBack().Pos = In[idx+0].Pos + (OldRay*(Radius*UnSkew));

		Out.PushBack().Pos = In[idx+0].Pos + (OldRay*(Radius*Skew));
		Out.PushBack().Pos = In[idx+0].Pos - (OldRay*(Radius*Skew));
		Out.PushBack().Pos = In[idx+1].Pos - (Ray*(Radius2));

/*
		Out.PushBack().Pos = In[idx+1].Pos - (Ray*(Radius2*Skew));
		Out.PushBack().Pos = In[idx+1].Pos + (Ray*(Radius2));
		Out.PushBack().Pos = In[idx+0].Pos + (Ray*(Radius*UnSkew));

		Out.PushBack().Pos = In[idx+0].Pos + (Ray*(Radius*Skew));
		Out.PushBack().Pos = In[idx+0].Pos - (Ray*(Radius*Skew));
		Out.PushBack().Pos = In[idx+1].Pos - (Ray*(Radius2));
*/

/*		
		// Fill Gap //
		Real RaySide = dot(Ray.Tangent(),OldRay);
		if ( RaySide < Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos - (Ray*Radius);
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos - (OldRay*Radius);
		}
		else if ( RaySide > Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos + (Ray*Radius);
			Out.PushBack().Pos = In[idx+0].Pos + (OldRay*Radius);
		}
		else {
			// Do nothing in Zero case (i.e. First time, axis aligned) //
		}
*/				
		OldRay = Ray;
		Radius = Radius2;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GENERATOR_GENERATOR_CURVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
