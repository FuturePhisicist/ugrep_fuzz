#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// Declare the function we renamed above:
#ifdef OS_WIN
int wmain_to_fuzz(int argc, const wchar_t **wargv);
#else
int main_to_fuzz(int argc, const char **argv);
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	if (Size == 0) {
		return 0;
	}
	std::string pattern(reinterpret_cast<const char*>(Data), Size);

	// Turn any embedded '\0' bytes into a space, so that main sees it as one string
	for (char &c : pattern) {
		if (c == '\0') {
			c = ' ';
		}
	}

#ifdef OS_WIN
	// TODO

#else
	// calling:  ugrep -nr --color=never -e <pattern> input_texts
	std::vector<const char*> argv;
	argv.push_back("ugrep"); // argv[0] "program name"
	argv.push_back("-nr");
	argv.push_back("--color=never");
	argv.push_back("-e");
	argv.push_back(pattern.c_str());
	argv.push_back("input_texts");
	argv.push_back(nullptr);

	int argc = static_cast<int>(argv.size() - 1);
	main_to_fuzz(argc, argv.data());
#endif

	return 0;
}

