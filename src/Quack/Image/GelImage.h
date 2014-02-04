// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELIMAGE_H__
#define __GEL_GELIMAGE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include "GelSTBImage.h"
// - ------------------------------------------------------------------------------------------ - //
class GelImage {
	typedef GelImage thistype;
	GelAssetPool::UID ID;
	GelSTBImage Image;
public:
	inline GelImage( const char* InFile ) :
		ID( 0 )
	{
		ID = Gel::AssetPool.Load( Gel::Search( InFile ) );
		Image = new_GelSTBImage( Gel::AssetPool[ID].GetDataBlock() );
	}
	inline ~GelImage() {
		delete_GelSTBImage( Image );
	}
	
	// Sizes //
	inline st Size() const {
		return Image.Width * Image.Height;
	}
	inline st SizeOf() const {
		return Image.Width * Image.Height * Image.Info;
	}

	// Dimensions //
	inline st32 Width() const {
		return Image.Width;
	}
	inline st32 Height() const {
		return Image.Height;
	}
	inline st32 BPP() const {
		return Image.Info;
	}

	// Get the Data //	
	inline unsigned char* Get() {
		return Image.Data;
	}
	inline const unsigned char* Get() const {
		return Image.Data;
	}
	
	inline st32 Index( const st32 _x, const st32 _y ) const {
		return ((_x + (_y * Image.Width)) * Image.Info);
	}
	inline st32 operator () ( const st32 _x, const st32 _y ) const {
		unsigned char* Ptr = Image.Data + Index(_x,_y);

		if ( Image.Info == 4 ) {
			return *((st32*)Ptr);
		}
		else if ( Image.Info == 3 ) {
			return Ptr[0] | (Ptr[1] << 8) | (Ptr[2] << 16);
		}
		else if ( Image.Info == 2 ) {
			return *((st16*)Ptr);			
		}
		else {
			return *Ptr;
		}
	}
	
	inline unsigned char operator [] ( const st32 _idx ) const {
		return Image.Data[_idx];
	}
	
public:
	// Math //
	inline st Area() const {
		return Image.Width * Image.Height;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELIMAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //
