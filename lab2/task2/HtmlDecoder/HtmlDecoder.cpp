#include "HtmlDecoder.h"
#include <map>
#include <regex>
#include <string>

std::string HtmlDecode(std::string const& html)
{
	std::map<std::string, std::string> regexForReplacedSubstrings = std::map<std::string, std::string>{
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	std::string htmlWithReplacedCodes = html;
	for (auto& pair : regexForReplacedSubstrings)
	{
		htmlWithReplacedCodes = std::regex_replace(htmlWithReplacedCodes, std::regex(pair.first), pair.second);
	}
	return htmlWithReplacedCodes;
}