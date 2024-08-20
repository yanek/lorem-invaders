#include "lipsum.h"
#include "resources.h"
#include "utils.h"

Lipsum::Lipsum()
{
	this->words = SplitString(res::lipsum, "\n");
	this->cursor = 0;
}

std::string Lipsum::Next()
{
	return this->words[this->cursor++];
}