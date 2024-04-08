#pragma once

namespace Utility
{
	wstring ToWString(string str);
	string ToString(wstring str);

	vector<string> SplitString(string origin, const string& tok);
}

using namespace Utility;