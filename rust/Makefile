all:
	rustc --emit obj -C panic=abort --target i686-unknown-linux-gnu hello.rs
	ld.lld -Tlink.ld hello.o ../libc/libsayori_c.a -o hellors
	
clean:
	rm hello.o hellors
