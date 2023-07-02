#pragma once

#include "../../instream/scanner/instream_token.h"
#include "../../environment/environment.h"


extern Environment* __environment;


inline void freeTokenListMemory(const TokenList& list) noexcept {
	for (const Token& token : list)
		if (token.getLiteral())
			delete token.getLiteral();
}

inline void freeTokenListMemoryWithNoReferences(const TokenList& list) noexcept {
	for (const Token& token : list)
		if (token.getLiteral() && !__environment->hasReferencesOf(token.getLiteral()))
			delete token.getLiteral();
}