#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

#include "image_type.h"

namespace Poppler{
	class Document;
}
class QByteArray;

namespace libpdf {

	/// <summary>
    /// Convert pdf to PNG or BMP image.
	///
	/// License GPL see copying
	/// Copyright from:
	/// Vladimir Vasiltsov
    /// </summary>
	public ref class LibPdf : public IDisposable
	{
	public:
        /// <summary>
        /// Default constructor. Make sure you call Init before using
		/// GetImage method
        /// </summary>
		/// <seealso cref="Init"/>
		LibPdf();

		/// <summary>
        /// Overloaded constructor. You don't have to call Init if you use this one.
        /// </summary>
		/// <param name="pdfFileData">byte array containing your pdf data</param>
		explicit LibPdf(array<unsigned char>^ pdfFileData);


		/// <summary>
        /// Initialize LibPdf.
        /// </summary>
		/// <param name="pdfFileData">byte array containing your pdf data.</param>
		void Init(array<unsigned char>^ pdfFileData);


		/// <summary>
        /// Get byte array that contains your converted image
        /// </summary>
		/// <param name="pageNumber">Number of a page to convert to an image</param>
		/// <param name="imageType">Output image format</param>
		/// <seealso cref="Init"/>
		/// <seealso cref="GetPNG"/>
		/// <seealso cref="Width"/>
		/// <seealso cref="Height"/>
		/// <seealso cref="NumPages"/>
		array<unsigned char>^ GetImage(int pageNumber, ImageType imageType);


		/// <summary>
        /// Get byte array that contains your PNG image
        /// </summary>
		/// <param name="pageNumber">Number of a page to convert to an image</param>
		/// <param name="imageType">Output image format</param>
		/// <seealso cref="Init"/>
		/// <seealso cref="GetImage"/>
		/// <seealso cref="Width"/>
		/// <seealso cref="Height"/>
		/// <seealso cref="NumPages"/>
		array<unsigned char>^ GetPNG(int pageNumber);

		
		/// <summary>
        /// Get or Set output image width
        /// </summary>
		property long long Width{
			long long get(){
				return width;
			}
			void set(long long newVal){
				width = newVal;
			}
		}

		/// <summary>
        /// Get or Set output image height
        /// </summary>
		property long long Height{
			long long get(){
				return height;
			}
			void set(long long newVal){
				height = newVal;
			}
		}

		/// <summary>
        /// Get number of pages in the PDF document
        /// </summary>
		property long long NumPages{
			long long get(){
				return numPages;
			}
		}

	private:
		virtual ~LibPdf();
		!LibPdf();
		Poppler::Document * document;
		unsigned char * rawData;
		QByteArray * qRawData;

		long long width;
		long long height;
		long long numPages;

		void clean();

	};
}
