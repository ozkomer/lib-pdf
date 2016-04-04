# LibPdf class #

Convert pdf to PNG or BMP image.

License GPL see copying
Copyright from:
Vladimir Vasiltsov

## Constructors ##

[LibPdf](LibPdfBasicConstructor.md)();

[LibPdf](LibPdfByteArrayConstructor.md)(byte[ ] pdfFileData);


## Methods ##

void [Init](Init.md)(byte [ ] pdfFileData);

byte[ ] GetImage(int pageNumber, ImageType imageType);

byte[ ] [GetPNG](GetPNG.md)(int pageNumber);

## Properties ##

int [Width](LibPdfWidth.md) { get; set; }

int [Height](LibPdfHeight.md) { get; set; }

int [NumPages](LibPdfNumPages.md) { get; set; }