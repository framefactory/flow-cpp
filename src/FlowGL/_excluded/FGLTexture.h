// ----------------------------------------------------------------------------------------------------
//  Title			FGLTexture.h
//  Description		Header file for FGLTexture.cpp
// ----------------------------------------------------------------------------------------------------
//  $Author: ralphw $
//  $Revision: 10 $
//  $Date: 2011-07-02 19:51:33 +0200 (Sa, 02 Jul 2011) $
// ----------------------------------------------------------------------------------------------------

#ifndef FGLTEXTURE_H
#define FGLTEXTURE_H

#include "FlowGLLib.h"
#include "FlowGLDefs.h"

#include "FGLTextureType.h"
#include "FGLPixelFormat.h"
#include "FGLDataFormat.h"
#include "FGLDataType.h"
#include "FGLFilterType.h"
#include "FGLWrapMode.h"
#include "FColor.h"

// ----------------------------------------------------------------------------------------------------
//  Class FGLTexture
// ----------------------------------------------------------------------------------------------------

/// General wrapper class for for OpenGL texture objects. Manages the reference counting
/// and holds the OpenGL texture name and bind target. Special descendant classes are available
/// for specific texture types.
class FLOWGL_EXPORT FGLTexture
{
	//  Static methods ---------------------------------------------------------

public:
	/// Returns the number of available texture slots (units).
	static quint32 slotCount();
	/// Returns the maximum amount of anisotropy. If zero is returned,
	/// anisotropic filtering is not supported.
	static float maxAnisotropy();

	//  Constructors and destructor --------------------------------------------

public:
	/// Default constructor. Creates a texture wrapper of type Texture2D.
	FGLTexture();
	/// Creates a wrapper for an OpenGL texture object of the given type.
	FGLTexture(FGLTextureType textureType);
	/// Create from existing OpenGL texture object.
	FGLTexture(GLuint glTextureName, GLenum glTextureTarget);
	/// Copy constructor.
	FGLTexture(const FGLTexture& other);
	/// Virtual destructor.
	virtual ~FGLTexture();

	//  Operators --------------------------------------------------------------

	/// Assignment operator.
	FGLTexture& operator=(const FGLTexture& other) {
		_assign(other); return *this;
	}
	/// Equality operator.
	bool operator==(const FGLTexture& other) const {
		return _isEqual(other);
	}

	//  Public commands --------------------------------------------------------

public:
	/// Creates the OpenGL texture object.
	void create();
	/// Releases the OpenGL texture object.
	void release();

	/// Binds the texture to the given texture slot.
	void bind(quint32 slot = 0) const;
	/// Unbinds any bound texture from the given slot.
	void unbind(quint32 slot = 0) const;

	/// Generates mipmaps for all texture levels except the base level.
	void generateMipmaps();
	/// Enables or disables linear filtering for minification, magnification and mipmapping.
	void setFilter(FGLFilterType minFilter, FGLFilterType magFilter,
		FGLFilterType mipFilter = FGLFilterType::Off);
	/// Sets the amount of anisotropy used for filtering.
	void setAnisotropy(float factor);
	/// Sets the texture wrap mode independently for the 3 texture coordinates.
	void setWrap(FGLWrapMode wrapS, FGLWrapMode wrapT, FGLWrapMode wrapR);
	/// Sets the texture wrap mode for all 3 texture coordinates.
	void setWrap(FGLWrapMode wrapMode);
	/// Sets the border color for the texture.
	void setBorderColor(const FColor& color);
	/// Sets the border values used when sampling outside of the texture.
	void setBorderValues(const FVector4f& values);

	//  Public queries ---------------------------------------------------------

	/// Returns true if the texture object has been created.
	inline bool isValid() const { return (m_glTexture != 0); }
	/// Returns the OpenGL texture name.
	GLuint glName() const { return m_glTexture; }
	/// Returns the OpenGL binding target (e.g. GL_TEXTURE_2D) of the texture.
	GLenum glTarget() const { return m_glTarget; }

	/// Returns the width of the texture.
	int width(int level = 0) const;
	/// Returns the height of the texture.
	int height(int level = 0) const;
	/// Returns the size of the texture.
	QSize size(int level = 0) const;

	//  Internal functions -----------------------------------------------------

protected:
	void _assign(const FGLTexture& other);

	bool _allocate2D(FGLPixelFormat textureFormat, const QSize& textureSize, quint32 mipLevel);
	bool _initialize2D(FGLPixelFormat textureFormat, const QSize& textureSize, quint32 mipLevel,
		FGLDataFormat dataFormat, FGLDataType dataType, size_t numBytes, const void* pData, bool flipY = true);
	bool _loadFromImage2D(QImage image, quint32 mipLevel, bool flipY = true);
	bool _loadFromFile2D(const QString& fileName, quint32 mipLevel, bool flipY = true);

	void _flipVertical(size_t stride, size_t numRows, const void* pSrc, void* pDst);

	bool _isEqual(const FGLTexture& other) const {
		return m_glTexture == other.m_glTexture;
	}

	static inline GLenum _slotName(quint32 slotIndex) {
		return (GLenum)((quint32)GL_TEXTURE0 + slotIndex);
	}
	static inline quint32 _slotIndex(GLenum slotName) {
		return (quint32)slotName - (quint32)GL_TEXTURE0;
	}

	//  Internal data members --------------------------------------------------

protected:
	GLuint m_glTexture;
	GLenum m_glTarget;
private:
	QAtomicInt* m_pRefCount;

};
	
// ----------------------------------------------------------------------------------------------------

#endif // FGLTEXTURE_H