// -----------------------------------------------------------------------------
//  File        Image.h
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#ifndef FLOWGRAPHICS_IMAGE_H
#define FLOWGRAPHICS_IMAGE_H

#include "FlowGraphics/Library.h"
#include "FlowGraphics/ImageType.h"
#include "FlowGraphics/ImageFileFormat.h"

#include "FlowCore/Range3T.h"

#include <QString>

struct _imageImpl_t;

// -----------------------------------------------------------------------------
//  Class FImage
// -----------------------------------------------------------------------------

/// Wrapper class for FreeImage images.
class FLOWGRAPHICS_EXPORT FImage
{
	//  Lifetime management ------------------------------------------

public:
	FImage();
	FImage(const FImage& other);

	~FImage();

	FImage& operator=(const FImage& other);

	//  Access -------------------------------------------------------
	  
	uint8_t* data();
	const uint8_t* data() const;

	uint8_t* line(uint32_t y);
	const uint8_t* line(uint32_t y) const;

	//  Public commands ----------------------------------------------

	bool create(uint32_t width, uint32_t height, FImageType type);
	bool load(const QString& filePath, FImageFileFormat format
		= FImageFileFormat::Unknown);
	bool paste(const FImage& source, uint32_t left, uint32_t top);

	void release();

	//  Public queries -----------------------------------------------

	bool save(const QString& filePath, FImageFileFormat format, int flags = 0) const;

	FImage clone() const;
	FImage convert(FImageType targetType) const;
	FImage map(FImageType targetType, const FRange3d& range, FRange3d* pBounds = NULL) const;
	FImage copy(uint32_t left, uint32_t top, uint32_t width, uint32_t height) const;
	FImage resize(uint32_t width, uint32_t height) const;

	FImageType type() const;
	uint32_t bitsPerPixel() const;
	uint32_t paletteSize() const;
	uint32_t width() const;
	uint32_t height() const;
	uint32_t bytesPerLine() const;
	uint32_t pitch() const;

	bool isNull() const { return !m_pImpl; }

	//  Internal functions -------------------------------------------

private:
	void _createRef();
	void _addRef();
	void _releaseRef();

	//  Internal data members ----------------------------------------

private:
	_imageImpl_t* m_pImpl;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWGRAPHICS_IMAGE_H