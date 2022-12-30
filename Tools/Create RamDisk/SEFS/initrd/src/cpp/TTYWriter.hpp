#pragma once
namespace std {
	class TTYWriter {
		public:
			TTYWriter() {}
			~TTYWriter() {}

			TTYWriter& operator<<(char* charptr) {
				asm volatile("int $0x50" ::
							 "a"(2),
							 "b"(1),
							 "c"(charptr)
				);
				return *this;
			}
	};

	extern TTYWriter cout;
	extern char endl[2]; // = {'\n', 0};
}
