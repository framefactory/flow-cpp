// -----------------------------------------------------------------------------
//  File        Image.cpp
//  Project     FlowGraphics
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/03 $
// -----------------------------------------------------------------------------

#include "FlowGraphics/Image.h"
#include "FlowCore/MemoryTracer.h"

#include <FreeImage.h>

// -----------------------------------------------------------------------------
//  Class FImage
// -----------------------------------------------------------------------------

// Implementation --------------------------------------------------------------

struct _imageImpl_t
{
	FIBITMAP* pBitmap;
	uint32_t refCount;
};

// Constructors and destructor -------------------------------------------------

FImage::FImage()
	: m_pImpl(NULL)
{
}

FImage::FImage(const FImage& other)
{
	m_pImpl = other.m_pImpl;
	_addRef();
}

FImage::~FImage()
{
	_releaseRef();
}

FImage& FImage::operator=(const FImage& other)
{
	if (this == &other)
		return *this;

	_releaseRef();
	m_pImpl = other.m_pImpl;
	_addRef();
	return *this;
}

// Access ----------------------------------------------------------------------

uint8_t* FImage::data()
{
	if (!m_pImpl)
		return NULL;

	return FreeImage_GetBits(m_pImpl->pBitmap);
}

const uint8_t* FImage::data() const
{
	if (!m_pImpl)
		return NULL;

	return FreeImage_GetBits(m_pImpl->pBitmap);
}

uint8_t* FImage::line(uint32_t y)
{
	if (!m_pImpl)
		return NULL;

	return FreeImage_GetScanLine(m_pImpl->pBitmap, y);
}

const uint8_t* FImage::line(uint32_t y) const
{
	if (!m_pImpl)
		return NULL;

	return FreeImage_GetScanLine(m_pImpl->pBitmap, y);
}

// Public commands -------------------------------------------------------------

bool FImage::create(uint32_t width, uint32_t height, FImageType type)
{
	FREE_IMAGE_TYPE fit = (FREE_IMAGE_TYPE)(int)type;
	FIBITMAP* pBmp = NULL;

	if (type < FImageType::Indexed_1)
		pBmp = FreeImage_AllocateT(fit, width, height);
	else
		pBmp = FreeImage_Allocate(width, height, type.bitsPerPixel());

	if (!pBmp)
		return false;

	_releaseRef();
	_createRef();
	m_pImpl->pBitmap = pBmp;
	return true;
}

bool FImage::load(const QString& filePath,
	FImageFileFormat format /* = FImageFileFormat::Unknown */)
{
	// TODO: Find proper image format if format is unknown
	F_ASSERT(format != FImageFileFormat::Unknown);

	FREE_IMAGE_FORMAT fif = (FREE_IMAGE_FORMAT)(int)format;
	FIBITMAP* pBmp = FreeImage_Load(fif, filePath.toLatin1());

	if (!pBmp)
		return false;

	_releaseRef();
	_createRef();
	m_pImpl->pBitmap = pBmp;
	return true;
}

bool FImage::paste(const FImage& source, uint32_t left, uint32_t top)
{
	if (m_pImpl)
	{
		BOOL result = FreeImage_Paste(
			m_pImpl->pBitmap, source.m_pImpl->pBitmap, left, top, /* Alpha */ 256);
		return (result != 0);
	}

	return false;
}

void FImage::release()
{
	_releaseRef();
}

// Public queries --------------------------------------------------------------

bool FImage::save(const QString& filePath,
				  FImageFileFormat format,
				  int flags /* = 0 */) const
{
	if (!m_pImpl)
		return false;

	FREE_IMAGE_FORMAT fif = (FREE_IMAGE_FORMAT)(int)format;
	return FreeImage_Save(fif, m_pImpl->pBitmap, filePath.toLatin1(), flags) != 0;
}

FImage FImage::clone() const
{
	FImage resultImage;

	if (m_pImpl)
	{
		FIBITMAP* pResult = FreeImage_Clone(m_pImpl->pBitmap);
		if (pResult)
		{
			resultImage._createRef();
			resultImage.m_pImpl->pBitmap = pResult;
		}
	}

	return resultImage;
}

FImage FImage::convert(FImageType targetType) const
{
	FImage convertedImage;
	FIBITMAP* pConvertedBitmap;
	FREE_IMAGE_TYPE fit = (FREE_IMAGE_TYPE)(int)targetType;
	FImageType sourceType = type();

	if (m_pImpl)
	{
		switch (targetType)
		{
		case FImageType::RGB_UInt8:
			if (sourceType == FImageType::RGBA_UInt16)
			{
				int width = FreeImage_GetWidth(m_pImpl->pBitmap);
				int height = FreeImage_GetHeight(m_pImpl->pBitmap);
				FIBITMAP* pRgba = FreeImage_ConvertTo32Bits(m_pImpl->pBitmap);
				FIBITMAP* pR = FreeImage_GetChannel(pRgba, FICC_RED);
				FIBITMAP* pG = FreeImage_GetChannel(pRgba, FICC_GREEN);
				FIBITMAP* pB = FreeImage_GetChannel(pRgba, FICC_BLUE);
				pConvertedBitmap = FreeImage_Allocate(width, height, 24);
				FreeImage_SetChannel(pConvertedBitmap, pR, FICC_RED);
				FreeImage_SetChannel(pConvertedBitmap, pG, FICC_GREEN);
				FreeImage_SetChannel(pConvertedBitmap, pB, FICC_BLUE);
				FreeImage_Unload(pRgba);
				FreeImage_Unload(pR);
				FreeImage_Unload(pG);
				FreeImage_Unload(pB);
			}
			else
			{
				pConvertedBitmap = FreeImage_ConvertTo24Bits(m_pImpl->pBitmap);
			}
			break;

		case FImageType::RGBA_UInt8:
			pConvertedBitmap = FreeImage_ConvertTo32Bits(m_pImpl->pBitmap);
			break;

		default:
			pConvertedBitmap = FreeImage_ConvertToType(m_pImpl->pBitmap, fit);
			break;
		}
	}

	if (pConvertedBitmap)
	{
		convertedImage._createRef();
		convertedImage.m_pImpl->pBitmap = pConvertedBitmap;
	}

	return convertedImage;
}

FImage FImage::copy(uint32_t left, uint32_t top, uint32_t width, uint32_t height) const
{
	FImage resultImage;

	if (m_pImpl)
	{
		FIBITMAP* pResult = FreeImage_Copy(m_pImpl->pBitmap, left, top, left + width, top + height);
		if (pResult)
		{
			resultImage._createRef();
			resultImage.m_pImpl->pBitmap = pResult;
		}
	}

	return resultImage;
}

FImage FImage::resize(uint32_t width, uint32_t height) const
{
	FImage resultImage;

	if (m_pImpl)
	{
		FIBITMAP* pResult = FreeImage_Rescale(m_pImpl->pBitmap, width, height, FILTER_CATMULLROM);
		if (pResult)
		{
			resultImage._createRef();
			resultImage.m_pImpl->pBitmap = pResult;
		}
	}

	return resultImage;
}

FImageType FImage::type() const
{
	if (!m_pImpl)
		return FImageType::Unknown;

	int type =  FreeImage_GetImageType(m_pImpl->pBitmap);
	return FImageType((FImageType::enum_type)type);
}

uint32_t FImage::bitsPerPixel() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetBPP(m_pImpl->pBitmap);
}

uint32_t FImage::paletteSize() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetColorsUsed(m_pImpl->pBitmap);
}

uint32_t FImage::width() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetWidth(m_pImpl->pBitmap);
}

uint32_t FImage::height() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetHeight(m_pImpl->pBitmap);
}

uint32_t FImage::bytesPerLine() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetLine(m_pImpl->pBitmap);
}

uint32_t FImage::pitch() const
{
	if (!m_pImpl)
		return 0;

	return FreeImage_GetPitch(m_pImpl->pBitmap);
}

// Internal functions ----------------------------------------------------------

void FImage::_createRef()
{
	F_ASSERT(!m_pImpl);
	m_pImpl = new _imageImpl_t();
	m_pImpl->refCount = 1;
	m_pImpl->pBitmap = NULL;
}

void FImage::_addRef()
{
	if (m_pImpl)
		m_pImpl->refCount++;
}

void FImage::_releaseRef()
{
	if (m_pImpl)
	{
		m_pImpl->refCount--;
		if (!m_pImpl->refCount)
		{
			FreeImage_Unload(m_pImpl->pBitmap);
			delete m_pImpl;
		}

		m_pImpl = NULL;
	}
}

// -----------------------------------------------------------------------------