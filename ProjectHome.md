# LibPdf #

This library converts converts PDF file to an image. Supported image formats are PNG and BMP, but you can easily add more.


This library uses [poppler-qt4](http://poppler.freedesktop.org/) library with QT frontend. Basically it's managed C++ wrapper over limited subpart of [poppler-qt4](http://poppler.freedesktop.org/) functionality.



## Usage example: ##

```

using (FileStream file = File.OpenRead(@"..\path\to\pdf\file.pdf")) // in file
{
    var bytes = new byte[file.Length];
    file.Read(bytes, 0, bytes.Length);
    using (var pdf = new LibPdf(bytes))
    {
        byte[] pngBytes = pdf.GetImage(0,ImageType.PNG); // image type
        using (var outFile = File.Create(@"..\path\to\pdf\file.png")) // out file
        {
            outFile.Write(pngBytes, 0, pngBytes.Length);
        }
    }
}

```

## Installation and configuration ##
