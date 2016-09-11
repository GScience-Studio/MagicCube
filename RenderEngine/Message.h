#pragma once

enum message_type
{
	msgError,msgWarning,msgInfo
};
class message
{
public:
	message(char*, message_type, bool);
};