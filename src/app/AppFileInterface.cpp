#include "AppFileInterface.h"
#include <stdio.h>

AppFileInterface::AppFileInterface(const Rml::String& root) : root(root) {}

AppFileInterface::~AppFileInterface() {}

Rml::FileHandle AppFileInterface::Open(const Rml::String& path)
{
	// Attempt to open the file relative to the application's root.
	FILE* fp = fopen((root + path).c_str(), "rb");
	if (fp != nullptr)
		return (Rml::FileHandle)fp;

	// Attempt to open the file relative to the current working directory.
	fp = fopen(path.c_str(), "rb");
	return (Rml::FileHandle)fp;
}

void AppFileInterface::Close(Rml::FileHandle file)
{
	fclose((FILE*)file);
}

size_t AppFileInterface::Read(void* buffer, size_t size, Rml::FileHandle file)
{
	return fread(buffer, 1, size, (FILE*)file);
}

bool AppFileInterface::Seek(Rml::FileHandle file, long offset, int origin)
{
	return fseek((FILE*)file, offset, origin) == 0;
}

size_t AppFileInterface::Tell(Rml::FileHandle file)
{
	return ftell((FILE*)file);
}