// Copyright 2011 Google Inc. All Rights Reserved.
//
// This code is licensed under the same terms as WebM:
//  Software License Agreement:  http://www.webmproject.org/license/software/
//  Additional IP Rights Grant:  http://www.webmproject.org/license/additional/
// -----------------------------------------------------------------------------
//
//  RIFF container manipulation for WEBP images.
//
// Authors: Urvang (urvang@google.com)
//          Vikas (vikasa@google.com)

// This API allows manipulation of WebP container images containing features
// like color profile, metadata, animation and fragmented images.
//
// Code Example#1: Creating a MUX with image data, color profile and XMP
// metadata.
//
//   int copy_data = 0;
//   WebPMux* mux = WebPMuxNew();
//   // ... (Prepare image data).
//   WebPMuxSetImage(mux, &image, copy_data);
//   // ... (Prepare ICCP color profile data).
//   WebPMuxSetChunk(mux, "ICCP", &icc_profile, copy_data);
//   // ... (Prepare XMP metadata).
//   WebPMuxSetChunk(mux, "XMP ", &xmp, copy_data);
//   // Get data from mux in WebP RIFF format.
//   WebPMuxAssemble(mux, &output_data);
//   WebPMuxDelete(mux);
//   // ... (Consume output_data; e.g. write output_data.bytes to file).
//   WebPDataClear(&output_data);
//
// Code Example#2: Get image and color profile data from a WebP file.
//
//   int copy_data = 0;
//   // ... (Read data from file).
//   WebPMux* mux = WebPMuxCreate(&data, copy_data);
//   WebPMuxGetFrame(mux, 1, &image);
//   // ... (Consume image; e.g. call WebPDecode() to decode the data).
//   WebPMuxGetChunk(mux, "ICCP", &icc_profile);
//   // ... (Consume icc_data).
//   WebPMuxDelete(mux);
//   free(data);

#ifndef WEBP_WEBP_MUX_H_
#define WEBP_WEBP_MUX_H_

#include "./mux_types.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define WEBP_MUX_ABI_VERSION 0x0100        // MAJOR(8b) + MINOR(8b)

typedef struct WebPMux WebPMux;   // main opaque object.
#if !(defined(__cplusplus) || defined(c_plusplus))
typedef enum WebPMuxError WebPMuxError;
typedef enum WebPChunkId WebPChunkId;
#endif
typedef struct WebPMuxFrameInfo WebPMuxFrameInfo;
typedef struct WebPMuxAnimParams WebPMuxAnimParams;

// Error codes
enum WebPMuxError {
  WEBP_MUX_OK                 =  1,
  WEBP_MUX_NOT_FOUND          =  0,
  WEBP_MUX_INVALID_ARGUMENT   = -1,
  WEBP_MUX_BAD_DATA           = -2,
  WEBP_MUX_MEMORY_ERROR       = -3,
  WEBP_MUX_NOT_ENOUGH_DATA    = -4
};

// IDs for different types of chunks.
enum WebPChunkId {
  WEBP_CHUNK_VP8X,     // VP8X
  WEBP_CHUNK_ICCP,     // ICCP
  WEBP_CHUNK_ANIM,     // ANIM
  WEBP_CHUNK_ANMF,     // ANMF
  WEBP_CHUNK_FRGM,     // FRGM
  WEBP_CHUNK_ALPHA,    // ALPH
  WEBP_CHUNK_IMAGE,    // VP8/VP8L
  WEBP_CHUNK_EXIF,     // EXIF
  WEBP_CHUNK_XMP,      // XMP
  WEBP_CHUNK_UNKNOWN,  // Other chunks.
  WEBP_CHUNK_NIL
};

//------------------------------------------------------------------------------

// Returns the version number of the mux library, packed in hexadecimal using
// 8bits or each of major/minor/revision. E.g: v2.5.7 is 0x020507.
WEBP_EXTERN(int) WebPGetMuxVersion(void);

//------------------------------------------------------------------------------
// Life of a Mux object

// Internal, version-checked, entry point
WEBP_EXTERN(WebPMux*) WebPNewInternal(int);

// Creates an empty mux object.
// Returns:
//   A pointer to the newly created empty mux object.
static WEBP_INLINE WebPMux* WebPMuxNew(void) {
  return WebPNewInternal(WEBP_MUX_ABI_VERSION);
}

// Deletes the mux object.
// Parameters:
//   mux - (in/out) object to be deleted
WEBP_EXTERN(void) WebPMuxDelete(WebPMux* mux);

//------------------------------------------------------------------------------
// Mux creation.

// Internal, version-checked, entry point
WEBP_EXTERN(WebPMux*) WebPMuxCreateInternal(const WebPData*, int, int);

// Creates a mux object from raw data given in WebP RIFF format.
// Parameters:
//   bitstream - (in) the bitstream data in WebP RIFF format
//   copy_data - (in) value 1 indicates given data WILL be copied to the mux
//               and value 0 indicates data will NOT be copied.
// Returns:
//   A pointer to the mux object created from given data - on success.
//   NULL - In case of invalid data or memory error.
static WEBP_INLINE WebPMux* WebPMuxCreate(const WebPData* bitstream,
                                          int copy_data) {
  return WebPMuxCreateInternal(bitstream, copy_data, WEBP_MUX_ABI_VERSION);
}

//------------------------------------------------------------------------------
// Non-image chunks.

// Note: Only non-image related chunks should be managed through chunk APIs.
// (Image related chunks are: "ANMF", "FRGM", "VP8 ", "VP8L" and "ALPH").
// To add, get and delete images, use APIs WebPMuxSetImage(),
// WebPMuxPushFrame(), WebPMuxGetFrame() and WebPMuxDeleteFrame().

// Adds a chunk with id 'fourcc' and data 'chunk_data' in the mux object.
// Any existing chunk(s) with the same id will be removed.
// Parameters:
//   mux - (in/out) object to which the chunk is to be added
//   fourcc - (in) a character array containing the fourcc of the given chunk;
//                 e.g., "ICCP", "XMP ", "EXIF" etc.
//   chunk_data - (in) the chunk data to be added
//   copy_data - (in) value 1 indicates given data WILL be copied to the mux
//               and value 0 indicates data will NOT be copied.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux, fourcc or chunk_data is NULL
//                               or if fourcc corresponds to an image chunk.
//   WEBP_MUX_MEMORY_ERROR - on memory allocation error.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxSetChunk(
    WebPMux* mux, const char fourcc[4], const WebPData* chunk_data,
    int copy_data);

// Gets a reference to the data of the chunk with id 'fourcc' in the mux object.
// The caller should NOT free the returned data.
// Parameters:
//   mux - (in) object from which the chunk data is to be fetched
//   fourcc - (in) a character array containing the fourcc of the chunk;
//                 e.g., "ICCP", "XMP ", "EXIF" etc.
//   chunk_data - (out) returned chunk data
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if either mux, fourcc or chunk_data is NULL
//                               or if fourcc corresponds to an image chunk.
//   WEBP_MUX_NOT_FOUND - If mux does not contain a chunk with the given id.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxGetChunk(
    const WebPMux* mux, const char fourcc[4], WebPData* chunk_data);

// Deletes the chunk with the given 'fourcc' from the mux object.
// Parameters:
//   mux - (in/out) object from which the chunk is to be deleted
//   fourcc - (in) a character array containing the fourcc of the chunk;
//                 e.g., "ICCP", "XMP ", "EXIF" etc.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux or fourcc is NULL
//                               or if fourcc corresponds to an image chunk.
//   WEBP_MUX_NOT_FOUND - If mux does not contain a chunk with the given fourcc.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxDeleteChunk(
    WebPMux* mux, const char fourcc[4]);

//------------------------------------------------------------------------------
// Images.

// Encapsulates data about a single frame/fragment.
struct WebPMuxFrameInfo {
  WebPData    bitstream;  // image data: can either be a raw VP8/VP8L bitstream
                          // or a single-image WebP file.
  int         x_offset;   // x-offset of the frame.
  int         y_offset;   // y-offset of the frame.
  int         duration;   // duration of the frame (in milliseconds).

  WebPChunkId id;         // frame type: should be one of WEBP_CHUNK_ANMF,
                          // WEBP_CHUNK_FRGM or WEBP_CHUNK_IMAGE
  WebPMuxAnimDispose dispose_method;  // Disposal method for the frame.
  uint32_t    pad[2];     // padding for later use
};

// Sets the (non-animated and non-fragmented) image in the mux object.
// Note: Any existing images (including frames/fragments) will be removed.
// Parameters:
//   mux - (in/out) object in which the image is to be set
//   bitstream - (in) can either be a raw VP8/VP8L bitstream or a single-image
//               WebP file (non-animated and non-fragmented)
//   copy_data - (in) value 1 indicates given data WILL be copied to the mux
//               and value 0 indicates data will NOT be copied.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux is NULL or bitstream is NULL.
//   WEBP_MUX_MEMORY_ERROR - on memory allocation error.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxSetImage(
    WebPMux* mux, const WebPData* bitstream, int copy_data);

// Adds a frame at the end of the mux object.
// Notes: (1) frame.id should be one of WEBP_CHUNK_ANMF or WEBP_CHUNK_FRGM
//        (2) For setting a non-animated non-fragmented image, use
//            WebPMuxSetImage() instead.
//        (3) Type of frame being pushed must be same as the frames in mux.
//        (4) As WebP only supports even offsets, any odd offset will be snapped
//            to an even location using: offset &= ~1
// Parameters:
//   mux - (in/out) object to which the frame is to be added
//   frame - (in) frame data.
//   copy_data - (in) value 1 indicates given data WILL be copied to the mux
//               and value 0 indicates data will NOT be copied.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux or frame is NULL
//                               or if content of 'frame' is invalid.
//   WEBP_MUX_MEMORY_ERROR - on memory allocation error.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxPushFrame(
    WebPMux* mux, const WebPMuxFrameInfo* frame, int copy_data);

// Gets the nth frame from the mux object.
// The content of 'frame->bitstream' is allocated using malloc(), and NOT
// owned by the 'mux' object. It MUST be deallocated by the caller by calling
// WebPDataClear().
// nth=0 has a special meaning - last position.
// Parameters:
//   mux - (in) object from which the info is to be fetched
//   nth - (in) index of the frame in the mux object
//   frame - (out) data of the returned frame
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux or frame is NULL.
//   WEBP_MUX_NOT_FOUND - if there are less than nth frames in the mux object.
//   WEBP_MUX_BAD_DATA - if nth frame chunk in mux is invalid.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxGetFrame(
    const WebPMux* mux, uint32_t nth, WebPMuxFrameInfo* frame);

// Deletes a frame from the mux object.
// nth=0 has a special meaning - last position.
// Parameters:
//   mux - (in/out) object from which a frame is to be deleted
//   nth - (in) The position from which the frame is to be deleted
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux is NULL.
//   WEBP_MUX_NOT_FOUND - If there are less than nth frames in the mux object
//                        before deletion.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxDeleteFrame(WebPMux* mux, uint32_t nth);

//------------------------------------------------------------------------------
// Animation.

// Animation parameters.
struct WebPMuxAnimParams {
  uint32_t bgcolor;  // Background color of the canvas stored (in MSB order) as:
                     // Bits 00 to 07: Alpha.
                     // Bits 08 to 15: Red.
                     // Bits 16 to 23: Green.
                     // Bits 24 to 31: Blue.
  int loop_count;    // Number of times to repeat the animation [0 = infinite].
};

// Sets the animation parameters in the mux object. Any existing ANIM chunks
// will be removed.
// Parameters:
//   mux - (in/out) object in which ANIM chunk is to be set/added
//   params - (in) animation parameters.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if either mux or params is NULL
//   WEBP_MUX_MEMORY_ERROR - on memory allocation error.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxSetAnimationParams(
    WebPMux* mux, const WebPMuxAnimParams* params);

// Gets the animation parameters from the mux object.
// Parameters:
//   mux - (in) object from which the animation parameters to be fetched
//   params - (out) animation parameters extracted from the ANIM chunk
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if either of mux or params is NULL
//   WEBP_MUX_NOT_FOUND - if ANIM chunk is not present in mux object.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxGetAnimationParams(
    const WebPMux* mux, WebPMuxAnimParams* params);

//------------------------------------------------------------------------------
// Misc Utilities.

// Gets the feature flags from the mux object.
// Parameters:
//   mux - (in) object from which the features are to be fetched
//   flags - (out) the flags specifying which features are present in the
//           mux object. This will be an OR of various flag values.
//           Enum 'WebPFeatureFlags' can be used to test individual flag values.
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if mux or flags is NULL
//   WEBP_MUX_NOT_FOUND - if VP8X chunk is not present in mux object.
//   WEBP_MUX_BAD_DATA - if VP8X chunk in mux is invalid.
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxGetFeatures(const WebPMux* mux,
                                             uint32_t* flags);

// Gets number of chunks having tag value tag in the mux object.
// Parameters:
//   mux - (in) object from which the info is to be fetched
//   id - (in) chunk id specifying the type of chunk
//   num_elements - (out) number of chunks with the given chunk id
// Returns:
//   WEBP_MUX_INVALID_ARGUMENT - if either mux, or num_elements is NULL
//   WEBP_MUX_OK - on success.
WEBP_EXTERN(WebPMuxError) WebPMuxNumChunks(const WebPMux* mux,
                                           WebPChunkId id, int* num_elements);

// Assembles all chunks in WebP RIFF format and returns in 'assembled_data'.
// This function also validates the mux object.
// Note: The content of 'assembled_data' will be ignored and overwritten.
// Also, the content of 'assembled_data' is allocated using malloc(), and NOT
// owned by the 'mux' object. It MUST be deallocated by the caller by calling
// WebPDataClear().
// Parameters:
//   mux - (in/out) object whose chunks are to be assembled
//   assembled_data - (out) assembled WebP data
// Returns:
//   WEBP_MUX_BAD_DATA - if mux object is invalid.
//   WEBP_MUX_INVALID_ARGUMENT - if either mux, output_data or output_size is
//                               NULL.
//   WEBP_MUX_MEMORY_ERROR - on memory allocation error.
//   WEBP_MUX_OK - on success
WEBP_EXTERN(WebPMuxError) WebPMuxAssemble(WebPMux* mux,
                                          WebPData* assembled_data);

//------------------------------------------------------------------------------

#if defined(__cplusplus) || defined(c_plusplus)
}    // extern "C"
#endif

#endif  /* WEBP_WEBP_MUX_H_ */
