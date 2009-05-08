using System;
using System.IO;
using libpdf;

namespace pdf_util_test
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            if(args.Length < 2)
            {
                Console.WriteLine("USAGE: pdf_util_test <BMP|PNG> <pdf_file.pdf> <image_file.png|bmp>");
                return;
            }
            try
            {
                using (FileStream file = File.OpenRead(args[1])) // in file
                {
                    var bytes = new byte[file.Length];
                    file.Read(bytes, 0, bytes.Length);
                    using (var pdf = new LibPdf(bytes))
                    {
                        byte[] pngBytes = pdf.GetImage(0, (ImageType)Enum.Parse(typeof(ImageType), args[0],true)); // image type
                        using (var outFile = File.Create(args[3])) // out file
                        {
                            outFile.Write(pngBytes, 0, pngBytes.Length);
                        }
                    }
                }
            }
            catch(Exception ex)
            {
                Console.WriteLine("Error:\n{0}",ex.Message);
            }
        }
    }
}