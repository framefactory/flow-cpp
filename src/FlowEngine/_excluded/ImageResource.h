// -----------------------------------------------------------------------------
//  File        ImageResource.h
//  Project     FlowEngine
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/04 $
// -----------------------------------------------------------------------------

#ifndef FLOWENGINE_IMAGERESOURCE_H
#define FLOWENGINE_IMAGERESOURCE_H

#include "FlowEngine/Library.h"
#include "FlowEngine/Resource.h"

#include "FlowGraphics/Image.h"
#include "FlowCore/String.h"



// -----------------------------------------------------------------------------
//  Class FImageResourceDesc
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FImageResourceDesc : public FResourceDesc
{
	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FImageResourceDesc();
	/// Virtual destructor.
	virtual ~FImageResourceDesc();

	//  Public commands ----------------------------------------------

public:
	void setFilePath(const wstring_t& filePath) {
		m_filePath = filePath;
	}

	//  Public queries -----------------------------------------------

	const wstring_t& filePath() const { return m_filePath; }

	virtual bool isEqual(const FResourceDesc& other) const;
	virtual size_t hashCode() const;
	
	//  Internal data members ----------------------------------------

private:
	wstring_t m_filePath;
};
	
// -----------------------------------------------------------------------------
//  Class FImageResource
// -----------------------------------------------------------------------------

class FLOWENGINE_EXPORT FImageResource : public FResource
{
	//  Constructors and destructor ----------------------------------

public:
	/// Creates an image resource managed by the given resource manager.
	FImageResource(FResourceManager* pManager, const FImageResourceDesc& desc);
	/// Virtual destructor.
	virtual ~FImageResource();

	//  Public queries -----------------------------------------------

	/// Returns the image managed by this resource.
	const FImage* image() const;
	/// Returns the resource description.
	const FImageResourceDesc& description() const;

	//  Overrides ----------------------------------------------------

protected:
	/// Creates the image resource.
	virtual bool onCreate();
	/// Releases the image resource.
	virtual void onRelease();

	//  Internal data members ----------------------------------------

private:
	FImageResourceDesc m_desc;
	FImage m_image;
};
	
// -----------------------------------------------------------------------------

#endif // FLOWENGINE_IMAGERESOURCE_H