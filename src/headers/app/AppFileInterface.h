#pragma once

#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/Types.h>

class AppFileInterface : public Rml::FileInterface {
public:
	AppFileInterface(const Rml::String& root);
	virtual ~AppFileInterface();

	/// Opens a file.
	Rml::FileHandle Open(const Rml::String& path) override;

	/// Closes a previously opened file.
	void Close(Rml::FileHandle file) override;

	/// Reads data from a previously opened file.
	size_t Read(void* buffer, size_t size, Rml::FileHandle file) override;

	/// Seeks to a point in a previously opened file.
	bool Seek(Rml::FileHandle file, long offset, int origin) override;

	/// Returns the current position of the file pointer.
	size_t Tell(Rml::FileHandle file) override;

private:
	Rml::String root;
};