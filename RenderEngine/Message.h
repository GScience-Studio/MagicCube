#pragma once

enum message_type
{
	msgError,msgWarning,msgInfo
};
class message
{
public:
	message(const char*, message_type, bool);
};