// - ------------------------------------------------------------------------------------------ - //
// TERMS:
//   FileName     - The full name of the file (without Directories).
//   Directory    - The full path to where file is located (without FileName).
//   BaseName     - A FileName without extensions.
//   Extensions   - The extensions of a FileName without the BaseName (dots included).
//   Extension    - A single file extension (dot included).
//   SubDirectory - A single Directory (without Slash).
//
//   SubName      - Underscore delimited strings (typically a BaseName or SubDirectory).
//   SubNumber    - The number found within a string (C64Font = 64, Image_02 = 2). Searches backwards.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_STDSTRING_STDSTRING_H__
#define __GEL_LIB_STDSTRING_STDSTRING_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
namespace String {
// - ------------------------------------------------------------------------------------------ - //
	// - -------------------------------------------------------------------------------------- - //
	// Return the File-Name part of a string //
	inline std::string GetFileName( const std::string& _FileName ) {
		// Find the last slash //
		size_t CharPos = _FileName.rfind( "/" );
		
		if ( CharPos == std::string::npos ) {
			// Slash not found //
			return _FileName;
		}
		
		// Return the entire string after the slash position //
		return _FileName.substr( CharPos + 1 );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the Directory part of a string, excluding the slash //
	inline std::string GetDirectory( const std::string& _FileName ) {
		// Find the last slash //
		size_t CharPos = _FileName.rfind( "/" );
		
		if ( CharPos == std::string::npos ) {
			// Slash not found //
			return "";
		}
		
		// Return the entire string before the slash position //
		return _FileName.substr( 0, CharPos - 0 );
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Return the Directory part of a string, including the slash //
	inline std::string GetDirectorySlash( const std::string& _FileName ) {
		// Find the last slash //
		size_t CharPos = _FileName.rfind( "/" );
		
		if ( CharPos == std::string::npos ) {
			// Slash not found //
			return "";
		}
		
		// Return the entire string before the slash position //
		return _FileName.substr( 0, CharPos + 1 - 0 );
	}	
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the base name (filename without extensions) of the filename //
	inline std::string GetBaseName( const std::string& _FileName ) {
		std::string WorkString = GetFileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( "." );
		
		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return WorkString;
		}
		
		// Return the entire string before the first period //
		return WorkString.substr( 0, DotPos - 0 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the base name including directory //
	inline std::string GetBaseDirectory( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// Find the trailing slash //
		size_t CharPos = WorkString.rfind( "/" );
		if ( CharPos == std::string::npos ) {
			CharPos = 0;
		}
			
		// Find the first dot //
		size_t DotPos = WorkString.find( ".", CharPos );
		
		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return WorkString;
		}
		
		// Return the entire string before the first period //
		return WorkString.substr( 0, DotPos - 0 );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the Extensions //
	inline std::string GetExtensions( const std::string& _FileName ) {
		std::string WorkString = GetFileName( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( "." );
		
		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return "";
		}
		
		// Return the entire string after and including the first period //
		return WorkString.substr( DotPos );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the last extension in the filename //
	inline std::string GetFirstExtension( const std::string& _FileName ) {
		std::string WorkString = GetExtensions( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.find( "." );
		size_t Dot2Pos = WorkString.find( ".", 1 );

		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return "";
		}
		else if ( Dot2Pos == std::string::npos ) {
			// Return the entire string after the last period //
			return WorkString.substr( DotPos );
		}

		// Return just the first Extension //
		return WorkString.substr( DotPos, Dot2Pos );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the last extension in the filename //
	inline std::string GetLastExtension( const std::string& _FileName ) {
		std::string WorkString = GetExtensions( _FileName );
			
		// Find the first dot //
		size_t DotPos = WorkString.rfind( "." );

		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return "";
		}
	
		// Return the entire string after the last period //
		return WorkString.substr( DotPos );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline st32 GetExtensionCount( const std::string& _FileName ) {
		std::string WorkString = GetExtensions( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '.' ) {
				Count++;
			}
		}
		return Count;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetExtension( const std::string& _FileName, const st32 Index ) {
		std::string WorkString = GetExtensions( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '.' ) {
				if ( Count == Index ) {
					return Gel::String::GetFirstExtension( WorkString.substr( idx ) );
				}
				Count++;
			}
		}
		return "";
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of GetLastExtension that takes an index //
	inline std::string GetLastExtension( const std::string& _FileName, const st32 Index ) {
		return GetExtension( _FileName, (GetExtensionCount( _FileName ) - 1) - Index );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return a specific number of Extensions //
	inline std::string GetExtensions( const std::string& _FileName, const st32 _Count ) {
		std::string WorkString = GetExtensions( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '.' ) {
				if ( Count == _Count ) {
					return WorkString.substr( 0, idx );
				}
				Count++;
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return a specific number of Extensions //
	inline std::string GetLastExtensions( const std::string& _FileName, const st32 _Count ) {
		if ( _Count == 0 )
			return "";
			
		std::string WorkString = GetExtensions( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = WorkString.size(); idx--; ) {
			if ( WorkString[idx] == '.' ) {
				Count++;
				if ( Count == _Count ) {
					return WorkString.substr( idx );
				}
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the last subdirectory in the filename //
	inline std::string GetFirstSubDirectory( const std::string& _FileName ) {
		std::string WorkString = GetDirectorySlash( _FileName );
			
		// Find the first slash //
		size_t CharPos = WorkString.find( "/" );

		if ( CharPos == std::string::npos ) {
			// Slash not found //
			return "";
		}

		// Return the first Directory //
		return WorkString.substr( 0, CharPos );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the last subdirectory in the filename //
	inline std::string GetLastSubDirectory( const std::string& _FileName ) {
		std::string WorkString = GetDirectory( _FileName );	// No Slash //
			
		// Find the first dot //
		size_t DotPos = WorkString.rfind( "/" );

		if ( DotPos == std::string::npos ) {
			// Dot not found //
			return "";
		}
	
		// Return the entire string after the last period //
		return WorkString.substr( DotPos + 1 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return 
	inline st32 GetSubDirectoryCount( const std::string& _FileName ) {
		std::string WorkString = GetDirectorySlash( _FileName );
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '/' ) {
				Count++;
			}
		}
		return Count;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetSubDirectory( const std::string& _FileName, const st32 Index ) {
		std::string WorkString = GetDirectorySlash( _FileName );
			
		st32 Count = 0;
		st32 StrPos = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '/' ) {
				if ( Count == Index ) {
					st32 Modifier = 1;
					if ( StrPos == 0 ) {
						Modifier = 0;
					}
					st32 ToCopy = (idx-StrPos) - Modifier;
					return WorkString.substr( StrPos + Modifier, ToCopy );
				}
				Count++;
				StrPos = idx;
			}
		}
		return "";
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of GetLastSubDirectory that takes an index //
	inline std::string GetLastSubDirectory( const std::string& _FileName, const st32 Index ) {
		return GetSubDirectory( _FileName, (GetSubDirectoryCount( _FileName ) - 1) - Index );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetSubDirectories( const std::string& _FileName, const st32 _Count ) {
		if ( _Count == 0 )
			return "";
		
		std::string WorkString = GetDirectory( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '/' ) {
				Count++;
				if ( Count == _Count ) {
					return WorkString.substr( 0, idx );
				}
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetLastSubDirectories( const std::string& _FileName, const st32 _Count ) {
		if ( _Count == 0 )
			return "";
		
		std::string WorkString = GetDirectory( _FileName );
			
		st32 Count = 0;
		for ( st32 idx = WorkString.size(); idx--; ) {
			if ( WorkString[idx] == '/' ) {
				Count++;
				if ( Count == _Count ) {
					st32 Modifier = 1;
					if ( idx == 0 )
						Modifier = 0;
					return WorkString.substr( idx + Modifier );
				}
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the last subname in the name //
	inline std::string GetFirstSubName( const std::string& _Name ) {
		std::string WorkString = _Name + "_";
			
		// Find the first underscore //
		size_t CharPos = WorkString.find( "_" );

		if ( CharPos == std::string::npos ) {
			// Underscore not found //
			return WorkString;
		}

		// Return the first SubName //
		return WorkString.substr( 0, CharPos );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the last subname in the filename //
	inline std::string GetLastSubName( const std::string& _Name ) {
		std::string WorkString = _Name;
			
		// Find the first dot //
		size_t CharPos = WorkString.rfind( "_" );

		if ( CharPos == std::string::npos ) {
			// Underscore not found //
			return WorkString;
		}
	
		// Return the entire string after the last period //
		return WorkString.substr( CharPos + 1 );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return 
	inline st32 GetSubNameCount( const std::string& _Name ) {
		std::string WorkString = _Name + "_";
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '_' ) {
				Count++;
			}
		}
		return Count;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetSubName( const std::string& _Name, const st32 Index ) {
		std::string WorkString = _Name + "_";
			
		st32 Count = 0;
		st32 StrPos = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '_' ) {
				if ( Count == Index ) {
					st32 Modifier = 1;
					if ( StrPos == 0 ) {
						Modifier = 0;
					}
					st32 ToCopy = (idx-StrPos) - Modifier;
					return WorkString.substr( StrPos + Modifier, ToCopy );
				}
				Count++;
				StrPos = idx;
			}
		}
		return "";
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of GetLastSubName that takes an index //
	inline std::string GetLastSubName( const std::string& _Name, const st32 Index ) {
		return GetSubName( _Name, (GetSubNameCount( _Name ) - 1) - Index );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetSubNames( const std::string& _Name, const st32 _Count ) {
		if ( _Count == 0 )
			return "";
		
		std::string WorkString = _Name;
			
		st32 Count = 0;
		for ( st32 idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[idx] == '_' ) {
				Count++;
				if ( Count == _Count ) {
					return WorkString.substr( 0, idx );
				}
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline std::string GetLastSubNames( const std::string& _Name, const st32 _Count ) {
		if ( _Count == 0 )
			return "";
		
		std::string WorkString = _Name;
			
		st32 Count = 0;
		for ( st32 idx = WorkString.size(); idx--; ) {
			if ( WorkString[idx] == '_' ) {
				Count++;
				if ( Count == _Count ) {
					st32 Modifier = 1;
					if ( idx == 0 )
						Modifier = 0;
					return WorkString.substr( idx + Modifier );
				}
			}
		}
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //


//	// - -------------------------------------------------------------------------------------- - //
//	// Return the text before the first underscore "_" (ignoring the underscore) //
//	inline std::string GetPreBaseName( const std::string& _FileName ) {
//		std::string WorkString = GetFileName( _FileName );
//			
//		// Find the first underscore //
//		size_t UnderscorePos = WorkString.find( "_" );
//		
//		if ( UnderscorePos == std::string::npos ) {
//			// Dot not found //
//			return WorkString;
//		}
//		
//		// Return the entire string before the first period //
//		return WorkString.substr( 0, UnderscorePos - 0 );
//	}
//	// - -------------------------------------------------------------------------------------- - //
//	// Return the text after the first underscore "_" (ignoring the underscore) //
//	inline std::string GetPostBaseName( const std::string& _FileName ) {
//		std::string WorkString = GetFileName( _FileName );
//			
//		// Find the first underscore //
//		size_t UnderscorePos = WorkString.find( "_" );
//		
//		if ( UnderscorePos == std::string::npos ) {
//			// Dot not found //
//			return WorkString;
//		}
//		
//		// Return the entire string before the first period //
//		return WorkString.substr( UnderscorePos + 1 );
//	}
//	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return all but the Extensions //
//	inline std::string NoExtensions( const std::string& _FileName ) {
//		// Return the entire string after excluding the file extensions //
//		return GetDirectorySlash( _FileName ) + GetBaseName( _FileName );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Return all but the last extension in the filename //
//	inline std::string NoLastExtension( const std::string& _FileName ) {
//		std::string WorkString = GetFileName( _FileName );
//			
//		// Find the first dot //
//		size_t DotPos = WorkString.find( "." );
//
//		if ( DotPos == std::string::npos ) {
//			// Dot not found //
//			return "";
//		}
//	
//		// Return the entire string after the first period, up until the last period //
//		return WorkString.substr( DotPos, WorkString.rfind( Dot ) - DotPos );
//	}
	// - -------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //

	// - -------------------------------------------------------------------------------------- - //
	// Check for whole file extensions. //
	inline bool HasExtension( const std::string& _FileName, const std::string& _Pattern ) {
		// NOTE: Appending a "." on to the end of the extensions simply the search. //
		return (GetExtensions( _FileName ) + ".").find(_Pattern + ".") != std::string::npos;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Check for partial file extensions (typically used in extension as argument searches). //
	inline bool HasBaseExtension( const std::string& _FileName, const std::string& _Pattern ) {
		return GetExtensions( _FileName ).find(_Pattern) != std::string::npos;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Like above, but returns if any extension from filenames or directory names contains pattern
//	inline bool HasAnyExtension( const std::string& _FileName, const std::string& _Pattern ) {
//		// NOTE: I'm not sure why we're adding a dash here. 
//		if ( _FileName.find( "-" + _Pattern ) != std::string::npos )
//			return true;
//			
//		if ( _FileName.find( _Pattern + "." ) != std::string::npos )
//			return true;
//		if ( _FileName.find( _Pattern + "/" ) != std::string::npos )
//			return true;
//		return false;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Has an extension that contains an argument //
//	inline bool HasArgExtension( const std::string& _FileName, const std::string& _Pattern ) {
//		return GetExtension( _FileName ).find( _Pattern ) != std::string::npos;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like above, but returns if any extension from filenames or directory names contains pattern
//	inline bool HasAnyArgExtension( const std::string& _FileName, const std::string& _Pattern ) {
//		return _FileName.find( _Pattern ) != std::string::npos;
//	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the string following an extension (an extension argument) //
//	inline int GetIntArgExtension( const std::string& _FileName, const std::string& _Pattern ) {
//		// Find the Argument //
//		size_t Pos = 0;
//		if ( (Pos = _FileName.find( _Pattern )) != std::string::npos ) {
//			// Move position past the extension itself to the start of the number //
//			Pos += _Pattern.size();
//			
//			// Find the end (start at the end of the string) //
//			size_t End = _FileName.size();
//			
//			// If I have a dot or slash after me, use them as the end point //
//			size_t NewEnd = 0;
//			if ( (NewEnd = _FileName.find( ".", Pos )) != std::string::npos ) {
//				End = NewEnd;
//			}
//			if ( (NewEnd = _FileName.find( "/", Pos )) != std::string::npos ) {
//				if ( NewEnd < End )
//					End = NewEnd;
//			}
//			
//			return atoi( _FileName.substr( Pos, End - Pos ).c_str() );
//		}
//		return 0;
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Extract the number part from the base name (i.e. Idle05.png would return 5) //
	inline int GetSubNumber( const std::string& _Name ) {
		std::string Base = _Name;
		
		// Find the last number //
		int End = -1;
		for ( int idx = (int)Base.size() - 1; idx >= 0; idx-- ) {
			if ( (Base[idx] >= '0') && (Base[idx] <= '9') ) {
				// Last Number Found //
				End = idx;
				break;
			}
		}
		
		// If no number found, return -1 //
		if ( End == -1 )
			return -1;

		// Find the starting digit //
		int Start = End;
		for ( int idx = End; idx >= 0; idx-- ) {
			if ( (Base[ idx ] >= '0') && (Base[ idx ] <= '9') ) {
			}
			else {
				// This is not a number! //
				Start = idx + 1;
				break;
			}
		}
		
		return atoi( Base.substr( Start, (End - Start) + 1 ).c_str() );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return's true if a directory is found in a string //
	inline bool HasDirectory( const std::string& _FileName, const std::string& _Pattern ) {
		std::string Pattern = _Pattern;

		// If the last character in the pattern isn't a slash //
		if ( _Pattern[ _Pattern.size() - 1 ] != '/' )
			// Append a slash //
			Pattern += "/";
		
		// Find the directory name pattern //
		size_t DirPos = _FileName.find( Pattern );
		
		// If pattern not found //
		if ( DirPos == std::string::npos )
			return false;
		
		// If string was found at the beginning, then our pattern was matched in full //
		if ( DirPos == 0 )
			return true;
		
		// If the previous character is a slash, then our pattern was matched in full //
		if ( _FileName[DirPos - 1] == '/' )
			return true;
		
		// Not a full match //
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //

	// - -------------------------------------------------------------------------------------- - //
	// Replaces all Windows slashes with Unix slashes //
	// ** NOTE ** : Only recommended for platform concious tools!  Don't use this in game code! //
	inline std::string UnixSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all Windows slashes with Unix slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == '\\' )
				WorkString[ idx ] = '/';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all Unix slashes with Windows slashes //
	// ** NOTE ** : Only recommended for platform concious tools!  Don't use this in game code! //
	inline std::string WindowsSlash( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, replace all Unix slashes with Windows slashes //
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] == '/' )
				WorkString[ idx ] = '\\';
		}
		
		// Return our slash updated string //
		return WorkString;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all slashes in a string with the system correct form of slash //
	inline std::string SystemSlash( const std::string& _FileName ) {
	#ifdef USES_WINDOWS_SLASH
		return WindowsSlash( _FileName );
	#else // USES_WINDOWS_SLASH //
		return UnixSlash( _FileName );
	#endif // USES_WINDOWS_SLASH //
	}
	// - -------------------------------------------------------------------------------------- - //
	// Replaces all slashes in a string with the incorrect system slash //
	inline std::string NotSystemSlash( const std::string& _FileName ) {
	#ifdef USES_WINDOWS_SLASH
		return UnixSlash( _FileName );
	#else // USES_WINDOWS_SLASH //
		return WindowsSlash( _FileName );
	#endif // USES_WINDOWS_SLASH //
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Converts lower case letters in a string to upper case //
	inline std::string UpperCase( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, offset characters in the lower case range to be upper//
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] >= 'a' )
				if ( WorkString[ idx ] <= 'z' )
					WorkString[ idx ] += 'A' - 'a';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Converts upper case letters in a string to lower case //
	inline std::string LowerCase( const std::string& _FileName ) {
		std::string WorkString = _FileName;
		
		// For all characters in the string, offset characters in the upper case range to be lower//
		for( size_t idx = 0; idx < WorkString.size(); idx++ ) {
			if ( WorkString[ idx ] >= 'A' )
				if ( WorkString[ idx ] <= 'Z' )
					WorkString[ idx ] -= 'A' - 'a';
		}
		
		// Return our slash updated string //
		return WorkString;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// Todo: Add Command line argument parsing code ... either here or elsewhere //

// - ------------------------------------------------------------------------------------------ - //
}; // namespace String //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_STDSTRING_STDSTRING_H__ //
// - ------------------------------------------------------------------------------------------ - //
