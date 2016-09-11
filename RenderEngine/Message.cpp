
#include <Windows.h>
#include <stdexcept>

#include "message.h"

message::message(char* message, message_type messageType,bool stop)
{
	switch (messageType)
	{
	case msgError:
		MessageBoxA(NULL, message, "Runtime Error", MB_OK | MB_ICONERROR);
		break;
	case msgInfo:
		MessageBoxA(NULL, message, "Runtime Error", MB_OK | MB_ICONINFORMATION);
		break;
	case msgWarning:
		MessageBoxA(NULL, message, "Runtime Error", MB_OK | MB_ICONWARNING);
	}

	if (stop)
		throw std::runtime_error(message);
}