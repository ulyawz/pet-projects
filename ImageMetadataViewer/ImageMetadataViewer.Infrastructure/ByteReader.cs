using System;
using System.IO;

namespace ImageMetadataViewer.Infrastructure
{

    public class CorruptedFileException : Exception
    {
        public CorruptedFileException(string message) : base(message) { }
    }

    public static class ByteReader
    {
        public static void RequireLength(byte[] buffer, int minLength, string what)
        {
            if (buffer == null || buffer.Length < minLength)
                throw new CorruptedFileException($"Заголовок обрезан: не хватает данных для {what}.");
        }

        public static ushort ReadUInt16LE(byte[] b, int offset)
        {
            RequireLength(b, offset + 2, "чтения 16-битного числа (LE)");
            return (ushort)(b[offset] | (b[offset + 1] << 8));
        }

        public static short ReadInt16LE(byte[] b, int offset) => (short)ReadUInt16LE(b, offset);

        public static uint ReadUInt32LE(byte[] b, int offset)
        {
            RequireLength(b, offset + 4, "чтения 32-битного числа (LE)");
            return (uint)(b[offset] | (b[offset + 1] << 8) | (b[offset + 2] << 16) | (b[offset + 3] << 24));
        }

        public static int ReadInt32LE(byte[] b, int offset) => (int)ReadUInt32LE(b, offset);

        public static ushort ReadUInt16BE(byte[] b, int offset)
        {
            RequireLength(b, offset + 2, "чтения 16-битного числа (BE)");
            return (ushort)((b[offset] << 8) | b[offset + 1]);
        }

        public static uint ReadUInt32BE(byte[] b, int offset)
        {
            RequireLength(b, offset + 4, "чтения 32-битного числа (BE)");
            return (uint)((b[offset] << 24) | (b[offset + 1] << 16) | (b[offset + 2] << 8) | b[offset + 3]);
        }

        public static int ReadInt32BE(byte[] b, int offset) => (int)ReadUInt32BE(b, offset);

        public static byte[] ReadExact(Stream stream, int count, string what)
        {
            byte[] buffer = new byte[count];
            int totalRead = 0;
            while (totalRead < count)
            {
                int read = stream.Read(buffer, totalRead, count - totalRead);
                if (read == 0)
                    throw new CorruptedFileException($"Файл короче, чем требуется для {what} (обрыв на {totalRead} из {count} байт).");
                totalRead += read;
            }
            return buffer;
        }
    }
}
