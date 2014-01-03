// -----------------------------------------------------------------------------
//  File        MainDialog.cpp
//  Project     FontConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/11 $
// -----------------------------------------------------------------------------

#include "FontConverter/MainDialog.h"
#include "FlowGraphics/BitmapFontFactory.h"
#include "FlowCore/MemoryTracer.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

// -----------------------------------------------------------------------------
//  Class FMainDialog
// -----------------------------------------------------------------------------

// Constructors and destructor -------------------------------------------------

FMainDialog::FMainDialog(QWidget* pParent /* = NULL */)
	: QDialog(pParent)
{
	m_fontPath = "C:\\Windows\\Fonts\\arial.ttf";
	m_targetFolder = "C:\\Users\\Administrator\\Desktop\\BitmapFonts";
	_initDialog();
}

FMainDialog::~FMainDialog()
{
}

// Public commands -------------------------------------------------------------

// Public queries --------------------------------------------------------------

uint32_t FMainDialog::fontHeight() const
{
	return ui.spinFontHeight->value();
}

uint32_t FMainDialog::bitmapSize() const
{
	QString texSize = ui.comboTexSize->currentText();
	return texSize.toInt();
}

// Slots -----------------------------------------------------------------------

void FMainDialog::onSelectFont()
{
	QString dir = QStandardPaths::standardLocations(QStandardPaths::FontsLocation).first();
	QFileDialog::Options options
		= QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog;

	QString file = QFileDialog::getOpenFileName(
		this, "Select font file", dir + "//arial.ttf", "Font files (*.ttf *.otf)", NULL, options);

	m_fontPath = file;
	ui.labelFontFile->setText(m_fontPath);
}

void FMainDialog::onSelectDestination()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Select output folder");
	m_targetFolder = dir;
	ui.labelDestination->setText(m_targetFolder);
}

void FMainDialog::onCreate()
{
	QFileInfo fontFile(m_fontPath);
	if (!fontFile.exists())
		return;

	FBitmapFontFactory fontFactory;
	fontFactory.setFontFile(fontFile.absoluteFilePath());
	fontFactory.setFontName(fontFile.baseName());
	fontFactory.setTargetFolder(m_targetFolder);
	fontFactory.setBitmapSize(bitmapSize());
	fontFactory.setFontHeight(fontHeight());

	fontFactory.createFont();
}

// Internal functions ----------------------------------------------------------

void FMainDialog::_initDialog()
{
	ui.setupUi(this);
	ui.labelFontFile->setText(m_fontPath);
	ui.labelDestination->setText(m_targetFolder);

	connect(ui.buttonFontFile, SIGNAL(clicked()), this, SLOT(onSelectFont()));
	connect(ui.buttonDestination, SIGNAL(clicked()), this, SLOT(onSelectDestination()));
	connect(ui.buttonCreate, SIGNAL(clicked()), this, SLOT(onCreate()));
}

// -----------------------------------------------------------------------------