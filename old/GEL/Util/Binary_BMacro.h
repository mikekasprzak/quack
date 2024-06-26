// - ------------------------------------------------------------------------------------------ - //
// Binary //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_UTIL_Binary_BMacro_H__
#define __GEL_UTIL_Binary_BMacro_H__
// - ------------------------------------------------------------------------------------------ - //
// the infamous 'b' macro //
#define b( _num )	( \
		                               (((_num % 10) / 1) << 0) | \
		                              (((_num % 100) / 10) << 1) | \
		                             (((_num % 1000) / 100) << 2) | \
		                            (((_num % 10000) / 1000) << 3) | \
		                           (((_num % 100000) / 10000) << 4) | \
		                          (((_num % 1000000) / 100000) << 5) | \
		                         (((_num % 10000000) / 1000000) << 6) | \
		                        (((_num % 100000000) / 10000000) << 7) | \
		                       (((_num % 1000000000) / 100000000) << 8) | \
		                      (((_num % 10000000000) / 1000000000) << 9) | \
		                     (((_num % 100000000000) / 10000000000) << 10) |\
		                    (((_num % 1000000000000) / 100000000000) << 11) |\
		                   (((_num % 10000000000000) / 1000000000000) << 12) |\
		                  (((_num % 100000000000000) / 10000000000000) << 13) |\
		                 (((_num % 1000000000000000) / 100000000000000) << 14) |\
		                (((_num % 10000000000000000) / 1000000000000000) << 15) |\
		               (((_num % 100000000000000000) / 10000000000000000) << 16) |\
		              (((_num % 1000000000000000000) / 100000000000000000) << 17)  \
	                )
//		             (((_num % 10000000000000000000) / 1000000000000000000) << 18) | \
//		            (((_num % 100000000000000000000) / 10000000000000000000) << 19) | \
//		           (((_num % 1000000000000000000000) / 100000000000000000000) << 20) | \
//		          (((_num % 10000000000000000000000) / 1000000000000000000000) << 21) | \
//		         (((_num % 100000000000000000000000) / 10000000000000000000000) << 22) | \
//		        (((_num % 1000000000000000000000000) / 100000000000000000000000) << 23) | \
//		       (((_num % 10000000000000000000000000) / 1000000000000000000000000) << 24) | \
//		      (((_num % 100000000000000000000000000) / 10000000000000000000000000) << 25) | \
//		     (((_num % 1000000000000000000000000000) / 100000000000000000000000000) << 26) | \
//		    (((_num % 10000000000000000000000000000) / 1000000000000000000000000000) << 27) | \
//		   (((_num % 100000000000000000000000000000) / 10000000000000000000000000000) << 28) | \
//		  (((_num % 1000000000000000000000000000000) / 100000000000000000000000000000) << 29) | \
//		 (((_num % 10000000000000000000000000000000) / 1000000000000000000000000000000) << 30) | \
//		(((_num % 100000000000000000000000000000000) / 10000000000000000000000000000000) << 31)   \
//	)
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_UTIL_Binary_BMacro_H__ //
// - ------------------------------------------------------------------------------------------ - //
