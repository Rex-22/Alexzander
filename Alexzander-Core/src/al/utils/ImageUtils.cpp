#include "ImageUtils.h"

#include <FreeImage.h>
#include "al/utils/Log.h"

namespace al {

	byte* ImageUtils::LoadImage(const char* filename, uint* width, uint* height)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(filename, 0);

		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);

		if (fif == FIF_UNKNOWN)
			return nullptr;

		AL_ASSERT(fif, "[Resource] Unknown image file format!");

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);

		if (!dib)
			return nullptr;

		AL_ASSERT(dib, "[Resource] Could not load image '", filename, "'!");

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);

		int bits = FreeImage_GetBPP(dib);
		
		int size = *width * *height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		return result;
	}
}
