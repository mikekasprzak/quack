// - ------------------------------------------------------------------------------------------ - //
#ifndef __GENERATOR_GENERATOR_CURVE_H__
#define __GENERATOR_GENERATOR_CURVE_H__
// - ------------------------------------------------------------------------------------------ - //
//#include <Array/Array.h>
// - ------------------------------------------------------------------------------------------ - //
template <typename OUT, typename IN>
inline void Gen_Curve( OUT& Out, const IN& In, const Real RadiusA, const Real RadiusB ) {
	typedef typename IN::Type InType;
	typedef typename IN::Type::Type VecType;

	Out.Reserve( In.Size() * (6+3) + (3*2) ); // Quad+Gaps, Caps //
	Out.Clear();
	
	st Size = In.Size();
	Real InvSize = Real::One / Real(In.Size()-1);
	Real RadiusDiff = RadiusB - RadiusA;
	VecType OldRayTan = VecType::Zero;

	for ( st idx = 1; idx < Size; idx++ ) {
		const InType& A = In[idx-1];
		const InType& B = In[idx];
		
		VecType Ray = B.Pos - A.Pos;
		Ray.Normalize();
		VecType RayTan = Ray.Tangent();

		Real Radius1 = RadiusA + (RadiusDiff * (Real(idx-1) * InvSize));
		Real Radius2 = RadiusA + (RadiusDiff * (Real(idx) * InvSize));

		Out.PushBack().Pos = A.Pos + (RayTan*Radius1);
		Out.PushBack().Pos = A.Pos - (RayTan*Radius1);
		Out.PushBack().Pos = B.Pos - (RayTan*Radius2);
                                  
		Out.PushBack().Pos = B.Pos - (RayTan*Radius2);
		Out.PushBack().Pos = B.Pos + (RayTan*Radius2);
		Out.PushBack().Pos = A.Pos + (RayTan*Radius1);

		// Fill Gap //
		Real RaySide = dot(RayTan.Tangent(),OldRayTan);
		if ( RaySide < Real::Zero ) {
			Out.PushBack().Pos = A.Pos - (RayTan*Radius1);
			Out.PushBack().Pos = A.Pos;
			Out.PushBack().Pos = A.Pos - (OldRayTan*Radius1);
		}
		else if ( RaySide > Real::Zero ) {
			Out.PushBack().Pos = A.Pos;
			Out.PushBack().Pos = A.Pos + (RayTan*Radius1);
			Out.PushBack().Pos = A.Pos + (OldRayTan*Radius1);
		}
		else {
			// Do nothing in Zero case (i.e. First time, axis aligned) //
		}
		
		// Add Front Cap //
		if ( idx == 1 ) {
			Out.PushBack().Pos = A.Pos - (RayTan*Radius1);
			Out.PushBack().Pos = A.Pos + (RayTan*Radius1);
			Out.PushBack().Pos = A.Pos - (Ray*Radius1);
		}

		if ( idx == Size-1 ) {
			Out.PushBack().Pos = B.Pos - (RayTan*Radius2);
			Out.PushBack().Pos = B.Pos + (Ray*Radius2);
			Out.PushBack().Pos = B.Pos + (RayTan*Radius2);
		}
				
		OldRayTan = RayTan;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template <typename IN, typename OUT>
inline void Gen_SpecialCurve( const IN& In, OUT& Out ) {
	Out.Reserve( In.Size() * 6 );
	Real Radius = 10;
	
	GelColor Color1;
	GelColor Color2;
	
	typename IN::Type::Type OldRayTan = IN::Type::Type::Zero;

	for ( st idx = 0; idx < In.Size()-1; idx++ ) {
		Color1 = GEL_RGB(30+(idx*6),80-(idx*3),170-(idx*2));
		Color2 = GEL_RGB(70+(idx*3),60-(idx*3),140-(idx*2));

		typename IN::Type::Type Ray = In[idx+1].Pos - In[idx+0].Pos;
		Real Mag = Ray.NormalizeRet();
		typename IN::Type::Type RayTan = Ray.Tangent();
		
		Real Radius2 = Radius - Real(0.75);

//		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*Radius2);
//		Out.PushBack().Pos = In[idx+1].Pos + (RayTan*Radius2);
//		Out.PushBack().Pos = In[idx+0].Pos + (RayTan*Radius);
//
//		Out.PushBack().Pos = In[idx+0].Pos + (RayTan*Radius);
//		Out.PushBack().Pos = In[idx+0].Pos - (RayTan*Radius);
//		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*Radius2);

		Real Skew(2);
		Real UnSkew(0.75);

		Out.PushBack().Pos = In[idx+0].Pos + (OldRayTan*(Radius*Skew));
		Out.Back().Color = Color1;
		Out.PushBack().Pos = In[idx+0].Pos - (OldRayTan*(Radius*Skew));
		Out.Back().Color = Color1;
		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*(Radius2));
		Out.Back().Color = Color1;

		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*(Radius2*Skew));
		Out.Back().Color = Color1;
		Out.PushBack().Pos = In[idx+1].Pos + (RayTan*(Radius2));
		Out.Back().Color = Color2;
		Out.PushBack().Pos = In[idx+0].Pos + (OldRayTan*(Radius*UnSkew)) + (Ray*Mag*Real(0.25));
		Out.Back().Color = Color1;

/*
		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*(Radius2*Skew));
		Out.PushBack().Pos = In[idx+1].Pos + (RayTan*(Radius2));
		Out.PushBack().Pos = In[idx+0].Pos + (RayTan*(Radius*UnSkew));

		Out.PushBack().Pos = In[idx+0].Pos + (RayTan*(Radius*Skew));
		Out.PushBack().Pos = In[idx+0].Pos - (RayTan*(Radius*Skew));
		Out.PushBack().Pos = In[idx+1].Pos - (RayTan*(Radius2));
*/

/*		
		// Fill Gap //
		Real RaySide = dot(RayTan.Tangent(),OldRayTan);
		if ( RaySide < Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos - (RayTan*Radius);
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos - (OldRayTan*Radius);
		}
		else if ( RaySide > Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos + (RayTan*Radius);
			Out.PushBack().Pos = In[idx+0].Pos + (OldRayTan*Radius);
		}
		else {
			// Do nothing in Zero case (i.e. First time, axis aligned) //
		}
*/				
		OldRayTan = RayTan;
		Radius = Radius2;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GENERATOR_GENERATOR_CURVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
