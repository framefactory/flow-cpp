// -----------------------------------------------------------------------------
//  File        MainDialog.h
//  Project     FontConverter
// -----------------------------------------------------------------------------
//  $Author: Ralph Wiedemeier $
//  $Revision: 1 $
//  $Date: 2013/02/11 $
// -----------------------------------------------------------------------------

#ifndef FONTCONVERTER_MAINDIALOG_H
#define FONTCONVERTER_MAINDIALOG_H

#include "FontConverter/Application.h"

#include "ui_MainDialog.h"
#include <QDialog>

class QLabel;

// -----------------------------------------------------------------------------
//  Class FMainDialog
// -----------------------------------------------------------------------------

class  FMainDialog : public QDialog
{
	Q_OBJECT;

	//  Constructors and destructor ----------------------------------

public:
	/// Default Constructor.
	FMainDialog(QWidget* pParent = NULL);
	/// Virtual destructor.
	virtual ~FMainDialog();

	//  Public commands ----------------------------------------------

public:

	//  Public queries -----------------------------------------------

	uint32_t fontHeight() const;
	uint32_t bitmapSize() const;

	//  Signals ------------------------------------------------------

signals:
	void createFont();

	//  Slots --------------------------------------------------------

protected slots:
	void onSelectFont();
	void onSelectDestination();
	void onCreate();

	//  Overrides ----------------------------------------------------

protected:

	//  Internal functions -------------------------------------------

private:
	void _initDialog();

	//  Internal data members ----------------------------------------

private:
	Ui::mainDialog ui;
	QString m_fontPath;
	QString m_targetFolder;
};
	
// -----------------------------------------------------------------------------

#endif // FONTCONVERTER_MAINDIALOG_H