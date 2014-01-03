// ----------------------------------------------------------------------------------------------------
//  Title			FGLTexture.cpp
//  Description		Implementation of class FGLTexture
// ----------------------------------------------------------------------------------------------------
//  $Author: ralphw $
//  $Revision: 10 $
//  $Date: 2011-07-02 19:51:33 +0200 (Sa, 02 Jul 2011) $
// ----------------------------------------------------------------------------------------------------

#include "FlowGLStable.h"

#include "FGLTexture.h"
#include "FMemoryTracer.h"

// ----------------------------------------------------------------------------------------------------
//  Class FGLTexture
// ----------------------------------------------------------------------------------------------------

quint32 FGLTexture::slotCount()
{
	int count = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &count);
	return count;
}

float FGLTexture::maxAnisotropy()
{
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		float v;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &v);
		return v;
	}

	return 0.0f;
}

// Constructors and destructor ------------------------------------------------------------------------

FGLTexture::FGLTexture()
: m_pRefCount(NULL),
  m_glTexture(0),
  m_glTarget(FGLTextureType(FGLTextureType::Texture2D).glEnum())
{
}

FGLTexture::FGLTexture(FGLTextureType textureType)
: m_pRefCount(NULL),
  m_glTexture(0),
  m_glTarget(textureType.glEnum())
{
}

FGLTexture::FGLTexture(GLuint glTextureName, GLenum glTextureTarget)
{
	F_ASSERT(glTextureName);
	F_ASSERT(glIsTexture(glTextureName));

	m_pRefCount = new QAtomicInt(1);
	m_glTexture = glTextureName;
	m_glTarget = glTextureTarget;
}

FGLTexture::FGLTexture(const FGLTexture& other)
{
	m_pRefCount = other.m_pRefCount;
	m_glTexture = other.m_glTexture;
	m_glTarget = other.m_glTarget;

	if (m_pRefCount)
		m_pRefCount->ref();
}

FGLTexture::~FGLTexture()
{
	release();
}

// Public commands ------------------------------------------------------------------------------------

void FGLTexture::create()
{
	release();
	m_pRefCount = new QAtomicInt(1);

	glGenTextures(1, &m_glTexture);
	F_GLERROR_THROW;

	glBindTexture(m_glTarget, m_glTexture);
	if (m_glTarget != GL_TEXTURE_BUFFER)
	{
		glTexParameteri(m_glTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_glTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	F_GLERROR_ASSERT;
}

void FGLTexture::release()
{
	if (m_glTexture)
	{
		if (!m_pRefCount->deref())
		{
			glDeleteTextures(1, &m_glTexture);
			delete m_pRefCount;
		}

		m_glTexture = 0;
		m_pRefCount = NULL;
	}
}

void FGLTexture::bind(quint32 slot /* = 0 */) const
{
	F_ASSERT(m_glTexture);
	glActiveTexture(_slotName(slot));
	glBindTexture(m_glTarget, m_glTexture);
	F_GLERROR_ASSERT;
}

void FGLTexture::unbind(quint32 slot /* = 0 */) const
{
	glActiveTexture(_slotName(slot));
	glBindTexture(m_glTarget, 0);
	F_GLERROR_ASSERT;
}

void FGLTexture::generateMipmaps()
{
	F_ASSERT(m_glTexture);
	glBindTexture(m_glTarget, m_glTexture);
	glGenerateMipmap(m_glTarget);
	F_GLERROR_ASSERT;
}

void FGLTexture::setFilter(FGLFilterType minFilter,
						   FGLFilterType magFilter,
						   FGLFilterType mipFilter /* = FGLFilterType::Off */)
{
	F_ASSERT(m_glTexture);

	GLint minF = (minFilter == FGLFilterType::Linear ? GL_LINEAR : GL_NEAREST);
	GLint magF = (magFilter == FGLFilterType::Linear ? GL_LINEAR : GL_NEAREST);
	
	if (mipFilter == FGLFilterType::Nearest)
		minF = (minF == GL_NEAREST ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_NEAREST);
	else if (mipFilter == FGLFilterType::Linear)
		minF = (minF == GL_NEAREST ? GL_NEAREST_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR);

	glBindTexture(m_glTarget, m_glTexture);
	glTexParameteri(m_glTarget, GL_TEXTURE_MIN_FILTER, minF);
	glTexParameteri(m_glTarget, GL_TEXTURE_MAG_FILTER, magF);
	F_GLERROR_ASSERT;
}

void FGLTexture::setAnisotropy(float factor)
{
	F_ASSERT(m_glTexture);
	F_ASSERT(wglewIsSupported("GL_EXT_texture_filter_anisotropic"));
	
	glBindTexture(m_glTarget, m_glTexture);
	glTexParameterf(m_glTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, factor);
	F_GLERROR_ASSERT;
}

void FGLTexture::setWrap(FGLWrapMode wrapS, FGLWrapMode wrapT, FGLWrapMode wrapR)
{
	F_ASSERT(m_glTexture);
	glBindTexture(m_glTarget, m_glTexture);
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_S, wrapS.glInt());
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_T, wrapT.glInt());
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_R, wrapR.glInt());
	F_GLERROR_ASSERT;
}

void FGLTexture::setWrap(FGLWrapMode wrapMode)
{
	F_ASSERT(m_glTexture);
	glBindTexture(m_glTarget, m_glTexture);
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_S, wrapMode.glInt());
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_T, wrapMode.glInt());
	glTexParameteri(m_glTarget, GL_TEXTURE_WRAP_R, wrapMode.glInt());
	F_GLERROR_ASSERT;
}

void FGLTexture::setBorderColor(const FColor& color)
{
	F_ASSERT(m_glTexture);
	glBindTexture(m_glTarget, m_glTexture);
	glTexParameterfv(m_glTarget, GL_TEXTURE_BORDER_COLOR, color.ptr());
	F_GLERROR_ASSERT;
}

void FGLTexture::setBorderValues(const FVector4f& values)
{
	F_ASSERT(m_glTexture);
	glBindTexture(m_glTarget, m_glTexture);
	glTexParameterfv(m_glTarget, GL_TEXTURE_BORDER_COLOR, values.ptr());
	F_GLERROR_ASSERT;
}

// Public queries -------------------------------------------------------------------------------------

int FGLTexture::width(int level /* = 0 */) const
{
	if (!m_glTexture)
		return 0;

	GLint width;
	glBindTexture(m_glTarget, m_glTexture);
	glGetTexLevelParameteriv(m_glTarget, level, GL_TEXTURE_WIDTH, &width);
	F_GLERROR_ASSERT;

	return width;
}

int FGLTexture::height(int level /* = 0 */) const
{
	if (!m_glTexture)
		return 0;

	GLint height;
	glBindTexture(m_glTarget, m_glTexture);
	glGetTexLevelParameteriv(m_glTarget, level, GL_TEXTURE_HEIGHT, &height);
	F_GLERROR_ASSERT;

	return height;
}

QSize FGLTexture::size(int level /* = 0 */) const
{
	if (!m_glTexture)
		return QSize();

	int width, height;
	glBindTexture(m_glTarget, m_glTexture);
	glGetTexLevelParameteriv(m_glTarget, level, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(m_glTarget, level, GL_TEXTURE_HEIGHT, &height);
	F_GLERROR_ASSERT;

	return QSize(width, height);
}

// Internal functions ---------------------------------------------------------------------------------

void FGLTexture::_assign(const FGLTexture& other)
{
	release();

	m_pRefCount = other.m_pRefCount;
	m_glTexture = other.m_glTexture;
	if (m_pRefCount)
		m_pRefCount->ref();
}

bool FGLTexture::_allocate2D(FGLPixelFormat format, const QSize& size, quint32 mipLevel)
{
	F_ASSERT(m_glTexture);
	if (!m_glTexture)
		return false;

	F_ASSERT(!size.isEmpty());
	if (size.isEmpty())
		return false;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_glTarget, m_glTexture);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	F_GLERROR_ASSERT;

	GLenum extFormat = format.isDepthStencilFormat() ? GL_DEPTH_COMPONENT : GL_RED;

	glTexImage2D(m_glTarget, mipLevel, format.glEnum(), size.width(), size.height(), 0,
		extFormat, GL_FLOAT, NULL);

	F_GLERROR_THROW;
	return F_GLNOERROR;
}

bool FGLTexture::_initialize2D(FGLPixelFormat textureFormat, const QSize& textureSize, quint32 mipLevel,
								 FGLDataFormat dataFormat, FGLDataType dataType,
								 size_t numBytes, const void* pData, bool flipY /* = true */)
{
	F_ASSERT(pData);
	F_ASSERT(m_glTexture);
	if (!m_glTexture)
		return false;

	F_ASSERT(!textureSize.isEmpty());
	if (textureSize.isEmpty())
		return false;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_glTarget, m_glTexture);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	if (flipY)
	{
		size_t stride = numBytes / textureSize.height();
		void* pBuf = malloc(numBytes);
		_flipVertical(stride, textureSize.height(), pData, pBuf);
		glTexImage2D(m_glTarget, mipLevel, textureFormat, textureSize.width(), textureSize.height(), 0,
			dataFormat, dataType, pBuf);
		free(pBuf);
	}
	else
	{
		glTexImage2D(m_glTarget, mipLevel, textureFormat, textureSize.width(), textureSize.height(), 0,
			dataFormat, dataType, pData);
	}

	F_GLERROR_THROW;
	return F_GLNOERROR;
}

bool FGLTexture::_loadFromImage2D(QImage image, quint32 mipLevel, bool flipY /* = true */)
{
	F_ASSERT(m_glTexture);
	F_ASSERT(!image.isNull());
	if (!m_glTexture || image.isNull())
		return false;

	bool isGrayscale = image.isGrayscale();

	// ensure image is either in 32-bit RGB or ARGB format
	if (image.format() != QImage::Format_RGB32 && image.format() != QImage::Format_ARGB32)
	{
		image = image.convertToFormat(QImage::Format_RGB32);
		if (image.isNull())
			return false;
	}
	bool hasAlpha = image.format() == QImage::Format_ARGB32;
	GLenum internalFormat = hasAlpha ? GL_RGBA8 : GL_RGB8;
	GLenum format = hasAlpha ? GL_BGRA : GL_BGR;
	GLenum type = GL_UNSIGNED_BYTE;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_glTarget, m_glTexture);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	if (flipY)
	{
		void* pBuf = malloc(image.byteCount());
		_flipVertical(image.bytesPerLine(), image.height(), (const void*)image.constBits(), pBuf);
		glTexImage2D(m_glTarget, mipLevel, internalFormat, image.width(), image.height(), 0,
			format, type, pBuf);
		free(pBuf);
	}
	else
	{
		glTexImage2D(m_glTarget, mipLevel, internalFormat, image.width(), image.height(), 0,
			format, type, (const void*)image.constBits());
	}

	F_GLERROR_THROW;
	return F_GLNOERROR;
}

bool FGLTexture::_loadFromFile2D(const QString& fileName, quint32 mipLevel, bool flipY /* = true */)
{
	QImage image(fileName);
	if (image.isNull())
		return false;

	return _loadFromImage2D(image, mipLevel, flipY);
}

void FGLTexture::_flipVertical(size_t stride, size_t numRows, const void* pSrc, void* pDst)
{
	if (stride % 4 != 0)
	{
		char* pS = (char*)pSrc;
		char* pD = (char*)pDst + (numRows - 1) * stride;
		int nr = (int)numRows;
		int nc = (int)stride;

		for (int r = 0; r < nr; r++)
		{
			for (int c = 0; c < nc; c++)
				pD[c] = pS[c];
			pS += stride;
			pD -= stride;
		}
	}
	else
	{
		quint32* pS = (quint32*)pSrc;
		quint32* pD = (quint32*)((char*)pDst + (numRows - 1) * stride);
		int nr = (int)numRows;
		int nc = (int)stride / 4;

		for (int r = 0; r < nr; r++)
		{
			for (int c = 0; c < nc; c++)
				pD[c] = pS[c];
			pS += nc;
			pD -= nc;
		}
	}
}

// ----------------------------------------------------------------------------------------------------