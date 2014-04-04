// - ------------------------------------------------------------------------------------------ - //
#ifndef __MESH_PMEFILE_SIMPLESELFSHADOW_H__
#define __MESH_PMEFILE_SIMPLESELFSHADOW_H__
// - ------------------------------------------------------------------------------------------ - //
#include "PMEFile.h"
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
void SimpleSelfShadow( cPMEFile& Data ) {	
	for ( size_t MeshIndex = 0; MeshIndex < Data.Mesh.size(); MeshIndex++ ) {
		std::vector< cPMEVertex >& v = Data.Mesh[MeshIndex].Vertex;
		
		for ( size_t VertexIndex = 0; VertexIndex < v.size(); VertexIndex++ ) {
			// Local face storage //
			std::vector< cPMEFaceGroup::FaceType > Face;
			
			Vector3D Pos( v[ VertexIndex ].Pos );
				
			// Find all faces containing this vertex //
			for ( size_t FaceGroupIndex = 0; FaceGroupIndex < Data.Mesh[MeshIndex].FaceGroup.size(); FaceGroupIndex++ ) {
				for ( size_t FaceIndex = 0; FaceIndex < Data.Mesh[MeshIndex].FaceGroup[FaceGroupIndex].Face.size(); FaceIndex++ ) {
					cPMEFaceGroup::FaceType& ThisFace = Data.Mesh[MeshIndex].FaceGroup[FaceGroupIndex].Face[FaceIndex];
					
					if ( ThisFace.a == VertexIndex ) {
						Face.push_back( ThisFace );
					}
					else if ( ThisFace.b == VertexIndex ) {
						Face.push_back( ThisFace );
					}
					else if ( ThisFace.c == VertexIndex ) {
						Face.push_back( ThisFace );
					}
				}
			}
			

			std::vector< Vector3D > Normal;
			
			for ( size_t idx = 0; idx < Face.size(); idx++ ) {
				Normal.push_back( 
					cross(	
						((v[ Face[idx].b ].Pos) - (v[ Face[idx].a ].Pos)),
						((v[ Face[idx].c ].Pos) - (v[ Face[idx].a ].Pos))
						).Normal()
					);
			}
			
//			v[VertexIndex].Normal = Vector3D::Zero;
//			for ( size_t idx = 0; idx < Normal.size(); idx++ ) {
//				v[VertexIndex].Normal.x += Normal[idx].x;
//				v[VertexIndex].Normal.y += Normal[idx].y;
//				v[VertexIndex].Normal.z += Normal[idx].z;
//			}
//			//v[VertexIndex].Normal.Normalize();


			int Value = 255;
			Real Constant(0.7);
			Real Dot = dot(v[VertexIndex].Pos.Normal(), v[VertexIndex].Normal);
			if ( Dot < Constant )
				Value = 255-(-(Dot-Constant) * Real(128));
			
			v[VertexIndex].Color = GEL_RGB( Value, Value, Value );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __MESH_PMEFILE_SIMPLESELFSHADOW_H__ //
// - ------------------------------------------------------------------------------------------ - //
