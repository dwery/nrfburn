#pragma once

// Opaque data type representing the USB device. This can be a Windows handle
// or a libusb handle, depending on the backend implementation.
struct usbDevice_t;

class HIDBurner
{
private:
	usbDevice_t*	hHIDDev;
	
public:
	HIDBurner();
	~HIDBurner();

	void Open();
	void Close();

	// reads the first and the second HID report
	void ReadFirst(uint8_t* buffer);	// buffer must be at least HIDREP_FIRST_BYTES bytes long
	void ReadSecond(uint8_t* buffer);	// buffer must be at least HIDREP_SECOND_BYTES bytes long
	
	void WriteBytes(const uint8_t* buffer, const int bytes);

	template <class T>
	void Write(const T& t)
	{
		WriteBytes((const uint8_t*)&t, sizeof t);
	}
};
