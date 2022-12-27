#pragma once

namespace std {
	class TTYWriter {
		public:
			TTYWriter() {}
			~TTYWriter() {}

			TTYWriter& operator<<(char* charptr) {
				asm volatile("int 0x50" ::
					"a"(1),
					"b"(2),
					"c"(charptr)
				);
				return *this;
			}
	};

	TTYWriter cout;
	char* endl = "\n\x00";
}
