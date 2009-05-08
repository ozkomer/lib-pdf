// This is the main DLL file.

#include "stdafx.h"
#include "libpdf.h"

#include <QtCore/QString>
#include <QtCore/QCoreApplication>
#include <QtCore/QPointer>
#include <QtGui/QImage>
#include <QtCore/QBuffer>
#include <QtCore/QList>
#include <QtGui/QImageWriter>
#include <poppler-qt4.h>


libpdf::LibPdf::LibPdf() : document(NULL), rawData(NULL), qRawData(NULL), width(952), height(1232), numPages(-1){
	
}

libpdf::LibPdf::LibPdf(array<unsigned char>^ pdfFileData) : document(NULL), rawData(NULL), qRawData(NULL), width(952), height(1232), numPages(-1){
	Init(pdfFileData);	
}


void libpdf::LibPdf::clean(){
	if(document != NULL){
		delete document;
		document = NULL;
	}
	if(qRawData != NULL){
		delete qRawData;
		qRawData = NULL;
	}
	if(rawData != NULL){
		delete rawData;
		rawData = NULL;
	}
}

void libpdf::LibPdf::Init(array<unsigned char>^ pdfFileData){
	clean();

	rawData = new unsigned char[pdfFileData->Length];
	pin_ptr<unsigned char> data = &pdfFileData[0];
	memcpy(rawData, data, pdfFileData->Length);
	qRawData = new QByteArray((const char *)(rawData),pdfFileData->Length);
	int length = qRawData->length();
	document = Poppler::Document::loadFromData(*qRawData);
	if(document == NULL || document->isLocked()){
		throw gcnew Exception(gcnew String("Could not read pdf contents. Possible reasons it is locked or the data is bad"));
	}
	numPages = document->numPages();
}

array<unsigned char>^ libpdf::LibPdf::GetImage(int pageNumber, ImageType imageType){

	if(document == NULL){
		throw gcnew Exception(gcnew String("LibPdf object is not initizlied properly"));
	}
	if(pageNumber > numPages){
		throw gcnew IndexOutOfRangeException(gcnew String("LibPdf.GetPNG method recived page index greater than the total number of pages in the document."));
	}
	Poppler::Page * page = document->page(pageNumber);
	try{
		QImage image = page->renderToImage(112*2,112*2);
		QImage scaled = image.scaled(width,height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
		
		QByteArray pngData;
		QBuffer buffer(&pngData);
		buffer.open(QIODevice::WriteOnly);
		
		array<Char>^ name = Enum::GetName(imageType.GetType(), imageType)->ToCharArray();
		pin_ptr<Char> typeName = &name[0];

		QString qName = QString::fromUtf16((const ushort *)typeName);

		scaled.save(&buffer,qName.toAscii().data());

		array<unsigned char>^ retVal = gcnew array<unsigned char>(pngData.length());

		pin_ptr<unsigned char> p = &retVal[0];

		memcpy(p, pngData.data(), pngData.length());

		return retVal;
	}
	catch(...){
		delete page;
		page = NULL;
		throw;
	}

}


array<unsigned char>^ libpdf::LibPdf::GetPNG(int pageNumber){
	return GetImage(pageNumber, ImageType::PNG);
}

libpdf::LibPdf::~LibPdf(){
	clean();
}

libpdf::LibPdf::!LibPdf(){
	clean();
}
