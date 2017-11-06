#include "al/al.h"
#include "ImageUtils.h"

#include <FreeImage.h>
#include "al/utils/Log.h"

namespace al {

	byte* ImageUtils::LoadImage(const char* filename, uint* width, uint* height)
	{
		AL_DEBUG("[Resource] Loading image resource '", filename,"'...");
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;

		fif = FreeImage_GetFIFFromFilename(filename);
		
		if (fif == FIF_UNKNOWN)
		{
			AL_WARN("[Resource] Could not detect image type from file name \nChecking image data...");
			fif = FreeImage_GetFileType(filename, 0);
			AL_ASSERT(fif == FIF_UNKNOWN, "[Resource] Unknown file format!");
		}
		
		AL_DEBUG("[Resource] File type found!");
			
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		AL_ASSERT(dib != NULL, "[Resource] Could not load image resource'", filename, "'!");

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		int bits = FreeImage_GetBPP(dib);
		
		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);
		AL_DEBUG("[Resource] Loaded image resource '", filename, "'!");
		return result;
	}
}
